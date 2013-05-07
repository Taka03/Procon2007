//*==============================================
//TextureFactory.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "TextureFactory.h"

TextureManager *CTextureFactory::m_pTexMgr = new TextureManager();
CFontSprite *CTextureFactory::m_Spr;

//===============================================
//コンストラクタ
//===============================================
CTextureFactory::CTextureFactory(void)
{

}

//===============================================
//デストラクタ
//===============================================
CTextureFactory::~CTextureFactory(void)
{
	
}

//===============================================
//テクスチャ生成
//===============================================
//[input]
//	cap:キャプション
//===============================================
CFontSprite *CTextureFactory::Create(eCaption cap)
{
	RECT Src;

	m_pTexMgr->CreateTexture("data/caption.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/chara_icon.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/loading.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/turn.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/sp_1.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/sp_2.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/red_win.png", Joker::GetDevice() );
	m_pTexMgr->CreateTexture("data/blue_win.png", Joker::GetDevice() );
	
	
	switch(cap)
	{
		case GRP_NUMBER:
		{
			Src.left = 0;
			Src.right = 320;
			Src.top = 0;
			Src.bottom = 96;
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap, Src);
			break;
		}
		
		case GRP_PLAYER1:
		{
			Src.left = 320;
			Src.right = 480;
			Src.top = 0;
			Src.bottom = 32;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		case GRP_PLAYER2:
		{
			Src.left = 320;
			Src.right = 480;
			Src.top = 32;
			Src.bottom = 64;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		
		case CAP_HP:
		{
			Src.left = 0;
			Src.right = 32;
			Src.top = 96;
			Src.bottom = 128;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);

			break;
		}
		
		case GRP_HP1:
		{
			Src.left = 0;
			Src.right = 128;
			Src.top = 128;
			Src.bottom = 192;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		case GRP_HP2:
		{
			Src.left = 128;
			Src.right = 256;
			Src.top = 128;
			Src.bottom = 192;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
	
			break;
		}
		
		
		case GRP_TURN:
		{
			Src.left = 0;
			Src.right = 256;
			Src.top = 192;
			Src.bottom = 320;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		case GRP_TEAM1:
		{
			Src.left = 0;
			Src.right = 384;
			Src.top = 320;
			Src.bottom = 384;
		
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
		
			break;
		}
		
		case GRP_TEAM2:
		{
			Src.left = 0;
			Src.right = 384;
			Src.top = 384;
			Src.bottom = 448;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		case GRP_CRYSTAL1:
		{
			Src.left = 32;
			Src.right = 64;
			Src.top = 96;
			Src.bottom = 128;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		case GRP_CRYSTAL2:
		{
			Src.left = 64;
			Src.right = 96;
			Src.top = 96;
			Src.bottom = 128;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/caption.png"), cap , Src);
			
			break;
		}
		
		case GRP_ICON:
		{
			Src.top = 0;
			Src.bottom = 0;
			Src.left = 0;
			Src.right = 0;
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/chara_icon.png"), cap, Src);
			
			break;
		}
		
		case GRP_LOADING:
		{
			Src.top = 0;
			Src.bottom = 600;
			Src.left = 0;
			Src.right = 800;		
			return new CFontSprite(m_pTexMgr->GetTexture("data/loading.png"), cap, Src);
			
			break;
		}
		
		case GRP_LARGETURN:
		{
			Src.top = 400;
			Src.bottom = 600;
			Src.left = 0;
			Src.right = 600;	
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/turn.png"), cap, Src);
			
			break;
			
		}
		
		case GRP_LARGENUMBER:
		{
			Src.top = 0;
			Src.bottom = 400;
			Src.left = 0;
			Src.right = 1000;		
				
			return new CFontSprite(m_pTexMgr->GetTexture("data/turn.png"), cap, Src);
			
			break;
		}
		
		case GRP_SPECIAL1:
		{
			Src.top = 0;
			Src.bottom = 1000;
			Src.left = 0;
			Src.right = 600;		
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/sp_1.png"), cap, Src);
			
			break;
		}
		
		case GRP_SPECIAL2:
		{
			Src.top = 0;
			Src.bottom = 1000;
			Src.left = 0;
			Src.right = 600;		
			
			return new CFontSprite(m_pTexMgr->GetTexture("data/sp_2.png"), cap, Src);
			
			break;
		}
		
		case GRP_RESULT1:
		{
			Src.top = 0;
			Src.bottom = 600;
			Src.left = 0;
			Src.right = 800;		
			return new CFontSprite(m_pTexMgr->GetTexture("data/red_win.png"), cap, Src);
			
			break;
		}
		
		case GRP_RESULT2:
		{
			Src.top = 0;
			Src.bottom = 600;
			Src.left = 0;
			Src.right = 800;		
			return new CFontSprite(m_pTexMgr->GetTexture("data/blue_win.png"), cap, Src);
			
			break;
		}
		
		default:
		{
			return NULL;
			
			break;
		}
	}
	
	return NULL;
	
}
