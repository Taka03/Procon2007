//===============================================
//light.h
//===============================================
//二重インクルード防止
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//class
//===============================================
class CLight :public CGameObject
{
	private:
	
		static D3DLIGHT9 m_light;
		static CVector3 m_vPos;	
	
	public:
	
		CLight();//コンストラクタ	
		
		void Init();//初期化
		void Exec();
		
		static void SetPosition(CVector3 *Pos);//ライトの位置の設定
		
		static void SetLightParam();//ライト状態の設定
		static bool SetLight();//ライトの設定
};