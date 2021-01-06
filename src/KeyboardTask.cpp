#include "../include/Task.h"
#include "../include/ConnectionHandler.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <thread>


KeyboardTask::KeyboardTask(const ConnectionHandler& ch, int id, std::mutex& mutex) : Task(ch, id, mutex) {}

KeyboardTask::~KeyboardTask() = default;

KeyboardTask::KeyboardTask(const KeyboardTask& aCT) = default;

void KeyboardTask::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len = line.length();
        if (!_ch.sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        if (line == "LOGOUT") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
}