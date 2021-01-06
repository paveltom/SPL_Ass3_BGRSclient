#include "../include/ConnectionHandler.h"
#include "../include/Task.h"
#include "../include/EncoderDecoder.h"

#include <stdexcept>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }

    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    std::mutex mutex;//probably not needed

    KeyboardTask keyboardTask(connectionHandler, 1, mutex);
    NetTask netTask(connectionHandler, 2, mutex);

    std::thread th1(&Task::run, &keyboardTask);
    std::thread th2(&Task::run, &netTask);

    th1.join(); // or detach()?
    th2.join(); //or detach()?


    return 0;
}



