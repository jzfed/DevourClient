#include "pch-il2cpp.h"
#include "Hooks.hpp"
#include "../features/menu.hpp"
#include "../settings/settings.hpp"
#include "../main.h"
#include "../utils/utils.hpp"

#include <iostream>
#include "helpers.h"

#pragma warning(push, 0) //important cuz dx11 throws so much warnings
#include <d3d11.h>
#pragma warning(pop)
#pragma comment (lib, "d3d11.lib" )

/*
    //Code about hooking stuff
    //Exemple of hooked function :
    typedef int (__stdcall* TEST)(); //We define the function, must be the EXACT same definition as the original one
    TEST test_org = NULL;
    int __stdcall test_hook() //MUST BE the original calling convention
    {
        std::cout << "called" << std::endl;
        return test_org(); //if we want to call the original one, we can just return 1 otherwise
    }

    //Exemple :
    MH_STATUS status_test = MH_CreateHook((LPVOID*)test_sig, &test_hook, reinterpret_cast<LPVOID*>(&test_org));
    //We say that for every call to the test_sig address we want to redirect it to the address of the function named test_hook (& gives the pointer to it)
    //We can store the original pointer to the original function into test_org if we want to call the org later --> trampoline hook
    //original_sum can be NULL if we don't want to trampoline hook

    if (status_test != MH_OK) { //If it failed
        print(MH_StatusToString(status)); //If we are in debug mode, we print the fail status into the console
        return 0; //We exit
    }
*/

typedef void(__stdcall* TDebug_2_Log)(app::Object *, MethodInfo *);
TDebug_2_Log oDebug_2_Log = NULL;
TDebug_2_Log oDebug_2_Warning = NULL;
TDebug_2_Log oDebug_2_Error = NULL;
void __stdcall hDebug_Log(app::Object* message, MethodInfo* method) {
	std::cout << "[UNITY] " << ToString(message) << std::endl;
	il2cppi_log_write(ToString(message));
}

typedef void(__stdcall* TNolanBehaviour_OnAttributeUpdateValue)(app::NolanBehaviour*, app::Attribute_1*, MethodInfo*);
TNolanBehaviour_OnAttributeUpdateValue oNolanBehaviour_OnAttributeUpdateValue = NULL;
void __stdcall hNolanBehaviour_OnAttributeUpdateValue(app::NolanBehaviour* __this, app::Attribute_1* attribute, MethodInfo* method) {
	if (settings::unlimited_uv && strcmp(il2cppi_to_string(attribute->fields.m_Name).c_str(), "Battery") == 0) {
		attribute->fields.m_Value = 100.0f;
	}
	oNolanBehaviour_OnAttributeUpdateValue(__this, attribute, method);
}

// DO_APP_FUNC(0x005E5E10, bool, OptionsHelpers_IsRobeUnlocked, (OptionsHelpers * __this, String * robe, String * character, MethodInfo * method));
typedef bool(__stdcall* TOptionsHelpers_IsRobeUnlocked)(app::OptionsHelpers*, app::String*, app::String*, MethodInfo*);
TOptionsHelpers_IsRobeUnlocked oOptionsHelpers_IsRobeUnlocked = NULL;
bool __stdcall hOptionsHelpers_IsRobeUnlocked(app::OptionsHelpers* __this, app::String* robe, app::String* character, MethodInfo* method) {

	if (settings::unlock_all)
		return true;

	return oOptionsHelpers_IsRobeUnlocked(__this, robe, character, method);
}

// DO_APP_FUNC(0x005E44C0, bool, OptionsHelpers_IsCharacterUnlocked, (OptionsHelpers * __this, String * prefab, MethodInfo * method));
typedef bool(__stdcall* TOptionsHelpers_IsCharacterUnlocked)(app::OptionsHelpers*, app::String* , MethodInfo*);
TOptionsHelpers_IsCharacterUnlocked oOptionsHelpers_IsCharacterUnlocked = NULL;
bool __stdcall hOptionsHelpers_IsCharacterUnlocked(app::OptionsHelpers* __this, app::String* prefab, MethodInfo* method) {

	if (settings::unlock_all)
		return true;

	return oOptionsHelpers_IsCharacterUnlocked(__this, prefab, method);
}

typedef app::RankHelpers_ExpGainInfo* (__stdcall* TRankHelpers_CalculateExpGain)(app::RankHelpers*, int32_t, int32_t, app::GameConfigToken*, MethodInfo*);
TRankHelpers_CalculateExpGain oRankHelpers_CalculateExpGain = NULL;
app::RankHelpers_ExpGainInfo* __stdcall hRankHelpers_CalculateExpGain(app::RankHelpers* __this, int32_t mapProgress, int32_t numAwards, app::GameConfigToken* gameConfigToken, MethodInfo* method) {
	app::RankHelpers_ExpGainInfo* gain = oRankHelpers_CalculateExpGain(__this, mapProgress, numAwards, gameConfigToken, method);

	if (settings::exp_modifier) {
		gain->fields.totalExp = settings::new_exp;
	}
	return gain;
}

void CreateHooks() {
	/*
	//Exemple :
	MH_STATUS SceneLoadLocalDoneStatus = MH_CreateHook((LPVOID*)test_sig, &hkSceneLoadLocalDone, reinterpret_cast<LPVOID*>(&oSceneLoadLocalDone));
	//We say that for every call to the test_sig address we want to redirect it to the address of the function named test_hook (& gives the pointer to it)
	//We can store the original pointer to the original function into test_org if we want to call the org later --> trampoline hook
	//original_sum can be NULL if we don't want to trampoline hook
	*/

	MH_STATUS status_Debug_Log = MH_CreateHook((LPVOID*)app::Debug_2_Log, &hDebug_Log, reinterpret_cast<LPVOID*>(&oDebug_2_Log));
	if (status_Debug_Log != MH_OK) {
		std::cout << "Failed to create Debug_Log hook: " << MH_StatusToString(status_Debug_Log) << std::endl;
		return;
	}
	status_Debug_Log = MH_CreateHook((LPVOID*)app::Debug_2_LogError, &hDebug_Log, reinterpret_cast<LPVOID*>(&oDebug_2_Error));
	if (status_Debug_Log != MH_OK) {
		std::cout << "Failed to create Debug_LogError hook: " << MH_StatusToString(status_Debug_Log) << std::endl;
		return;
	}
	status_Debug_Log = MH_CreateHook((LPVOID*)app::Debug_2_LogWarning, &hDebug_Log, reinterpret_cast<LPVOID*>(&oDebug_2_Warning));
	if (status_Debug_Log != MH_OK) {
		std::cout << "Failed to create Debug_LogWarning hook: " << MH_StatusToString(status_Debug_Log) << std::endl;
		return;
	}
	MH_STATUS status_uv = MH_CreateHook((LPVOID*)app::NolanBehaviour_OnAttributeUpdateValue , &hNolanBehaviour_OnAttributeUpdateValue, reinterpret_cast<LPVOID*>(&oNolanBehaviour_OnAttributeUpdateValue));
	if (status_uv != MH_OK) {
		std::cout << "Failed to create uv hook: " << MH_StatusToString(status_uv) << std::endl;
		return;
	}
	MH_STATUS status_xp = MH_CreateHook((LPVOID*)app::RankHelpers_CalculateExpGain , &hRankHelpers_CalculateExpGain, reinterpret_cast<LPVOID*>(&oRankHelpers_CalculateExpGain));
	if (status_uv != MH_OK) {
		std::cout << "Failed to create xp hook: " << MH_StatusToString(status_xp) << std::endl;
		return;
	}
	MH_STATUS status_robe = MH_CreateHook((LPVOID*)app::OptionsHelpers_IsRobeUnlocked, &hOptionsHelpers_IsRobeUnlocked, reinterpret_cast<LPVOID*>(&oOptionsHelpers_IsRobeUnlocked));
	if (status_robe != MH_OK) {
		std::cout << "Failed to create robe hook: " << MH_StatusToString(status_robe) << std::endl;
		return;
	}
	MH_STATUS status_characterUnlock = MH_CreateHook((LPVOID*)app::OptionsHelpers_IsCharacterUnlocked, &hOptionsHelpers_IsCharacterUnlocked, reinterpret_cast<LPVOID*>(&oOptionsHelpers_IsCharacterUnlocked));
	if (status_characterUnlock != MH_OK) {
		std::cout << "Failed to create character unlock hook: " << MH_StatusToString(status_characterUnlock) << std::endl;
		return;
	}
	MH_STATUS enable_status_Debug_Log = MH_EnableHook(MH_ALL_HOOKS);
	if (enable_status_Debug_Log != MH_OK) {
		std::cout << "Failed to enable hooks: " << MH_StatusToString(enable_status_Debug_Log) << std::endl;
		return;
	}
}

typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
D3D11PresentHook phookD3D11Present = NULL;

ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND window = NULL;
WNDPROC oWndProc;
bool open_menu = false;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (open_menu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}

	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse && open_menu) {
		return true;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

static bool pressed = false;
bool initonce = false;
static bool cursor_switch = false;
ID3D11RenderTargetView* mainRenderTargetViewD3D11 = NULL;

HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!initonce)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			auto context = ImGui::CreateContext();
			ImGui::SetCurrentContext(context);
			InitStyle();
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(pDevice, pContext);
			initonce = true;
		}
		else
			return phookD3D11Present(pSwapChain, SyncInterval, Flags);
	}

	if (GetKeyState(VK_INSERT) & 0x8000) {
		pressed = true;
	}
		

	else if (!(GetKeyState(VK_INSERT) & 0x8000) && pressed) {
		open_menu = !open_menu;
		pressed = false;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*
	seems that there are issues with opening the menu in the pause menu
	the cursor will still be visible but locked in the middle of the screen
	//TOFIX
	*/

	if (open_menu) {
		/*Unity::CGameObject* UIHelpers = Unity::GameObject::Find("UIHelpers");
		if (UIHelpers) {
			Unity::CComponent* UI = UIHelpers->GetComponent("UIHelpers");
			if (UI) {
				UI->CallMethodSafe<void*>("ShowMouseCursor");
				cursor_switch = true;
			}
		}*/
		
		DrawMenu(open_menu);
	}
	/*if (!open_menu && cursor_switch) {
		Unity::CGameObject* UIHelpers = Unity::GameObject::Find("UIHelpers");
		if (UIHelpers) {
			Unity::CComponent* UI = UIHelpers->GetComponent("UIHelpers");
			if (UI) {
				UI->CallMethodSafe<void*>("HideMouseCursor");
				cursor_switch = false;
			}
		}
	}*/

	ImGui::GetIO().MouseDrawCursor = open_menu;

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pContextVTable = NULL;
DWORD_PTR* pDeviceVTable = NULL;
IDXGISwapChain* pSwapChain;
bool HookDX11() {
	HMODULE hDXGIDLL = GetModuleHandle(L"dxgi.dll");
	while (!hDXGIDLL) {
		hDXGIDLL = GetModuleHandle(L"dxgi.dll");
		Sleep(100);
	}

	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = GetForegroundWindow();
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = true;

	// LibOVR 0.4.3 requires that the width and height for the backbuffer is set even if
	// you use windowed mode, despite being optional according to the D3D11 documentation.
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	UINT createFlags = 0;
#ifdef _DEBUG
	// This flag gives you some quite wonderful debug text. Not wonderful for performance, though!
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGISwapChain* d3dSwapChain = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)))
	{
		return false;
	}


	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];

	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];

	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], hookD3D11Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { return false; }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { return false; }

	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	return true;
}

bool InitializeHooks() {
	return MH_Initialize() == MH_OK;
}

void DisableHooks() {
	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));
	if (pSwapChain) { pSwapChain->Release(); }
	if (mainRenderTargetViewD3D11) { mainRenderTargetViewD3D11->Release(); mainRenderTargetViewD3D11 = NULL; }
	if (pContext) { pContext->Release(); pContext = NULL; }
	if (pDevice) { pDevice->Release(); pDevice = NULL; }
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}