#include <stdexcept>
#include "GUI.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../Feature/HackFeatures.h";

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParam,
	LPARAM longParam
);

// Window Process:
LRESULT CALLBACK WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParam,
	LPARAM longParam
);


bool GUI::SetupWindowClass(LPCWSTR windowClassName) noexcept {
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = windowClassName;
	windowClass.hIconSm = NULL;

	if (!RegisterClassEx(&windowClass))
		return false;

	return true;
}

void GUI::DestroyWindowClass() noexcept {
	UnregisterClass(
		windowClass.lpszClassName,
		windowClass.hInstance
	);
}

bool GUI::SetupWindow(LPCWSTR windowName) noexcept {
	window = CreateWindow(
		windowClass.lpszClassName,
		windowName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		100,
		100,
		0,
		0,
		windowClass.hInstance,
		0
	);
	
	if (!window)
		return false;
	
	return true;
}

void GUI::DestroyWindow() noexcept {
	if (window)
		DestroyWindow(window);
}

bool GUI::SetupDirectX() noexcept {
	const auto handle = GetModuleHandle(L"d3d9.dll");

	if (!handle)
		return false;

	using CreateFn = LPDIRECT3D9(__stdcall*)(UINT);

	const auto create = reinterpret_cast<CreateFn>(GetProcAddress(
		handle,
		"Direct3DCreate9"
	));

	if (!create)
		return false;

	d3d9 = create(D3D_SDK_VERSION);

	if (!d3d9)
		return false;

	D3DPRESENT_PARAMETERS params = { };

	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	if (d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_NULLREF,
		window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
		&params,
		&device
	) < 0)
		return false;

	return true;
}

void GUI::DestroyDirectX() noexcept {
	if (device) {
		device->Release();
		device = NULL;
	}
	
	if (d3d9) {
		d3d9->Release();
		d3d9 = NULL;
	}
}

void GUI::Setup() {
	if (!SetupWindowClass(L"CSGO Ruby"))
		throw std::runtime_error("Failed to create window class.");

	if (!SetupWindow(L"CSGO Ruby"))
		throw std::runtime_error("Failed to create window.");

	if (!SetupDirectX())
		throw std::runtime_error("Failed to create device.");

	DestroyWindow();
	DestroyWindowClass();
}

void GUI::SetupMenu(LPDIRECT3DDEVICE9 device) noexcept {
	auto params = D3DDEVICE_CREATION_PARAMETERS { };
	device->GetCreationParameters(&params);

	window = params.hFocusWindow;

	originalWindowProcess = reinterpret_cast<WNDPROC>(
		SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcess))
	);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	setup = true;
}

void GUI::Destroy() noexcept {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(
		window,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(originalWindowProcess)
	);

	DestroyDirectX();
}

void GUI::Render() noexcept {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::Begin("CSGO Ruby", &open, ImGuiWindowFlags_NoCollapse)) {
		if (ImGui::BeginTabBar("Tabs")) {
			if (ImGui::BeginTabItem("Aim")) {
				ImGui::Checkbox("Aimbot", &AimbotHack.isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Toggles aimbot (very obvious)");

				ImGui::Checkbox("RCS", &RCSHack.isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Toggles RCS");

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Visuals")) {
				static const char* ESPOptions[] = {
					"None",
					"2D",
					"3D"
				};

				static int selected = 0;
				
				ImGui::ListBox("ESP", &selected, ESPOptions, 3);

				switch (selected) {
				case 0:
					if (ESPHack->settings.box2D) ESPHack->settings.box2D = false;
					if (ESPHack->settings.box3D) ESPHack->settings.box3D = false;
					if (ESPHack->isActive) ESPHack->Toggle();
					break;

				case 1:
					if (!ESPHack->settings.box2D) ESPHack->settings.box2D = true;
					if (ESPHack->settings.box3D) ESPHack->settings.box3D = false;
					if (!ESPHack->isActive) ESPHack->Toggle();
					ImGui::Checkbox("Snaplines", &ESPHack->settings.snapLines);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Draws snaplines to enemies infront of you.");

					ImGui::Checkbox("Status", &ESPHack->settings.status2D);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Shows bars of hp and armor next to person.");

					ImGui::Checkbox("Show Teammates", &ESPHack->settings.showTeammates);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Shows teammates on ESP.");

					ImGui::Separator();
					
					break;

				case 2:
					if (ESPHack->settings.box2D) ESPHack->settings.box2D = false;
					if (!ESPHack->settings.box3D) ESPHack->settings.box3D = true;
					if (!ESPHack->isActive) ESPHack->Toggle();
					ImGui::Checkbox("Snaplines", &ESPHack->settings.snapLines);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Draws snaplines to enemies infront of you.");

					ImGui::Checkbox("Status", &ESPHack->settings.statusText);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Shows text of hp and armor below the person.");

					ImGui::Checkbox("Show Teammates", &ESPHack->settings.showTeammates);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Shows teammates on ESP.");

					ImGui::Checkbox("Headline", &ESPHack->settings.headlineESP);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Shows where the enemies are looking.");

					ImGui::Separator();

					break;
				}

				ImGui::Checkbox("Recoil Crosshair", &rCrosshairHack->isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Shows a crosshair where the next bullet is gonna hit.");

				ImGui::Checkbox("Radar", &RadarHack.isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Shows enemies on radar even when not visible.");

				ImGui::Checkbox("Glow", &GlowHack.isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Toggles glowhack.");

				ImGui::Checkbox("Anti Flash", &FlashHack.isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("You can't get flashed.");

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc")) {
				ImGui::Checkbox("BunnyHop", &BunnyHop.isActive);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Allows the user to BunnyHop holding spacebar.");

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CALLBACK WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParam,
	LPARAM longParam
) {
	if (GetAsyncKeyState(MENU_KEY) & 1)
		GUI::open = !GUI::open;

	if (GUI::open && ImGui_ImplWin32_WndProcHandler(
		window,
		message,
		wideParam,
		longParam
	))
		return 1L;

	return CallWindowProc(
		GUI::originalWindowProcess,
		window,
		message,
		wideParam,
		longParam
	);
}