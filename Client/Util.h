#pragma once

#include "WindowsStrict.h"

#include <string>
#include <sstream>
#include <stdexcept>

class BadHResultError : public std::runtime_error {

public:
	BadHResultError( HRESULT hr );
};


std::string GetLastErrorString(HRESULT hr);
void ThrowIfFailed(HRESULT hr);
