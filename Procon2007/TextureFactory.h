//*==============================================
//TextureFactory.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "fontsprite.h"
#include "TextureManager.h"

//===============================================
//class
//===============================================
//[Desc]
//	テクスチャ生成用クラス
//===============================================
class CTextureFactory
{
	private:
	
		static TextureManager *m_pTexMgr;
		static CFontSprite *m_Spr;
	
	public:

		CTextureFactory(void);//コンストラクタ
		virtual ~CTextureFactory(void);//デストラクタ
		
		static CFontSprite *Create(eCaption cap);//生成
};
