#pragma once

class Bindable;

#include <vector>
#include <memory>

/*
A drawable instance represents anything that can be drawn using DX11.
It functions by holding a vector of Bindables, which are objects that can be bound to the
graphics pipeline. Instead of holding copies of the Bindables, it holds shared_ptrs to them
to enable optimizations by reusing bindables multiple times.
Note that copy constructing/assigning a Drawable will only copy its bindable pointers, not the bindables.
*/
class Drawable {

public:

	void Draw();
	void AddBindable( const std::shared_ptr<Bindable>& b );

private:
	std::vector<std::shared_ptr<Bindable>> bindables;
	size_t indexCount;

};

