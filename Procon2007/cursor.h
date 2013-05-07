//*==============================================
//cursor.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"
#include "texture.h"

//===============================================
//class
//===============================================
//[Desc]
//	ゲームカーソル用クラス
//===============================================
class CCursor :public CXModel
{
	private:
	
		CVector3 m_vPos;//位置
		
		bool m_IsEnd;//キャラクター選択終了判定フラグ
		
		int Cursor;//カーソル
		
		int CursorMax;//カーソルの最大
		
		int next;//次のキャラクター
		
		//CTexture m_CurTex;//テクスチャ
		
	
	public:
	
		CCursor();//コンストラクタ
		CCursor(const char *name);//コンストラクタ
		~CCursor();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		void SetCursor(ePlayerType player, CCharacter *obj);//カーソルセット
		void SetEndFlag(bool flag);//選択終了フラグセット
		
		int GetCursor();//カーソルの取得
		
		void MoveCursor(int no, int num);//カーソルの移動
		void ChooseCharacter(CCharacter *attacker, CCharacter *target);//攻撃対象の選択
		void ChooseCharacter(ePlayerType plType, CCharacter *attacker[], CCharacter *target[]);//攻撃対象の選択
	
	public:
	
		bool GetEndFlag();//選択終了フラグの取得
};

