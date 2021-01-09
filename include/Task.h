#ifndef CLIENT_TASK_H
#define CLIENT_TASK_H

#include "ConnectionHandler.h"
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <boost/asio.hpp>
#include <condition_variable>

class Task{
public:
    Task (ConnectionHandler& ch, int id, std::mutex& mutex);
    virtual ~Task();
    virtual void run() = 0;

protected:
    ConnectionHandler& _ch;

private:
    int _id;
    std::mutex& _mutex;
};

//        for (int i= 0; i < 100; i++){
//            std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
//            std::cout << i << ") Task " << _id << " is working" << std::endl;
//        }
//        throw std::invalid_argument( "Not implemented" );
//    }

class KeyboardTask : public Task{
public:
    KeyboardTask(ConnectionHandler& ch, int id, std::mutex& mutex);
    virtual ~KeyboardTask();

    virtual void run();
};

class NetTask : public Task{
public:
    NetTask(ConnectionHandler& ch, int id, std::mutex& mutex, std::condition_variable& cv);
    virtual ~NetTask();
    virtual void run();
    bool isDone() const;

private:
    bool done;
    std::condition_variable* _cv;
};



#endif //CLIENT_TASK_H
