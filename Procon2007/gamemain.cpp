//*==============================================
//gamemain.h
//*==============================================

//===============================================
//include 
//===============================================
#include "gamemain.h"

/*CTaskHeadクラス*/
//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CTaskHead::CTaskHead()
{
	lasttime = 0;
	Rect.Set(0, 0, 0, 0);
}

//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CTaskHead::~CTaskHead()
{

}

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CTaskHead::Init()
{
	lasttime = 0;
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CTaskHead::Exec()
{
	//const DWORD WAIT_TIME = 16;//約60FPS
	//
	////最後に行った処理からの時間を調べる
	//DWORD ntime = timeGetTime();
	//DWORD rtime = ntime - lasttime;
	//
	//lasttime = ntime;
	//
	//if(rtime < WAIT_TIME)
	//{
	//	/*ウェイト処理を行う*/
	//	Sleep(WAIT_TIME - rtime);
	//}
	//
	//if(Joker::GetDevice() == NULL)
	//{
	//	MessageBox(NULL, "pD3DDeviceが見つからない", "Base", MB_OK | MB_ICONSTOP);
	//}
	
	/*レンダリング状態のセット*/
	Joker3D::SetRenderState();
	
	/*開始宣言*/
	Joker::GetDevice()->BeginScene();
	
	/*画面のクリア*/
	//Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, COLOR_BLACK, 1.0f, 0);
	Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , COLOR_BLACK, 1.0f, 0);
	
}

/*TaskKillクラス*/
//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CTaskKill::Exec()
{
	//Joker::GetDevice()->SetViewport(&m_Client);
	
	/*表示*/
	Joker::GetDevice()->EndScene();
	Joker::GetDevice()->Present(NULL, NULL, NULL, NULL);
	
}
