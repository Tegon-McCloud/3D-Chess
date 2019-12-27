#pragma once

#include "winsock2.h"
#include <string>

class Server {

public:
	Server( std::string port ); // starts a server. Will block until both players are connected
	~Server();

	Server( const Server& ) = delete;
	Server& operator=( const Server& ) = delete;

	void getMSG( int side, std::string& msg ); // gets the next message from the specified client. if none are available, it will block until the client sends one.
	void sendMSG( int side, const std::string& msg );

private:
	SOCKET serverSocket, clientWhite, clientBlack;

};


class WSALoader {
public:
	static const WSADATA& getData();

private:
	WSALoader();
	~WSALoader();

	WSADATA data;

	static WSALoader loader;
};
