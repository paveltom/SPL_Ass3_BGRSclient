#include "../include/Task.h"
#include "../include/ConnectionHandler.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <thread>

NetTask::NetTask(const ConnectionHandler& ch, int id, std::mutex& mutex) : Task(ch, id, mutex) {}

NetTask::~NetTask() = default;

NetTask::NetTask(const NetTask& aCT) = default;

void NetTask::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::string line(buf);
        if (!_ch.getLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        int len = line.length();
        //line.resize(len - 1); ?????????????????????????????????????????????????????
        std::cout << "Reply: " << line << " " << len << " bytes " << std::endl << std::endl;
        if (line == "ACK 4") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
}
