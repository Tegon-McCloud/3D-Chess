#pragma once

// Bindable is an interface implemented by anything that is bindable to the graphics pipeline.
class Bindable {

public:
	virtual void Bind() = 0;

};
