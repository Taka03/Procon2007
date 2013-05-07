//*==============================================
//debug.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "debug.h"

//===============================================
//variable
//===============================================
HWND CDebug::m_hWnd = NULL;

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	ブール値
//===============================================
bool CDebug::Initialize()
{
	return true;
}

//===============================================
//終了処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CDebug::Finalize()
{
	CDebug::CloseWindow();
}

//===============================================
//ウィンドウオープン
//===============================================
//[input]
//	なし
//[return]
//	ブール値
//===============================================
bool CDebug::OpenWindow()
{
	m_hWnd = ::CreateWindow("LISTBOX", "DebugWindow",
							WS_CAPTION | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_HSCROLL | WS_SIZEBOX,
							0, 0, 320, 320,
							NULL, NULL, NULL, NULL );
							
	::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);			
	::UpdateWindow(m_hWnd);
	
	return (m_hWnd != NULL);
}

//===============================================
//デバッグウィンドウを閉じる
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CDebug::CloseWindow()
{
	if(m_hWnd != NULL)
	{
		::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		m_hWnd = NULL;
	}
}

//===============================================
//文字の描画
//===============================================
//[input]
//	pStr:文字列
//[return]
//	なし
//===============================================
void CDebug::DrawString(const char *pStr,...)
{
	if(m_hWnd != NULL)
	{
		char Buff[MAX_PATH] = "";
		vsprintf(Buff, pStr, (char *)(&pStr + 1) );
		
		::SendMessage(m_hWnd, LB_ADDSTRING, 0, (long)Buff);
		::SendMessage(m_hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
	}
}

//===============================================
//画面の消去
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CDebug::Clear()
{
	if(m_hWnd != NULL)
	{
		::SendMessage(m_hWnd, LB_RESETCONTENT, 0, 0);
	}
}