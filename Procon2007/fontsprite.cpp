//*==============================================
//fontsprite.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "fontsprite.h"

//===============================================
//コンストラクタ
//===============================================
CFontSprite::CFontSprite()
{

}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	pFile:ファイル名
//===============================================
CFontSprite::CFontSprite(const char *pFile, eCaption cap)
{
	m_pDraw = new C2DPol9();
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
		
	m_Caption = cap;
	
	m_Text.clear();
	
	m_Tex.LoadTexture(pFile);
	
	m_plType = PLAYER_1;
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	pFile:ファイル名
//===============================================
CFontSprite::CFontSprite(LPDIRECT3DTEXTURE9 Tex, eCaption cap, RECT Src)
{
	m_pDraw = new C2DPol9();
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Caption = cap;
	
	m_CharaType = FENCER;
	
	m_Src = Src;
	
	m_Text.clear();
	
	m_Tex.LoadTexture(Tex);
	
	m_plType = PLAYER_1;
	
	m_IsVisible = true;
	
	
}


//===============================================
//コンストラクタ
//===============================================
//[input]
//	fontsize:フォントサイズ
//===============================================
CFontSprite::CFontSprite(int fontsize)
{
	m_pDraw = new C2DPol9();
	m_pDrawTex = new C2DPolVB9();
	m_pDrawTex->Init(Joker::GetDevice() );
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Caption = GRP_FONT;
	
	m_pTex = NULL;
	
	m_plType = PLAYER_1;
	
	//m_Text = 
	//m_Text = 0;
	
	
	//CreateFontA(fontsize);
	
}


//===============================================
//コンストラクタ
//===============================================
//[input]
//	pFile:ファイル名
//	Src:転送元矩形
//===============================================
CFontSprite::CFontSprite(const char *pFile, RECT Src)
{
	m_pDraw = new C2DPol9();
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Caption = GRP_NUMBER;
	
	m_Src = Src;
	
	m_Text.clear();
	
	m_TexMgr = new TextureManager();
	
	m_TexMgr->CreateTexture(pFile, pD3DDevice);
	
	m_Tex.LoadTexture( m_TexMgr->GetTexture(pFile) );
	
	m_plType = PLAYER_1;
	
	
	//::D3DXLoadSurfaceFromFile(m_pSurf, NULL, 	
	
}


//===============================================
//デストラクタ
//===============================================
CFontSprite::~CFontSprite()
{
	RELEASE(m_pSurface);
}

//===============================================
//フォントの作成
//===============================================
//[input]
//	fontsize:フォントサイズ
//[return]
//	HRESULT値
//===============================================
HRESULT CFontSprite::CreateFontA(int fontsize)
{
//	m_pDraw = new C2DPol9();
//	m_pDraw->Init(pD3DDevice);
	
	//LOGFONT lf = {fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
	//				CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("ＭＳ 明朝")};
	//				
	//m_hFont = CreateFontIndirectA(&lf);
	//
	//if(m_hFont == NULL)					
	//{
	//	return E_FAIL;
	//}
	//
	//m_hdc = GetDC(NULL);
	//m_hOldFont = (HFONT)SelectObject(m_hdc, m_hFont);
	//
	return S_OK;
}

//===============================================
//フォントビットマップの取得
//===============================================
//[input]
//	data:フォントデータ
//===============================================
HRESULT CFontSprite::GetFontBitMap(char *pData, float PosX, float PosY)
{
	//m_pDraw = new C2DPol9();
//	m_pDraw->Init(pD3DDevice);
	
	LOGFONT lf = {22, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
					CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T("ＭＳ 明朝")};
					
	HFONT hFont;
	
	if(!(hFont = CreateFontIndirect(&lf) ))					
	{
		return E_FAIL;
	}
	
	HDC hdc = GetDC(NULL);
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	
	char *Str = pData;
	
	UINT code = 0;
	
	#if _UNICODE
	
		code = (UINT)*Str;
		
	#else
	
			if(IsDBCSLeadByte(*Str) )
			{
				code = (BYTE)Str[0] << 8 | (BYTE)Str[1];
			}
			
			else
			{
				code = Str[0];
			}
		
	#endif
	
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	
	GLYPHMETRICS GM;
	
	const MAT2 Mat = 
	{
		{0,1},{0,0},{0,0},{0,1}
	};
	
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);
	
	//デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);
	
	/*頂点情報*/
	float a = 1.0f; //テクスチャの縮尺
	float fTexW = GM.gmCellIncX * a;//テクスチャの横幅
	float fTexH = TM.tmHeight * a;//テクスチャの高さ
	DWORD FontColor = 0xffffffff;//テクスチャカラー
	
	//m_pDrawTex->SetPosition(&D3DXVECTOR3(PosX, PosY, 0.0f), fTexW, fTexH, FontColor);
	
	m_pDraw->SetPosition(&D3DXVECTOR3(PosX, PosY, 0.0f), fTexW, fTexH, FontColor);
	
	/*テクスチャ作成*/
	
    if(FAILED(Joker::GetDevice()->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
                                                    D3DPOOL_DEFAULT, &m_pTex, NULL)))
	{
		delete[] ptr;
		return E_FAIL;
	}
	
	//------------------------------------
	//フォント情報の書き込み
	//------------------------------------
	
	/*テクスチャにフォントビットマップ書き込み*/
	D3DLOCKED_RECT LockedRect;
	if(FAILED( m_pTex->LockRect( 0, &LockedRect, NULL, D3DLOCK_DISCARD ) ) )
	{
		delete[] ptr;
		return E_FAIL;
	}
	
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	FillMemory(LockedRect.pBits , LockedRect.Pitch * TM.tmHeight, 0);

	for(y=iOfs_y; y<iOfs_y+iBmp_h; y++)
	{
		for(x=iOfs_x; x<iOfs_x+iBmp_w; x++)
		{
		  Alpha = (255 * ptr[x-iOfs_x + iBmp_w*(y-iOfs_y)]) / (Level-1);
		  Color = 0x00ffffff | (Alpha<<24);
		  memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4*x, &Color, sizeof(DWORD));
		}
	
	}
	
	m_pTex->UnlockRect(0);
	delete[] ptr;
	
	m_Tex.LoadTexture(m_pTex);
	
	Joker::GetDevice()->SetTexture(0, m_pTex);
	
	Joker::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE ); 
    Joker::GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP , D3DTOP_MODULATE );
    Joker::GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE ); 
    Joker::GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    Joker::GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP , D3DTOP_MODULATE ); 
    Joker::GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE ); 	
    
	m_pDrawTex->Draw(Joker::GetDevice() );
	
	//Joker::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//Joker::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//Joker::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	

    return S_OK;
	
}

//===============================================
//初期化
//===============================================
void CFontSprite::Init()
{

}

//===============================================
//処理
//===============================================
void CFontSprite::Exec()
{
	if(m_Tex.GetTexture() != NULL)
	{
		this->m_Tex.GetTexture()->GetSurfaceLevel(0, &m_pSurface);
			
		/*バックバッファの取得*/
		Joker::GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	}
	
	//Joker::GetDevice()->SetRenderTarget(0, m_pSurface);
	
	switch(m_Caption)
	{
		case GRP_NUMBER:
		{
			if(m_IsVisible)
			{
				if(!m_Text.empty() )
				{
					DrawNumber(m_vPos.x, m_vPos.y);
				}
			}
			
			break;
		}
		
		case GRP_FONT:
		{
			//DrawFont(m_vPos.x, m_vPos.y);			
			break;
		}
		
		case GRP_PLAYER1:
		{
			Draw(0, 502);
			break;
		}
		
		case GRP_PLAYER2:
		{
			Draw(656, 502);
			break;
		}
		
		case GRP_TURN:
		{
			Draw(288, 0);
			break;
		}	
		
		case GRP_TEAM1:
		{
			Draw(0, 520);
			break;
		}
		
		case GRP_TEAM2:
		{
			Draw(416, 520);
			break;
		}
		
		case GRP_CRYSTAL1:
		{
			Draw(336, 502);
			break;
		}
		
		case GRP_CRYSTAL2:
		{
			Draw(436, 502);
			break;
		}
		
		case GRP_LARGETURN:
		{
			Draw(100, 100);
			break;
		}
		
		case GRP_LARGENUMBER:
		{
			DrawLargeNumber(m_vPos.x, m_vPos.y);
			break;
		}
		
		//case GRP_SPECIAL:
		//{
		//	break;
		//}
		
		case GRP_ICON:
		{
//			DrawCharaIcon(m_vPos.x, m_vPos.y, m_CharaType);
			break;
		}
		
		default:
		{
			Draw(m_vPos.x, m_vPos.y);
			
			break;
		}
		
	}
	
}

//===============================================
//数字の描画
//===============================================
//[input]
//	pText:テキスト
//	x:X座標
//	y:Y座標
//===============================================
void CFontSprite::DrawNumber(char *pText, float x, float y)
{
	const int FONT_SIZE = 32;
	
	RECT rect;
	//unsigned char alphabet;
	//int strx;
	//int stry;
	float DispX;
	float DispY;
	
	/*座標の保持*/
	DispX = x;
	DispY = y;
	
	while( *pText != NULL )
	{
		switch(*pText)
		{
			case '0':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 0;
				rect.right = FONT_SIZE;
				
				break;
			}
			
			case '1':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = FONT_SIZE;
				rect.right = 2*FONT_SIZE;
				
				break;
			}
			
			case '2':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 2*FONT_SIZE;
				rect.right = 3*FONT_SIZE;

				break;
			}
			
			case '3':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 3*FONT_SIZE;
				rect.right = 4*FONT_SIZE;
				
				break;
			}
			
			case '4':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 4*FONT_SIZE;
				rect.right = 5*FONT_SIZE;
				
				break;
			}

			case '5':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 5*FONT_SIZE;
				rect.right = 6*FONT_SIZE;

				break;
			}

			case '6':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 6*FONT_SIZE;
				rect.right = 7*FONT_SIZE;
				
				break;
			}

			case '7':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 7*FONT_SIZE;
				rect.right = 8*FONT_SIZE;
				
				break;
			}
			
			case '8':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 8*FONT_SIZE;
				rect.right = 9*FONT_SIZE;
				
				break;
			}
			
			case '9':
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 9*FONT_SIZE;
				rect.right = 10*FONT_SIZE;
				
				break;
			}
			
			default:
			{
				rect.top = 0;
				rect.bottom = FONT_SIZE;
				rect.left = 0;
				rect.right = FONT_SIZE;
				
				break;
			}
			
		}
		
		*pText++;	
		
		//Joker::GetDevice()->SetRenderTarget(0, m_pBackBuffer);
		
		//m_pDraw->Draw(pD3DDevice, m_Tex.GetTexture() );
		//
		//Joker::GetDevice()->SetTexture(0, NULL);
		//
	
		m_Tex.Draw(DispX, DispY, 0.0f, rect);
		
		//m_Tex.Draw(DispX, DispY, 0.0f);	
		
		DispX += FONT_SIZE;
		
	}
	
	
	
	//while( *pText != NULL )
	//{
	//	alphabet = *pText++;
	//	
	//	if( alphabet == 0x0a )
	//	{//改行処理
	//		DispX = x;
	//		DispY += FONT_SIZE_Y;
	//		continue;
	//	}
	//	
	//	/*文字の表示処理*/
	//	alphabet -= ' ';
	//	
	//	/*元のビットマップ座標を計算*/
	//	strx = (alphabet % 0x10) * FONT_SIZE_X;
	//	stry = (alphabet / 0x10) * FONT_SIZE_Y;
	//	
	//	rect.top = stry;
	//	rect.bottom = stry + FONT_SIZE_Y;
	//	rect.left = strx;
	//	rect.right = strx + FONT_SIZE_X;
	//	
	//	
	//	DispX += FONT_SIZE_X;
	//	
	//}
}

//===============================================
//数字の描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CFontSprite::DrawNumber(float x, float y)
{
	const int FONT_SIZE = 32;
	
	RECT rect;
	//unsigned char alphabet;
	//int strx;
	//int stry;
	float DispX;
	float DispY;
	
	/*座標の保持*/
	DispX = x;
	DispY = y;
	
	//std::string::iterator i = m_Text.begin();
	
	const char *Buff= m_Text.c_str();
	
	while( *Buff != NULL )
	{
		//if(m_Text.find("0") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 0;
		//	rect.right = FONT_SIZE;
		//}
		//
		//else if(m_Text.find("1") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = FONT_SIZE;
		//	rect.right = 2*FONT_SIZE;
		//
		//}
		//
		//else if(m_Text.find("2") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 2*FONT_SIZE;
		//	rect.right = 3*FONT_SIZE;
		//
		//}

		//else if(m_Text.find("3") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 3*FONT_SIZE;
		//	rect.right = 4*FONT_SIZE;
		//
		//}

		//else if(m_Text.find("4") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 4*FONT_SIZE;
		//	rect.right = 5*FONT_SIZE;
		//
		//}

		//else if(m_Text.find("5") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 5*FONT_SIZE;
		//	rect.right = 6*FONT_SIZE;
		//
		//}

		//else if(m_Text.find("6") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 6*FONT_SIZE;
		//	rect.right = 7*FONT_SIZE;
	
		//}

		//else if(m_Text.find("7") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 7*FONT_SIZE;
		//	rect.right = 8*FONT_SIZE;
		//
		//}

		//else if(m_Text.find("8") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 8*FONT_SIZE;
		//	rect.right = 9*FONT_SIZE;
		//
		//}
		//
		//else if(m_Text.find("9") )
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 9*FONT_SIZE;
		//	rect.right = 10*FONT_SIZE;
		//
		//}
		//
		//else
		//{
		//	rect.top = 0;
		//	rect.bottom = FONT_SIZE;
		//	rect.left = 9*FONT_SIZE;
		//	rect.right = 10*FONT_SIZE;
		//
		//}
		
		if(*Buff == '1')
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 0;
			rect.right = FONT_SIZE;
		}
		
		else if(*Buff == '2')
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = FONT_SIZE;
			rect.right = 2*FONT_SIZE;
		
		}
		
		else if(*Buff == '3')
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 2*FONT_SIZE;
			rect.right = 3*FONT_SIZE;
		
		}

		else if(*Buff == '4' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 3*FONT_SIZE;
			rect.right = 4*FONT_SIZE;
		
		}

		else if(*Buff == '5' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 4*FONT_SIZE;
			rect.right = 5*FONT_SIZE;
		
		}

		else if(*Buff == '6') 
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 5*FONT_SIZE;
			rect.right = 6*FONT_SIZE;
		
		}

		else if(*Buff == '7' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 6*FONT_SIZE;
			rect.right = 7*FONT_SIZE;
	
		}

		else if(*Buff == '8' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 7*FONT_SIZE;
			rect.right = 8*FONT_SIZE;
		
		}

		else if(*Buff == '9' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 8*FONT_SIZE;
			rect.right = 9*FONT_SIZE;
		
		}
		
		else if(*Buff == '0' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 9*FONT_SIZE;
			rect.right = 10*FONT_SIZE;
		
		}
		
		else
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 9*FONT_SIZE;
			rect.right = 10*FONT_SIZE;
		
		}
		
		*Buff++;
	
		/*サーフェイスレベルの取得*/
		//m_Tex.GetTexture()->GetSurfaceLevel(0, &m_pSurf);
		//
		///*バックバッファの取得*/
		//pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	
		//pD3DDevice->SetRenderTarget(0, m_pBackBuffer);
		//
		//pD3DDevice->SetTexture(0, m_Tex.GetTexture());
		
		//Joker::GetDevice()->SetRenderTarget(0, m_pBackBuffer);
		
		//m_pDraw->Draw(pD3DDevice, m_Tex.GetTexture() );
		
		//Joker::GetDevice()->SetTexture(0, NULL);
		
		
		/*描画*/
		m_Tex.Draw(DispX, DispY, 0.0f, rect);
		
		//m_pDraw->SetPosition(&D3DXVECTOR3(DispX, DispY, 0.0f), FONT_SIZE, FONT_SIZE, NULL);
		
		//m_pDraw->Draw(pD3DDevice, m_Tex.GetTexture() );
		
		//pD3DDevice->SetTexture(0, NULL);
		
		
		//m_Tex.Draw(DispX, DispY, 0.0f);	
		
		DispX += FONT_SIZE - 10;
		
	}
	
}

//===============================================
//数字の描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CFontSprite::DrawLargeNumber(float x, float y)
{
	const int FONT_SIZE = 200;
	
	RECT rect;
	//unsigned char alphabet;
	//int strx;
	//int stry;
	float DispX;
	float DispY;
	
	/*座標の保持*/
	DispX = x;
	DispY = y;
	
	//std::string::iterator i = m_Text.begin();
	
	const char *Buff= m_Text.c_str();
	
	while( *Buff != NULL )
	{
		
		if(*Buff == '1')
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 0;
			rect.right = FONT_SIZE;
		}
		
		else if(*Buff == '2')
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = FONT_SIZE;
			rect.right = 2*FONT_SIZE;
		
		}
		
		else if(*Buff == '3')
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 2*FONT_SIZE;
			rect.right = 3*FONT_SIZE;
		
		}

		else if(*Buff == '4' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 3*FONT_SIZE;
			rect.right = 4*FONT_SIZE;
		
		}

		else if(*Buff == '5' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 4*FONT_SIZE;
			rect.right = 5*FONT_SIZE;
		
		}

		else if(*Buff == '6') 
		{
			rect.top = FONT_SIZE;
			rect.bottom = FONT_SIZE * 2;
			rect.left = 0;
			rect.right = FONT_SIZE;
		
		}

		else if(*Buff == '7' )
		{
			rect.top = FONT_SIZE;
			rect.bottom = FONT_SIZE * 2;
			rect.left = FONT_SIZE;
			rect.right = 2*FONT_SIZE;
	
		}

		else if(*Buff == '8' )
		{
			rect.top = FONT_SIZE;
			rect.bottom = FONT_SIZE * 2;
			rect.left = 2*FONT_SIZE;
			rect.right = 3*FONT_SIZE;
		
		}

		else if(*Buff == '9' )
		{
			rect.top = FONT_SIZE;
			rect.bottom = FONT_SIZE * 2;
			rect.left = 3*FONT_SIZE;
			rect.right = 4*FONT_SIZE;
		
		}
		
		else if(*Buff == '0' )
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 4*FONT_SIZE;
			rect.right = 5*FONT_SIZE;
		
		}
		
		else
		{
			rect.top = 0;
			rect.bottom = FONT_SIZE;
			rect.left = 9*FONT_SIZE;
			rect.right = 10*FONT_SIZE;
		
		}
		
		*Buff++;
	
		/*描画*/
		m_Tex.Draw(DispX, DispY, 0.0f, rect);
		
		DispX += FONT_SIZE;
		
	}
	
}

//===============================================
//特殊能力(攻撃ver)の描画
//===============================================
//[input]
//	spType:特殊能力タイプ	
//===============================================
void CFontSprite::DrawSpecialAttack(eSpecial spType)
{
	const int WIDTH  = 600;
	const int HEIGHT = 200; 
	
	RECT Src;
	
	switch(spType)
	{
		case CRITICAL:
		{
			Src.top = 0;
			Src.bottom = HEIGHT;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		}
		
		case ALLMAGIC:
		{
			Src.top = HEIGHT;
			Src.bottom = HEIGHT * 2;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		}
		
		case CHARGE_ATTACK:
		{
			Src.top = HEIGHT * 2;
			Src.bottom = HEIGHT * 3;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;	
		}
		
		case BURST:
		{
			Src.top = HEIGHT * 3;
			Src.bottom = HEIGHT * 4;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		}
		
		case FIRST_ATTACK:
		{
			Src.top = HEIGHT * 4;
			Src.bottom = HEIGHT * 5;
			Src.left = 0;
			Src.right = WIDTH;
			
			
			break;
		}
		
	}
	
	m_Tex.Draw(m_vPos, Src);
}

//===============================================
//特殊能力(特殊ver)の描画
//===============================================
//[input]
//	spType:特殊能力タイプ	
//===============================================
void CFontSprite::DrawSpecialAssist(eSpecial spType)
{
	const int WIDTH  = 600;
	const int HEIGHT = 200; 
	
	RECT Src;
	
	switch(spType)
	{
		case ALTER:
		{
			Src.top = 0;
			Src.bottom = HEIGHT;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;	
		}
		
		case RECOVER:
		{
			Src.top = HEIGHT;
			Src.bottom = HEIGHT * 2;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		
		}
		
		case COUNTER:
		{
			Src.top = HEIGHT * 2;
			Src.bottom = HEIGHT * 3;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		}
		
		case GUARD:
		{
			Src.top = HEIGHT * 3;
			Src.bottom = HEIGHT * 4;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		}
		
		case BUILDUP:
		{
			Src.top = HEIGHT * 4;
			Src.bottom = HEIGHT * 5;
			Src.left = 0;
			Src.right = WIDTH;
			
			break;
		
		}		
	}
	
	m_Tex.Draw(m_vPos, Src);
	
}




//===============================================
//描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CFontSprite::Draw(float x, float y)
{
	/*サーフェイスレベルの取得*/
	//m_Tex.GetTexture()->GetSurfaceLevel(0, &m_pSurf);
	//
	///*バックバッファの取得*/
	//pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	//
	//pD3DDevice->SetRenderTarget(0, m_pBackBuffer);
	
	//pD3DDevice->SetTexture(0, m_Tex.GetTexture());
	
	//m_pDraw->SetPosition(&D3DXVECTOR3(x, y, 0.0f), m_Src.right, m_Src.bottom 
	
	//Joker::GetDevice()->SetRenderTarget(0, m_pBackBuffer);
	
	//m_pDraw->Draw(pD3DDevice, m_Tex.GetTexture() );
	
	//Joker::GetDevice()->SetTexture(0, NULL);
	
	
	m_Tex.Draw(x, y, 0.0f, m_Src);
	
	//pD3DDevice->SetTexture(0, NULL);
	
}

//===============================================
//武器アイコンの描画
//===============================================
//[input]
//	plType:プレイヤータイプ
//	type:キャラタイプ
//===============================================
void CFontSprite::DrawWeaponIcon(eCharaType type)
{
	const int SPRITE_SIZE = 50;
	
	RECT rect;
	
	switch(type)
	{
		case FENCER:
		{
			if(m_plType == PLAYER_1)
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = 0;
				rect.right = SPRITE_SIZE;
			}
			
			else
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 5;
				rect.right = SPRITE_SIZE * 6;
			}
			
			break;
		}
		
		case MAGICIAN:
		{
			if(m_plType == PLAYER_1)
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE;
				rect.right = SPRITE_SIZE * 2;
			}
			
			else
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 6;
				rect.right = SPRITE_SIZE * 7;
			}
			
			break;
		}
		
		case RANGER:
		{
			if(m_plType == PLAYER_1)
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 2;
				rect.right = SPRITE_SIZE * 3;
			}
			
			else
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 7;
				rect.right = SPRITE_SIZE * 8;
			}
			
		
			break;
		}
		
		case CONTRACTOR:
		{
			if(m_plType == PLAYER_1)
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 3;
				rect.right = SPRITE_SIZE * 4;
			}
			
			else
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 8;
				rect.right = SPRITE_SIZE * 9;
			}
			
			break;
		}
		
		case GUARDIAN:
		{
			if(m_plType == PLAYER_1)
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 4;
				rect.right = SPRITE_SIZE * 5;
			}
			
			else
			{
				rect.top = 0;
				rect.bottom = SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 9;
				rect.right = SPRITE_SIZE * 10;
			}

			break;
		}
		
	}
	
	m_Tex.Draw(m_vPos.x, m_vPos.y, 0.0f, rect);
		
}

//===============================================
//キャラアイコンの描画
//===============================================
//[input]
//	plType:プレイヤータイプ
//	type:キャラタイプ
//===============================================
void CFontSprite::DrawCharaIcon(ePlayerType plType, eCharaType type)
{
	const int SPRITE_SIZE = 75;
	
	RECT rect;
	
	switch(type)
	{
		case FENCER:
		{
			if(plType == PLAYER_1)
			{
				rect.top = 50 + SPRITE_SIZE;
				rect.bottom = 50 + SPRITE_SIZE * 2;
				rect.left = 0;
				rect.right = SPRITE_SIZE;
			
			}
			
			else
			{
				
				rect.top = 50;
				rect.bottom = 50 + SPRITE_SIZE;
				rect.left = 0;
				rect.right = SPRITE_SIZE;
				
			}
			
			break;
		}
		
		case MAGICIAN:
		{
			if(plType == PLAYER_1)
			{
				rect.top = 50;
				rect.bottom = 50 + SPRITE_SIZE;
				rect.left = SPRITE_SIZE;
				rect.right = SPRITE_SIZE * 2;
			}
			
			else
			{
				rect.top = 50 + SPRITE_SIZE;
				rect.bottom = 50 + SPRITE_SIZE * 2;
				rect.left = SPRITE_SIZE;
				rect.right = SPRITE_SIZE * 2;
			}
			
			break;
		}
		
		case RANGER:
		{
			if(plType == PLAYER_1)
			{
				rect.top = 50;
				rect.bottom = 50 + SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 2;
				rect.right = SPRITE_SIZE * 3;
			}
			
			else
			{
				rect.top = 50 + SPRITE_SIZE;
				rect.bottom = 50 + SPRITE_SIZE * 2;
				rect.left = SPRITE_SIZE * 2;
				rect.right = SPRITE_SIZE * 3;
			}
			
		
			break;
		}
		
		case CONTRACTOR:
		{
			if(plType == PLAYER_1)
			{
				rect.top = 50;
				rect.bottom = 50 + SPRITE_SIZE;
				rect.left = SPRITE_SIZE * 3;
				rect.right = SPRITE_SIZE * 4;
			}
			
			else
			{
				rect.top = 50 + SPRITE_SIZE;
				rect.bottom = 50 + SPRITE_SIZE * 2;
				rect.left = SPRITE_SIZE * 3;
				rect.right = SPRITE_SIZE * 4;
			}
			
			break;
		}
		
		case GUARDIAN:
		{
			if(plType == PLAYER_1)
			{
				rect.top = 50 + SPRITE_SIZE;
				rect.bottom = 50 + SPRITE_SIZE * 2;
				rect.left = SPRITE_SIZE * 4;
				rect.right = SPRITE_SIZE * 5;
			}
			
			else
			{
				rect.top = 50 + SPRITE_SIZE;
				rect.bottom = 50 + SPRITE_SIZE * 2;
				rect.left = SPRITE_SIZE * 4;
				rect.right = SPRITE_SIZE * 5;
			}

			break;
		}
		
	}
	
	m_Tex.Draw(m_vPos.x, m_vPos.y, 0.0f, rect);
		
	
	
	
	
}


//===============================================
//描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CFontSprite::DrawFont(void)
{
	const int FONT_SIZE = 32;
	
//	RECT rect;
	//unsigned char alphabet;
	//int strx;
	//int stry;
	float DispX;
	float DispY;
	
	/*座標の保持*/
	DispX = m_vPos.x;
	DispY = m_vPos.y;
	
	string OldStr;
	
	for(int i = 0;i < 17;i++ )
	{
		OldStr += m_pName[i];
	}
	
	string::iterator i = OldStr.begin();
	
	for( i = OldStr.begin();i != OldStr.end() - 1;i+=2 )
	{
		string Str;
		
		Str += m_pName[*i];
		Str += m_pName[*(i+1)];
		
		GetFontBitMap( (char *)Str.c_str(), DispX, DispY);
		
		m_pDraw->Draw(pD3DDevice, m_Tex.GetTexture() );
		
		//OldStr.erase(
		
		DispX += FONT_SIZE;
		
	}
	
	
		
	//DispX += FONT_SIZE;
	
		

	
}



//===============================================
//キャプションの設定
//===============================================
//[input]
//	cap:設定するキャプション
//===============================================
void CFontSprite::SetCaption(eCaption cap)
{
	m_Caption = cap;
}

//===============================================
//位置の設定
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CFontSprite::SetPosition(float x, float y)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = 0.0f;
}

//===============================================
//転送元矩形の設定
//===============================================
//[input]
//	Src:設定用矩形
//===============================================
void CFontSprite::SetRect(RECT Src)
{
	m_Src = Src;
}

//===============================================
//テキストの設定
//===============================================
//[input]
//	pText:テキスト
//===============================================
void CFontSprite::SetTeamName(char *pText)
{
	for(int i = 0;i < 17;i++ )
	{
		m_pName[i] = pText[i];
	}
}

//===============================================
//テキストの設定
//===============================================
//[input]
//	pText:テキスト
//===============================================
void CFontSprite::SetText(string Text)
{
	this->m_Text = Text;
}

//===============================================
//キャラタイプの設定
//===============================================
//[input]
//	type:キャラタイプ
//===============================================
void CFontSprite::SetCharaType(eCharaType type)
{
	m_CharaType = type;
}

//===============================================
//プレイヤータイプの設定
//===============================================
//[input]
//	type:プレイヤータイプ
//===============================================
void CFontSprite::SetPlayerType(ePlayerType type)
{
	m_plType = type;
}

//===============================================
//存在フラグの設定
//===============================================
//[input]
//	flag:存在フラグ
//===============================================
void CFontSprite::SetVisibleFlag(bool flag)
{
	m_IsVisible = flag;
}

//===============================================
//存在フラグの取得
//===============================================
//[return]
//	存在フラグ
//===============================================
bool CFontSprite::GetVisibleFlag()
{
	return m_IsVisible;
}




//===============================================
//位置の取得
//===============================================
//[return]
//	位置
//===============================================
CVector3 CFontSprite::GetPosition()
{
	return m_vPos;
}



