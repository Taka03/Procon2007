//*==============================================
//input.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#define _CRT_SECURE_NO_DEPRECATE
#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif

#include <wbemidl.h>
#include <objbase.h>

//===============================================
//enum
//===============================================
//キーの状態
enum eKeyState
{
	KEY_STATE_FREE,//何も入力されていない状態
	KEY_STATE_PUSH,//キーが押された瞬間
	KEY_STATE_PULL,//キーが離された瞬間
	KEY_STATE_HOLD,//キーが押され続けている瞬間	
};

//マウスの状態
enum eMouseState
{
	MOUSE_FREE,//何も入力されていない状態
	MOUSE_PUSH,//マウスボタンが押された瞬間
	MOUSE_PULL,//マウスボタンが離された瞬間
	MOUSE_HOLD,//マウスボタンが押され続けている状態
};

//POVキー
enum ePov
{
	POV_0   = 0,
	POV_45  = 45,
	POV_90  = 90,
	POV_135 = 135,
	POV_180 = 180,
	POV_225 = 225,
	POV_270 = 270,
	POV_315 = 315,
	POV_N   = POV_0,
	POV_NE  = POV_45,
	POV_E   = POV_90,
	POV_SE  = POV_135,
	POV_S   = POV_180,
	POV_SW  = POV_225,
	POV_W   = POV_270,
	POV_NW  = POV_315,
	
};

//パッドの状態
enum ePadState
{
	PAD_STATE_PUSH,
	PAD_STATE_PULL,
	PAD_STATE_HOLD,
	PAD_STATE_REPEAT,
	
	PAD_STATE_MAX,
};

//パッドのボタン
enum ePadSort
{
	PAD_DIR_UP,
	PAD_DIR_DOWN,
	PAD_DIR_LEFT,
	PAD_DIR_RIGHT,
	
	PAD_BUTTON_01,
	PAD_BUTTON_02,
	PAD_BUTTON_03,
	PAD_BUTTON_04,
	PAD_BUTTON_05,
	PAD_BUTTON_06,
	PAD_BUTTON_07,
	PAD_BUTTON_08,
	PAD_BUTTON_09,
	PAD_BUTTON_10,
	PAD_BUTTON_11,
	PAD_BUTTON_12,
	PAD_BUTTON_13,
	PAD_BUTTON_14,
	PAD_BUTTON_15,
	PAD_BUTTON_16,
	
	PAD_SORT_MAX,
	
	PAD_SORT_NONE,
};

const int PAD_BUTTON_MAX = 16;
const int JOYSTICK_MAX = 16;

//===============================================
//struct
//===============================================
struct XINPUT_DEVICE_NODE
{
	DWORD dwVidPid;
	XINPUT_DEVICE_NODE *pNext;
};

struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG *pPrefrredJoyCfg;
	bool IsPreferredJoyCfg;
};

//キーボードデータ
struct KEYBOARDDATA
{
	char Key[256];//キーデータ
};

//マウスデータ
struct MOUSEDATA
{
	int PosX;//X座標
	int PosY;//Y座標
	int PosW;//Z座標
	
	int Mx;//X移動量
	int My;//Y移動量
	
	bool IsClickL;//左ボタンクリック判定
	bool IsClickR;//右ボタンクリック判定
	bool IsClickW;//ホイールクリック判定
	
	bool IsDClickL;//左ボタンダブルクリック判定
	bool IsDClickR;//右ボタンダブルクリック判定
	bool IsDClickW;//ホイールダブルクリック判定
	
	eMouseState StateL;//左ボタン状態
	eMouseState StateR;//右ボタン状態
	eMouseState StateW;//ホイールボタン状態
};

//軸データ
struct AXISDATA
{
	Sint32 Ax;
	Sint32 Ay;
	Sint32 Az;
};

//パッドの状態
struct PADSTATUS
{
	Sint32 KeyState[PAD_STATE_MAX];
};

//パッド保存用データ
struct PADSAVEHEADER
{
	char Guid[4]; //ファイル識別用
	Sint32 LayerMax;	//レイヤー数
	Sint32 FrameMax;	//フレーム数
};

//ジョイスティックデータ
struct JOYSTICKDATA
{
	CVector3 Pos;//軸
	CVector3 Rot;//回転軸
	CVector3 Sp;//速度
	CVector3 SpRot;//角速度
	CVector3 Acc;//加速度
	CVector3 AccRot;//角加速度
	CVector3 Force;//フォース
	CVector3 ForRot;//トルク
	
	int Slider[2];//スライダー
	int Pov[4];//POV
	
	char Button[PAD_BUTTON_MAX];//ボタン
	
};



struct JOYSTICKWORK
{
	DIJOYSTATE2 Data;
	LPDIRECTINPUTDEVICE8 pDevice;//ジョイスティックデバイス
	
	bool IsPolling;//ポーリング判定フラグ
	bool IsForceFeedback;//フォースフィードバックに対応判定フラグ
	
	int LockKey;//ロックするキー
	int KeyState[PAD_STATE_MAX];//キーの状態
	int KeyStateWork[2];//キー情報取得用ワーク
	int KeyRepeatCounter[PAD_SORT_MAX];//キーリピートカウンター
	int PadMap[PAD_SORT_MAX];//パッドマッピング情報
	int KeyAlias[PAD_SORT_MAX];//キーボードマッピング用
	
	bool IsUsePOVDirection;//POVを方向キー判定
};




//===============================================
//class
//===============================================
class CInput :public CGameObject
{
	protected:
	
		static bool m_IsFilterXInputDevice;
		static XINPUT_DEVICE_NODE *m_pXInputDeviceList;
		
		static KEYBOARDDATA m_KeyboardData;//キーボードデータ
		static JOYSTICKWORK m_pJoystickData[JOYSTICK_MAX];//ジョイスティックデータ
		
		static Uint32 m_JoystickMax;//ジョイスティック最大数
		static Uint32 m_JoystickCount;//ジョイスティックのカウンタ
		
		static LPDIRECTINPUT8 m_pDirectInput;//デバイス
		static LPDIRECTINPUTDEVICE8 m_pKeyboard;//キーボードデバイス
		static MOUSEDATA m_MouseData;//マウスデータ
		
		static bool m_DoubleClickL;//左ボタンダブルクリック判定
		static bool m_DoubleClickR;//右ボタンダブルクリック判定
		static bool m_DoubleClickW;//ホイールダブルクリック判定
		
		
		
	public:
	
		CInput(){};//コンストラクタ
		~CInput(){};//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		static void Update();//更新
		
		static HRESULT CreateDevice();//デバイスの生成
		static HRESULT SetupXInputDevice();//Xインプットのセットアップ
		static bool IsXInputDevice(const GUID *pGuidDirectInput);
		static void ReleaseXInputDevice();
		static bool GetJoystickData(int no, DIJOYSTATE2 *pJoy);//ジョイスティックデータの取得
		//static JOYSTICKDATA GetJoystickData(int no);
		static bool GetKeyData(int key);//キーデータ取得
		static void GetMouseData(MOUSEDATA *pMouse);//マウスデータの取得
		
		
		static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);//ジョイスティックの列挙
		static BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);//オブジェクトの列挙
		static HRESULT InitJoystick();//ジョイスティックの初期化
		static HRESULT InitKeyboard();//キーボードの初期化
		
		static void UpdateKeyboard();//キーボードデータの更新
		static void UpdateMouse();//マウスデータの更新
		static void UpdateInputState();//状態の更新
	
		static VOID ReleaseDevice();//デバイスの解放
		
		
};
