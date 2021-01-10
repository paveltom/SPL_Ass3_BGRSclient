#include "../include/Task.h"
#include <mutex>

Task::Task(ConnectionHandler& ch, int id, std::mutex& mutex) : _ch(ch), _id(id), _mutex(mutex) {}
Task::~Task() = default;
