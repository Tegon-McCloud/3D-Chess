#pragma once

#include "Winsock2.h"
#include <mutex>
#include <queue>
#include <thread>


class Client {

public:
	// start a new thread with a ConnectAndLoop call
	Client( const std::string& ipAndPort );
	~Client();

	Client( const Client& ) = delete;
	Client& operator=( const Client& ) = delete;

	// get the oldest message from the server. Returns false if none are available
	bool GetMSG( std::string& msg );
	// send a message to the server
	void SendMSG( const std::string& msg );
	
private:
	//call Connect and then start a message receiving loop that lasts until the connection to the server is broken
	int ConnectAndLoop( const std::string& ip, const std::string& port );

	/*
	try to connect to the server given by the ip and port.
	returns 0 if succesful and non-zero otherwise.
	*/
	int Connect( const std::string& ip, const std::string& port );
	
	SOCKET clientSocket;

	std::queue<std::string> inbox;
	std::mutex mutex;
	std::thread loopThread;
	
};

class WSALoader {
public:
	static const WSADATA& GetData();

private:
	WSALoader();
	~WSALoader();

	WSADATA data;

	static WSALoader loader;
};


