#pragma once
#include "Bindable.h"
#include <vector>
#include <memory>

class Drawable {

public:
	void Draw();
	void AddBindable( std::unique_ptr<Bindable> b );

private:
	std::vector<std::unique_ptr<Bindable>> bindables;
	size_t indexCount;

};

