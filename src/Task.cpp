#include "../include/Task.h"
#include "../include/ConnectionHandler.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <thread>

Task::Task(const ConnectionHandler& ch, int id, std::mutex& mutex) : _ch(ch) _id(id), _mutex(mutex) {}
Task::~Task() = default;
//Task::Task(const ConnectionHandler &ch, int id, std::mutex &mutex) { }
