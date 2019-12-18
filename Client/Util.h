#pragma once

#include "WindowsStrict.h"

#include <string>
#include <sstream>
#include <stdexcept>
#include <chrono>

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
