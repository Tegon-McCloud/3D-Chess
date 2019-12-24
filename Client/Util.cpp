#include "Util.h"
#include "WindowsStrict.h"


std::string GetLastErrorString(HRESULT hr) {
	
	std::stringstream ss;
	ss << "Bad HRESULT returned:\n0x" << std::hex << hr << "\nError message:\n";

	//Get the error message, if any.
	DWORD errorMessageID = GetLastError();
	if ( errorMessageID == 0 )
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								  NULL, errorMessageID, MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ), (LPSTR)&messageBuffer, 0, NULL );

	ss << std::string( messageBuffer, size ) << "\n";

	//Free the buffer.
	LocalFree( messageBuffer );

	return ss.str();

}

#ifdef _DEBUG
void ThrowIfFailed( HRESULT hr ) {
	if ( FAILED( hr ) ) {
		throw BadHResultError( hr );
	}
}
#else
void ThrowIfFailed( hr ) {}
#endif // _DEBUG


// BadHResultError
BadHResultError::BadHResultError( HRESULT hr ) : std::runtime_error(GetLastErrorString(hr)) {}



Timer::Timer() {
	lastReset = std::chrono::steady_clock::now();
}

float Timer::Time() {
	return std::chrono::duration<float>( std::chrono::steady_clock::now() - lastReset ).count();
}

void Timer::Reset() {
	lastReset = std::chrono::steady_clock::now();
}


