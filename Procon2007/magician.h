//*==============================================
//magician.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"
#include "Effect.h"

//===============================================
//class
//===============================================
//[Desc]
//	魔法使い用クラス
//===============================================
class CMagician :public CCharacter
{
	private:
	
		CEffect *Magic;
					
	public:
	
		CMagician();//コンストラクタ
		CMagician(ePlayerType no);//コンストラクタ
		CMagician(ePlayerType no, const char *name);//コンストラクタ
		~CMagician();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		
		void SetAbility();//特殊能力の設定
		void SpecialAttack();//全体攻撃
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//ライフ回復
		
		void SetAnimation(int animID);
		
		void DrawEffect();
};