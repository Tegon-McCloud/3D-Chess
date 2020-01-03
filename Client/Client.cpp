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
Client::Client( const std::string& ipAndPort ) : sock( INVALID_SOCKET ) {

	const std::regex ipRegex( "([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}|localhost):[0-9]{1,5}" );

	if ( !std::regex_match( ipAndPort, ipRegex ) ) {
		throw std::runtime_error( "Client received string that wasn't an ip and port." );
	}

	size_t colonIndex = ipAndPort.find(":");

	loopThread = std::thread( &Client::ConnectAndLoop, this, ipAndPort.substr( 0, colonIndex ), ipAndPort.substr( colonIndex + 1 ) );
}

Client::~Client() {
	if ( sock != INVALID_SOCKET ) {
		shutdown( sock, SD_BOTH );
		loopThread.join();
		closesocket( sock );
	}
}

bool Client::GetMSG( std::string& msg ) {
	mutex.lock();

	if ( inbox.empty() ) { // calling front() on an empty std::queue is undefined behaviour
		mutex.unlock();
		return false;
	}

	msg = inbox.front();
	inbox.pop();
	mutex.unlock();
	
	return true;
}

void Client::SendMSG( const std::string& msg ) {
	send( sock, msg.c_str(), (int) msg.length(), 0 );
}

int Client::ConnectAndLoop( const std::string& ip, const std::string& port ) {
	
	int result = 0;

	result = Connect( ip, port );
	
	if ( result != 0 ) {
		return result;
	}

	// for receiving
	const int bufLength = 2048;
	char* recvBuf = new char[bufLength];
	int recvLength = 0;
	
	// for processing
	std::stringstream stream;
	std::string streamBuf;
	size_t delimitterIndex;

	while ( true ) {

		recvLength = recv( sock, recvBuf, bufLength, 0 );
		if ( recvLength <= 0 ) { // connection broken from serverside or some error occured
			result = recvLength;
			break;
		}; 
		
		stream.write( recvBuf, recvLength ); // write received data to stream
		
		// split the received data into pieces seperated by ;
		while ( true ) {
			streamBuf = stream.str();
			delimitterIndex = streamBuf.find( ';' ); // find the first index of a ;
			if ( delimitterIndex == std::string::npos ) break;

			mutex.lock();
			inbox.push( streamBuf.substr( 0, delimitterIndex ) ); // write everything earlier than the ; to the inbox
			mutex.unlock();
			stream.str( streamBuf.substr( delimitterIndex + 1 ) ); // set the streams content to be what came after the ;
		}

	}

	delete[] recvBuf;

#ifdef _DEBUG
	std::cout << "connection to server broken with exit code: " << result << "\n";
#endif // _DEBUG

	return result;
}

int Client::Connect( const std::string& ip, const std::string& port ) {
	
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

	sock = socket( info->ai_family, info->ai_socktype, info->ai_protocol );
	if ( sock == INVALID_SOCKET ) {
		freeaddrinfo( info );
		return WSAGetLastError();
	}

	result = connect( sock, info->ai_addr, (int)info->ai_addrlen );
	if ( result != 0 ) {
#ifdef _DEBUG
		std::cout << "failed to connect to address: " << ip << ":" << port << "\n";
#endif // _DEBUG
		freeaddrinfo( info );
		return result;
	}

	freeaddrinfo( info );

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

