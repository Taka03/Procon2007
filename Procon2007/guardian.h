//*==============================================
//guardian.h
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
//	ドラゴン用クラス
//===============================================
class CGuardian :public CCharacter
{
	private:
	
	public:
	
		CGuardian();//コンストラクタ
		CGuardian(ePlayerType no);//コンストラクタ
		CGuardian(ePlayerType no, const char *name);//コンストラクタ
		~CGuardian();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		
		void SetAbility();//特殊能力の設定
		void SpecialAttack();//溜め攻撃
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//カウンター
};