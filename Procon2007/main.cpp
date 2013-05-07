//*==============================================
//main.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joker.h"
#include "joypad.h"
#include "light.h"
#include "sound.h"
#include "debug.h"
#include "scenemanager.h"
#include "network.h"
#include "multithread.h"
#include "rand.h"

//#include "scene2.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//===============================================
//メイン関数
//===============================================
//[input]
//	hInst:アプリケーションインスタントハンドル
//[return]
//	なし
//===============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	/*シーンマネージャの生成*/
	CSceneManager *scene = new CSceneManager();
	CJoyPad *JoyPad = new CJoyPad();
	
	/*デバッグウィンドウを開く*/
	//CDebug::OpenWindow();
	
	/*ウィンドウの生成*/
	Joker::RegisterWindowClass(hInstance);

	/*初期化*/
	Joker::Initialize();
	
	/*乱数生成*/
	JRand::Seed( (Uint32)::time_t( NULL ) * ::timeGetTime() );
	
	
	
	/*Inputデバイスの生成*/
	CInput::CreateDevice();
	
	/*サウンドデバイスの生成*/
	CSound::CreateDevice();
	
	/*Ayameの初期化*/
	CSound::InitAyame();
	
	JoyPad->Init();
	
	if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
	{
		return false;
	}
	
	/*ウィンドウが閉じられるまでループ*/
	MSG msg;
	
	//while(TRUE)
	//{
	//	if( !(CNetWork::CServer::GetConnectFlag() ) )
	//	{
	//			/*ウィンドウに通達されようとしているイベントを取得*/
	//		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
	//		{
	//			/*終了イベントだったら終了*/
	//			if(msg.message == WM_QUIT)
	//			{
	//				break;
	//			}

	//			/*仮想キーメッセージを文字メッセージに変換*/
	//			TranslateMessage(&msg);
	//			
	//			/*ウィンドウにイベントを通達*/
	//			DispatchMessage(&msg);
	//		}
	//			
	//		else
	//		{
	//			
	//			/*フレームの同期*/
	//			Joker::SyncFrame();
	//			
	//			/*デバッグ画面の消去*/
	//			CDebug::Clear();
	//			
	//			/*シーンの描画*/
	//			scene->DrawScene(SCENE_INIT);
	//			
	//			/*入力機器の更新*/
	//			CInput::Update();
	//	
	//		}
	//		
	//	}
	//	
	//	else
	//	{
	//		break;
	//	}
	//	
	//}
	
	while(TRUE)
	{
		/*ウィンドウに通達されようとしているイベントを取得*/
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			/*終了イベントだったら終了*/
			if(msg.message == WM_QUIT)
			{
				break;
			}

			/*仮想キーメッセージを文字メッセージに変換*/
			TranslateMessage(&msg);
			
			/*ウィンドウにイベントを通達*/
			DispatchMessage(&msg);
			
		}
			
		else
		{
			/*フレームの同期*/
			Joker::SyncFrame();
			
			JoyPad->Exec();
			
			/*デバッグ画面の消去*/
			CDebug::Clear();
			
			/*シーンの描画*/
			scene->DrawScene();
			
			/*入力機器の更新*/
			CInput::Update();
	
		}
		
	}
	
	/*COMの開放*/
	CoUninitialize();

	/*サーバーの終了処理*/
	if( !( scene->GetAnalogFlag() ) )
	{
		CNetWork::CServer::Finalize();
	}
	
	/*デバイスの解放*/
	CInput::ReleaseDevice();
	
	/*デバッグウィンドウの終了*/
	CDebug::Finalize();
	
	/*デバイスの解放*/
	Joker3D::ReleaseDevice();

	/*終了処理*/
	Joker::Finalize();
	
	return 0;
	
}
