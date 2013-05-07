//*==============================================
//Effect.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "CXModel.h"

//===============================================
//class
//===============================================
//[Desc]
//	エフェクト用クラス
//===============================================
class CEffect :	public CXModel
{
	private:
	
		CVector3 m_vPos;//位置
		CVector3 m_vRot;//角度
		
		CVector3 m_vScale;//拡縮
		
		float m_AnimSpeed;//アニメーション速度
		
		bool m_IsVariable;//表示フラグ
		
	public:
		
		CEffect(void);//コンストラクタ
		CEffect(char *name);//コンストラクタ
		virtual ~CEffect(void);//デストラクタ
		
		void Exec();//処理
		
		void SetPosition(CVector3 Pos);//位置の設定
		void AddPosition(CVector3 Pos);//位置の加算
		void SetVariableFlag(bool flag);//表示フラグの設定
		void SetScale(CVector3 Scale);//拡縮率の設定
		void SetRotate(CVector3 Rot);
	
	public:
	
	
	
		bool GetVariableFlag();//表示フラグの設定
};
