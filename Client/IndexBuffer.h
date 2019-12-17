#pragma once

#include "Bindable.h"
#include "WRL.h"
#include "d3d11.h"
#include <unordered_map>
#include <string>

class IndexBuffer : public Bindable {
	

public:
	IndexBuffer( const unsigned short* indices, size_t size, std::string tag = "" );
	IndexBuffer() = delete;

	void Bind() override;
	size_t GetSize() const;

private:
	
	static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>>& GetCodex() {
		static std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11Buffer>> codex; // lib will hold all tagged IndexBuffers
		return codex;
	}
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;

};

