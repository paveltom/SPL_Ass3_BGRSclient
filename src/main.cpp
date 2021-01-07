#include "../include/ConnectionHandler.h"
#include "../include/Task.h"
#include <iostream>

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }

    std::string host = argv[1];
    short port = atoi(argv[2]);

    EncoderDecoder* encdec = new EncoderDecoder();
    ConnectionHandler connectionHandler(host, port, *encdec );
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    std::mutex mutex;//probably not needed

    //KeyboardTask keyboardTask(connectionHandler, 1, mutex);
    NetTask netTask(connectionHandler, 2, mutex);

    //std::thread th1(&Task::run, &keyboardTask);
    std::thread th2(&Task::run, &netTask);

    // or detach()?
    //th1.join();


    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        //char bufNet[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len=line.length();
        if (!connectionHandler.sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

//        std::string answer;
//
//        if (!connectionHandler.getLine(answer)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }

//        len=answer.length();
//
        if (line == "LOGOUT") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
    th2.detach();
     //or detach()?

    return 0;
}



