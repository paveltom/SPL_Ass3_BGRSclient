#ifndef ENCODERDECODER_H
#define ENCODERDECODER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class EncoderDecoder {
private:
    int len;
    char decodeBytes[1<<10];
    vector<char>* vecBytes = new vector<char>;
    short opCode = 0;
    string result = "";
public:
    EncoderDecoder();

    char* encode(const std::string& msg, string& size, char* output); //returns bytes[]
    const string decode( char c); // why const char in argument??
    short bytesToShort(char* bytesArr);
    void shortToBytes(short num, char* bytesArr);




};
#endif //ENCODERDECODER_H