#pragma once

#include "Bindable.h"
#include "WRL.h"
#include "d3d11.h"
#include <unordered_map>

class IndexBuffer : public Bindable {
	

public:
	IndexBuffer( const unsigned short* indices, size_t size, std::string tag = "" );
	IndexBuffer() = delete;

	void Bind() override;

private:
	
	static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>>& GetLib() {
		static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>> lib;
		return lib;
	}
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;

};

