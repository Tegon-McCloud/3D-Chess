#pragma once

struct ID3D11Device;
struct ID3D11BlendState;
struct ID3D11DepthStencilState;

#include "WRL.h"

class BlendState {

	friend class Graphics;

private:
	void Init( ID3D11Device* pDevice );

public:
	void Enabled( bool enabled ) const;

private:

	Microsoft::WRL::ComPtr<ID3D11BlendState> pEnabledState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> pDisabledState;

};

class DepthState {

	friend class Graphics;

private:
	void Init( ID3D11Device* pDevice );

public:
	void Enabled( bool enabled ) const;

private:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pEnabledState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDisabledState;

};