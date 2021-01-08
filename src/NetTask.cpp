#include "../include/Task.h"
#include "../include/ConnectionHandler.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

NetTask::NetTask(ConnectionHandler& ch, int id, std::mutex& mutex, std::condition_variable& cv) : Task(ch, id, mutex) {
    done = false;
    _cv = &cv;
}

NetTask::~NetTask() = default;
void NetTask::run() {

    while (1) {
        std::string line;
        if (!_ch.getLine(line)) {
            std::cout << "NetTask: Disconnected. Exiting...\n" << std::endl;
            break;
        }

        std::cout << line << std::endl;

        if (line == "ACK 04\n") {
            done = true;
            std::cout << "netTaskExiting...\n" << std::endl;
            _cv->notify_all();
            break;
        }
        _cv->notify_all();//!!!!!!!! maybe not needed??????????????????????????????????????
    }
}

bool NetTask::isDone() const {
    return done;
}
