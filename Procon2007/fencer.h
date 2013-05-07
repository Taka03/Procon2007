//*==============================================
//fencer.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"
#include "camera.h"

//===============================================
//class
//===============================================
//[Desc]
//	剣士用クラス
//===============================================
class CFencer :public CCharacter
{
	private:
	
		//void ProcessCritical();//クリティカル用の処理
	
	public:
	
		CFencer();//コンストラクタ
		CFencer(ePlayerType no);//コンストラクタ
		CFencer(ePlayerType no, const char *name);//コンストラクタ
		~CFencer();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		

		void SetAbility();//特殊能力の設定
		
		void SpecialAttack();//クリティカル攻撃
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//身代わり
		
		void Rendering();//レンダリング
		
};