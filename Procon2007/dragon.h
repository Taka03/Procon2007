//*==============================================
//dragon.h
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
class CDragon :public CCharacter
{
	private:
	
		CVector3 m_vPos;//座標
		CVector3 m_vRot;//角度
		CVector3 m_vScale;//拡縮
		
		float m_Anim;//アニメーション
		float m_AnimSpeed;//アニメーション速度
				
	public:
	
		CDragon();//コンストラクタ
		CDragon(ePlayerType no);//コンストラクタ
		~CDragon();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
};