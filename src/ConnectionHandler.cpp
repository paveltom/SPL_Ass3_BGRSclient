#include "../include/ConnectionHandler.h"

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
 
ConnectionHandler::ConnectionHandler(string host, short port): host_(host), port_(port), io_service_(), socket_(io_service_) {
    encdec = new EncoderDecoder();
}
    
ConnectionHandler::~ConnectionHandler() {
    delete(encdec);
    close();
}
 
bool ConnectionHandler::connect() {
    std::cout << "Starting connect to "
        << host_ << ":" << port_ << std::endl;
    try {
		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
		boost::system::error_code error;
		socket_.connect(endpoint, error);
		if (error)
			throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        return false;
    }
    return true;
}
 
bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
			tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const std::string& msg) {
    std::string size("0");
    char bytes[1<<10];
    encdec->encode(msg, size, bytes);
    int len = std::stoi(size)+1;

    size_t tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && len > tmp ) {
			tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, len - tmp), error);
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        return false;
    }
    return true;
}

bool ConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\0');
}

bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char ch;
    string result = "";
    try {
        do{
            if(!getBytes(&ch, 1))
            {
                return false;
            }
            result = encdec->decode(ch);
        }while (result == "");
    } catch (std::exception& e) {
        return false;
    }
    frame.clear();
    frame.append(result);
    result.clear();
    return true;
}

// Close down the connection properly.
    void ConnectionHandler::close() {
        try {
            socket_.close();
        } catch (...) {
        }
    }
