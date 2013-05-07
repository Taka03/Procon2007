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
//	�e�N�X�`�������p�N���X
//===============================================
class CTextureFactory
{
	private:
	
		static TextureManager *m_pTexMgr;
		static CFontSprite *m_Spr;
	
	public:

		CTextureFactory(void);//�R���X�g���N�^
		virtual ~CTextureFactory(void);//�f�X�g���N�^
		
		static CFontSprite *Create(eCaption cap);//����
};
