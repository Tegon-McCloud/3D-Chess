#include "Client.h"
#include "Util.h"

#include "winsock2.h"
#include "ws2tcpip.h"
#include <thread>
#include <cassert>
#include <regex>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


#pragma comment(lib, "Ws2_32.lib")

// Client
Client::Client( const std::string& ipAndPort ) : clientSocket( INVALID_SOCKET ) {

	const std::regex ipRegex( "([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}|localhost):[0-9]{1,5}" );

	if ( !std::regex_match( ipAndPort, ipRegex ) ) {
		throw std::runtime_error( "Client received string that wasn't an ip and port." );
	}

	size_t colonIndex = ipAndPort.find(":");

	loopThread = std::thread( &Client::ConnectAndLoop, this, ipAndPort.substr( 0, colonIndex ), ipAndPort.substr( colonIndex + 1 ) );
}

Client::~Client() {
	if ( clientSocket != INVALID_SOCKET ) {
		shutdown( clientSocket, SD_SEND );
		loopThread.join();
		closesocket( clientSocket );
	}
}

bool Client::GetMSG( std::string& msg ) {
	mutex.lock();

	if ( messages.empty() ) { // calling front() on an empty std::queue is undefined behaviour
		mutex.unlock();
		return false;
	}

	msg = messages.front();
	messages.pop();
	mutex.unlock();
	
	return true;
}

void Client::SendMSG( const std::string& msg ) {
	send( clientSocket, msg.c_str(), (int) msg.length(), 0 );
}

int Client::ConnectAndLoop( const std::string& ip, const std::string& port ) {
	
	int result;

	addrinfo hints = { 0 };
	hints.ai_family = AF_INET;			// IPv4
	hints.ai_socktype = SOCK_STREAM;	// stream-based
	hints.ai_protocol = IPPROTO_TCP;	// TCP

	addrinfo* info;

	result = getaddrinfo( ip.c_str(), port.c_str(), &hints, &info );
	if ( result != 0 ) {
		return result;
	}

	clientSocket = socket( info->ai_family, info->ai_socktype, info->ai_protocol );
	if ( clientSocket == INVALID_SOCKET ) {
		freeaddrinfo( info );
		return WSAGetLastError();
	}

	result = connect( clientSocket, info->ai_addr, (int)info->ai_addrlen );
	if ( result != 0 ) {
#ifdef _DEBUG
		std::cout << "failed to connect to address: " << ip << ":" << port << "\n";
#endif // _DEBUG
		freeaddrinfo( info );
		return result;
	}

	freeaddrinfo( info );

	constexpr int bufLength = 2048;
	char* recvBuf = new char[bufLength]; // heap allocation bcs 2 kB is a bit high for stack
	int recvLength = 0;

	while ( true ) {

		recvLength = recv( clientSocket, recvBuf, bufLength, 0 );

		if ( recvLength <= 0 ) break; // connection broken from serverside

		mutex.lock();
		messages.push( std::string( recvBuf, recvLength ) );
		mutex.unlock();
	}

	delete[] recvBuf;

#ifdef _DEBUG
	std::cout << "connection to server broken\n";
#endif // _DEBUG

	return 0;
}

// WSALoader
WSALoader WSALoader::loader = WSALoader();

const WSADATA& WSALoader::GetData() {
	return loader.data;
}

WSALoader::WSALoader() {
	WSAThrowIfFailed( WSAStartup( MAKEWORD( 2, 2 ), &data ) ); // request version 2.2 
	assert( data.wVersion == MAKEWORD(2, 2) );	
	// version 2.2 is needed in order to make sure that it is threadsafe
	// to be locked in recv() on one thread while using send() from another thread.
}

WSALoader::~WSALoader() {
	WSACleanup();
}

