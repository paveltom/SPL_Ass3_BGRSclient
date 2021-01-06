#ifndef CLIENT_ENCODERDECODER_H
#define CLIENT_ENCODERDECODER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class EncoderDecoder {
public:
    EncoderDecoder();

    const char* encode(string& msg); //returns bytes[]
    const string decode(const char bytes[]);




};
#endif //CLIENT_ENCODERDECODER_H
