cmake_minimum_required(VERSION 3.17)
project(BGRSclient)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS)


set(CMAKE_CXX_STANDARD 11)

link_libraries("-lboost_system")
link_libraries(-pthread)
add_executable(BGRSclient src/main.cpp src/ConnectionHandler.cpp src/EncoderDecoder.cpp src/Task.cpp src/KeyboardTask.cpp src/NetTask.cpp)

