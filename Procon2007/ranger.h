//*==============================================
//ranger.h
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
//	獣用クラス
//===============================================
class CRanger :public CCharacter
{
	private:
	
		//CVector3 m_vPos;//座標
		//CVector3 m_vRot;//角度
		//CVector3 m_vScale;//拡縮
		//
		//float m_Anim;//アニメーション
		//float m_AnimSpeed;//アニメーション速度
				
	public:
	
		CRanger();//コンストラクタ
		CRanger(ePlayerType no);//コンストラクタ
		CRanger(ePlayerType no, const char *name);//コンストラクタ
		~CRanger();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		void Rendering();//レンダリング
		
		void SetAbility();//特殊能力の設定
		void SpecialAttack();//先制攻撃
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//強化
};