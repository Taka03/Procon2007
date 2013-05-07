//*==============================================
//input.h
//*==============================================

//===============================================
//include
//===============================================
#include "input.h"
#include "joker.h"

//===============================================
//variable
//===============================================
bool CInput::m_IsFilterXInputDevice;
XINPUT_DEVICE_NODE *CInput::m_pXInputDeviceList;

KEYBOARDDATA CInput::m_KeyboardData;
MOUSEDATA CInput::m_MouseData;

LPDIRECTINPUT8 CInput::m_pDirectInput;
LPDIRECTINPUTDEVICE8 CInput::m_pKeyboard;

JOYSTICKWORK CInput::m_pJoystickData[JOYSTICK_MAX];
Uint32 CInput::m_JoystickMax;
Uint32 CInput::m_JoystickCount;

bool CInput::m_DoubleClickL;
bool CInput::m_DoubleClickR;
bool CInput::m_DoubleClickW;



//static DIOBJECTDATAFORMAT JoystickDataFormat[] =
//{
//	// 軸
//	{ &GUID_XAxis,	FIELD_OFFSET(JOYSTICKDATA,         Pos.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	{ &GUID_YAxis,	FIELD_OFFSET(JOYSTICKDATA,         Pos.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	{ &GUID_ZAxis,	FIELD_OFFSET(JOYSTICKDATA,         Pos.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	// 回転軸
//	{ &GUID_RxAxis,	FIELD_OFFSET(JOYSTICKDATA,         Rot.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	{ &GUID_RyAxis,	FIELD_OFFSET(JOYSTICKDATA,         Rot.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	{ &GUID_RzAxis,	FIELD_OFFSET(JOYSTICKDATA,         Rot.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	// 軸の速度
//	{ &GUID_XAxis,	FIELD_OFFSET(JOYSTICKDATA,         Sp.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	{ &GUID_YAxis,	FIELD_OFFSET(JOYSTICKDATA,         Sp.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	{ &GUID_ZAxis,	FIELD_OFFSET(JOYSTICKDATA,         Sp.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	// 軸の角速度
//	{ &GUID_RxAxis,	FIELD_OFFSET(JOYSTICKDATA,        SpRot.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	{ &GUID_RyAxis,	FIELD_OFFSET(JOYSTICKDATA,        SpRot.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	{ &GUID_RzAxis,	FIELD_OFFSET(JOYSTICKDATA,        SpRot.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	// 軸の加速度
//	{ &GUID_XAxis,	FIELD_OFFSET(JOYSTICKDATA,         Acc.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	{ &GUID_YAxis,	FIELD_OFFSET(JOYSTICKDATA,         Acc.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	{ &GUID_ZAxis,	FIELD_OFFSET(JOYSTICKDATA,         Acc.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	// 軸の角加速度
//	{ &GUID_RxAxis,	FIELD_OFFSET(JOYSTICKDATA,        AccRot.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	{ &GUID_RyAxis,	FIELD_OFFSET(JOYSTICKDATA,        AccRot.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	{ &GUID_RzAxis,	FIELD_OFFSET(JOYSTICKDATA,        AccRot.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	// 軸のフォース
//	{ &GUID_XAxis,	FIELD_OFFSET(JOYSTICKDATA,         Force.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	{ &GUID_YAxis,	FIELD_OFFSET(JOYSTICKDATA,         Force.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	{ &GUID_ZAxis,	FIELD_OFFSET(JOYSTICKDATA,         Force.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	// 軸のトルク
//	{ &GUID_RxAxis,	FIELD_OFFSET(JOYSTICKDATA,        ForRot.x), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	{ &GUID_RyAxis,	FIELD_OFFSET(JOYSTICKDATA,        ForRot.y), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	{ &GUID_RzAxis,	FIELD_OFFSET(JOYSTICKDATA,        ForRot.z), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },	
//	// スライダー
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTPOSITION },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTVELOCITY },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTACCEL },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	{ &GUID_Slider,	FIELD_OFFSET(JOYSTICKDATA,  Slider[1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_AXIS, DIDOI_ASPECTFORCE },
//	// POV
//	{ &GUID_POV,	FIELD_OFFSET(JOYSTICKDATA,     Pov[0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_POV, 0 },
//	{ &GUID_POV,	FIELD_OFFSET(JOYSTICKDATA,     Pov[1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_POV, 0 },
//	{ &GUID_POV,	FIELD_OFFSET(JOYSTICKDATA,     Pov[2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_POV, 0 },
//	{ &GUID_POV,	FIELD_OFFSET(JOYSTICKDATA,     Pov[3]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_POV, 0 },
//	// ボタン
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 0]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 1]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 2]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 3]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 4]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 5]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 6]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 7]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 8]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[ 9]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[10]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[11]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[12]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[13]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[14]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//	{ &GUID_Button,	FIELD_OFFSET(JOYSTICKDATA, Button[15]), DIDFT_OPTIONAL | DIDFT_ANYINSTANCE | DIDFT_BUTTON, 0 },
//};
//
//static const Sint32 JoyDataNum = sizeof(JoystickDataFormat) / sizeof(DIOBJECTDATAFORMAT);
//
//static DIDATAFORMAT DIJoystickDataFormat = 
//{ 
//	sizeof(DIDATAFORMAT),			// この構造体のサイズ
//	sizeof(DIOBJECTDATAFORMAT),		// オブジェクト データ形式のサイズ
//	DIDF_ABSAXIS,					// 絶対軸の座標
//	sizeof(JOYSTICKDATA),			// デバイス データのサイズ
//	JoyDataNum,						// オブジェクト数
//	JoystickDataFormat,				// データ位置
//};

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::Init()
{

}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::Exec()
{

}

//===============================================
//DirectInputの初期化
//===============================================
//[input]
//	なし
//[return]
//	hr:結果
//===============================================
HRESULT CInput::CreateDevice()
{
	HRESULT hr;
	
	/*デバイスの生成*/
	hr = DirectInput8Create(Joker::GetHInst(), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDirectInput, NULL);
	
	if(FAILED(hr) )
	{
		return hr;
	}
	
	InitKeyboard();
	InitJoystick();
	
	return S_OK;
	
}

//===============================================
//キーボードの初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
HRESULT CInput::InitKeyboard()
{
	/*デバイスオブジェクトを作成*/
	HRESULT hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	
	if(FAILED(hr) )
	{
		MessageBox(NULL, "キーボードの作成に失敗", "Error", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	/*データ形式を設定*/
	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	
	if(FAILED(hr) )
	{
		MessageBox(NULL, "c_dfDIKeyboard形式の設定に失敗", "Error", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	/*モードを設定(フォアグラウンド & 非排他モード)*/
	hr = m_pKeyboard->SetCooperativeLevel(Joker::GetHWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	
	if(FAILED(hr) )
	{
		MessageBox(NULL, "フォアグラウンド&非排他モードの設定に失敗", "Error", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	/*デバイス情報取得*/
	DIDEVCAPS caps = {sizeof(DIDEVCAPS) };
	m_pKeyboard->GetCapabilities(&caps);
	
	/*入力制御開始*/
	m_pKeyboard->Acquire();
	
	return S_OK;
} 

//===============================================
//ジョイスティックの列挙
//===============================================
//[input]
//	pdidInstance:
//	pContext:
//[return]
//
//===============================================
BOOL CALLBACK CInput::EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, void *pContext)
{
	DI_ENUM_CONTEXT *pEnumContext = (DI_ENUM_CONTEXT*)pContext;
	
	HRESULT hr;
	
	if(m_IsFilterXInputDevice && IsXInputDevice(&pdidInstance->guidProduct) )
	{
		return DIENUM_CONTINUE;
	}
	
	if(pEnumContext->IsPreferredJoyCfg && 
	   !IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPrefrredJoyCfg->guidInstance) )
	{
		return DIENUM_CONTINUE;
	}
	
	/*デバイスの生成*/
	hr = m_pDirectInput->CreateDevice(pdidInstance->guidInstance, &m_pJoystickData[m_JoystickCount].pDevice, NULL);
	
	if(SUCCEEDED(hr) )
	{
		return (++m_JoystickCount == m_JoystickMax) ? (DIENUM_STOP) : (DIENUM_CONTINUE);
	}
	
	return DIENUM_STOP;
	
}

//===============================================
//オブジェクトの列挙
//===============================================
//[input]
//
//[return]
//
//===============================================
BOOL CALLBACK CInput::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, void *pContext)
{
	HRESULT hr;
	
	DIPROPRANGE diprg;
	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -1000;
	diprg.lMax = +1000;
	
	LPDIRECTINPUTDEVICE8 Joy = (LPDIRECTINPUTDEVICE8)pContext;
	
	hr = Joy->SetProperty(DIPROP_RANGE, &diprg.diph);
	
	if(FAILED(hr) )
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}



//===============================================
//ジョイスティックの初期化
//===============================================
//[input]
//	なし
//[return]
//	hr
//===============================================
HRESULT CInput::InitJoystick()
{
	HRESULT hr;
	
	if(m_IsFilterXInputDevice)
	{
		SetupXInputDevice();
	}
	
	DIJOYCONFIG PreferJoyCfg = {0};
	DI_ENUM_CONTEXT eContext;
	
	eContext.pPrefrredJoyCfg = &PreferJoyCfg;
	eContext.IsPreferredJoyCfg = false;
	
	IDirectInputJoyConfig8 *pJoyConfig = NULL;
	
	hr = m_pDirectInput->QueryInterface(IID_IDirectInputJoyConfig8, (void **)&pJoyConfig);
	
	if(FAILED(hr) )
	{
		return hr;
	}
	
	PreferJoyCfg.dwSize = sizeof(PreferJoyCfg);
	
	hr = pJoyConfig->GetConfig(0, &PreferJoyCfg, DIJC_GUIDINSTANCE);
	
	if(SUCCEEDED(hr) )
	{
		eContext.IsPreferredJoyCfg = true;
	}
	
	RELEASE(pJoyConfig);
	
	//------------------------------------
	//使用可能なジョイスティック数
	//------------------------------------
	m_JoystickMax = joyGetNumDevs();
	
	if(m_JoystickMax >= JOYSTICK_MAX)
	{
		m_JoystickMax = JOYSTICK_MAX;
	}
	
	//------------------------------------
	//ジョイスティックの列挙
	//------------------------------------
	m_JoystickCount = 0;
	
	hr = m_pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &eContext, DIEDFL_ATTACHEDONLY);
		
	if(FAILED(hr) )
	{
		for(int i = 0;i < JOYSTICK_MAX;i++)
		{		
			F_RELEASE(m_pJoystickData[i].pDevice);
			
			return hr;
		}	
	}
	
	for(Uint32 i = 0;i < m_JoystickCount;i++)
	{
		if(m_IsFilterXInputDevice)
		{
			ReleaseXInputDevice();
		}
		
		if(m_pJoystickData[i].pDevice == NULL)
		{
			MESSAGE("ジョイスティックが見つかりません");
			return S_OK;
		}

		//------------------------------------
		//データフォーマットの設定
		//------------------------------------
		hr = m_pJoystickData[i].pDevice->SetDataFormat(&c_dfDIJoystick2);
		
		if(FAILED(hr) )
		{
			return hr;
		} 
		
		//------------------------------------
		//協調レベルの設定
		//------------------------------------
		hr = m_pJoystickData[i].pDevice->SetCooperativeLevel(Joker::GetHWnd(), DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		
		if(FAILED(hr) )
		{
			return hr;	
		}
		
		//-----------------------------------
		//軸モードの設定
		//-----------------------------------
		hr = m_pJoystickData[i].pDevice->EnumObjects(EnumObjectsCallback, (VOID*)m_pJoystickData[i].pDevice, DIDFT_ALL);
		
		if(FAILED(hr) )
		{
			return hr;	
		}
		
		//-----------------------------------
		//デバイス情報取得
		//-----------------------------------
		DIDEVCAPS caps = {sizeof(DIDEVCAPS) };
		m_pJoystickData[i].pDevice->GetCapabilities(&caps);
		
		//ポーリングが必要か調べる
		if(caps.dwFlags & (DIDC_POLLEDDATAFORMAT & DIDC_POLLEDDEVICE) )
		{
			m_pJoystickData[i].IsPolling = true;	
		}
		
		else
		{
			m_pJoystickData[i].IsPolling = false;
		}
		
		/*入力制御開始*/
		m_pJoystickData[i].pDevice->Acquire();
	}
		
	return S_OK;
	
}

//===============================================
//XInputの設定
//===============================================
//[input]
//
//[return]
//	hr
//===============================================
HRESULT CInput::SetupXInputDevice()
{
	IWbemServices *pIWbemServices = NULL;
	IEnumWbemClassObject *pEnumDevices = NULL;
	IWbemLocator *pIWbemLocator = NULL;
	IWbemClassObject *pDevice[20] = {0};
	BSTR bstrDeviceID = NULL;
	BSTR bstrClassName = NULL;
	BSTR bstrNamespace = NULL;
	DWORD Returned = 0;
	bool IsCleanupCOM = false;
	UINT Device = 0;
	VARIANT var;
	HRESULT hr;
	
	hr = CoInitialize(NULL);
	IsCleanupCOM = SUCCEEDED(hr);
	
	/*WMIの生成*/
	hr = CoCreateInstance(__uuidof(WbemLocator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator), (LPVOID*)&pIWbemLocator);
	
	if(FAILED(hr) || pIWbemLocator == NULL)
	{
		goto LCleanUp;
	}
	
	/*BSTRの生成*/
	bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2");
	bstrDeviceID  = SysAllocString(L"DeviceID");
	bstrClassName = SysAllocString(L"Win32_PNPEntity");
	
	if(bstrNamespace == NULL)
	{
		goto LCleanUp;
	}
	
	if(bstrDeviceID == NULL)
	{
		goto LCleanUp;
	}
	
	if(bstrClassName == NULL)
	{
		goto LCleanUp;
	}
	
	/*WMIへの接続*/
	hr = pIWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L, 0L, NULL, NULL, &pIWbemServices);
	
	if(FAILED(hr) || pIWbemServices == NULL)
	{
		goto LCleanUp;
	}
	
	/*セキュリティーレベルの切替*/
	//CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
	//					RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0); 
						
	/*リストを得る*/
	hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, &pEnumDevices);
	
	if(FAILED(hr) )
	{
		goto LCleanUp;
	}
	
	for(;;)
	{
		hr = pEnumDevices->Next(10000, 20, pDevice, &Returned);
		
		if(FAILED(hr) )
		{
			goto LCleanUp;
		}
		
		if(Returned == 0)
		{
			break;
		}
		
		for(Device = 0;Device < Returned;Device++)
		{
			hr = pDevice[Device]->Get(bstrDeviceID, 0L, &var, NULL, NULL);
			
			if(SUCCEEDED(hr) )
			{
				if(wcsstr(var.bstrVal, L"IG_") )
				{
					DWORD dwPid = 0;
					DWORD dwVid = 0;
					
					WCHAR *pstrVid = wcsstr(var.bstrVal, L"VID_" );
					
					if(pstrVid && swscanf_s(pstrVid, L"VID_%4X", &dwVid) != 1)
					{
						dwVid = 0;
					}
					
					WCHAR *pstrPid = wcsstr(var.bstrVal, L"PID_");
					
					if(pstrPid && swscanf_s(pstrPid, L"PID_%4L", &dwPid) != 1)
					{
						dwPid = 0;
					}
					
					DWORD dwVidPid = MAKELONG(dwVid, dwPid); 
					
					XINPUT_DEVICE_NODE *pNewNode = new XINPUT_DEVICE_NODE;
					
					if(pNewNode)
					{
						pNewNode->dwVidPid = dwVidPid;
					}
					
				}
			}
			
			RELEASE(pDevice[Device] );
		}
	}
	
LCleanUp:
	if(bstrNamespace)
	{
		SysFreeString(bstrNamespace);
	}	
	
	if(bstrDeviceID)
	{
		SysFreeString(bstrDeviceID);
	}
	
	if(bstrClassName)
	{
		SysFreeString(bstrClassName);
	}
	
	for(Device = 0;Device < 20;Device++)
	{
		RELEASE(pDevice[Device]);
	}
	
	RELEASE(pEnumDevices);
	RELEASE(pIWbemLocator);
	RELEASE(pIWbemServices);
	
	return hr;
	
}

//===============================================
//XInputDeviceの判定フラグ
//===============================================
//[input]
//	pGuidDirectInput:
//[return]
//
//===============================================
bool CInput::IsXInputDevice(const GUID *pGuidDirectInput)
{
	XINPUT_DEVICE_NODE *pNode = m_pXInputDeviceList;
	
	while(pNode)
	{
		if(pNode->dwVidPid == pGuidDirectInput->Data1)
		{
			return true;
		}
		
		pNode = pNode->pNext;
		
	}
	
	return false;
}

//===============================================
//XInputDeviceの解放
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::ReleaseXInputDevice()
{
	/*リストの解放*/
	XINPUT_DEVICE_NODE *pNode = m_pXInputDeviceList;
	
	while(pNode)
	{
		XINPUT_DEVICE_NODE *pDelete = pNode;
		pNode = pNode->pNext;
		SAFE_DELETE(pDelete);
	}
}

//===============================================
//キーデータ取得
//===============================================
//[input]
//	key:キーデータ
//[return]
//	なし
//===============================================
bool CInput::GetKeyData(int key)
{
	return (m_KeyboardData.Key[key] == 0x01);		
}

//===============================================
//マウスデータの取得
//===============================================
//[input]
//	pMouse:マウスデータ
//[return]
//	なし
//===============================================
void CInput::GetMouseData(MOUSEDATA *pMouse)
{
	*pMouse = m_MouseData;
}

//===============================================
//ジョイスティックデータの取得
//===============================================
//[input]
//	no:パッド番号
//	pJoy:ジョイスティックデータ
//[return]
//	パッドデータ
//===============================================
bool CInput::GetJoystickData(int no, DIJOYSTATE2 *pJoy)
{
	*pJoy = m_pJoystickData[no].Data;
	
	return (m_pJoystickData[no].pDevice != NULL);
}


//===============================================
//キー状態更新
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::UpdateKeyboard()
{
	if(m_pKeyboard != NULL)
	{
		/*キーボード状態取得*/
		HRESULT hr = m_pKeyboard->GetDeviceState(256, m_KeyboardData.Key);
		
		if(SUCCEEDED(hr) )
		{
			for(int i = 0;i < 256;i++)
			{
				m_KeyboardData.Key[i] = (UCHAR)((m_KeyboardData.Key[i] >> 7) & 0x01);
			}
			
			return;
		}
		
		/*再アクセス*/
		m_pKeyboard->Acquire();
		
	}

	/*メモリ解放*/
	MemoryClear(m_KeyboardData.Key, sizeof(m_KeyboardData.Key) ); 
	
}

//===============================================
//マウスデータの更新
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::UpdateMouse()
{
	bool BtnL = (::GetKeyState(VK_LBUTTON) >> 7) & 0x01;
	bool BtnR = (::GetKeyState(VK_RBUTTON) >> 7) & 0x01;
	bool BtnW = (::GetKeyState(VK_MBUTTON) >> 7) & 0x01;
	
	/*左クリック処理*/
	if(BtnL)
	{
		if(m_MouseData.IsClickL)
		{
			m_MouseData.StateL = MOUSE_HOLD;
		}
		
		else
		{
			m_MouseData.StateL = MOUSE_PUSH;
		}
	}
	
	else
	{
		if(m_MouseData.IsClickL)
		{
			m_MouseData.StateL = MOUSE_PULL;
		}
		
		else
		{
			m_MouseData.StateL = MOUSE_FREE;
		}
	}
	
	/*右クリック処理*/
	if(BtnR)
	{
		if(m_MouseData.IsClickR)
		{
			m_MouseData.StateR = MOUSE_HOLD;
		}
		
		else
		{
			m_MouseData.StateR = MOUSE_PUSH;
		}
	}
	
	else
	{
		if(m_MouseData.IsClickR)
		{
			m_MouseData.StateR = MOUSE_PULL;
		}
		
		else
		{
			m_MouseData.StateR = MOUSE_FREE;
		}
	}
	
	/*ホイールクリック処理*/
	if(BtnW)
	{
		if(m_MouseData.IsClickW)
		{
			m_MouseData.StateW = MOUSE_HOLD;
		}
		
		else
		{
			m_MouseData.StateW = MOUSE_PUSH;
		}
	}
	
	else
	{
		if(m_MouseData.IsClickW)
		{
			m_MouseData.StateW = MOUSE_PULL;
		}
		
		else
		{
			m_MouseData.StateW = MOUSE_FREE;
		}
	}
	
	/*状態保存*/
	m_MouseData.IsClickL = BtnL;
	m_MouseData.IsClickR = BtnR;
	m_MouseData.IsClickW = BtnW;
	
	/*ダブルクリック*/
	m_MouseData.IsDClickL = m_DoubleClickL;
	m_MouseData.IsDClickR = m_DoubleClickR;
	m_MouseData.IsDClickW = m_DoubleClickW;
	
	m_DoubleClickL = false;
	m_DoubleClickR = false;
	m_DoubleClickW = false;
	
	/*スクリーン上の位置*/
	POINT Cursor;
	::GetCursorPos(&Cursor);//カーソルの位置取得
	::ScreenToClient(Joker::GetHWnd(), &Cursor);
	
	m_MouseData.Mx = Cursor.x - m_MouseData.PosX;
	m_MouseData.My = Cursor.y - m_MouseData.PosY;
	m_MouseData.PosX = Cursor.x;
	m_MouseData.PosY = Cursor.y;
	
}
//===============================================
//パッドデータの更新
//===============================================
//[input]
//	なし
//[return]
//	hr:結果
//===============================================
void CInput::UpdateInputState()
{
	HRESULT hr;
	
	for(Uint32 i = 0;i < m_JoystickCount;i++)
	{
		if(m_pJoystickData[i].pDevice != NULL)
		{
			/*ポーリングが必要な場合*/
			if(m_pJoystickData[i].IsPolling)
			{
				m_pJoystickData[i].pDevice->Poll();
			}
			
			hr = m_pJoystickData[i].pDevice->GetDeviceState(sizeof(DIJOYSTATE2), &m_pJoystickData[i].Data);
			
			if(SUCCEEDED(hr) )
			{
				continue;
			}
			
			/*デバイス再アクセス*/
			m_pJoystickData[i].pDevice->Acquire();
			ZeroMemory(&m_pJoystickData[i].Data, sizeof(DIJOYSTATE2) );
		}
	}	
		
		
}

//===============================================
//更新
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::Update()
{
	/*キーデータ更新*/
	CInput::UpdateKeyboard();
	
	/*マウスデータ更新*/
	CInput::UpdateMouse();
	
	/*データの更新*/
	CInput::UpdateInputState();
			

}

//===============================================
//DirectInputの解放
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CInput::ReleaseDevice()
{
	//------------------------------------
	//キーボードの解放
	//------------------------------------
	if(m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
	}
	
	for(int i = 0;i < JOYSTICK_MAX;i++)
	{
		
		if(m_pJoystickData[i].pDevice)
		{
			m_pJoystickData[i].pDevice->Unacquire();
		}
		
		RELEASE(m_pJoystickData[i].pDevice);
		
	}
	
	RELEASE(m_pKeyboard);
	RELEASE(m_pDirectInput);
	
}
