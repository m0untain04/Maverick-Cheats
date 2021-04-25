//Maverick v3.2

#include <windows.h>
#include <d3d9.h>
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "vtable.h"
#include "main.h"

#define sleep Sleep
#define D3D_VFUNCTIONS 119
#define DEVICE_PTR 0xC97C28
#define ENDSCENE_INDEX 42
#define RESET_INDEX 16
#define SAMP_CHAT_INFO_OFFSET 0x21A0E4

typedef HRESULT(__stdcall* _EndScene)(IDirect3DDevice9* pDevice);
_EndScene oEndScene;

typedef long(__stdcall* _Reset)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pp);
_Reset oReset = nullptr;

bool Mouse_Fix = false;

bool g_bwasInitialized = false;
bool m_IsGameFullyLoaded = false;
bool menuOpen = false;
bool wndproc = false;
bool* p_open = NULL;
bool recon = false;
static int item = 0;
int startstop;
int close;
int hwndd;
int startmenu;

DWORD key;
HMODULE samp = GetModuleHandleA("samp.dll");
DWORD address = (DWORD)samp + 0x64230;
DWORD procID;
DWORD g_dwSAMP_Addr = NULL;
DWORD *g_Chat = NULL;
HANDLE handle;
HWND hWnd;

WNDPROC oriWndProc = NULL;
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void everything()
{
	GetWindowThreadProcessId(hWnd, &procID);
	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
}

void toggleSAMPCursor(int iToggle)
{
	void        *obj = *(void **)((DWORD)samp + 0x21A10C);
	((void(__thiscall *) (void *, int, bool)) ((DWORD)samp + 0x9BD30))(obj, iToggle ? 3 : 0, !iToggle);
	if (!iToggle)
		((void(__thiscall *) (void *)) ((DWORD)samp + 0x9BC10))(obj);
}

void toggleChat(int toggle)
{
	int togchattrue = 0xC3;
	int togchatfalse = 2347862870;
	everything();

	if (toggle == 1)
	{
		WriteProcessMemory(handle, (LPVOID)((DWORD)samp + 0x64230), &togchattrue, sizeof(togchattrue), 0);
	}
	else
	{
		WriteProcessMemory(handle, (LPVOID)((DWORD)samp + 0x64230), &togchatfalse, sizeof(togchatfalse), 0);
	}
}

void Shutdown()
{
	void** vTableDevice = *(void***)(*(DWORD*)DEVICE_PTR);
	VTableHookManager* vmtHooks = new VTableHookManager(vTableDevice, D3D_VFUNCTIONS);
	vmtHooks->Unhook(ENDSCENE_INDEX);
	menuOpen = false;
	toggleSAMPCursor(0);
	toggleChat(0);
	close = 1;
}


SAMPFramework *pSAMP;
CD3DHook *pD3DHook;

void theme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = ImGui::GetStyle().Colors;
	style.WindowRounding = 0.00f;
	style.ScrollbarSize = 15.00f;
	style.ScrollbarRounding = 0.00f;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 0.68f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.34f, 0.33f, 0.34f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.33f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.80f, 0.80f, 1.00f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.50f, 0.58f, 0.85f, 0.65f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.40f, 0.40f, 0.39f, 0.80f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.41f, 0.71f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.22f, 0.39f, 0.73f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.30f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.30f, 0.60f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.30f, 0.66f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.30f, 0.80f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.27f, 0.58f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.70f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.20f, 0.57f, 1.00f, 0.84f);
	colors[ImGuiCol_Button] = ImVec4(0.27f, 0.58f, 1.00f, 0.78f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.64f, 1.00f, 0.94f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.27f, 0.44f, 1.00f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.41f, 0.71f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.27f, 0.58f, 1.00f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.57f, 1.00f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.47f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.76f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.27f, 0.54f, 1.00f, 0.47f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.24f, 0.58f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.23f, 0.47f, 1.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.16f, 0.37f, 0.98f, 0.75f);

}

void RenderGUI()
{
	static float f = 0.0f;
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_MenuBar;
	ImGuiWindowFlags window_flags_about = 0;
	window_flags_about |= ImGuiWindowFlags_NoResize;
	window_flags_about |= ImGuiWindowFlags_NoCollapse;
	window_flags_about |= ImGuiWindowFlags_NoMove;
	ImGui::SetNextWindowSize(ImVec2(687.f, 450.f));
	if (!ImGui::Begin("Maverick V3.2", p_open = NULL, window_flags))
	{
		ImGui::End();
		return;
	}
	if (ImGui::BeginMenuBar())
	{
		ImGui::SetNextWindowSize(ImVec2(140.f, 60.f));
		if (ImGui::BeginMenu("Panic"))
		{
			if (ImGui::Button("Panic", ImVec2(125.f, 20.f)))
			{
				ImGui::OpenPopup("Panic");
			}
			if (ImGui::BeginPopupModal("Panic", p_open = NULL, window_flags_about))
			{
				ImGui::SetWindowSize(ImVec2(293.f, 80.f));
				ImGui::Text("Are you sure about this?");
				if (ImGui::Button("Yes", ImVec2(135.f, 20.f)))
				{
					Shutdown();
				}
				ImGui::SameLine();
				if (ImGui::Button("No", ImVec2(135.f, 20.f)))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings"))
		{
			const char* items[] = { "Insert", "Home", "Delete","End" };
			ImGui::PushItemWidth(125.f);
			ImGui::Combo("##2000", &startmenu, items, 4);
			if (startmenu == 0)
			{
				key = VK_INSERT;
			}
			if (startmenu == 1)
			{
				key = VK_HOME;
			}
			if (startmenu == 2)
			{
				key = VK_DELETE;
			}
			if (startmenu == 3)
			{
				key = VK_END;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Informations"))
		{
			if (ImGui::Button("Cheat Info", ImVec2(125.f, 20.f)))
			{
				ImGui::OpenPopup("Cheat Info");
			}
			ImGui::SetWindowSize(ImVec2(293.f, 80.f));
			if (ImGui::BeginPopupModal("Cheat Info", p_open = NULL, window_flags_about))
			{
				ImGui::Text("Cheat Developer:");
				ImGui::Text("Kimiksen#3122");
				ImGui::Text("m0untain#9999");
				ImGui::Separator();
				ImGui::Text("Support Tehnic:");
				ImGui::Text("nix0n#1759");
				ImGui::Text("freshy#5129");
				ImGui::Separator();
				ImGui::Text("Contribuitori:");
				ImGui::Text("Anto666#1751");
				ImGui::Separator();
				ImGui::Text("Licensed To: Kimiksen#3122");
				ImGui::Text("Expire at 23-05-2021 - 18:07");
				ImGui::Text("Your token is: bl2151aslaksjalkjgastybasoihatsas2819075mbnas");
				ImGui::Separator();
				ImGui::Text("RO: Pentru mai multe informatii legate de cheat contactati pe discord Kimiksen#3122");
				ImGui::Text("EN: For more informations about this cheat contact on discord Kimiksen#3122");
				if (ImGui::Button("Close"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (ImGui::CollapsingHeader("Weapon Menu"))
	{
		ImGui::Checkbox("Aimbot Range", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Settings");
		ImGui::Checkbox("Silent Aimbot", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Settings");
		ImGui::Checkbox("Smooth Aimbot", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Settings");
		ImGui::Checkbox("Rapid-Fire", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("No Reload", &Mouse_Fix);
		ImGui::Checkbox("ProAimbot", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Settings");
	}
	if (ImGui::CollapsingHeader("Visual Menu"))
	{
		ImGui::Checkbox("WallHack", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Skeleton", &Mouse_Fix);
		ImGui::Checkbox("Chams", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Fake lag", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Fake Ping", &Mouse_Fix);
	}
	if (ImGui::CollapsingHeader("Player Menu"))
	{
		ImGui::Checkbox("Fast Respawn", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Airbrack", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Fast Run", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Fast Rotation", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Config");
		ImGui::Checkbox("Infinite Run", &Mouse_Fix);
		ImGui::Checkbox("Allow CBug", &Mouse_Fix);
		ImGui::Checkbox("Anti Stun", &Mouse_Fix);
	}
	if (ImGui::CollapsingHeader("Teleport"))
	{
		ImGui::Checkbox("Teleport on map", &Mouse_Fix);
		ImGui::Checkbox("Teleport to player", &Mouse_Fix);
	}
	if (ImGui::CollapsingHeader("Developer"))
	{
		ImGui::Checkbox("One Man Maverick", &Mouse_Fix);
		ImGui::SameLine();
		ImGui::Button("Setting");
	}
	   ImGui::End();
}

void mainThread(void *pvParams)
{
	
}

void functions()
{
	if (Mouse_Fix)
	{
		float x;
		float y;
		ReadProcessMemory(handle, (PBYTE*)0xB6EC1C, &x, 4, 0);
		ReadProcessMemory(handle, (PBYTE*)0xB6EC18, &y, 4, 0);
		if (x != y)
		{
			WriteProcessMemory(handle, (LPVOID)0xB6EC18, &x, 4, 0);
		}
	}
}

LRESULT CALLBACK hWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplDX9_WndProcHandler(hwnd, uMsg, wParam, lParam) && GetKeyState(key) == 1 && menuOpen && wndproc)
	{
		return 1l;
	}

	return CallWindowProc(oriWndProc, hwnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pp)
{
	if (g_bwasInitialized)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		g_bwasInitialized = false;
	}
	return oReset(pDevice, pp);
}

HRESULT __stdcall hkEndScene(IDirect3DDevice9* pDevice)
{
	if (!g_bwasInitialized)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		io.IniFilename = NULL;
		io.DeltaTime = 1.0f / 60.0f;
		ImFont* pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\impact.ttf", 18);
		D3DDEVICE_CREATION_PARAMETERS d3dcp;
		pDevice->GetCreationParameters(&d3dcp);
		hWnd = d3dcp.hFocusWindow;
		io.Fonts->AddFontDefault();
		style.AntiAliasedLines = false;
		style.AntiAliasedShapes = false;
		if (hwndd == 0)
		{
			oriWndProc = (WNDPROC)SetWindowLongPtr(d3dcp.hFocusWindow,
				GWL_WNDPROC, (LONG)(LONG_PTR)hWndProc);
			hwndd++;
		}
		ImGui_ImplDX9_Init(d3dcp.hFocusWindow, pDevice);
		g_bwasInitialized = true;
	}
	if (item == 0)
	{
		theme();
	}
	if (startmenu == 0)
	{
		key = VK_INSERT;
	}
	if (startmenu == 1)
	{
		key = VK_HOME;
	}
	if (startmenu == 2)
	{
		key = VK_DELETE;
	}
	if (startmenu == 3)
	{
		key = VK_END;
	}
	ImGui_ImplDX9_NewFrame();
	if (menuOpen)
	{
		toggleSAMPCursor(1);
		toggleChat(1);
		RenderGUI();
	}
	else
	{
		if (startstop == 0)
		{
			toggleSAMPCursor(0);
			toggleChat(0);
			startstop++;
		}
	}
	ImGui::Render();
	return oEndScene(pDevice);
}
DWORD APIENTRY MainThread(LPVOID lparam)
{
	while (g_dwSAMP_Addr == NULL)
	{
		g_dwSAMP_Addr = (DWORD)GetModuleHandle("samp.dll");
		sleep(250);
	}

	while (!g_Chat)
	{
		g_Chat = *(DWORD**)(g_dwSAMP_Addr + SAMP_CHAT_INFO_OFFSET);
		sleep(25);
	}

	void** vTableDevice = *(void***)(*(DWORD*)DEVICE_PTR);
	VTableHookManager* vmtHooks = new VTableHookManager(vTableDevice, D3D_VFUNCTIONS);

	oEndScene = (_EndScene)vmtHooks->Hook(ENDSCENE_INDEX, (void*)hkEndScene);
	oReset = (_Reset)vmtHooks->Hook(RESET_INDEX, (void*)hkReset);
	everything();
	functions();
	while (true)
	{
		if (GetAsyncKeyState(key) & 1)
		{
			menuOpen = !menuOpen;
			startstop = 0;
		}
		if (close == 1)
		{
			return 0;
		}
		functions();
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);

		pSAMP = new SAMPFramework(GetModuleHandle("samp.dll"));
		_beginthread(mainThread, NULL, NULL);
		pD3DHook = new CD3DHook();
		break;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}