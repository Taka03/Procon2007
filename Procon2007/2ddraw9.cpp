//
//			2D用クラスソース
//		Created by TAKAHASHI Masafumi
//
#include "2ddraw9.h"

//頂点のセット
void C2DPol9::SetPosition(const D3DXVECTOR3* vPos, const float fWidth, const float fHeight, const D3DCOLOR color)
{
	//左上
	ver[0].position = *vPos;
	ver[0].rhw = 1;
	ver[0].color = color;
	ver[0].specular = 0;
	ver[0].tu = m_fumin;ver[0].tv = m_fvmin;

	//右上
	ver[1].position = *vPos;
	ver[1].position.x+=fWidth; 
	ver[1].rhw = 1;
	ver[1].color = color;
	ver[1].specular = 0;
	ver[1].tu = m_fumax;ver[1].tv = m_fvmin;

	//左下
	ver[2].position = *vPos;
	ver[2].position.y+=fHeight; 
	ver[2].rhw = 1;
	ver[2].color = color;
	ver[2].specular = 0;
	ver[2].tu = m_fumin;ver[2].tv = m_fvmax;

	//右下
	ver[3].position = *vPos;
	ver[3].position.x+=fWidth;
	ver[3].position.y+=fHeight; 
	ver[3].rhw = 1;
	ver[3].color = color;
	ver[3].specular = 0;
	ver[3].tu = m_fumax;ver[3].tv = m_fvmax;
};

//描画
HRESULT C2DPol9::Draw(IDirect3DDevice9 * pd3dDevice, LPDIRECT3DTEXTURE9 pTex)
{
	HRESULT hr = S_OK;

	if(FAILED(hr = pd3dDevice->SetFVF(D3DFVF_2DVERTEX)))
		return hr;
		
	if(FAILED(hr = pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (void*)ver, sizeof(D3DTLVERTEX))))
		return hr;
	
	if(pTex != NULL)
	{
		hr = pd3dDevice->SetTexture(0, pTex);
	}
	
	else
	{
		hr = pd3dDevice->SetTexture(0, NULL);
	}

	return hr;
}

//
//	2Dポリゴンクラス(頂点バッファあり)
//

//初期化
HRESULT C2DPolVB9::Init(IDirect3DDevice9 * pd3dDevice)
{
	HRESULT	hr = S_OK;

	hr = pd3dDevice->CreateVertexBuffer(sizeof(D3DTLVERTEX)*4, 0, D3DFVF_2DVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL );

	return hr;
}

//頂点セット
HRESULT C2DPolVB9::SetPosition(const D3DXVECTOR3* vPos, const float fWidth, const float fHeight, const D3DCOLOR color)
{
	D3DTLVERTEX*	pV = NULL;
	HRESULT hr = S_OK;

	if(!m_pVB)
		return FALSE;

	hr = m_pVB->Lock( 0, 0, (void**)&pV, 0 );
	if(FAILED(hr))return hr;

	//左上
	pV[0].position = *vPos;pV[0].rhw = 1.0f;
	pV[0].color = color;
	pV[0].specular = 0;
	pV[0].tu = m_fumin;pV[0].tv = m_fvmin;

	//右上
	pV[1].position = *vPos;pV[1].rhw = 1.0f;
	pV[1].position.x+=fWidth;
	pV[1].color = color;
	pV[1].specular = 0;
	pV[1].tu = m_fumax;pV[1].tv = m_fvmin;

	//左下
	pV[2].position = *vPos;pV[2].rhw = 1.0f;
	pV[2].position.y+=fHeight;
	pV[2].color = color;
	pV[2].specular = 0;
	pV[2].tu = m_fumin;pV[2].tv = m_fvmax;

	//右下
	pV[3].position = *vPos;pV[3].rhw = 1.0f;
	pV[3].position.x+=fWidth;pV[3].position.y+=fHeight;
	pV[3].color = color;
	pV[3].specular = 0;
	pV[3].tu = m_fumax;pV[3].tv = m_fvmax;

	hr = m_pVB->Unlock();
	if(FAILED(hr))return hr;

	return hr;
}

//描画
HRESULT C2DPolVB9::Draw(IDirect3DDevice9 * pd3dDevice)
{
	HRESULT hr = S_OK;

	hr = pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(D3DTLVERTEX) );
	if(FAILED(hr))return hr;

	hr = pd3dDevice->SetFVF( D3DFVF_2DVERTEX );
	if(FAILED(hr))return hr;

	hr = pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
	if(FAILED(hr))return hr;

	return hr;
}