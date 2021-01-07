#ifndef ENCODERDECODER_H
#define ENCODERDECODER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class EncoderDecoder {
public:
    EncoderDecoder();

    const char* encode(string& msg); //returns bytes[]
    const string decode( char bytes[]); // why const char in argument??
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);




};
#endif //ENCODERDECODER_H