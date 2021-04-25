//hai sal luati coduri na sal 

#include <windows.h>
#include <d3d9.h>
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "vtable.h"
#include "main.h"
#include <math.h>
#include <ymath.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


#define sleep Sleep
#define D3D_VFUNCTIONS 119
#define DEVICE_PTR 0xC97C28
#define ENDSCENE_INDEX 42
#define RESET_INDEX 16

#define SAMP_INFO  0x21A0F8
#define SAMP_SETTINGS  0x3C5
#define SAMP_FUNC_SAY								0x57F0
#define SAMP_FUNC_SENDCMD							0x65C60	
#define M_PI 3.14159265358979323846
#define PILOT_ADDR                                  0x96914C

#define Ryon 1076115084 
#define Over 1254581962
#define Narda 1946938678
#define Medik 1551226685
#define Andy -626896906
#define mlg 437135449
#define kegan -189440424
#define kz 951980208
#define dumi -558884738
#define razvan 115159147
#define theweek -2043349170
#define benq 1912777623



#define DEFCOLOR_SRC(name, r, g, b) \
	static Color name## (uint8_t a = 240){ return Color (r, g, b, a); }

bool rainbowmenu = false;
bool RainbowRadar = false;
bool RainbowHeadLights = false;
bool slapper = false;
bool no_bike_fall = false;

class Color {
public:

	Color() {
		SetColor(0, 0, 0, 255);
	}

	Color(uint8_t r, uint8_t g, uint8_t b) {
		SetColor(r, g, b, 255);
	}

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		SetColor(r, g, b, a);
	}

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
		_color[0] = (uint8_t)r;
		_color[1] = (uint8_t)g;
		_color[2] = (uint8_t)b;
		_color[3] = (uint8_t)a;
	}

	void GetColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const {
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	uint8_t &operator[](int index) {
		return _color[index];
	}

	const uint8_t &operator[](int index) const {
		return _color[index];
	}

	bool operator == (const Color &rhs) const {
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const Color &rhs) const {
		return !(operator==(rhs));
	}

	int r() { return _color[0]; }
	int g() { return _color[1]; }
	int b() { return _color[2]; }
	int a() { return _color[3]; }

	int GetR() { return _color[0]; }
	int GetG() { return _color[1]; }
	int GetB() { return _color[2]; }
	int GetA() { return _color[3]; }

	void SetR(uint8_t _i) { _color[0] = _i; }
	void SetG(uint8_t _i) { _color[1] = _i; }
	void SetB(uint8_t _i) { _color[2] = _i; }
	void SetA(uint8_t _i) { _color[3] = _i; }

	Color &operator=(const Color &rhs) {
		*(int*)(&_color[0]) = *(int*)&rhs._color[0];
		return *this;
	}

	Color operator+(const Color &rhs) const {
		int red = _color[0] + rhs._color[0];
		int green = _color[1] + rhs._color[1];
		int blue = _color[2] + rhs._color[2];
		int alpha = _color[3] + rhs._color[3];

		red = red > 255 ? 255 : red;
		green = green > 255 ? 255 : green;
		blue = blue > 255 ? 255 : blue;
		alpha = alpha > 255 ? 255 : alpha;

		return Color(red, green, blue, alpha);
	}

	Color operator-(const Color &rhs) const {
		int red = _color[0] - rhs._color[0];
		int green = _color[1] - rhs._color[1];
		int blue = _color[2] - rhs._color[2];
		int alpha = _color[3] - rhs._color[3];
		red = red < 0 ? 0 : red;
		green = green < 0 ? 0 : green;
		blue = blue < 0 ? 0 : blue;
		alpha = alpha < 0 ? 0 : alpha;
		return Color(red, green, blue, alpha);
	}

	operator const uint8_t*() {
		return (uint8_t*)(&_color[0]);
	}

	static Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}

	ImU32 GetU32()
	{
		return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
			+ (_color[0] & 0xff);
		//return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
	}

	DEFCOLOR_SRC(Black, 0, 0, 0);
	DEFCOLOR_SRC(White, 255, 255, 255);
	DEFCOLOR_SRC(Red, 255, 0, 0);
	DEFCOLOR_SRC(Green, 0, 255, 0);
	DEFCOLOR_SRC(Blue, 0, 0, 255);
	DEFCOLOR_SRC(Lime, 0, 255, 0);
	DEFCOLOR_SRC(Yellow, 255, 255, 0);
	DEFCOLOR_SRC(Cyan, 0, 255, 255);
	DEFCOLOR_SRC(Magenta, 255, 0, 255);
	DEFCOLOR_SRC(Silver, 192, 192, 192);
	DEFCOLOR_SRC(Gray, 128, 128, 128);
	DEFCOLOR_SRC(Maroon, 128, 0, 0);
	DEFCOLOR_SRC(Olive, 128, 128, 0);
	DEFCOLOR_SRC(Purple, 128, 0, 128);
	DEFCOLOR_SRC(Teal, 0, 128, 128);
	DEFCOLOR_SRC(Navy, 0, 0, 128);
	DEFCOLOR_SRC(DarkRed, 139, 0, 0);
	DEFCOLOR_SRC(Brown, 165, 42, 42);
	DEFCOLOR_SRC(Firebrick, 178, 34, 34);
	DEFCOLOR_SRC(Crimson, 220, 20, 60);
	DEFCOLOR_SRC(IndianRed, 205, 92, 92);
	DEFCOLOR_SRC(LightCoral, 240, 128, 128);
	DEFCOLOR_SRC(DarkSalmon, 233, 150, 122);
	DEFCOLOR_SRC(Salmon, 250, 128, 114);
	DEFCOLOR_SRC(LightSalmon, 255, 160, 122);
	DEFCOLOR_SRC(OrangeRed, 255, 69, 0);
	DEFCOLOR_SRC(DarkOrange, 255, 140, 0);
	DEFCOLOR_SRC(Orange, 255, 165, 0);
	DEFCOLOR_SRC(Gold, 255, 215, 0);
	DEFCOLOR_SRC(DarkGoldenRod, 184, 134, 11);
	DEFCOLOR_SRC(GoldenRod, 218, 165, 32);
	DEFCOLOR_SRC(YellowGreen, 154, 205, 50);
	DEFCOLOR_SRC(DarkOliveGreen, 85, 107, 47);
	DEFCOLOR_SRC(OliveDrab, 107, 142, 35);
	DEFCOLOR_SRC(LawnGreen, 124, 252, 0);
	DEFCOLOR_SRC(ChartReuse, 127, 255, 0);
	DEFCOLOR_SRC(GreenYellow, 173, 255, 47);
	DEFCOLOR_SRC(DarkGreen, 0, 100, 0);
	DEFCOLOR_SRC(ForestGreen, 34, 139, 34);
	DEFCOLOR_SRC(LimeGreen, 50, 205, 50);
	DEFCOLOR_SRC(DarkCyan, 0, 139, 139);
	DEFCOLOR_SRC(Aqua, 0, 255, 255);
	DEFCOLOR_SRC(LightCyan, 224, 255, 255);
	DEFCOLOR_SRC(DarkTurquoise, 0, 206, 209);
	DEFCOLOR_SRC(Turquoise, 64, 224, 208);
	DEFCOLOR_SRC(MediumTurquoise, 72, 209, 204);
	DEFCOLOR_SRC(PaleTurquoise, 175, 238, 238);
	DEFCOLOR_SRC(Aquamarine, 127, 255, 212);
	DEFCOLOR_SRC(PowderBlue, 176, 224, 230);
	DEFCOLOR_SRC(DodgerBlue, 30, 144, 255);
	DEFCOLOR_SRC(Lightblue, 173, 216, 230);
	DEFCOLOR_SRC(SkyBlue, 135, 206, 235);
	DEFCOLOR_SRC(LightSkyBlue, 135, 206, 250);
	DEFCOLOR_SRC(MidnightBlue, 25, 25, 112);
	DEFCOLOR_SRC(DarkBlue, 0, 0, 139);
	DEFCOLOR_SRC(MediumBlue, 0, 0, 205);
	DEFCOLOR_SRC(RoyalBlue, 65, 105, 225);
	DEFCOLOR_SRC(BlueViolet, 138, 43, 226);
	DEFCOLOR_SRC(Indigo, 75, 0, 130);
	DEFCOLOR_SRC(DarkSlateBlue, 72, 61, 139);
	DEFCOLOR_SRC(SlateBlue, 106, 90, 205);
	DEFCOLOR_SRC(MediumSlateBlue, 123, 104, 238);
	DEFCOLOR_SRC(MediumPurple, 147, 112, 219);
	DEFCOLOR_SRC(Darkmagenta, 139, 0, 139);
	DEFCOLOR_SRC(Darkviolet, 148, 0, 211);
	DEFCOLOR_SRC(DarkGray, 169, 169, 169);
	DEFCOLOR_SRC(LightGray, 211, 211, 211);
	DEFCOLOR_SRC(Gainsboro, 220, 220, 220);
	DEFCOLOR_SRC(LtBlue, 0, 150, 255);
	DEFCOLOR_SRC(LtGreen, 0, 255, 100);
private:
	uint8_t _color[4];
};
struct Color2
{
	int r;
	int g;
	int b;
	int a;

	Color2()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 255;
	}

	Color2(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	Color2(int r, int g, int b, int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color2 operator / (float div)
	{
		Color2 color = *this;
		color.r = color.r / div;
		color.g = color.g / div;
		color.b = color.b / div;
		return color;
	}

	Color2& operator /= (float div)
	{
		Color2& color = *this;
		color.r /= div;
		color.g /= div;
		color.b /= div;
		return color;
	}

	Color2& operator *= (float coeff)
	{
		Color2& color = *this;
		color.r *= coeff;
		color.g *= coeff;
		color.b *= coeff;
		return color;
	}

	static Color2 FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color2(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color2(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color2(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color2(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color2(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color2(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}

	static Color2 FromImColor(ImColor color)
	{
		return Color2(
			(int)(color.Value.x * 255),
			(int)(color.Value.y * 255),
			(int)(color.Value.z * 255),
			(int)(color.Value.w * 255)
		);
	}


	static ImColor ToImColor(Color2 color)
	{
		return ImColor(
			color.r / 255.f,
			color.g / 255.f,
			color.b / 255.f,
			color.a / 255.f
		);
	}

};

extern HINSTANCE hAppInstance;

UCHAR szFileSys[255], szVolNameBuff[255];
DWORD dwMFL, dwSysFlags;
DWORD dwSerial;
LPCTSTR szHD = "C:\\";

HINSTANCE HThisModule;
bool DoUnload;


typedef HRESULT(__stdcall* _EndScene)(IDirect3DDevice9* pDevice);
_EndScene oEndScene;

typedef long(__stdcall* _Reset)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pp); 
_Reset oReset = nullptr;

const char stunanims[12][15]
{
	"DAM_armL_frmBK",
	"DAM_armL_frmFT",
	"DAM_armL_frmLT",
	"DAM_armR_frmBK",
	"DAM_armR_frmFT",
	"DAM_armR_frmRT",
	"DAM_LegL_frmBK",
	"DAM_LegL_frmFT",
	"DAM_LegL_frmLT",
	"DAM_LegR_frmBK",
	"DAM_LegR_frmFT",
	"DAM_LegR_frmRT"
};
const char stunanims2[4][18]
{
	"DAM_stomach_frmBK",
	"DAM_stomach_frmFT",
	"DAM_stomach_frmLT",
	"DAM_stomach_frmRT"
};

bool bAntiStun = false;
bool tintarainbow = false;
bool fake_ping = false;
bool InvertWalk = false;
bool bAntiStunned = false;
bool antiaim = false;
bool pilot = false;


bool atentat1 = false;//e c mortii lui de c++
bool tick_done;
bool bEditFootSync;
DWORD tick;
float fWeaponDamage[55] =
{
	82.5, // 0 - Fist
	1.0, // 1 - Brass knuckles
	1.0, // 2 - Golf club
	1.0, // 3 - Nitestick
	1.0, // 4 - Knife
	1.0, // 5 - Bat
	1.0, // 6 - Shovel
	1.0, // 7 - Pool cue
	1.0, // 8 - Katana
	1.0, // 9 - Chainsaw
	1.0, // 10 - Dildo
	1.0, // 11 - Dildo 2
	1.0, // 12 - Vibrator
	1.0, // 13 - Vibrator 2
	1.0, // 14 - Flowers
	1.0, // 15 - Cane
	82.5, // 16 - Grenade
	0.0, // 17 - Teargas
	1.0, // 18 - Molotov
	9.9, // 19 - Vehicle M4 (custom)
	46.2, // 20 - Vehicle minigun (custom)
	0.0, // 21
	8.25, // 22 - Colt 45
	13.2, // 23 - Silenced
	46.2, // 24 - Deagle
	49.5,//3.3, // 25 - Shotgun
	49.5,//3.3, // 26 - Sawed-off
	39.6,//4.95, // 27 - Spas
	6.6, // 28 - UZI
	8.25, // 29 - MP5
	9.900001, // 30 - AK47
	9.900001, // 31 - M4
	6.6, // 32 - Tec9
	24.750001, // 33 - Cuntgun
	41.25, // 34 - Sniper
	82.5, // 35 - Rocket launcher
	82.5, // 36 - Heatseeker
	1.0, // 37 - Flamethrower
	46.2, // 38 - Minigun
	82.5, // 39 - Satchel
	0.0, // 40 - Detonator
	0.33, // 41 - Spraycan
	0.33, // 42 - Fire extinguisher
	0.0, // 43 - Camera
	0.0, // 44 - Night vision
	0.0, // 45 - Infrared
	0.0, // 46 - Parachute
	0.0, // 47 - Fake pistol
	2.64, // 48 - Pistol whip (custom)
     9.9, // 49 - Vehicle
	330.0, // 50 - Helicopter blades
	82.5, // 51 - Explosion
	1.0, // 52 - Car park (custom)
	1.0, // 53 - Drowning
	165.0 // 54 - Splat
};
bool OnSendPacket(BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	uint8_t packetId;
	stOnFootData OnFootData;
	parameters->ResetReadPointer();
	parameters->Read(packetId);
	parameters->Read((char *)&OnFootData, sizeof(stOnFootData));
	switch (packetId)
	{
	case ID_PLAYER_SYNC:

		if (antiaim)
		{
			bEditFootSync = true;
			//stOnFootData OnFootData;
			//memcpy(&OnFootData, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
			OnFootData.byteSpecialAction = 3;
			//parameters->Reset();
			//parameters->Write((BYTE)ID_PLAYER_SYNC);
			//parameters->Write((PCHAR)&OnFootData, sizeof(stOnFootData));
			//g_RakFuncs->Send(parameters, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		}
		if (InvertWalk)
		{
			bEditFootSync = true;

			D3DXQUATERNION Quat, Quat2;
			Quat.w = OnFootData.fQuaternion[0];
			Quat.x = OnFootData.fQuaternion[1];
			Quat.y = OnFootData.fQuaternion[2];
			Quat.z = OnFootData.fQuaternion[3];
			//
			D3DXVECTOR3 Axis;
			Axis.x = 0;
			Axis.y = 1;
			Axis.z = 0;
			D3DXQuaternionRotationAxis(&Quat2, &Axis, M_PI);
			D3DXQuaternionMultiply(&Quat, &Quat, &Quat2);
			OnFootData.fQuaternion[0] = Quat.w;
			OnFootData.fQuaternion[1] = Quat.x;
			OnFootData.fQuaternion[2] = Quat.y;
			OnFootData.fQuaternion[3] = Quat.z;

		}
        if (bEditFootSync)
		{
			parameters->Reset();
			parameters->Write((BYTE)ID_PLAYER_SYNC);
			parameters->Write((PCHAR)&OnFootData, sizeof(stOnFootData));
			pSAMP->sendPacket(parameters);
			bEditFootSync = false;
		}
		if (atentat1)
		{

			if (!tick_done)
			{
				tick = GetTickCount64();
				tick_done = true;
			}
			if (GetTickCount64() - tick > 700)
		{
				static int current_tick = 1;

				stBulletData BulletData;
				parameters->ResetReadPointer();
				parameters->Read(packetId);
				parameters->Read((PCHAR)&BulletData, sizeof(stBulletData));

				int weaponid = pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon;

				for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
				{
					if (pSAMP->getPlayers()->pRemotePlayer[i] == nullptr)
						continue;
					if (pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData == nullptr)
						continue;
					if (!pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fActorHealth)
						continue;
					float damage_t = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fActorHealth / fWeaponDamage[pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon];


					for (int z = 0; z < round(damage_t) + 1; z++)
					{
						BulletData.byteType = 1;
						BulletData.fOrigin[0] = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fOnFootPos[0];
						BulletData.fOrigin[1] = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fOnFootPos[1];
						BulletData.fOrigin[2] = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fOnFootPos[2];

						BulletData.fTarget[0] = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fOnFootPos[0];
						BulletData.fTarget[1] = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fOnFootPos[1];
						BulletData.fTarget[2] = pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->fOnFootPos[2];

						if (pSAMP->getPlayers()->pRemotePlayer[i]->pPlayerData->bytePlayerState == PLAYER_STATE_ONFOOT)
						{
							BulletData.fCenter[0] = (1.0f / 2) - ((rand() % (int)(1.0f * 10.0f) / 100.0f));
							BulletData.fCenter[1] = (1.0f / 2) - ((rand() % (int)(1.0f * 10.0f) / 100.0f));
							BulletData.fCenter[2] = 0.50f - ((rand() % 100) / 100.0f);
						}

						else
						{
							BulletData.fCenter[0] = 0.0f;
							BulletData.fCenter[1] = 0.0f;
							BulletData.fCenter[2] = 0.56f - ((rand() % 5) / 100.0f);
						}
						BulletData.sTargetID = i;
						BulletData.byteWeaponID = weaponid;
						BitStream bsGiveDamage;
						bsGiveDamage.Write(false);
						bsGiveDamage.Write((USHORT)i);
						bsGiveDamage.Write((float)fWeaponDamage[weaponid]);
						bsGiveDamage.Write((int)weaponid);
						bsGiveDamage.Write((rand() % 7) + 3);
						pSAMP->sendRPC(RPC_GiveTakeDamage, &bsGiveDamage, HIGH_PRIORITY, RELIABLE_SEQUENCED, NULL, false);


						parameters->Reset();
						parameters->Write((BYTE)ID_BULLET_SYNC);
						parameters->Write((PCHAR)&BulletData, sizeof(stBulletData));
						pSAMP->sendPacket(parameters);
					}


				}

				tick = 0;
				tick_done = false;
			}
		}

	}
	return TRUE;
}

bool gamespeedovar1 = false;
////////// AIMBOT STUFF ///////////////
DWORD gpoint;
bool c_aimbot = false;
int t = 0;
int keyt;
float fcxpos;
float fcypos;
float camxpos;
float fpvectorx;
float fpvectory;
float fxpos1;
float fypos1;
float fxpos2;
float fypos2;
float fxpos2a;
float fypos2a;
float fphp;
float aa;
float ab;
float ac;
float beta;
float alpha;
float fFps = NULL;
float fLastTickCount = NULL;
float fCurrentTickCount;
float centerX = 0.0f;
float centerY = 0.0f;
float resX = 0.0f;
float resY = 0.0f;

DWORD* pTarget = (DWORD*)0xB6F3B8;//pointer of target object.
DWORD* pActor = (DWORD*)0xB6F5F0;//pointer of player actor 
DWORD* pCamera = (DWORD*)0xB6F99C;//camera pointer
float* camXpos = (float*)0xB6F258;//writeable camera Z angle 
int smooth_aim = 0;


LONG x;
LONG y;
POINT pos;
DWORD php;
DWORD xpos1;
DWORD ypos1;
DWORD xpos2;
DWORD ypos2;
DWORD pmtrx1;
DWORD pmtrx2;
DWORD pvectorx;
DWORD pvectory;
DWORD ptarget;
DWORD pped;
DWORD pId;
DWORD dwOldProtect = 0;


//SMNEKERIE//SMSM

bool RainbowHud = false;
bool mapteleport = false;
bool bEditBulletSync = false;
bool teleport_checkpoint = false;
static float misc_RainbowSpeed;
int rrspeed;
bool culoare_pusa;
//int setrotation = 0;
//wal menu
bool wallmenu = false;
//menuname
bool menuname = false;
//poormenu
bool pooraim = false;
bool poormenu = false;
bool sniperpoor2 = false;
bool deaglepoor2 = false;
bool deagletrigger2 = false;
bool riflepoor2 = false;
bool mp5poor2 = false;
bool combatpoor2 = false;
bool akpoor2 = false;
bool m4poor2 = false;
//no recoil
bool poormenu2 = false;
bool sniperpoor24 = false;
bool deaglepoor24 = false;
bool deagletrigger24 = false;
bool riflepoor24 = false;
bool mp5poor24 = false;
bool combatpoor24 = false;
bool akpoor24 = false;
bool m4poor24 = false;
//trigger menu
bool triggermenu = false;
bool sniperpoor23 = false;
bool deaglepoor23 = false;
bool deagletrigger23 = false;
bool riflepoor23 = false;
bool mp5poor23 = false;
bool combatpoor23 = false;
bool akpoor23 = false;
bool m4poor23 = false;

bool tp = false;
int cheat_spammer_delay = 1;
bool cheat_enable_spammer = false;
char cheat_spammer_text[256];
bool Mouse_Fix = false;
//nitro car
bool nitrocar = false;
//tankmode
bool tankmodecar = false;
//bool c_slap = false;
//BYTE* slap = (BYTE*)0xB6F5F0;
bool watercarvar = false;
bool Trigger = false;
bool wall = false;
bool weather = false;
bool taim = false;
bool megajumpvar = false;
//bool noreload = false;
BYTE* bjump = (BYTE*)0x969161;
bool c_bjump = false;
bool c_norecoil = false;
bool normalaim = false;
bool fake_kick = false;
bool ioxygen = false;
bool c_infRun = false;
BYTE* infRun = (BYTE*)0xB7CEE4;
bool c_GodMode = false;
BYTE* GodMode = (BYTE*)0x96916D;
bool fastrot = false;
bool fpsunlockvar = false;
bool thermalvisionvar = false;
bool infammovar = false;
DWORD* pInfo = NULL;
BYTE* ThroughWalls = NULL;
float* fDistance = NULL;
bool nop = false;
///aimbotmenu
bool aimbotmenu = false;
bool mp5checked = false;
bool akchecked = false;
bool sniperchecked = false;
bool minigunchecked = false;
bool silencedchecked = false;
bool shotgunchecked = false;
bool riflechecked = false;
bool tecchecked = false;
bool combatchecked = false;
bool m4a1checked = false;
bool deaglechecked = false;
bool panic = false;

// nu il mai gasesc pan
bool g_bwasInitialized = false;
bool m_IsGameFullyLoaded = false;
bool menuOpen = false;
bool wndproc = false;
bool* p_open = NULL;
bool recon = false;
int item = 0;
int timeset;
int weatherset;
int whsize = 5;
int setfakeping;
int setgamespeed;
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
	normalaim = false;
     Mouse_Fix = false;
	//nitro car
	 nitrocar = false;
	//tankmode
	 tankmodecar = false;
	//bool c_slap = false;
	//BYTE* slap = (BYTE*)0xB6F5F0;
	 watercarvar = false;
	 Trigger = false;
	 wall = false;
	 megajumpvar = false;
	 //bool noreload = false;
	 bjump = (BYTE*)0x969161;
	 c_bjump = false;
	 c_norecoil = false;
	 fake_kick = false;
	 ioxygen = false;
	 c_infRun = false;
	 c_GodMode = false;
	 fastrot = false;
	 fpsunlockvar = false;
	 thermalvisionvar = false;
     infammovar = false;;
	 mp5checked = false;
	 akchecked = false;
	 sniperchecked = false;
	 minigunchecked = false; 
	 silencedchecked = false;
	 shotgunchecked = false;
	 riflechecked = false;
	 tecchecked = false;
	 combatchecked = false;
	 m4a1checked = false;
	 deaglechecked = false;
	 atentat1 = false;
}


//OLEACA
char namechanger[256];
bool namech = false;


int setLocalPlayerName(const char *name)
{
	if (pSAMP->getPlayers() == NULL || pSAMP->getPlayers()->pLocalPlayer == NULL)
		return 0;

	int strlen_name = strlen(name);
	if (strlen_name == 0 || strlen_name > SAMP_ALLOWED_PLAYER_NAME_LENGTH)
		return 0;

	((void(__thiscall *) (void *, const char *name, int len)) (g_dwSAMP_Addr + 0xB290)) (&pSAMP->getPlayers()->pVTBL_txtHandler, name, strlen_name);
	return 1;
}
//?/???A($@($(#$(#(R(ERFNDF(#((#%EJTRje


//SPAMMER FMM
void addSayToChatWindow(char *msg)
{
	if (pSAMP == NULL)
		return;

	if (msg == NULL)
		return;

	if (msg == NULL)
		return;

	if (msg[0] == '/')
	{
		((void(__thiscall *) (void *_this, char *message)) (g_dwSAMP_Addr + SAMP_FUNC_SENDCMD))(pSAMP->getInput(), msg);
	}
	else
	{
		((void(__thiscall *) (void *_this, char *message)) (g_dwSAMP_Addr + SAMP_FUNC_SAY)) (pSAMP->getPlayers()->pLocalPlayer, msg);
	}
}

void say(char *text, ...)
{
	if (pSAMP == NULL)
		return;

	if (text == NULL)
		return;

	va_list ap;
	char    tmp[128];
	memset(tmp, 0, 128);

	va_start(ap, text);
	vsprintf(tmp, text, ap);
	va_end(ap);

	addSayToChatWindow(tmp);
}
//SPAMMER


SAMPFramework *pSAMP;
CD3DHook *pD3DHook;

//v2
void Boss()
{
	ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.30f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.84f, 0.01f, 0.01f, 0.59f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.53f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_CloseButton] = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
    style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
    style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    style.WindowTitleAlign = ImGuiAlign_Center;
}

void RainbowM()
{
	static float rainbow_color_redus;	//speed
	rainbow_color_redus += misc_RainbowSpeed = 0.0001 * rrspeed;
	if (rainbow_color_redus > 1.f) rainbow_color_redus = 0.f;
	DWORD rainbow_color_x = Color2::ToImColor(Color2::FromHSB(rainbow_color_redus, 1.f, 1.f));
	ImVec4 mainColorActive = Color2::ToImColor(Color2::FromHSB(rainbow_color_redus, 1.f, 1.f));
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, .78f);
	style.Colors[ImGuiCol_TextDisabled] = mainColorActive;;
	style.Colors[ImGuiCol_WindowBg] = mainColorActive;
	style.Colors[ImGuiCol_ChildWindowBg] = mainColorActive;
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = mainColorActive;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorActive;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = mainColorActive;
	style.Colors[ImGuiCol_SliderGrab] = mainColorActive;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = mainColorActive;
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Header] = mainColorActive;
	style.Colors[ImGuiCol_HeaderHovered] = mainColorActive;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
	style.Colors[ImGuiCol_Column] = ImVec4(0.15f, 0.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_ColumnHovered] = mainColorActive;
	style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGrip] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorActive;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorActive;
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorActive;
	style.Colors[ImGuiCol_TextSelectedBg] = mainColorActive;
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
	style.WindowTitleAlign = ImGuiAlign_Center;
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
	ImGui::SetNextWindowSize(ImVec2(400.f, 400.f));
	if (!ImGui::Begin("V3.4", p_open = NULL, window_flags))
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
		if (ImGui::BeginMenu("Themes"))
		{
			ImGui::PushItemWidth(125.f);
			const char* items[] = { "Default", "Rainbow" };
			ImGui::Combo("##1000", &item, items, 2);
			if (item == 0)
			{
				Boss();
			}
			if (item == 1)
			{
				RainbowM();
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
		if (ImGui::BeginMenu("Info"))
		{
			if (ImGui::Button("Info", ImVec2(125.f, 20.f)))
			{
				ImGui::OpenPopup("Info");
			}
			ImGui::SetWindowSize(ImVec2(293.f, 80.f));
			if (ImGui::BeginPopupModal("Info", p_open = NULL, window_flags_about))
			{
				ImGui::Text("CHEAT FOR SAMPCAC VERSION:");
				ImGui::Text("V.0.0.9");
				ImGui::Separator();
				ImGui::Text("LICENCE:");
				ImGui::Text("DEVELOPER: Yes");
				ImGui::Text("EXPIRED: No");
				ImGui::Separator();
				ImGui::Text("CREDITS:");
				ImGui::Separator();
				ImGui::Text("DEVELOPER :");
				ImGui::TextColored(ImColor(255, 100, 100), "NiLmeR");
				ImGui::Separator();
				ImGui::Text("CONTRIBUTOR :");
				//ImGui::Text("Serban1337");
				ImGui::Text("Ryon.SILENT");
				ImGui::Text("DarkADV");
				ImGui::Text("IMGUI BY MALWELL");
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

	if (ImGui::CollapsingHeader("WEAPON MENU"))
	{
		ImGui::Checkbox("##68", &c_aimbot); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Aimbot");
		ImGui::Checkbox("", &normalaim); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Smooth");
		ImGui::SameLine(300.f);
		if (ImGui::Button("Settings## Smooth"))
		{
			aimbotmenu = !aimbotmenu;
		}
		ImGui::Checkbox("##1", &pooraim); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Poor Aimbot");
		ImGui::SameLine(300.f);
		if (ImGui::Button("Settings##Poor Aimbot"))
		{
			poormenu = !poormenu;
		}
		ImGui::Checkbox(" Triggerbot", &Trigger);
		ImGui::SameLine(300.f);
		if (ImGui::Button("Settings## Triggerbot"))
		{
			triggermenu = !triggermenu;
		}
		ImGui::Checkbox("##2", &c_norecoil);ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "No Recoil");
		ImGui::SameLine(300.f);
		if (ImGui::Button("Settings## No Recoil"))
		{
			poormenu2 = !poormenu2;
		}
		ImGui::Checkbox("##3", &infammovar); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Infinite Ammo");

	}
	if (ImGui::CollapsingHeader("VISUAL MENU"))
	{
		ImGui::Checkbox(" Wallhack", &wall);
		ImGui::SameLine(300.f);
		if (ImGui::Button("Settings## Wallhack"))
		{
			wallmenu = !wallmenu;
		}
		ImGui::Checkbox(" Time", &taim); ImGui::SameLine(); ImGui::SliderInt("##1", &timeset, 0, 24, "TIME: %0.0f");
		ImGui::Checkbox(" Weather", &weather); ImGui::SameLine(); ImGui::SliderInt("##2", &weatherset, 0, 10, "WEATHER: %0.0f");
		ImGui::Checkbox(" Thermal Vision", &thermalvisionvar);
	}
	if (ImGui::CollapsingHeader("PLAYER MENU"))
	{
		ImGui::Checkbox("##4", &megajumpvar); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Mega Jump");
		ImGui::Checkbox("##", &c_bjump); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Mega Jump Bike");
		ImGui::Checkbox("  Infinite Run", &c_infRun);
		ImGui::Checkbox("  Infinite Oxygen", &ioxygen);
		ImGui::Checkbox("  Anti Stun", &bAntiStun);
		ImGui::Checkbox("##5", &c_GodMode); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "GodMode");
		ImGui::Checkbox("  Fast Rotation", &fastrot);
		//ImGui::SliderInt("##9234", &setrotation, 1, 100, "%.0f");
		ImGui::Checkbox("##12", &antiaim); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Anti Aim");
		ImGui::Checkbox("##10", &InvertWalk); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Upside Mode");
		//ImGui::SliderInt("##500", &setrotation, 1, 100, "%.0f")
		//ImGui::Checkbox("Auto Slap", &c_slap);
	}
	if (ImGui::CollapsingHeader("CARS MENU"))
	{
		ImGui::Checkbox("##6", &watercarvar); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Water Car");
		ImGui::Checkbox("##7", &tankmodecar); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Tank Mode");
		ImGui::Checkbox("##6261", &pilot); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Pro Diriving");
		if (pilot == true)
		{
	    *(bool*)PILOT_ADDR = true;
		}
		else
		{
			*(bool*)PILOT_ADDR = false;
		}
		ImGui::Checkbox("  Nitro All Cars", &nitrocar);
	}
	if (ImGui::CollapsingHeader("OTHER MENU"))
	{
		ImGui::Checkbox(" Mouse Fix", &Mouse_Fix);
		ImGui::Checkbox(" Fps Unlocker", &fpsunlockvar);
		ImGui::Checkbox("##12", &no_bike_fall); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Anti Bike Fall");
		ImGui::Checkbox("##8", &teleport_checkpoint); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Teleport Checkpoint F9");
		ImGui::Checkbox("##12", &tp); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Teleport Map F10");
		ImGui::Checkbox("##123", &slapper); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Slap F7");
		ImGui::Checkbox("##14", &fake_ping); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Fake Lag");
		ImGui::SameLine(320.0f);
		ImGui::PushItemWidth(65.0f);
		ImGui::SliderInt("##9234", &setfakeping, 500, 1000, "%.0f");
		ImGui::Checkbox("##142", &gamespeedovar1); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "Game Speed");
		ImGui::SameLine(320.0f);
		ImGui::PushItemWidth(65.0f);
		ImGui::SliderInt("##92342", &setgamespeed, 1, 1000, "%.0f");
		if (ImGui::Button("Spawn ##5345"))
		{
			if (pSAMP == NULL)
				return;

			((void(__thiscall *) (void *_this)) (g_dwSAMP_Addr + 0x3EC0)) (pSAMP->getPlayers()->pLocalPlayer);
			((void(__thiscall *) (void *_this)) (g_dwSAMP_Addr + 0x3AD0)) (pSAMP->getPlayers()->pLocalPlayer);
		}
		ImGui::SameLine();
		if (ImGui::Button("Fake Death"))
		{
			if (pSAMP == NULL)
				return;
			((void(__thiscall *) (void *)) (g_dwSAMP_Addr + 0x55E0))
				(pSAMP->getPlayers()->pLocalPlayer);
		}
		ImGui::PushItemWidth(100.0f);
		ImGui::InputText("SPAMMER TEXT", cheat_spammer_text, sizeof(cheat_spammer_text));
		ImGui::PushItemWidth(95.0f);
	    ImGui::InputInt("Delay (in ms)", &cheat_spammer_delay);

		if (cheat_enable_spammer)
		{
			if (ImGui::Button("Stop")) cheat_enable_spammer = false;
		}
		else
		{
			if (ImGui::Button("Start")) cheat_enable_spammer = true;
		}
	}
	if (ImGui::CollapsingHeader("RAINBOW MENU"))
	{
		if (ImGui::Button("Sync All Rainbow"))
		{
			RainbowHud = true;
			culoare_pusa = true;
			rainbowmenu = true;
			tintarainbow = true;
			RainbowHeadLights = true;
			RainbowRadar = true;

		}
		ImGui::Checkbox("Rainbow Crosshair", &tintarainbow);
		ImGui::Checkbox(" Rainbow Hud", &RainbowHud);
		ImGui::Checkbox(" Radar Rainbow", &RainbowRadar);
		ImGui::Checkbox(" Rainbow Car Lights", &RainbowHeadLights);
		ImGui::Checkbox(" Rainbow Car", &culoare_pusa);
		ImGui::Checkbox(" Rainbow Menu", &rainbowmenu);
		ImGui::PushItemWidth(230.0f);
		ImGui::SliderInt("Speed", &rrspeed, 0, 100, "%.0f%%");
	}
	if (ImGui::CollapsingHeader("DEVELOPER MENU"))
	{
		ImGui::Checkbox("##9", &atentat1); ImGui::SameLine(); ImGui::TextColored(ImColor(255, 100, 100), "AtentatBOT");
		ImGui::Checkbox(" Fake Kick", &fake_kick);
		ImGui::Checkbox(" LOCAL NICK CHANGE", &namech);
		ImGui::SameLine(300.f);
		if (ImGui::Button("Settings## Change"))
		{
			menuname = !menuname;
		}
	}
	ImGui::End();
	//poor menu
	if (poormenu)
	{
		ImGui::SetNextWindowSize(ImVec2(310.0f, 300.0f));
		if (ImGui::Begin("Poor Aimbot Settings", p_open = NULL, window_flags))
		{
			ImGui::Checkbox("Deagle", &deaglepoor2);
			ImGui::Checkbox("M4", &m4poor2);
			ImGui::Checkbox("AK47", &akpoor2);
			ImGui::Checkbox("Rifle", &riflepoor2);
			ImGui::Checkbox("MP5", &mp5poor2);
			ImGui::Checkbox("Combat Shotgun", &combatpoor2);
			ImGui::Text(" ");
			if (ImGui::Button("Hide", ImVec2(75.f, 20.f)))
			{
				poormenu = !poormenu;
			}
			ImGui::End();
		}
	}
	//aimbotmenu
	if (aimbotmenu)
	{
		ImGui::SetNextWindowSize(ImVec2(310.0f, 300.0f));
		if (ImGui::Begin("Smooth Settings", p_open = NULL, window_flags))
		{
			ImGui::Checkbox("Deagle", &deaglechecked);
			ImGui::Checkbox("SD Pistol", &silencedchecked);
			ImGui::Checkbox("M4", &m4a1checked);
			ImGui::Checkbox("AK47", &akchecked);
			ImGui::Checkbox("Rifle", &riflechecked);
			ImGui::Checkbox("MP5", &mp5checked);
			ImGui::Checkbox("Combat Shotgun", &combatchecked);
			ImGui::Checkbox("ShotGun", &shotgunchecked);
			ImGui::Checkbox("TEC", &tecchecked);
			ImGui::Checkbox("Minigun", &minigunchecked);
			ImGui::Checkbox("Rifle", &riflechecked);
			ImGui::Text(" ");
			if (ImGui::Button("Hide", ImVec2(75.f, 20.f)))
			{
				aimbotmenu = !aimbotmenu;
			}
			ImGui::End();
		}
	}
	//trigger menu
	if (triggermenu)
	{
		ImGui::SetNextWindowSize(ImVec2(310.0f, 300.0f));
		if (ImGui::Begin("Trigger Settings", p_open = NULL, window_flags))
		{
			ImGui::Checkbox("Deagle", &deaglepoor23);
			ImGui::Checkbox("M4", &m4poor23);
			ImGui::Checkbox("AK47", &akpoor23);
			ImGui::Checkbox("Rifle", &riflepoor23);
			ImGui::Checkbox("MP5", &mp5poor23);
			ImGui::Checkbox("Combat Shotgun", &combatpoor23);
			ImGui::Text(" ");
			if (ImGui::Button("Hide", ImVec2(75.f, 20.f)))
			{
				triggermenu = !triggermenu;
			}
			ImGui::End();
		}
	}
	//recoil menu
	if (poormenu2)
	{
		ImGui::SetNextWindowSize(ImVec2(310.0f, 300.0f));
		if (ImGui::Begin("No Recoil Settings", p_open = NULL, window_flags))
		{
			ImGui::Checkbox("Deagle", &deaglepoor24);
			ImGui::Checkbox("M4", &m4poor24);
			ImGui::Checkbox("AK47", &akpoor24);
			ImGui::Checkbox("Rifle", &riflepoor24);
			ImGui::Checkbox("MP5", &mp5poor24);
			ImGui::Checkbox("Combat Shotgun", &combatpoor24);
			ImGui::Text(" ");
			if (ImGui::Button("Hide", ImVec2(75.f, 20.f)))
			{
				poormenu2 = !poormenu2;
			}
			ImGui::End();
		}
	}
	if (wallmenu)
	{
		ImGui::SetNextWindowSize(ImVec2(210.0f, 200.0f));
		if (ImGui::Begin("WallHack Settings", p_open = NULL, window_flags))
		{
			ImGui::SliderInt("##5231", &whsize, 0, 100, ("Range: %0.0f"));
			ImGui::Text(" ");
			if (ImGui::Button("Hide", ImVec2(75.f, 20.f)))
			{
				wallmenu = !wallmenu;
			}
			ImGui::End();
		}
	}
	if (menuname)
	{
		ImGui::SetNextWindowSize(ImVec2(220.0f, 210.0f));
		if (ImGui::Begin("Local Nick Settings", p_open = NULL, window_flags))
		{
			ImGui::InputText("CHANGE", namechanger, sizeof(namechanger));
			ImGui::Text(" ");
			if (ImGui::Button("Hide", ImVec2(75.f, 20.f)))
			{
				menuname = !menuname;
			}
			ImGui::End();
		}
	}
}

void mainThread(void *pvParams)
{
	
}

void Fakekick()
{
	if (fake_kick)
	{
		unsigned int func = (unsigned int)GetModuleHandleA("samp.dll") + 0x58C0;//g_dwSAMP_Addr + 0x4D70
		__asm {
			PUSH 00
			PUSH 0xFFFF
			CALL func
		}
	}
}

void InfOxygen()
{
	if (ioxygen)
	{
		everything();
		DWORD infiniteoxygenAddr = 0x96916E;
		DWORD infiniteoxygen = 1;

		WriteProcessMemory(handle, (LPVOID)infiniteoxygenAddr, &infiniteoxygen, sizeof(infiniteoxygen), 0);
	}
}

void fastrotation()
{
	if (fastrot)
	{
		DWORD cped = 0;
		ReadProcessMemory(handle, (LPCVOID)0xB6F5F0, &cped, sizeof(DWORD), 0);
		DWORD moveAddr = cped + 0x560;
		DWORD move = 0; ReadProcessMemory(handle, (LPCVOID)moveAddr, &move, sizeof(move), 0);
		if (move == 1103626240) {} if (move >= 1089470463) {
			DWORD ceva = 1103626240;
			WriteProcessMemory(handle, (LPVOID)moveAddr, &ceva, sizeof(ceva), 0);
		}
	}
}

void functions()
{
	if (namech)
	{
		if (strlen(namechanger))
		{

			{
				setLocalPlayerName(namechanger);
			}
		}

	}

	if (no_bike_fall)
	{
		DWORD bikefall = 1;
		ReadProcessMemory(handle, (LPVOID)(0x004BA3B9), &bikefall, sizeof(bikefall), 0);

		if (bikefall != 239593)
		{
			bikefall = 239593;
			WriteProcessMemory(handle, (LPVOID)(0x004BA3B9), &bikefall, sizeof(bikefall), 0);
		}
	}

	if (!no_bike_fall)
	{
		DWORD bikefall = 1;
		ReadProcessMemory(handle, (LPVOID)(0x004BA3B9), &bikefall, sizeof(bikefall), 0);

		if (bikefall != 61244431)
		{
			bikefall = 61244431;
			WriteProcessMemory(handle, (LPVOID)(0x004BA3B9), &bikefall, sizeof(bikefall), 0);
		}
	}

	if (slapper)
	{
		if (!tick_done)
		{
			tick = GetTickCount64();
			tick_done = true;
		}

		if (GetAsyncKeyState(VK_F7))
		{

			if (GetTickCount64() - tick > 100) // every 100 ms + 5´meter height
			{

				DWORD ped = *(DWORD*)(0xB6F5F0);



				DWORD matrix = *(DWORD*)(ped + 0x14);
				float *zcrd = (float*)(matrix + 0x38);


				float zcrd2 = *(float*)(matrix + 0x38);

				*zcrd = zcrd2 + 6.0f;

				tick_done = false;
			}

		}

	}

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

	if (fake_ping)
	{
		DWORD fakeping = 1;
		ReadProcessMemory(handle, (LPVOID)((DWORD)samp + 0xEC0A8), &fakeping, sizeof(fakeping), 0);

		if (fakeping != setfakeping)
		{
			fakeping = setfakeping;
			WriteProcessMemory(handle, (LPVOID)((DWORD)samp + 0xEC0A8), &fakeping, sizeof(fakeping), 0);
		}
	}
	if (!fake_ping)
	{
		DWORD fakeping = 1;
		ReadProcessMemory(handle, (LPVOID)((DWORD)samp + 0xEC0A8), &fakeping, sizeof(fakeping), 0);

		if (fakeping != 100)
		{
			fakeping = 100;
			WriteProcessMemory(handle, (LPVOID)((DWORD)samp + 0xEC0A8), &fakeping, sizeof(fakeping), 0);
		}
	}
	if (gamespeedovar1)
	{
		*(float*)(0xB7CB64) = setgamespeed;
	}
	else
	{
		*(float*)(0xB7CB64);
	}
	if (bAntiStun)
	{
		if (!pSAMP->getPlayers())
			return;
		if (!bAntiStunned)
		{
			// but it doesn't work only for sniper
			DWORD dwStunAddr = *(DWORD*)0x00B6F5F0;
			*(BYTE*)(dwStunAddr + 0x478) = 4;
		}

		// for sniper stun
		float fRate = 100.f;
		bAntiStunned = true;
	}
	else
	{
		if (bAntiStunned)
		{
			DWORD dwStunAddr = *(DWORD*)0x00B6F5F0;
			*(BYTE*)(dwStunAddr + 0x478) = 0;

			float fRate = 1.f;
			bAntiStunned = false;
		}
	}
	if (tp)
	{
		if (GetAsyncKeyState(VK_F10))
		{
			DWORD mapx, mapy, cpz, cped, cpon, matrix;
			mapx = *(DWORD*)0xBA67B8;
			mapy = *(DWORD*)0xBA67BC;
			cped = *(DWORD*)0xB6F5F0;
			matrix = *(DWORD*)(cped + 0x14);

			*(DWORD*)(matrix + 0x30) = mapx;
			*(DWORD*)(matrix + 0x34) = mapy;
		}
	}

	if (teleport_checkpoint)
	{
		if (GetAsyncKeyState(VK_F10))
		{
			int cpx, cpy, cpz, cped, matrix, cpon;
			ReadProcessMemory(handle, (LPVOID)0xC7DEC8, &cpx, sizeof(cpx), NULL);
			ReadProcessMemory(handle, (LPVOID)0xC7DECC, &cpy, sizeof(cpy), NULL);
			ReadProcessMemory(handle, (LPVOID)0xC7DED0, &cpz, sizeof(cpz), NULL);
			ReadProcessMemory(handle, (LPCVOID)0xB6F5F0, &cped, sizeof(cped), NULL);
			ReadProcessMemory(handle, (LPCVOID)(cped + 0x14), &matrix, sizeof(matrix), NULL);
			ReadProcessMemory(handle, (LPVOID)0xC7DEEA, &cpon, sizeof(cpon), NULL);
			if (cpon != 0) {
				WriteProcessMemory(handle, (LPVOID)(matrix + 0x30), &cpx, sizeof(cpx), NULL);
				WriteProcessMemory(handle, (LPVOID)(matrix + 0x34), &cpy, sizeof(cpy), NULL);
				WriteProcessMemory(handle, (LPVOID)(matrix + 0x38), &cpz, sizeof(cpz), NULL);
			}

		}
	}

	if (pooraim)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			int wID;
			wID = *(BYTE*)0xBAA410;
			DWORD* pActor = (DWORD*)0xB6F5F0;//pointer of player actor
			DWORD* pPed = (DWORD*)((*pActor) + 0x79C);//pointer to target player
			DWORD* pMtrx2 = (DWORD*)((*pPed) + 0x14);//matrix of target player
			float* playerHP = (float*)((*pPed) + 0x540);//health of target player
			DWORD* pMtrx1 = (DWORD*)((*pActor) + 0x14);//matrix of player actor

			if (wID == 24 && deaglepoor2 || wID == 31 && m4poor2 || wID == 30 && akpoor2 || wID == 27 && combatpoor2 || wID == 33 && riflepoor2 || wID == 29 && mp5poor2 || wID == 34 && sniperpoor2)
			{
				if (deaglepoor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}

				if (m4poor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}
				if (riflepoor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}

				if (akpoor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}

				if (combatpoor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}

				if (mp5poor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}

				if (sniperpoor2)
				{
					if (*pPed > 0)
					{

						if (*playerHP > 0.0f)
						{
							float* x = (float*)((*pMtrx1) + 0x30);//X position Ped
							float* y = (float*)((*pMtrx1) + 0x34);//Y position Ped
							float* z = (float*)((*pMtrx1) + 0x38);//Z position Ped


							float* x1 = (float*)((*pMtrx2) + 0x30);//X position Target
							float* y1 = (float*)((*pMtrx2) + 0x34);//Y position Target
							float* z1 = (float*)((*pMtrx2) + 0x38);//Z position Target
							float* RotAngle = (float*)((*pActor) + 0x558);//health of target player
							float Xwiping = (float)*x + 2 * (float)cos(*RotAngle + 1.48353F);
							float Ywiping = (float)*y + 2 * (float)sin(*RotAngle + 1.48353F);
							float Zwiping = (float)*z + 0.5F;
							*x1 = (float)Xwiping;
							*y1 = (float)Ywiping;
							*z1 = (float)Zwiping;
						}
					}
				}
			}
		}
	}
     		
	if (cheat_enable_spammer)
	{
		if (strlen(cheat_spammer_text))
		{
			if (cheat_spammer_delay)
			{
				static int sent = 0;

				if ((GetTickCount() - sent) >= cheat_spammer_delay)
				{
					say(cheat_spammer_text);
					sent = GetTickCount();
				}
			}
			else
			{
				say(cheat_spammer_text);
			}
		}
	}

	//WaterCar
	// start watercar
	if (watercarvar)
	{
		everything();
		DWORD watercarAddr = 0x6C2759;
		DWORD watercar = 1;
		ReadProcessMemory(handle, (LPVOID)watercarAddr, &watercar, sizeof(watercar), 0);

		watercar = 1;
		WriteProcessMemory(handle, (LPVOID)watercarAddr, &watercar, sizeof(watercar), 0);
		Sleep(10);

	}
	// stop watercar
	if (!watercarvar)
	{
		everything();
		DWORD watercarAddr = 0x6C2759;
		DWORD watercar = 0;
		ReadProcessMemory(handle, (LPVOID)watercarAddr, &watercar, sizeof(watercar), 0);

		if (watercar = 1)
		{
			watercar = 0;
			WriteProcessMemory(handle, (LPVOID)watercarAddr, &watercar, sizeof(watercar), 0);
			Sleep(10);
		}

	}

	//tankmode
	if (tankmodecar)
	{
		everything();
		DWORD tankmodeAddr = 0x969164;
		DWORD tankmode = 1;
		ReadProcessMemory(handle, (LPVOID)tankmodeAddr, &tankmode, sizeof(tankmode), 0);

		tankmode = 1;
		WriteProcessMemory(handle, (LPVOID)tankmodeAddr, &tankmode, sizeof(tankmode), 0);
		Sleep(10);

	}
	// stop tank
	if (!tankmodecar)
	{
		everything();
		DWORD tankmodeAddr = 0x969164;
		DWORD tankmode = 0;
		ReadProcessMemory(handle, (LPVOID)tankmodeAddr, &tankmode, sizeof(tankmode), 0);

		if (tankmode = 1)
		{
			tankmode = 0;
			WriteProcessMemory(handle, (LPVOID)tankmodeAddr, &tankmode, sizeof(tankmode), 0);
			Sleep(10);
		}

	}
	//nitro
	if (nitrocar)
	{
		everything();
		DWORD nitromodeAddr = 0x969165;
		DWORD nitromode = 1;
		ReadProcessMemory(handle, (LPVOID)nitromodeAddr, &nitromode, sizeof(nitromode), 0);

		nitromode = 1;
		WriteProcessMemory(handle, (LPVOID)nitromodeAddr, &nitromode, sizeof(nitromode), 0);
		Sleep(10);

	}
	// stop nitro
	if (!nitrocar)
	{
		everything();
		DWORD nitromodeAddr = 0x969165;
		DWORD nitromode = 0;
		ReadProcessMemory(handle, (LPVOID)nitromodeAddr, &nitromode, sizeof(nitromode), 0);

		if (nitromode = 1)
		{
			nitromode = 0;
			WriteProcessMemory(handle, (LPVOID)nitromodeAddr, &nitromode, sizeof(nitromode), 0);
			Sleep(10);
		}

	}

	// TRIGGERBOT
	if (Trigger)
	{

		int rem[5];
		int wID;
		wID = *(BYTE*)0xBAA410;
		rem[0] = *(int *)0xB6F3B8;
		rem[1] = rem[0];
		rem[1] += 0x79C;
		if (wID == 24 && deaglepoor23 || wID == 31 && m4poor23 || wID == 30 && akpoor23 || wID == 27 && combatpoor23 || wID == 33 && riflepoor23 || wID == 29 && mp5poor23 || wID == 34 && sniperpoor23)
		{
			if (deaglepoor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
			if (m4poor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
			if (akpoor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
			if (combatpoor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
			if (riflepoor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
			if (mp5poor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
			if (sniperpoor23)
			{
				if (*(int *)rem[1] > 0)
				{
					INPUT    Input = { 0 };
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &Input, sizeof(INPUT));
					Sleep(100);
					ZeroMemory(&Input, sizeof(INPUT));
					Input.type = INPUT_MOUSE;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &Input, sizeof(INPUT));
				}
			}
		}
	}
	

	// inf ammo
	if (infammovar)
	{
		everything();
		DWORD infiniteammoAddr = 0x969178;
		DWORD infiniteammo3 = 1;
		WriteProcessMemory(handle, (LPVOID)infiniteammoAddr, &infiniteammo3, sizeof(infiniteammo3), 0);
	}

	if (!infammovar)
	{
		everything();
		DWORD infiniteammoAddr = 0x969178;
		DWORD infiniteammo3 = 0;
		WriteProcessMemory(handle, (LPVOID)infiniteammoAddr, &infiniteammo3, sizeof(infiniteammo3), 0);

		infiniteammo3 = 0;
		Sleep(10);

	}
	if (thermalvisionvar)
	{
		everything();
		DWORD thermalvisionAddr = 0xC402B8;
		DWORD thermalvision = 1;

		ReadProcessMemory(handle, (LPCVOID)thermalvisionAddr, &thermalvision, sizeof(thermalvision), 0);

		thermalvision = 1;
		DWORD valuetherm = 256;
		WriteProcessMemory(handle, (LPVOID)thermalvisionAddr, &valuetherm, sizeof(valuetherm), 0);
		Sleep(10);

	}
	//stop thermal
	if (!thermalvisionvar)
	{
		everything();
		DWORD thermalvisionAddr = 0xC402B8;
		DWORD thermalvision = 0;

		ReadProcessMemory(handle, (LPCVOID)thermalvisionAddr, &thermalvision, sizeof(thermalvision), 0);

		thermalvision = 0;
		DWORD valuetherm = 0;
		WriteProcessMemory(handle, (LPVOID)thermalvisionAddr, &thermalvision, sizeof(valuetherm), 0);

	}
	if (c_norecoil)
	{
		everything();
		int wID;
		wID = *(BYTE*)0xBAA410;
		DWORD norecoilAddr = 0xB7CDC8;
		DWORD norecoil = 1;
		if (wID == 24 && deaglepoor24 || wID == 31 && m4poor24 || wID == 30 && akpoor24 || wID == 27 && combatpoor24 || wID == 33 && riflepoor24 || wID == 29 && mp5poor24)
		{
			if (m4poor24)
			{

				ReadProcessMemory(handle, (LPCVOID)norecoilAddr, &norecoil, sizeof(norecoil), 0);

				norecoil = 1;
				DWORD valuetherm = 1.074754357;
				WriteProcessMemory(handle, (LPVOID)norecoilAddr, &valuetherm, sizeof(valuetherm), 0);
				Sleep(10);
			}
			if (deaglepoor24)
			{

				ReadProcessMemory(handle, (LPCVOID)norecoilAddr, &norecoil, sizeof(norecoil), 0);

				norecoil = 1;
				DWORD valuetherm = 1.074754357;
				WriteProcessMemory(handle, (LPVOID)norecoilAddr, &valuetherm, sizeof(valuetherm), 0);
				Sleep(10);
			}
			if (akpoor24)
			{

				ReadProcessMemory(handle, (LPCVOID)norecoilAddr, &norecoil, sizeof(norecoil), 0);

				norecoil = 1;
				DWORD valuetherm = 1.074754357;
				WriteProcessMemory(handle, (LPVOID)norecoilAddr, &valuetherm, sizeof(valuetherm), 0);
				Sleep(10);
			}
			if (combatpoor24)
			{

				ReadProcessMemory(handle, (LPCVOID)norecoilAddr, &norecoil, sizeof(norecoil), 0);

				norecoil = 1;
				DWORD valuetherm = 1.074754357;
				WriteProcessMemory(handle, (LPVOID)norecoilAddr, &valuetherm, sizeof(valuetherm), 0);
				Sleep(10);
			}
			if (riflepoor24)
			{

				ReadProcessMemory(handle, (LPCVOID)norecoilAddr, &norecoil, sizeof(norecoil), 0);

				norecoil = 1;
				DWORD valuetherm = 1.074754357;
				WriteProcessMemory(handle, (LPVOID)norecoilAddr, &valuetherm, sizeof(valuetherm), 0);
				Sleep(10);
			}
			if (mp5poor24)
			{

				ReadProcessMemory(handle, (LPCVOID)norecoilAddr, &norecoil, sizeof(norecoil), 0);

				norecoil = 1;
				DWORD valuetherm = 1.074754357;
				WriteProcessMemory(handle, (LPVOID)norecoilAddr, &valuetherm, sizeof(valuetherm), 0);
				Sleep(10);
			}
		}
	}

	if (wall)
	{
		pInfo = (DWORD*)(g_dwSAMP_Addr + SAMP_INFO);
		while (*pInfo == 0) Sleep(1000);
		while (*(DWORD*)(*pInfo + SAMP_SETTINGS) == 0) Sleep(1000);
		ThroughWalls = (BYTE*)(*(DWORD*)(*pInfo + SAMP_SETTINGS) + 0x2F);
		fDistance = (float*)((DWORD*)(*(DWORD*)(*pInfo + SAMP_SETTINGS) + 0x27));

		DWORD OldProt;
		VirtualProtect((LPVOID)ThroughWalls, 0x100, PAGE_EXECUTE_READWRITE, &OldProt);
		VirtualProtect((LPVOID)fDistance, 0x100, PAGE_EXECUTE_READWRITE, &OldProt);

		if (*ThroughWalls != 512)
		{

			*fDistance = (float)whsize * 15;
			*ThroughWalls = 512;
		}

		if (GetAsyncKeyState(VK_F8))
		{
			*fDistance = 70;
			Sleep(100);
			*ThroughWalls = 513;
		}
	}
	else
	{
		pInfo = (DWORD*)(g_dwSAMP_Addr + SAMP_INFO);
		while (*pInfo == 0) Sleep(1000);
		while (*(DWORD*)(*pInfo + SAMP_SETTINGS) == 0) Sleep(1000);
		ThroughWalls = (BYTE*)(*(DWORD*)(*pInfo + SAMP_SETTINGS) + 0x2F);
		fDistance = (float*)((DWORD*)(*(DWORD*)(*pInfo + SAMP_SETTINGS) + 0x27));

		DWORD OldProt;
		VirtualProtect((LPVOID)ThroughWalls, 0x100, PAGE_EXECUTE_READWRITE, &OldProt);
		VirtualProtect((LPVOID)fDistance, 0x100, PAGE_EXECUTE_READWRITE, &OldProt);

		if (*ThroughWalls != 513)
		{

			*fDistance = 70;
			*ThroughWalls = 513;
		}
	}
	// FPS UNLOCKER
	if (fpsunlockvar)
	{
		everything();
		DWORD fps = 0;
		ReadProcessMemory(handle, (LPCVOID)((DWORD)samp + 0x9D9D0), &fps, sizeof(fps), 0);

		if (fps != 1347550997)
		{
			DWORD pFps = 1347550997;
			WriteProcessMemory(handle, (LPVOID)((DWORD)samp + 0x9D9D0), &pFps, sizeof(pFps), 0);

		}
	}

	//FPS UNLOCKER STOP
	if (!fpsunlockvar)
	{
		everything();
		DWORD fps = 0;
		ReadProcessMemory(handle, (LPCVOID)((DWORD)samp + 0x9D9D0), &fps, sizeof(fps), 0);

		if (fps == 1347550997)
		{
			DWORD pFps = 1347550997;
			WriteProcessMemory(handle, (LPVOID)((DWORD)samp + 0x9D9D0), &pFps, sizeof(pFps), 0);

		}
	}

	// Infinite oxygen
	// start oxygen
	if (ioxygen)
	{
		everything();
		DWORD infiniteoxygenAddr = 0x96916E;
		DWORD infiniteoxygen = 1;

		WriteProcessMemory(handle, (LPVOID)infiniteoxygenAddr, &infiniteoxygen, sizeof(infiniteoxygen), 0);
	}

	// stop oxygen
	if (!ioxygen)
	{
		everything();
		DWORD infiniteoxygenAddr = 0x96916E;
		DWORD infiniteoxygen = 0;

		WriteProcessMemory(handle, (LPVOID)infiniteoxygenAddr, &infiniteoxygen, sizeof(infiniteoxygen), 0);
	}

	// INFINITE RUN
	if (c_infRun)
	{

		*infRun = 1;
		c_infRun = true;

	}
	else {
		*infRun = 0;
		c_infRun = false;
	}

	if (c_aimbot)
	{
		c_aimbot = true;

		ReadProcessMemory(GetCurrentProcess(), (LPCVOID)0xB6F5F0, &gpoint, 4, 0);

		if ((gpoint > 0) && (t == 0))
		{
			t = 1;
		}
		if (gpoint > 0)
		{
			pmtrx1 = gpoint + 0x14;
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)pmtrx1, &pmtrx1, 4, 0);
			xpos1 = pmtrx1 + 0x30;
			ypos1 = pmtrx1 + 0x34;
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)xpos1, &fxpos1, 4, 0);
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ypos1, &fypos1, 4, 0);
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)0xB6F9CC, &fcxpos, 4, 0);
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)0xB6F9D0, &fcypos, 4, 0);
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)0xB6F3B8, &ptarget, 4, 0);
			pped = ptarget + 0x79C;
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)pped, &pped, 4, 0);

			if (pped > 0)
			{
				pvectorx = pped + 0x44;
				pvectory = pped + 0x48;
				ReadProcessMemory(GetCurrentProcess(), (LPCVOID)pvectorx, &fpvectorx, 4, 0);
				ReadProcessMemory(GetCurrentProcess(), (LPCVOID)pvectory, &fpvectory, 4, 0);
				pmtrx2 = pped + 0x14;
				ReadProcessMemory(GetCurrentProcess(), (LPCVOID)pmtrx2, &pmtrx2, 4, 0);
				xpos2 = pmtrx2 + 0x30;
				ypos2 = pmtrx2 + 0x34;
				ReadProcessMemory(GetCurrentProcess(), (LPCVOID)xpos2, &fxpos2, 4, 0);
				ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ypos2, &fypos2, 4, 0);
				php = pped + 0x540;
				ReadProcessMemory(GetCurrentProcess(), (LPCVOID)php, &fphp, 4, 0);
				if (fphp > 0)
				{
					fxpos2a = fxpos2;
					fypos2a = fypos2;
					aa = fabs(fcxpos - fxpos2);
					ab = fabs(fcypos - fypos2);
					ac = sqrt(aa*aa + ab * ab);
					alpha = asin(aa / ac);
					beta = acos(aa / ac);
					if ((fxpos1 > fxpos2) && (fypos1 < fypos2))
					{
						beta = -beta;
					}
					if ((fxpos1 > fxpos2) && (fypos1 > fypos2))
					{
						beta = beta;
					}
					if ((fxpos1 < fxpos2) && (fypos1 > fypos2))
					{
						beta = (alpha + (3.14 / 2));
					}
					if ((fxpos1 < fxpos2) && (fypos1 < fypos2))
					{
						beta = (-alpha - (3.14 / 2));
					}
					camxpos = beta + 0.0389;
					ReadProcessMemory(GetCurrentProcess(), (LPCVOID)0xB7347A, &keyt, 4, 0);
					if (keyt > 0)
					{
						WriteProcessMemory(GetCurrentProcess(), (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL);
					}
				}
			}
		}
	}
	else {
		c_aimbot = false;
	}

	if (normalaim)
	{
		float fcxpos;
		float fcypos;
		float camxpos;
		float camypos;
		float fpvectorx;
		float fpvectory;
		float fxpos1;
		float fypos1;
		float fzpos1;
		float fxpos2;
		float fypos2;
		float fzpos2;
		float fxpos2a;
		float fypos2a;
		float fzpos2a;
		float fphp;
		float aa;
		float ab;
		float ac;
		float beta;
		float alpha;
		int t;
		int wID;
		int keyt;
		t = 0;

		DWORD php;
		DWORD xpos1;
		DWORD ypos1;
		DWORD zpos1;
		DWORD xpos2;
		DWORD ypos2;
		DWORD zpos2;
		DWORD pmtrx1;
		DWORD pmtrx2;
		DWORD pvectorx;
		DWORD pvectory;
		DWORD gpoint;
		DWORD ptarget;
		DWORD pped;
		DWORD pId;
		ReadProcessMemory(handle, (LPCVOID)0xBAA410, &wID, sizeof(int), 0);
		ReadProcessMemory(handle, (LPCVOID)0xB6F5F0, &gpoint, 4, 0);



		if (gpoint > 0) {
			pmtrx1 = gpoint + 0x14; // location pointer of player XYZ
			ReadProcessMemory(handle, (LPCVOID)pmtrx1, &pmtrx1, 4, 0);

			xpos1 = pmtrx1 + 0x30; // x position of player
			ypos1 = pmtrx1 + 0x34; // y position of player
			zpos1 = pmtrx1 + 0x38; // z position of player

			ReadProcessMemory(handle, (LPCVOID)xpos1, &fxpos1, 4, 0);
			ReadProcessMemory(handle, (LPCVOID)ypos1, &fypos1, 4, 0);
			ReadProcessMemory(handle, (LPCVOID)zpos1, &fzpos1, 4, 0);

			ReadProcessMemory(handle, (LPCVOID)0xB6F9CC, &fcxpos, 4, 0); // not really sure
			ReadProcessMemory(handle, (LPCVOID)0xB6F9D0, &fcypos, 4, 0); // not really sure

			ReadProcessMemory(handle, (LPCVOID)0xB6F3B8, &ptarget, 4, 0); // pointer to target

			pped = ptarget + 0x79C; // our current target
			ReadProcessMemory(handle, (LPCVOID)pped, &pped, 4, 0);

			if (pped > 0)
			{
				pvectorx = pped + 0x44; // border (x) (hitbox)
				pvectory = pped + 0x48; // border (y) (hitbox)

				ReadProcessMemory(handle, (LPCVOID)pvectorx, &fpvectorx, 4, 0);
				ReadProcessMemory(handle, (LPCVOID)pvectory, &fpvectory, 4, 0);

				pmtrx2 = pped + 0x14; // pointer to XYZ of target
				ReadProcessMemory(handle, (LPCVOID)pmtrx2, &pmtrx2, 4, 0);

				xpos2 = pmtrx2 + 0x30; // x position (of target)
				ypos2 = pmtrx2 + 0x34; // y position (of target)
				zpos2 = pmtrx2 + 0x38; //  position (of target)

				ReadProcessMemory(handle, (LPCVOID)xpos2, &fxpos2, 4, 0);
				ReadProcessMemory(handle, (LPCVOID)ypos2, &fypos2, 4, 0);
				ReadProcessMemory(handle, (LPCVOID)zpos2, &fzpos2, 4, 0);

				php = pped + 0x540; // ped health
				ReadProcessMemory(handle, (LPCVOID)php, &fphp, 4, 0);

				float theta, dist;
				if (fphp > 0) // if ped health > 0
				{
					//dist = sqrt((float)(xpos2-xpos1)*(xpos2-xpos1) + (ypos2-ypos1)*(ypos2-ypos1) + (zpos2-zpos1)*(zpos2-zpos1));

					dist = sqrt((fxpos2 - fxpos1)*(fxpos2 - fxpos1) + (fypos2 - fypos1)*(fypos2 - fypos1) + (fzpos2 - fzpos1)*(fzpos2 - fzpos1));
					theta = asin((fzpos2 - fzpos1) / dist);
					theta -= (90 / (3.14 * 180));

					fxpos2a = fxpos2;
					fypos2a = fypos2;

					aa = fabs(fcxpos - fxpos2);
					ab = fabs(fcypos - fypos2);
					ac = sqrt(aa*aa + ab * ab);

					alpha = asin(aa / ac);
					beta = acos(aa / ac);

					if ((fxpos1 > fxpos2) && (fypos1 < fypos2))
					{
						beta = -beta;
					}
					if ((fxpos1 > fxpos2) && (fypos1 > fypos2))
					{
						beta = beta;
					}
					if ((fxpos1 < fxpos2) && (fypos1 > fypos2))
					{
						beta = (alpha + (3.14 / 2));
					}
					if ((fxpos1 < fxpos2) && (fypos1 < fypos2))
					{
						beta = (-alpha - (3.14 / 2));
					}

					if (wID == 24 && deaglechecked) {
						camxpos = beta + 0.0410;
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 31 && m4a1checked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 27 && combatchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 32 && tecchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 33 && riflechecked){
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 25 && shotgunchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 23 && silencedchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 38 && minigunchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 34 && sniperchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 30 && akchecked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
					if (wID == 29 && mp5checked) {
						camxpos = beta + 0.0300 + (dist / 14000);
						camypos = theta + 0.0389 + dist / 3000;
						WriteProcessMemory(handle, (LPVOID)0xB6F258, (LPVOID)&camxpos, 4, NULL); // write X-coordinate vector to X-coordinate vector of camera                        
					}
				}
			}
		}
	}

}


HRESULT __stdcall Hooked_Present(IDirect3DDevice9 *pDevice, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion)
{
	static float rainbow_color_redus;	//speed
	rainbow_color_redus += misc_RainbowSpeed = 0.0001 * rrspeed;
	if (rainbow_color_redus > 1.f) rainbow_color_redus = 0.f;
	DWORD rainbow_color_x = Color2::ToImColor(Color2::FromHSB(rainbow_color_redus, 1.f, 1.f));
	ImVec4 mainColorActive = Color2::ToImColor(Color2::FromHSB(rainbow_color_redus, 1.f, 1.f));

	if (RainbowHud)
	{
		*(DWORD*)(0xBAB22C) = rainbow_color_x;
		*(DWORD*)(0xBAB230) = rainbow_color_x;
		*(DWORD*)(0xBAB234) = rainbow_color_x;
		*(DWORD*)(0xBAB238) = rainbow_color_x;
		*(DWORD*)(0xBAB23C) = rainbow_color_x;
		*(DWORD*)(0xBAB260) = rainbow_color_x;
		*(DWORD*)(0xBAB240) = rainbow_color_x;
		*(DWORD*)(0xBAB244) = rainbow_color_x;
		*(DWORD*)(0xBAB248) = rainbow_color_x;
		*(DWORD*)(0xBAB24C) = rainbow_color_x;
		*(DWORD*)(0xBAB250) = rainbow_color_x;
		*(DWORD*)(0xBAB254) = rainbow_color_x;
		//B1G SOURCE BY RYONADV#1052
		*(DWORD*)(0xBAB258) = rainbow_color_x;
		*(DWORD*)(0xBAB25C) = rainbow_color_x;
		*(DWORD*)(0xBAB260) = rainbow_color_x;
		*(BYTE*)(0x58D973 + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58D96E + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58D969 + 1) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x58D8AF + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58D8AA + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58D89F + 1) = (BYTE)round(mainColorActive.z * 255.f);
		for (int i = 0; i < SAMP_MAX_TEXTDRAWS; i++)
		{
			if (pSAMP->getInfo()->pPools->pTextdraw->textdraw[i] == nullptr)
				continue;
			pSAMP->getInfo()->pPools->pTextdraw->textdraw[i]->dwLetterColor = rainbow_color_x;
			//    pSAMP->getInfo()->pPools->pTextdraw->textdraw[i]->dwBoxColor = rainbow_color_x;
		}

		for (int i = 0; i < SAMP_MAX_PLAYERTEXTDRAWS; i++) {
			if (pSAMP->getInfo()->pPools->pTextdraw->playerTextdraw[i] == nullptr)
				continue;
			pSAMP->getInfo()->pPools->pTextdraw->playerTextdraw[i]->dwLetterColor = rainbow_color_x;
			//    pSAMP->getInfo()->pPools->pTextdraw->playerTextdraw[i]->dwBoxColor = rainbow_color_x;
		}
	}
	if (RainbowHud == false)
	{
		*(DWORD*)(0xBAB22C) = 0xFF1D19B4;
		*(DWORD*)(0xBAB230) = 0xFF2C6836;
		*(DWORD*)(0xBAB234) = 0xFF7F3C32;
		*(DWORD*)(0xBAB238) = 0xFFF1CBAC;
		*(DWORD*)(0xBAB23C) = 0xFFE1E1E1;
		*(DWORD*)(0xBAB240) = 0xFF000000;
		*(DWORD*)(0xBAB244) = 0xFF106290;
		*(DWORD*)(0xBAB248) = 0xFFFC6EA8;
		*(DWORD*)(0xBAB24C) = 0xFF969696;
		*(DWORD*)(0xBAB250) = 0xFF110F68;
		*(DWORD*)(0xBAB254) = 0xFF1F4726;
		*(DWORD*)(0xBAB258) = 0xFF63C0E2;
		*(DWORD*)(0xBAB25C) = 0xFF6B5A4A;
		*(DWORD*)(0xBAB260) = 0xFFC81914;
		*(DWORD*)(0xBAB264) = 0xFF00FFFF;

		//fist
		*(BYTE*)(0x58D973 + 1) = 255;
		*(BYTE*)(0x58D96E + 1) = 255;
		*(BYTE*)(0x58D969 + 1) = 255;

		*(BYTE*)(0x58D8AF + 1) = 255;
		*(BYTE*)(0x58D8AA + 1) = 255;
		*(BYTE*)(0x58D89F + 1) = 255;
	}
	if (culoare_pusa)
	{
		if (*(DWORD*)0xBA18FC > 0) // car
		{
			*(byte*)(*(DWORD*)0xBA18FC + 1076) = 255;
			*(byte*)(*(DWORD*)0xBA18FC + 1077) = 255;
			*(byte*)(*(DWORD*)0xBA18FC + 1078) = 255;
			*(byte*)(*(DWORD*)0xBA18FC + 1079) = 255;

			*(DWORD*)((g_dwSAMP_Addr + 0x215AC8) + 4 * 255) = rainbow_color_x;
		}
	}

	if (RainbowRadar)
	{
		*(BYTE*)(0x58A9A2) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58A99A) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58A996) = (BYTE)round(mainColorActive.z * 240.f);

		*(BYTE*)(0x58A8EE) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58A8E6) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58A8DE) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x58A89A) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58A896) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58A894) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x58A798) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58A790) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58A78E) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x582F20) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x582F1A) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x582F18) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x588690 + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58868B + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x588686 + 1) = (BYTE)round(mainColorActive.z * 255.f);

		*(byte*)(0x5860CC + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(byte*)(0x5860C1 + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(byte*)(0x5860BC + 1) = (BYTE)round(mainColorActive.z * 255.f);
	}

	if (RainbowRadar == false)

	{
		*(BYTE*)(0x58A9A2) = 0;
		*(BYTE*)(0x58A99A) = 0;
		*(BYTE*)(0x58A996) = 0;

		*(BYTE*)(0x58A8EE) = 0;
		*(BYTE*)(0x58A8E6) = 0;
		*(BYTE*)(0x58A8DE) = 0;

		*(BYTE*)(0x58A89A) = 0;
		*(BYTE*)(0x58A896) = 0;
		*(BYTE*)(0x58A894) = 0;

		*(BYTE*)(0x58A798) = 0;
		*(BYTE*)(0x58A790) = 0;
		*(BYTE*)(0x58A78E) = 0;

		*(BYTE*)(0x582F20) = 0;
		*(BYTE*)(0x582F1A) = 0;
		*(BYTE*)(0x582F18) = 0;

		*(BYTE*)(0x588690 + 1) = 255;
		*(BYTE*)(0x58868B + 1) = 255;
		*(BYTE*)(0x588686 + 1) = 255;

		*(byte*)(0x5860CC + 1) = 255;
		*(byte*)(0x5860C1 + 1) = 255;
		*(byte*)(0x5860BC + 1) = 255;
	}
	if (tintarainbow)
	{
		// partea dreapta jos
		*(BYTE*)0x58E47C = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)0x58E473 = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)0x58E466 = (BYTE)round(mainColorActive.z * 255.f);
		// partea dreapta jos
		*(BYTE*)(0x58E432 + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58E429 + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58E424 + 1) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x58E3D9 + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58E3D0 + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58E3C7 + 1) = (BYTE)round(mainColorActive.z * 255.f);

		*(BYTE*)(0x58E300 + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(BYTE*)(0x58E2F5 + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(BYTE*)(0x58E2F0 + 1) = (BYTE)round(mainColorActive.z * 255.f);
	}
	if (tintarainbow == false)
	{
		// partea dreapta jos
		*(BYTE*)0x58E47C = 255;
		*(BYTE*)0x58E473 = 255;
		*(BYTE*)0x58E466 = 255;
		// partea dreapta jos
		*(BYTE*)(0x58E432 + 1) = 255;
		*(BYTE*)(0x58E429 + 1) = 255;
		*(BYTE*)(0x58E424 + 1) = 255;

		*(BYTE*)(0x58E3D9 + 1) = 255;
		*(BYTE*)(0x58E3D0 + 1) = 255;
		*(BYTE*)(0x58E3C7 + 1) = 255;

		*(BYTE*)(0x58E300 + 1) = 255;
		*(BYTE*)(0x58E2F5 + 1) = 255;
		*(BYTE*)(0x58E2F0 + 1) = 255;
	}
	if (RainbowHeadLights)
	{
		*(byte*)(0x6E155F + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(byte*)(0x6E155D + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(byte*)(0x6E1555 + 1) = (BYTE)round(mainColorActive.z * 255.f);

		*(byte*)(0x6E1688 + 1) = (BYTE)round(mainColorActive.x * 255.f);
		*(byte*)(0x6E1686 + 1) = (BYTE)round(mainColorActive.y * 255.f);
		*(byte*)(0x6E1684 + 1) = (BYTE)round(mainColorActive.z * 255.f);
	}
	if (RainbowHeadLights == false)
	{
		*(byte*)(0x6E155F + 1) = 45;
		*(byte*)(0x6E155D + 1) = 45;
		*(byte*)(0x6E1555 + 1) = 45;

		*(byte*)(0x6E1688 + 1) = 45;
		*(byte*)(0x6E1686 + 1) = 45;
		*(byte*)(0x6E1684 + 1) = 45;
	}
	if (rainbowmenu)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, .78f);
		style.Colors[ImGuiCol_TextDisabled] = mainColorActive;;
		style.Colors[ImGuiCol_WindowBg] = mainColorActive;
		style.Colors[ImGuiCol_ChildWindowBg] = mainColorActive;
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.78f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = mainColorActive;
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorActive;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = mainColorActive;
		style.Colors[ImGuiCol_SliderGrab] = mainColorActive;
		style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_Button] = mainColorActive;
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.86f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_Header] = mainColorActive;
		style.Colors[ImGuiCol_HeaderHovered] = mainColorActive;
		style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
		style.Colors[ImGuiCol_Column] = ImVec4(0.15f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_ColumnHovered] = mainColorActive;
		style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGrip] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGripHovered] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = mainColorActive;
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorActive;
		style.Colors[ImGuiCol_TextSelectedBg] = mainColorActive;
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
	}
	if (!pDevice)
		return pD3DHook->Orginal_Present(pDevice, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);

	if (pD3DHook->bD3DRenderInit == false)
	{
		pD3DHook->pRender->Initialize(pDevice);
		pD3DHook->pD3DFont->Initialize(pDevice);

		pD3DHook->bD3DRenderInit = true;
	}

	if (!pSAMP->isInited)
		pD3DHook->pD3DFont->Print(1, 1, D3DCOLOR_ARGB(255, rand() % 255, rand() % 255, rand() % 255), "", true);

	return pD3DHook->Orginal_Present(pDevice, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);
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
	if (c_GodMode)
	{
		everything();
		*GodMode = 1;
		c_GodMode = true;
	}
	else
	{
		everything();
		*GodMode = 0;
		c_GodMode = false;
	}
	/*if (c_slap)
	{
		everything();
		*slap = 1;
		c_slap = true;
	}
	else
	{
		everything();
		*slap = 0;
		c_slap = false;
	}*/
	if (c_bjump)
	{
		everything();
		*bjump = 1;
		c_bjump = true;
	}
	else
	{
		everything();
		*bjump = 0;
		c_bjump = false;
	}
	if (taim)
	{
		*(DWORD*)(0xB70153) = timeset;
	}
	if (!taim)
	{
		*(DWORD*)(0xB70153) = 12;
	}
	if (weather)
	{
		*(DWORD*)(0xC81320) = weatherset;
	}
	if (!weather)
	{
		*(DWORD*)(0xC81320) = 12;
	}
	// ASA
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
		Boss();
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
	if (megajumpvar)
	{
		DWORD megajumpAddr = 0x96916C;
		DWORD megajump = 1;
		ReadProcessMemory(handle, (LPCVOID)megajumpAddr, &megajump, sizeof(megajump), 0);

		megajump = 1;
		WriteProcessMemory(handle, (LPVOID)megajumpAddr, &megajump, sizeof(megajump), 0);
		Sleep(10);

	}
	//stop megajump
	if (!megajumpvar)
	{
		DWORD megajumpAddr = 0x96916C;
		DWORD megajump = 0;
		ReadProcessMemory(handle, (LPCVOID)megajumpAddr, &megajump, sizeof(megajump), 0);

		if (megajump == 1)
		{
			megajump = 0;
			WriteProcessMemory(handle, (LPVOID)megajumpAddr, &megajump, sizeof(megajump), 0);
			Sleep(10);
		}
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
	/*while (g_dwSAMP_Addr == NULL)
	{
		g_dwSAMP_Addr = (DWORD)GetModuleHandle("samp.dll");
		sleep(250);
	}

	while (!g_Chat)
	{
		g_Chat = *(DWORD**)(g_dwSAMP_Addr + SAMP_CHAT_INFO_OFFSET);
		sleep(25);
	}*/
	//atentat on
	 if (pSAMP)
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

		while (!pSAMP->tryInit())
		Sleep(100);
	}
	void** vTableDevice = *(void***)(*(DWORD*)DEVICE_PTR);
	VTableHookManager* vmtHooks = new VTableHookManager(vTableDevice, D3D_VFUNCTIONS);

	oEndScene = (_EndScene)vmtHooks->Hook(ENDSCENE_INDEX, (void*)hkEndScene);
	oReset = (_Reset)vmtHooks->Hook(RESET_INDEX, (void*)hkReset);
	everything();
	Fakekick();
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
		everything();
		functions();
		InfOxygen();
		fastrotation();
		Fakekick();
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
		GetVolumeInformation(szHD, (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

		if (dwSerial == Ryon | dwSerial == Over | dwSerial == Narda | dwSerial == Medik | dwSerial == Andy | dwSerial == mlg | dwSerial == kegan | dwSerial == kz | dwSerial == dumi | dwSerial == razvan | dwSerial == theweek | dwSerial == benq )
		{
			Sleep(100);
		}
		else
		{
			// when HWID rejected
			MessageBox(NULL, "HWID-ul tau nu este inregistrat in baza noastra de date.", "HWID CHECKER", MB_OK);
			exit(0);
			return TRUE;
		}
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
