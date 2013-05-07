//*==============================================
//debug.h
//*==============================================

//===============================================
//include
//===============================================
#include <windows.h>
#include <stdio.h>

//===============================================
//class
//===============================================
//[Desc]
//デバッグ用クラス
//===============================================
class CDebug
{
	private:
	
		static HWND m_hWnd;//ウィンドウハンドル
	
	public:
	
		static bool Initialize();
		static void Finalize();
		
		static bool OpenWindow();//デバッグウィンドウを開く
		static void CloseWindow();//デバッグウィンドウを閉じる
		
		static void DrawString(const char *pStr,...);//文字の描画
		static void Clear();//文字の消去
		
};