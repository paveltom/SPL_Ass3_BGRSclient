#include "../include/ConnectionHandler.h"
#include "../include/Task.h"
#include "../include/EncoderDecoder.h"
#include <iostream>
#include <condition_variable>

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }

    std::string host = argv[1];
    short port = atoi(argv[2]);

    EncoderDecoder *encdec = new EncoderDecoder;
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    std::mutex mutex_;//probably not needed
    std::condition_variable cv;
    //boost::asio::io_service io;
    //boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));
    //KeyboardTask keyboardTask(connectionHandler, 1, mutex);
    NetTask netTask(connectionHandler, 2, mutex_, cv);
    //std::thread::id mainThread = std::this_thread::get_id();
    std::thread th2(&Task::run, &netTask);
    th2.detach();

    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);;
        if (!connectionHandler.sendBytes(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        if (line == "LOGOUT") {
            std::unique_lock<std::mutex> uniqueLock(mutex_);
            cv.wait(uniqueLock);
            if (netTask.isDone()) {
                std::cout << "mainExiting...\n" << std::endl;
                break;
            }
        }
        //memset(buf, 0 , 1024);
    }
    return 0;
}



