#include "../include/EncoderDecoder.h"
#include <boost/lexical_cast.hpp>
EncoderDecoder::EncoderDecoder() {
    len = 0;
}
//const string EncoderDecoder::decode(const char *bytes) {
//
//}
vector<char>* EncoderDecoder::encode(string &msg) {
    //decodeBytes[1<<10];
    vector<char> *temp = new vector<char>;
    char bytes[1<<10];
    std::string delimiter = " ";
    std::string opString = msg.substr(0, msg.find(delimiter));
    std::string restOfMsg = msg.substr(msg.find(delimiter) + 1);

    if (opString == "ADMINREG") { //1
        short op = 1;
        shortToBytes(op,bytes);

        //msg = (op & 0xFF);;
        int curI = 2;
        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
        for(int i = 0; i < userName.length() ; i++){
            bytes[curI + i] = userName[i];
        }

        curI += userName.length();
        bytes[curI] = 0;
        curI++;
        std::string password = restOfMsg.substr(restOfMsg.find(delimiter)+1);
        for(int i = 0 ; i < password.length() ; i++){
            bytes[curI + i] = password[i];
        }

        curI += password.length();
        bytes[curI] = 0;
        curI++;
        //char* result = str
        for(int i = 0 ; i < curI ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString == "STUDENTREG") {
        short op = 2;
        shortToBytes(op,bytes);

        //msg = (op & 0xFF);;
        int curI = 2;
        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
        for(int i = 0; i < userName.length() ; i++){
            bytes[curI + i] = userName[i];
        }

        curI += userName.length();
        bytes[curI] = 0;
        curI++;
        std::string password = restOfMsg.substr(restOfMsg.find(delimiter)+1);
        for(int i = 0 ; i < password.length() ; i++){
            bytes[curI + i] = password[i];
        }

        curI += password.length();
        bytes[curI] = 0;
        curI++;
        //char* result = str
        for(int i = 0 ; i < curI ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString =="LOGIN"){
        short op = 3;
        shortToBytes(op,bytes);

        //msg = (op & 0xFF);;
        int curI = 2;
        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
        for(int i = 0; i < userName.length() ; i++){
            bytes[curI + i] = userName[i];
        }

        curI += userName.length();
        bytes[curI] = 0;
        curI++;
        std::string password = restOfMsg.substr(restOfMsg.find(delimiter)+1);
        for(int i = 0 ; i < password.length() ; i++){
            bytes[curI + i] = password[i];
        }

        curI += password.length();
        bytes[curI] = 0;
        curI++;
        //char* result = str
        for(int i = 0 ; i < curI ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString == "LOGOUT"){
        short op = 4;
        shortToBytes(op,bytes);
        for(int i = 0 ; i < 2 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString =="COURSEREG"){
        short op = 5;
        shortToBytes(op,bytes);
        short courseNum = boost::lexical_cast<short>(restOfMsg);
        bytes[2] = ((courseNum >> 8) & 0xFF);
        bytes[3] = ((courseNum  & 0xFF));
        for(int i = 0 ; i < 4 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString=="KDAMCHECK"){
        short op = 6;
        shortToBytes(op,bytes);
        short courseNum = boost::lexical_cast<short>(restOfMsg);
        bytes[2] = ((courseNum >> 8) & 0xFF);
        bytes[3] = (courseNum & 0xFF);
        for(int i = 0 ; i < 4 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString =="COURSESTAT"){
        short op = 7;
        shortToBytes(op,bytes);
        short courseNum = boost::lexical_cast<short>(restOfMsg);
        bytes[2] = ((courseNum >> 8) & 0xFF);
        bytes[3] = (courseNum & 0xFF);
        for(int i = 0 ; i < 4 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString == "STUDENTSTAT"){
        short op = 8;
        shortToBytes(op,bytes);
        int curI = 2;
        std::string userName = restOfMsg.substr(0, restOfMsg.find(delimiter));
        for(int i = 0; i < userName.length() ; i++){
            bytes[curI + i] = userName[i];
        }
        curI += userName.length();
        bytes[curI] = 0;
        curI++;
        for(int i = 0 ; i < curI ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString =="ISREGISTERED"){
        short op = 9;
        shortToBytes(op,bytes);
        short courseNum = boost::lexical_cast<short>(restOfMsg);
        bytes[2] = ((courseNum >> 8) & 0xFF);
        bytes[3] = (courseNum & 0xFF);
        for(int i = 0 ; i < 4 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString =="UNREGISTER"){
        short op = 10;
        shortToBytes(op,bytes);
        short courseNum = boost::lexical_cast<short>(restOfMsg);
        bytes[2] = ((courseNum >> 8) & 0xFF);
        bytes[3] = (courseNum & 0xFF);
        for(int i = 0 ; i < 4 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
    if(opString == "MYCOURSES"){
        short op = 11;
        shortToBytes(op,bytes);
        for(int i = 0 ; i < 2 ; i++){
            temp->push_back(bytes[i]);
        }
        return temp;
    }
}
const string EncoderDecoder::decode(char c) {
    //result = "";
    if(len ==0){
        result = "";
    }
    if(len == 2){
        opCode = bytesToShort(decodeBytes);
    }

    if (opCode == 12) { //ACK
        if(len == 2)
        result.append("ACK ");
        if(len >= 4 && c=='\0') {
            short msgOp = (short) ((decodeBytes[2] & 0xff) << 8);
            msgOp += (short) (decodeBytes[3] & 0xff);
            //result.append("0");
            result = result + to_string(msgOp);
            len = 0;
            opCode = 0;
            result.append(vecBytes->begin()+4,vecBytes->end());
            vecBytes->clear();
            return result;
            result.append(" ");
        }
//        if(c=='\0' && len > 3){
//
//        }

    }
    if (opCode == 13) { //ERROR
        if(len == 2)
            result.append("ERROR ");
        if(len == 3) {
            short msgOp = (short) ((decodeBytes[2] & 0xff) << 8);
            msgOp += (short) (c & 0xff);
            result = result + to_string(msgOp);
//            result.append(vecBytes->begin()+4,vecBytes->end());
            len = 0;
            opCode = 0;
            vecBytes->clear();
            return result;
        }
    }
    decodeBytes[len] = c;
    vecBytes->push_back(c);
    len++;
    return "";
}
short EncoderDecoder::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
void EncoderDecoder::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}