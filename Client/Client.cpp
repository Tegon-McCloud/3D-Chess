#include "Client.h"
#include "Util.h"

#include "winsock2.h"
#include "ws2tcpip.h"
#include <thread>
#include <cassert>

#pragma comment(lib, "Ws2_32.lib")

Client::Client( std::string ip, std::string port ) : clientSocket( INVALID_SOCKET ) {

	addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo* info;
	try {
		WSAThrowIfFailed( getaddrinfo( ip.c_str(), port.c_str(), &hints, &info ) );
		
		clientSocket = socket( info->ai_family, info->ai_socktype, info->ai_protocol );
		if ( clientSocket == INVALID_SOCKET ) {
			throw BadWSAResultError( WSAGetLastError() );
		}

		WSAThrowIfFailed( connect( clientSocket, info->ai_addr, (int) info->ai_addrlen ) );

	} catch ( BadWSAResultError& e ) {
		freeaddrinfo( info );
		throw e;
	}
	
	freeaddrinfo( info );

	loopThread = std::thread( &Client::Loop, this );
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

void Client::Loop() {

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
