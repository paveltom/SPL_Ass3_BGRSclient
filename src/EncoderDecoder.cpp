#include "../include/EncoderDecoder.h"
#include "../include/ConnectionHandler.h"

#include <boost/lexical_cast.hpp>
EncoderDecoder::EncoderDecoder() {}
//const string EncoderDecoder::decode(const char *bytes) {
//
//}
char* EncoderDecoder::encode(const std::string& msg, string& size) {
    static char bytes[1 << 10];
    std::string delimiter = " ";
    std::string opString = msg.substr(0, msg.find(delimiter));
    std::string restOfMsg = msg.substr(msg.find(delimiter) + 1);

    if (opString == "ADMINREG") { //1
        short op = 1;
        shortToBytes(op, bytes);
        int curI = 2;
        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
        for (int i = 0; i < userName.length(); i++) {
            bytes[curI + i] = userName[i];
        }
        curI += userName.length();
        bytes[curI] = 0;
        curI++;
        std::string password = restOfMsg.substr(restOfMsg.find(delimiter) + 1);
        for (int i = 0; i < password.length(); i++) {
            bytes[curI + i] = password[i];
        }
        curI += password.length();
        bytes[curI] = 0;
        size = to_string(curI);
//        for (int i = 0; i < curI; i++)
//            msg[i] = bytes[i];
        return bytes;
    }
//    if(opString == "STUDENTREG"){
//        short op = 2;
//        shortToBytes(op,bytes);
//        int curI = 2;
//        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
//        for(int i = 0; i < userName.length() ; i++){
//            bytes[curI + i] = userName[i];
//        }
//        curI += userName.length();
//        bytes[curI] = 0;
//        curI++;
//        std::string password = restOfMsg.substr(restOfMsg.find(delimiter)+1);
//        for(int i = 0 ; i < password.length() ; i++){
//            bytes[curI + i] = password[i];
//        }
//        curI += password.length();
//        bytes[curI] = 0;
//
//        return bytes;
//    }
//    if(opString =="LOGIN"){
//        short op = 3;
//        shortToBytes(op,bytes);
//        int curI = 2;
//        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
//        for(int i = 0; i < userName.length() ; i++){
//            bytes[curI + i] = userName[i];
//        }
//        curI += userName.length();
//        bytes[curI] = 0;
//        curI++;
//        std::string password = restOfMsg.substr(restOfMsg.find(delimiter)+1);
//        for(int i = 0 ; i < password.length() ; i++){
//            bytes[curI + i] = password[i];
//        }
//        curI += password.length();
//        bytes[curI] = 0;
//
//        return bytes;
//    }
//    if(opString == "LOGOUT"){
//        short op = 4;
//        shortToBytes(op,bytes);
//
//        return bytes;
//    }
//    if(opString =="COURSEREG"){
//        short op = 5;
//        shortToBytes(op,bytes);
//        short courseNum = boost::lexical_cast<short>(restOfMsg);
//        bytes[2] = ((courseNum >> 8) & 0xFF);
//        bytes[3] = (courseNum & 0xFF);
//
//        return bytes;
//    }
//    if(opString=="KDAMCHECK"){
//        short op = 6;
//        shortToBytes(op,bytes);
//        short courseNum = boost::lexical_cast<short>(restOfMsg);
//        bytes[2] = ((courseNum >> 8) & 0xFF);
//        bytes[3] = (courseNum & 0xFF);
//
//        return bytes;
//    }
//    if(opString =="COURSESTAT"){
//        short op = 7;
//        shortToBytes(op,bytes);
//        short courseNum = boost::lexical_cast<short>(restOfMsg);
//        bytes[2] = ((courseNum >> 8) & 0xFF);
//        bytes[3] = (courseNum & 0xFF);
//
//        return bytes;
//    }
//    if(opString == "STUDENTSTAT"){
//        short op = 8;
//        shortToBytes(op,bytes);
//        int curI = 2;
//        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
//        for(int i = 0; i < userName.length() ; i++){
//            bytes[curI + i] = userName[i];
//        }
//        curI += userName.length();
//        bytes[curI] = 0;
//
//        return bytes;
//    }
//    if(opString =="ISREGISTERED"){
//        short op = 9;
//        shortToBytes(op,bytes);
//        short courseNum = boost::lexical_cast<short>(restOfMsg);
//        bytes[2] = ((courseNum >> 8) & 0xFF);
//        bytes[3] = (courseNum & 0xFF);
//
//        return bytes;
//    }
//    if(opString =="UNREGISTER"){
//        short op = 10;
//        shortToBytes(op,bytes);
//        short courseNum = boost::lexical_cast<short>(restOfMsg);
//        bytes[2] = ((courseNum >> 8) & 0xFF);
//        bytes[3] = (courseNum & 0xFF);
//
//        return bytes;
//    }
//    if(opString.compare("MYCOURSES")){
//        short op = 11;
//        shortToBytes(op,bytes);
//
//        return bytes;
//    }
//}
//const string EncoderDecoder::decode(char *bytes) {
//    string result = "";
//    short opCode = bytesToShort(bytes);
//    result.append(""+opCode);
//
//    short msgOp = (short)((bytes[0] & 0xff) << 8);
//    result += (short)(bytes[1] & 0xff);
//    result.append(""+msgOp);
//    bool flag = true;
//    int i = 0;
//    while(flag){
//        if(bytes[i] == 0) {
//            flag = false;
//        }
//        result += bytes[i];
//        i++;
//    }
//
//    if(opCode == 12) { //ACK
//
//    }
//    if(opCode == 13){ //ERROR
//
//    }
//}
}
    short EncoderDecoder::bytesToShort(char *bytesArr) {
        short result = (short) ((bytesArr[0] & 0xff) << 8);
        result += (short) (bytesArr[1] & 0xff);
        return result;
    }
    void EncoderDecoder::shortToBytes(short num, char *bytesArr) {
        bytesArr[0] = ((num >> 8) & 0xFF);
        bytesArr[1] = (num & 0xFF);
    }