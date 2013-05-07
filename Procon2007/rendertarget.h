//*==============================================
//rendertarget.cpp
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
//	レンダリングターゲット開始用クラス
//===============================================
class CRenderTargetHead :public CGameObject
{
	private:
	
	
	//	LPDIRECT3DTEXTURE9	
	
	public:
	
		void Init();
		void Exec();
};

//===============================================
//class
//===============================================
//[Desc]
//	レンダリングターゲット終了用クラス
//===============================================
class CRenderTargetEnd :public CGameObject
{
	private:
	
	
	
	public:
		
		void Init(){};
		void Exec();
};

