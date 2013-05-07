//*==============================================
//joker.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joker.h"

//===============================================
//variable
//===============================================
HWND	Joker::m_hWnd = NULL;
HINSTANCE	Joker::m_hInst = NULL;
LPCSTR Joker::m_WndClass = NULL;
char Joker::m_AppName[MAX_PATH];
bool Joker::m_IsWinMode = true;
bool Joker::m_IsSetWindowInfo = true;

UINT Joker::m_WinWidth = 800;
UINT Joker::m_WinHeight = 600;

DWORD Joker::m_MaxVertexBlend = 0;

HDROP Joker::m_hDrop;
string Joker::m_DragFile;
char Joker::m_DragFileName[256];
	
LPDIRECT3D9	Joker::pD3D = NULL;
LPDIRECT3DDEVICE9 Joker::pD3DDevice = NULL;
LPD3DXSPRITE Joker::pSprite = NULL;

Uint64 Joker::m_NowTime = 0;
Uint64 Joker::m_OldTime = 0; 
Uint64 Joker::m_BeforeTime = 0;
		
long Joker::m_SyncCount = 0; //総フレーム数
long Joker::m_FrameRate = 60; //フレームレート
long Joker::m_FPS = 0; //秒間フレーム数
long Joker::m_OldFPS = 0; //上のバックアップ
long Joker::m_PPS = 0; //秒間ポリゴン数
long Joker::m_OldPPS = 0;//上のバックアップ
long Joker::m_PPS3D = 0;//秒間3Dポリゴン数
long Joker::m_OldPPS3D = 0; //上のバックアップ
long Joker::m_PPF = 0; //フレームポリゴン数
long Joker::m_OldPPF = 0;//上のバックアップ
long Joker::m_PPF3D = 0;//フレーム3Dポリゴン数
long Joker::m_OldPPF3D = 0;//上のバックアップ
float Joker::m_fFrameTime = 0.0f;//フレーム時間


//===============================================
//ウィンドウイベント処理関数
//===============================================
//[input]
//	hWnd:ウィンドウハンドル
//	msg:メッセージハンドル(イベントの内容)
//	wParam:イベントから通知されたデータ
//	lParam:イベントから通知されたデータ
//[return]
//	DefWindowProc:システムにイベント丸投げ
//===============================================
LRESULT CALLBACK Joker::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UINT FileNo = 0;
	
	if(msg == WM_CREATE)
	{
		//::DragAcceptFiles(hWnd, TRUE);
	}
	
	/*ウィンドウ破棄時*/
	if(msg == WM_DESTROY)
	{
		/*プログラムの終了をシステムに通知する*/
		PostQuitMessage(NULL);

		return TRUE;
	}
	
	/*キーを押したとき*/
	if(msg == WM_KEYDOWN)
	{
		if(wParam == VK_ESCAPE)
		{
			PostQuitMessage(NULL);
		}
		
		if(wParam == VK_F1)
		{
			ChangeWindowMode();
		}
	}
	
	if(msg == WM_DROPFILES)
	{
/*		m_DragFile.clear();
		
		m_hDrop = (HDROP)wParam;
		
		FileNo = DragQueryFile( (HDROP)wParam, 0xFFFFFFFF, NULL, 0);
		
		for( int i = 0;i < (int)FileNo;i++ )
		{
			::DragQueryFile(m_hDrop, i, m_DragFileName, sizeof(m_DragFileName) );
			
		}
		
		::DragFinish(m_hDrop); 
		
	*/	
	}
	
	else
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
	return 0;
		
}


//===============================================
//ウィンドウクラスの生成
//===============================================
//[input]
//	hInst:インスタンスハンドル
//[return]
//
//===============================================
bool Joker::RegisterWindowClass(HINSTANCE hInst)
{
	m_hInst = hInst;
	
	m_WndClass = _T("Game");
	
	//strcpy( m_WndClass, "Game" );
	
	strcpy( m_AppName, "Sample" );
	
	WNDCLASSEX wc;//ウィンドウクラス
	
	ZeroMemory(&wc, sizeof(wc) );//初期化
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;//構造体のサイズを拡張するバイト数
	wc.cbWndExtra = 0;//ウィンドウのサイズを拡張するバイト数
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景色
	wc.hCursor = LoadCursor(m_hInst, IDC_ARROW);//カーソル
	wc.hIcon = NULL;//アイコン
	wc.hInstance = m_hInst;//インスタンスハンドル
	wc.lpfnWndProc = WndProc;//ウィンドウのイベント処理
	wc.lpszClassName = m_WndClass;//登録するウィンドウクラス名
	wc.lpszMenuName = NULL;//メニュー名
	wc.style = NULL;//ウィンドウクラスのスタイル
	
	/*ウィンドウクラスの登録*/
	if(RegisterClassEx(&wc) == NULL)
	{
		MESSAGE("ウィンドウクラスの登録に失敗");
		return false;
	}
	
	m_hWnd = CreateWindow(wc.lpszClassName, m_AppName, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, m_WinWidth, m_WinHeight, NULL, NULL, m_hInst, NULL);
	
	/*ウィンドウを見せる*/
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);
	
	return true;	
	

}	

//===============================================
//ウィンドウのサイズ設定
//===============================================
//[input]
//	width:ウィンドウの幅
//	height:ウィンドウの高さ
//[return]
//	
//===============================================
void Joker::SetWindowSize(int width, int height)
{
	m_WinWidth = width;
	m_WinHeight = height;
}

//===============================================
//初期化
//===============================================
//[input]
//	hWnd:ウィンドウハンドル
//	hInst:インスタンスハンドル
//[return]
//
//===============================================
bool Joker::Initialize()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(pD3D == NULL)
	{
		MessageBox(NULL, "DirectXDeviceの初期化に失敗しました。", "Base", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	SetWindowInfo(m_IsWinMode);
	
	//----------------------------------------------
	//ブレンドモードの設定
	//----------------------------------------------
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 8);
	
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	
	D3DXMATRIX mat;
	
	D3DXMatrixIdentity(&mat);
	
	/*移動行列を作成*/
	D3DXMatrixTranslation(&mat, 0.0f, 0.0f, 10.0f);
	
	/*レンダリングパイプラインにダミーのビュー変換を設定*/
	pD3DDevice->SetTransform(D3DTS_VIEW, &mat);
	
	
	if(FAILED(D3DXCreateSprite(pD3DDevice, &pSprite) ) )
	{
		MessageBox(NULL, "SpriteObjectの作成に失敗しました。", "Base", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	return true;
	
}

//===============================================
//ウィンドウモードの切替
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void Joker::ChangeWindowMode()
{
	m_IsWinMode = !m_IsWinMode;
}

//===============================================
//3Dデバイスのリセット
//===============================================
//[input]
//	IsChange:画面モードを切り替えるかどうか
//===============================================
void Joker::ResetDevice(bool IsChange)
{
	HRESULT hr = NULL;
	
	/*デバイスが生成されていない場合*/
	if(pD3DDevice == NULL)
	{
		return;
	}
	
	/*スクリーンモードの変更でない時*/
	if( !IsChange && (pD3DDevice->TestCooperativeLevel() == D3D_OK) )
	{
		return;
	}
	
	
}

//===============================================
//画面情報の設定
//===============================================
//[input]
//	IsFull:ウィンドウかどうか
//[return]
//	なし
//===============================================
bool Joker::SetWindowInfo(bool IsWindow)
{
	D3DDISPLAYMODE d3ddm;
	
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) ) )
	{
		MessageBox(NULL, "DirectX3DDeviceの初期化に失敗しました。", "Base", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	D3DPRESENT_PARAMETERS d3dpp;
	
	ZeroMemory(&d3dpp, sizeof(d3dpp) );
	
	if(IsWindow)
	{
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		
	}
	
	else
	{
		d3dpp.BackBufferWidth = m_WinWidth;
		d3dpp.BackBufferHeight = m_WinHeight;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.Windowed = FALSE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.FullScreen_RefreshRateInHz = 75;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
	}
	
	//hr = Joker::GetDevice()->Reset(&d3dpp);
	//
	//if(hr == D3DERR_DEVICELOST)
	//{
	//	return true;
	//}
	//
	//if(FAILED(hr) )
	//{
	//	return false;
	//}
	
	D3DCAPS9 caps;
	DWORD behavior = D3DCREATE_MIXED_VERTEXPROCESSING;
	pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	
	m_MaxVertexBlend = caps.MaxVertexBlendMatrices;
	
	//ハードウェア
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice) ) )
	{
		//MESSAGE("ハードウェアでの作成に失敗。");
		
		//ソフトウェア
		if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice) ) ) 
		{
			MESSAGE("ソフトウェアでの作成に失敗");
			
			if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice) ) )
			{
				MessageBox(NULL, "3DDeviceObjectの初期化に失敗しました。", "Base", MB_OK | MB_ICONSTOP);
				
				return false;
			}
		}
	}
	
	return true;

}

//===============================================
//フレームの同期
//===============================================
void Joker::SyncFrame()
{
	/*現在の時間を取得*/
	m_NowTime = GetSystemTime();
	
	/*差分*/
	Uint64 DiffTime = m_NowTime - m_OldTime;
	
	//------------------------------------
	//フレームレートが0でない場合
	//------------------------------------	
	if( m_FrameRate > 0 )
	{
		Uint64 WaitTime = GetSystemTimeSecond() / m_FrameRate;
		
		//------------------------------------
		//時間経過を待つ
		//------------------------------------
		if( DiffTime < WaitTime )
		{
			Uint32 SleepTime = (Uint32)( (WaitTime - DiffTime) >> TIMER_SCALE_SHIFT );
			
			if(SleepTime > 3)
			{
				::SleepEx( SleepTime - 2, TRUE );
			}
			
			/*空ループで厳密に処理をする*/
			do
			{
				m_NowTime = GetSystemTime();
				
			} while( m_NowTime - m_OldTime < WaitTime );
			
			DiffTime = m_NowTime - m_OldTime;
  		}
	}
	
	else
	{
		::SleepEx( 0, TRUE);
	}
	
	/*終了*/
	m_OldTime = m_NowTime;
	
	/*フレーム数加算*/
	m_SyncCount++;
	m_FPS++;
	
	//------------------------------------
	//FPS算出
	//------------------------------------
	if( (m_NowTime - m_BeforeTime) >= GetSystemTimeSecond() )
	{
		m_BeforeTime = m_NowTime;
		
		//FPS保存
		m_OldFPS = m_FPS;
		m_OldPPS = m_PPS;
		m_OldPPF = m_PPS / m_FPS;
		m_OldPPF3D = m_PPS3D / m_FPS;
		m_FPS = 0;
		m_PPS = 0;
		m_PPF = 0;
		m_PPS3D = 0;
		m_PPF3D = 0;
		
		/*描画ONならタイトル部に表示*/
		if( m_IsSetWindowInfo )
		{
			char Temp[MAX_PATH]	= "";
			
			sprintf( Temp, "%s FPS[%d] PPF[%d] PPF3D[%d]", 
					 m_AppName,
					 m_OldFPS, m_OldPPF, m_OldPPF3D );
					 
			::SetWindowText(m_hWnd, Temp);
		}
	}
}

//===============================================
//現在のカウンターを取得
//===============================================
//[return]
//	カウント数
//===============================================
Uint64 Joker::GetSystemTime()
{
	Uint64 Time = (Uint64)::timeGetTime();
	return Time << TIMER_SCALE_SHIFT;
}

//===============================================
//現在のカウンターを取得(秒間)
//===============================================
//[return]
//	カウント数
//===============================================
Uint64 Joker::GetSystemTimeSecond()
{
	Uint64 Time = (Uint64)1000;
	return Time << TIMER_SCALE_SHIFT;
}

//===============================================
//D3Dオブジェクトの解放
//===============================================
//[return]
//	HRESULT値
//===============================================
HRESULT Joker::ReleaseD3DDevice()
{
	if(pSprite)
	{
		pSprite->OnLostDevice();
	}
	
	return S_OK;
}

//===============================================
//終了処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void Joker::Finalize()
{
	RELEASE(pD3DDevice);
	RELEASE(pD3D);
	RELEASE(pSprite);
	
	/*ウィンドウクラス登録解除*/
	UnregisterClass(m_WndClass, m_hInst);
}




