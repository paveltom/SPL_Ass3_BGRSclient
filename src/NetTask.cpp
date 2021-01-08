#include "../include/Task.h"
#include "../include/ConnectionHandler.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <thread>

NetTask::NetTask(ConnectionHandler& ch, int id, std::mutex& mutex) : Task(ch, id, mutex) {}

NetTask::~NetTask() = default;

NetTask::NetTask(const NetTask& aCT) = default;

void NetTask::run() {
    //boost::asio::io_service io;
    while (1) {
        std::string line;
//        boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));
//        timer.wait();

        if (!_ch.getLine(line)) {
            std::cout << "NetTask: Disconnected. Exiting...\n" << std::endl;
            break;
        }
        //int len = line.length();
        //line.resize(len - 1); ?????????????????????????????????????????????????????
        //bool write = false;
        //while (!write) {
            //std::lock_guard<std::mutex> lockGuard(mutex);
            std::cout << line << std::endl;
            //write = true;
        //}
        if (line == "ACK 04") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
}
