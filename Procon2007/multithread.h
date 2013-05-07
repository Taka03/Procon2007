//*==============================================
//multithread.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "joker.h"

//===============================================
//class
//===============================================
//[Desc]
//	マルチスレッド用クラス
//===============================================
class CMultiThread
{
	private:
		
		static HANDLE m_hThread;//スレッドのハンドル
		static DWORD  m_ThreadID;//スレッドID
		
	public:
	
		static bool Initialize();//初期化
		static LRESULT CALLBACK StThreadProc(LPVOID lpParam);//スレッド処理関数
		
};