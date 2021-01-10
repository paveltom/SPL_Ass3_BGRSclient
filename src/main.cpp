#include "../include/ConnectionHandler.h"
#include "../include/Task.h"
#include <iostream>
#include <condition_variable>

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }

    ConnectionHandler connectionHandler(argv[1], atoi(argv[2]));
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << argv[1] << ":" << atoi(argv[2]) << std::endl;
        return 1;
    }

    std::mutex mutex_;
    std::condition_variable cv;\
    NetTask netTask(connectionHandler, 2, mutex_, cv);
    std::thread th2(&Task::run, &netTask);
    th2.detach();

    while (true) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        if (!connectionHandler.sendBytes(line)) {
            break;
        }
        if (line == "LOGOUT") {
            std::unique_lock<std::mutex> uniqueLock(mutex_);
            cv.wait_for(uniqueLock, std::chrono::seconds{2});
            if (netTask.isDone()) {
                break;
            }
        }
    }
    return 0;
}

