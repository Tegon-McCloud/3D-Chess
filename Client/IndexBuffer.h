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
	size_t GetSize();

private:
	
	static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>>& GetLib() {
		static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>> lib; // lib will hold all tagged IndexBuffers
		return lib;
	}
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
	size_t size;

};

