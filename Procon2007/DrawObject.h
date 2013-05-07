//*==============================================
//DrawObject.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//class
//===============================================
//[Desc]
//	描画用オブジェクト
//===============================================
class CDrawObject :	public CGameObject
{
	protected:
	
		CVector3 m_vPos; //座標
		CVector3 m_vRot;//角度
		CVector3 m_vScale;//拡縮
	
	public:
	
		CDrawObject(void);//コンストラクタ
		virtual ~CDrawObject(void);//デストラクタ
		
		virtual void Init(){};//初期化
		virtual void Exec(){};//処理
		
	public:
	
		CVector3 GetPosition();//位置の取得
		CVector3 GetRotate();//回転角度の取得
		CVector3 GetScale();//拡縮の取得
};
