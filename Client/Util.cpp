#include "Util.h"
#include "WindowsStrict.h"

#include <limits>

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

float intersection( const Ray& r, const Box& b ) {
	
	float tmin, tmax;

						// plane: x = boxMin.x and x = boxMax.x intersection distances
	float txmin = (b.min.x - r.ori.x) / r.dir.x;
	float txmax = (b.max.x - r.ori.x) / r.dir.x;
	if ( txmin > txmax ) std::swap( txmin, txmax );

	// no testing as there is no min and max for t yet
	tmin = txmin;
	tmax = txmax;

	// plane: y = boxMin.y and y = boxMax.y intersection distances
	float tymin = (b.min.y - r.ori.y) / r.dir.y;
	float tymax = (b.max.y - r.ori.y) / r.dir.y;
	if ( tymin > tymax ) std::swap( tymin, tymax );

	if ( tymax < tmin || tymin > tmax ) return std::numeric_limits<float>::infinity(); // overshot in y direction

	if ( tymin > tmin ) tmin = tymin;
	if ( tymax < tmax ) tmax = tymax;

	// plane: z = boxMin.z and z = boxMax.z intersection distances
	float tzmin = (b.min.z - r.ori.z) / r.dir.z;
	float tzmax = (b.max.z - r.ori.z) / r.dir.z;
	if ( tzmin > tzmax ) std::swap( tzmin, tzmax );

	if ( tzmax < tmin || tzmin > tmax ) return std::numeric_limits<float>::infinity(); // overshot in z direction

	if ( tzmin > tmin ) tmin = tzmin;
	if ( tzmax < tmax ) tmax = tzmax;


	if ( tmax < 0 ) return std::numeric_limits<float>::infinity();
	float t = tmin > 0.0f ? tmin : tmax;

}