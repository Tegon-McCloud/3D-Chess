#pragma once
#include "Bindable.h"
#include <vector>
#include <memory>

class Drawable {

public:
	void Draw();
	void AddBindable( std::shared_ptr<Bindable> b );

private:
	std::vector<std::shared_ptr<Bindable>> bindables;
	size_t indexCount;

};

