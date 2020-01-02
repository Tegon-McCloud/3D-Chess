#pragma once

struct Material;

#include "WindowsStrict.h"

#include "DirectXMath.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <array>
#include <optional>

// Constants:
constexpr const float pi = 3.14159265359f;

// Error handling:
std::string GetLastErrorString( HRESULT hr );

void ThrowIfFailed( HRESULT hr );
void WSAThrowIfFailed( int r );

class BadHResultError : public std::runtime_error {

public:
	BadHResultError( HRESULT hr );
};

class BadWSAResultError : public std::runtime_error {

public:
	BadWSAResultError( int r );
};


// Time and position keeping:
class Timer {

public:
	Timer();
	float Time();
	void Reset();
private:
	std::chrono::steady_clock::time_point lastReset;
};

struct PositionLFR {
	PositionLFR( const PositionLFR& p );
	PositionLFR( int l, int f, int r );

	int l, f, r;
};

struct PositionXYZ {
	PositionXYZ( const PositionXYZ& p );
	PositionXYZ( int x, int y, int z );

	int y, z, x;
};

union Position {
	Position();
	Position( const Position& p );
	Position( const PositionLFR& p );
	Position( const PositionXYZ& p );
	Position( const std::string& alg );

	bool operator==( const Position& p );

	std::string ToAlg();

	PositionLFR lfr;
	PositionXYZ xyz;
};

enum class Side {
	WHITE, BLACK
};

// Math/Raytracing
struct Ray {
	DirectX::XMFLOAT3 ori;
	DirectX::XMFLOAT3 dir;
};

struct Box {
	Box();
	Box( const DirectX::XMFLOAT3& min, const DirectX::XMFLOAT3& max );
	Box( float minx, float miny, float minz, float maxx, float maxy, float maxz );

	void Draw( const Material& mtl );

	DirectX::XMFLOAT3 min;
	DirectX::XMFLOAT3 max;
};

float intersection( const Ray& r, const Box& b );

