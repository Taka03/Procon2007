//*==============================================
//contractor.h
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
//	ゴーレム用クラス
//===============================================
class CContractor :public CCharacter
{
	private:
	
	public:
	
		CContractor();//コンストラクタ
		CContractor(ePlayerType no);//コンストラクタ
		CContractor(ePlayerType no, const char *name);//コンストラクタ
		
		~CContractor();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理	
		
		void Rendering();
		
		void SetAbility();//特殊能力の設定
		void Burst(CCharacter *target);//自爆処理
		void Guard();//ガード処理
		
};

