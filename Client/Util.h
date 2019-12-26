#pragma once

#include "WindowsStrict.h"

#include "DirectXMath.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <array>
#include <optional>

constexpr const float pi = 3.14159265359f;

class BadHResultError : public std::runtime_error {

public:
	BadHResultError( HRESULT hr );
};


std::string GetLastErrorString(HRESULT hr);
void ThrowIfFailed(HRESULT hr);

class Timer {

public:
	Timer();
	float Time();
	void Reset();
private:
	std::chrono::steady_clock::time_point lastReset;
};


typedef struct {
	DirectX::XMFLOAT3 ori;
	DirectX::XMFLOAT3 dir;
} Ray;

typedef struct {
	DirectX::XMFLOAT3 min;
	DirectX::XMFLOAT3 max;
} Box;

float intersection( const Ray& r, const Box& b );

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

	std::string toAlg();

	PositionLFR lfr;
	PositionXYZ xyz;
};
