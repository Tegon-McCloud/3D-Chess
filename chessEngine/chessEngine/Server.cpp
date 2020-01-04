#include "Server.h"

#include "ws2tcpip.h"
#include <cassert>
#include <iostream>
#include <random>

#pragma comment(lib, "ws2_32.lib")

inline void printAndExit( const std::string& message, int code = 0 ) {
	std::cout << message << "\n";
	exit( code );
}

// Server
Server::Server( std::string port ) : serverSocket( INVALID_SOCKET ), clientWhite( INVALID_SOCKET ), clientBlack( INVALID_SOCKET ) {

	int result;

	addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	addrinfo* info;
	result = getaddrinfo( NULL, "8877", &hints, &info );
	if ( result != 0 ) {
		printAndExit( "failed to get address info.", 1 );
	}

	serverSocket = socket( info->ai_family, info->ai_socktype, info->ai_protocol );
	if ( serverSocket == INVALID_SOCKET ) {
		freeaddrinfo( info );
		printAndExit( "failed to create server socket.", 1 );
	}

	result = bind( serverSocket, info->ai_addr, (int) info->ai_addrlen );
	if ( result != 0 ) {
		freeaddrinfo( info );
		printAndExit( "failed to bind server socket to address.", 1 );
	}

	freeaddrinfo( info );

	result = listen( serverSocket, 2 );
	if ( result != 0 ) printAndExit( "failed to put server socket into listening mode.", 1 );

	std::cout << "waiting for white...\n";
	clientWhite = accept( serverSocket, NULL, NULL );
	if ( clientWhite == INVALID_SOCKET ) printAndExit( "failed to accept white client connection.", 1 );
	std::cout << "white connected.\n";

	std::cout << "waiting for black...\n";
	clientBlack = accept( serverSocket, NULL, NULL );
	if ( clientBlack == INVALID_SOCKET ) printAndExit( "failed to accept black client connection.", 1 );
	std::cout << "black connected.\n";

	std::default_random_engine rng;
	std::uniform_int_distribution<int> dist( 0, 1 );
	if ( dist( rng ) == 1 ) {
		std::swap( clientWhite, clientBlack );
	}
}

Server::~Server() {

	if ( clientWhite != INVALID_SOCKET && shutdown( clientWhite, SD_SEND ) != 0 )
		printf( "error occured during shutdown of connection to whites client." );
	if ( clientBlack != INVALID_SOCKET && shutdown( clientBlack, SD_SEND ) != 0 )
		printf( "error occured during shutdown of connection to blacks client." );

	if ( clientWhite != INVALID_SOCKET && closesocket( clientWhite ) != 0 )
		printf( "error occured while closing white clients socket." );
	if ( clientBlack != INVALID_SOCKET && closesocket( clientBlack ) != 0 )
		printf( "error occured while closing black clients socket." );
	if ( serverSocket != INVALID_SOCKET && closesocket( serverSocket ) != 0 )
		printf( "error occured while closing the servers socket." );

}

void Server::getMSG( int side, std::string& msg ) {
	constexpr int bufLength = 2048;
	char* recvBuf = new char[bufLength]; // heap allocation bcs 2 kB is a bit high for stack
	int recvLength = 0;

	recvLength = recv( side == 1 ? clientWhite : clientBlack, recvBuf, bufLength, 0 );

	if ( recvLength <= 0 ) {
		std::cout << (side == 1 ? "white" : "black") << " has disconnected.\n";
		shutdown( side == 1 ? clientWhite : clientBlack, SD_SEND );
		msg = "d:";
	} else {
		msg = std::string( recvBuf, recvLength );
	}

	delete[] recvBuf;
}

void Server::sendMSG( int side, const std::string& msg ) {
	send( side == 1 ? clientWhite : clientBlack, msg.c_str(), (int) msg.length(), 0 );
}

// WSALoader
WSALoader WSALoader::loader = WSALoader();

const WSADATA& WSALoader::getData() {
	return loader.data;
}

WSALoader::WSALoader() {
	int result = WSAStartup( MAKEWORD( 2, 2 ), &data ); // request version 2.2

	if ( result != 0 ) {
		printAndExit( "failed to start Winsocks.", 1 );
	}
}

WSALoader::~WSALoader() {
	if ( WSACleanup() != 0 ) {
		printf( "Error occured during Winsock cleanup.\n" );
	}
}