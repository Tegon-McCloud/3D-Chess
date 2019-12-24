#pragma once
#include "Bindable.h"

#include "WRL.h"
#include "d3d11.h"


class BlendState : public Bindable {
	

public:
	BlendState( bool blend );
	
	void Bind() override;
	
private:
	Microsoft::WRL::ComPtr<ID3D11BlendState> pState;

};

