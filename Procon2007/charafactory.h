//*==============================================
//charafactory.h
//*==============================================
#pragma once 

//===============================================
//include
//===============================================
#include "character.h"

//===============================================
//class
//===============================================
//[Desc]
//	キャラクター生成用クラス
//===============================================
class CCharaFactory
{
	private:
	
	public:
	
		CCharaFactory(){};//コンストラクタ
		~CCharaFactory(){};//デストラクタ
		
		static CCharacter *Create(eCharaType type);//キャラクターの生成
		static CCharacter *Create(eCharaType chara, ePlayerType plType);//キャラクターの生成
};