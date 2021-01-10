#include "../include/Task.h"
#include <iostream>
#include <mutex>
#include <condition_variable>

NetTask::NetTask(ConnectionHandler& ch, int id, std::mutex& mutex, std::condition_variable& cv) : Task(ch, id, mutex), done(false), _cv(&cv) {
}

NetTask::~NetTask() = default;
void NetTask::run() {

    while (true) {
        std::string line;
        if (!_ch.getLine(line)) {
            break;
        }

        std::cout << line << std::endl;

        if (line == "ACK 4") {
            done = true;
            _cv->notify_all();
            break;
        }
    }
}

bool NetTask::isDone() const {
    return done;
}
