#pragma once
#include <d3d9.h>

#define MENU_KEY VK_HOME

namespace GUI {
	// show menu?
	inline bool open = false;
	
	// is menu setup?
	inline bool setup = false;

	// winapi related
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};
	inline WNDPROC originalWindowProcess = nullptr;

	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(LPCWSTR windowClassName) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(LPCWSTR windowName) noexcept;
	void DestroyWindow() noexcept;

	bool SetupDirectX() noexcept;
	void DestroyDirectX() noexcept;

	void Setup();

	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destroy() noexcept;

	void Render() noexcept;
}