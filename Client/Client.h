#pragma once

#include "Winsock2.h"
#include <mutex>
#include <queue>
#include <thread>

class Client {

public:
	Client( std::string ip, std::string port );
	~Client();

	Client( const Client& ) = delete;
	Client& operator=( const Client& ) = delete;

	bool GetMSG( std::string& msg );
	void SendMSG( const std::string& msg );
	
private:
	void Loop();

	SOCKET clientSocket;

	std::queue<std::string> messages;
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