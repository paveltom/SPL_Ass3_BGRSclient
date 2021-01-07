#include "../include/ConnectionHandler.h"
#include "../include/Task.h"
#include <iostream>

int main(int argc, char** argv) {

//    if (argc < 3) {
//        cerr << "Usage: " << argv[0] << " host port" << endl << endl;
//        return -1;
//    }

//    string host = argv[1];
//    short port = atoi(argv[2]);
    std::string host = "127.0.0.1";
    short port = 7777;
    
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



