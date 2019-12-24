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

struct Position {
	Position( int l, int f, int r );
	Position( const std::string& alg );
	int l, f, r;
	std::string toAlg();
};