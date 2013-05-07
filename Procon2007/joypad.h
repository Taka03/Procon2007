//*==============================================
//joypad.h
//*==============================================
//二重インクルード防止
#pragma once

//===============================================
//include
//===============================================
#include "input.h"

//===============================================
//class
//===============================================

class CJoyPad :public CInput
{

	
	protected:
	
			static bool m_IsUseAlias;//キーの代用判定フラグ
			static int m_UseMapPadMax;
			static int m_KeyRepeatTime;//キーリピート時間
			static int m_KeyRepeatInterval;
	
	protected:
	
	public:
	
		CJoyPad(){};//コンストラクタ
		virtual ~CJoyPad(){};//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		static void Initialize(int PadMax, bool IsUseAlias, int KeyRepeatTime, int KeyRepeatInter);	//初期化
		static void SetButton(int no, ePadSort sort, int button);//ボタン設定
		static void SetAlias(int no, ePadSort sort, int Keyno);//代わりのボタン設定
		
		static void UsePOVDirection(int no, bool IsUse);//POVキーを使用
		static BOOL IsUsePOVDirection(int no);
		
		static bool GetState(int no, ePadState state, ePadSort sort);
		static void SetState(int no, ePadState state, ePadSort sort);
		
		static ePadSort CursorWrapUpDown(int no, int *pCursor, int max);
		static ePadSort CursorWrapLeftRight(int no, int *pCursor, int max);
		
		static void Update();//更新
		
		
};