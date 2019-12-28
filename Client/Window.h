#pragma once

#include "WindowsStrict.h"
#include "Graphics.h"
#include "Input.h"

#include <optional>

class Window {

	friend class WindowClass; // Give WindowClass access to the Procedure method

private:
	Window();

public:

	HWND GetHandle() const;
	const Graphics& GetGraphics() const;

	const Input& GetInput() const;

	void SetVisible( bool visible, bool maximized = false ) const;

	std::optional<int> ProcessMessages() const;

	int GetWidth() const;
	int GetHeight() const;
	float GetAspect() const;
	bool IsInFocus() const;

	operator HWND() const;

	static const Window& Get() { // singleton getter
		return GetInternal();
	}

	// quick accessors
	inline static const Graphics& GFX() {
		return Get().gfx;
	}

	inline static const ID3D11Device* GFXDevice() { 
		return Get().gfx.pDevice.Get();
	}

	inline static const ID3D11DeviceContext* GFXContext() {
		return Get().gfx.pContext.Get();
	}

private:
	
	static Window& GetInternal() {
		static Window inst;
		return inst;
	}

	// delete these so no one can copy the window instance
	Window(const Window& ) = delete;
	Window& operator=( const Window& ) = delete;

	void SizeChanged( int width, int height );
	HWND Create();

	// the win32 window procedure
	static LRESULT CALLBACK Procedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	
public:
	static constexpr const wchar_t title[] = L"3D-Chess";

private:
	int x, y, width, height;
	float aspectRatio;
	HWND hWnd;
	Graphics gfx;
	Input input;
	bool focus;

};

class WindowClass {

public:
	static constexpr const wchar_t wndClsName[] = L"FunctionRenderWindowClass";

private:
	WindowClass();
	~WindowClass();

private:
	static WindowClass inst;

};
