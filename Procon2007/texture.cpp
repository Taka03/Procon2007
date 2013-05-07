//*==============================================
//texture.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "texture.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CTexture::CTexture()
{
	m_pTex = NULL;
	m_pSurface = NULL;
	
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	name:データ名
//[return]
//	なし
//===============================================
CTexture::CTexture(LPCTSTR name)
{
	m_pTex = NULL;
	m_pSurface = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Width = 0;
	m_Height = 0;
	
	m_Src.left = 0;
	m_Src.right = 0;
	m_Src.top = 0;
	m_Src.bottom = 0;
	
	LoadTexture(name);
	
	
	//LoadTextureEx(name);
}

//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CTexture::~CTexture()
{
	RELEASE(m_pTex);
}

//===============================================
//テクスチャ読み込み
//===============================================
//[input]
//	name:データ名
//[return]
//	bool値
//===============================================
bool CTexture::LoadTexture(LPCTSTR name)
{
	RELEASE(m_pTex);
	
	bool b = SUCCEEDED(D3DXCreateTextureFromFile(pD3DDevice, name, &m_pTex) );
	
	//if(FAILED(hr) )
	//{
	//	char Buff[256];
	//	sprintf(Buff, "%sが見つかりません", name);
	//	MESSAGE(Buff);
	//	
	//	return false;
	//}
	
	
	return b;
}

//===============================================
//テクスチャ読み込み
//===============================================
//[input]
//	Tex:テクスチャ
//[return]
//	bool値
//===============================================
bool CTexture::LoadTexture(LPDIRECT3DTEXTURE9 Tex)
{
	m_pTex = Tex;
	
	return true;
	
}

//===============================================
//テクスチャ読込み
//===============================================
//[input]
//	name:データ名
//[return]
//	bool値
//===============================================
bool CTexture::LoadTextureEx(LPCTSTR name)
{
	HRESULT hr = NULL;
	m_pTex = NULL;
	m_pSurface = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	//D3DSURFACE_DESC Desc;
	//
	//m_pBackBuffer->GetDesc(&Desc);
	//
	//if( FAILED(hr) )
	//{
	//	return false;
	//}
	
	m_Width = 0;
	m_Height = 0;
	
	D3DXIMAGE_INFO ImageInfo;
	
	hr = D3DXGetImageInfoFromFile(name, &ImageInfo);
	
	m_Width = ImageInfo.Width;
	m_Height = ImageInfo.Height;
	
	//hr = pD3DDevice->CreateOffscreenPlainSurface(m_Width, m_Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pSurface, NULL);
	
	//if(FAILED(hr) )
	//{
	//	return false;
	//}
	//
	//m_Dest.Set(m_vPos.x, m_vPos.y, (float)m_Width, (float)m_Height);
	//
	//m_Src.Set(0, 0, m_Width, m_Height);
	//
	//hr = D3DXLoadSurfaceFromFileA(m_pSurface, NULL, NULL, name, NULL, D3DX_FILTER_NONE, 0, NULL); 
	
	//if( FAILED(hr) )
	//{
	//	return false;
	//}
	
	hr = D3DXCreateTextureFromFileExA(Joker::GetDevice(), name, m_Width, m_Height, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_pTex);
	
	if( FAILED(hr) )
	{
		CHAR str[128];
		
		wsprintf(str, "%sが見つかりません", name);
		
		MESSAGE(str);

		return false;
	}
	
	D3DSURFACE_DESC Desc;
	
	m_pTex->GetLevelDesc(0, &Desc);
	
	m_Width = (int)Desc.Width;
	m_Height = (int)Desc.Height;
	
	return true;
}

//===============================================
//描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CTexture::Draw(float x, float y)
{
	/*スプライト描画開始*/
	pSprite->Begin(NULL);
	
	m_vPos.Set(x, y, 0.0f);
	
	//m_pSurface->
	
	m_Poly.SetPosition(&m_vPos, (float)(m_Width), (float)(m_Height), NULL );
	
	m_Poly.Draw(Joker::GetDevice(), m_pRenderTex );
	
	/*スプライト描画終了*/
	pSprite->End();
	
}


//===============================================
//描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//	z:Z座標
//[return]
//	なし
//===============================================
void CTexture::Draw(float x, float y, float z)
{
	/*スプライト描画開始*/
	pSprite->Begin(NULL);
	
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	
	/*描画*/
	pSprite->Draw(m_pTex, NULL, NULL, &vec, 0xFFFFFFFF);
	
	/*スプライト描画終了*/
	pSprite->End();
	
}



//===============================================
//描画
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//	z:Z座標
//	rect
//[return]
//	なし
//===============================================
void CTexture::Draw(float x, float y, float z, RECT Src)
{
	/*スプライト描画開始*/
	pSprite->Begin(D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_ALPHABLEND);
	
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	
	/*描画*/
	pSprite->Draw(m_pTex, &Src, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &vec, 0xFFFFFFFF);
	
	/*スプライト描画終了*/
	pSprite->End();
	
}



//===============================================
//描画
//===============================================
//[input]
//	Tex:テクスチャハンドル
//	x:X座標
//	y;Y座標
//===============================================
void CTexture::Draw(LPDIRECT3DTEXTURE9 Tex, float x, float y)
{
	m_pTex = Tex;
	
	/*スプライト描画開始*/
	pSprite->Begin(NULL);
	
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = 0.0f;
	
	/*描画*/
	pSprite->Draw(m_pTex, NULL, NULL, &vec, 0xFFFFFFFF);
	
	/*スプライト描画終了*/
	pSprite->End();

}

//===============================================
//描画
//===============================================
//[input]
//	pos:座標
//	Src:描画元
//===============================================
void CTexture::Draw(CVector3 pos, RECT Src)
{
	/*スプライト描画開始*/
	pSprite->Begin(D3DXSPRITE_SORT_TEXTURE);
	
	/*描画*/
	pSprite->Draw(m_pTex, &Src, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &pos, 0xFFFFFFFF);
	
	/*スプライト描画終了*/
	pSprite->End();
}


//===============================================
//描画
//===============================================
void CTexture::Draw()
{
	/*スプライト描画開始*/
	pSprite->Begin(NULL);
	
	/*描画*/
	pSprite->Draw(m_pTex, &m_Src, NULL, &m_vPos, NULL);
	
	/*スプライト描画終了*/
	pSprite->End();
	
}

//===============================================
//描画先領域の設定
//===============================================
//[input]
//	Rect:設定する矩形
//===============================================
void CTexture::SetDstRect(RECT Rect)
{
	m_Dest = Rect;
}

//===============================================
//描画元矩形
//===============================================
//[input]
//	Rect:設定する矩形
//===============================================
void CTexture::SetSrcRect(RECT Rect)
{
	m_Src = Rect;
}

//===============================================
//描画位置の設定
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//	z:Z座標
//===============================================
void CTexture::SetPosition(float x, float y, float z)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CTexture::Exec()
{
	Draw();
}
