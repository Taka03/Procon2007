//
//			2D用クラスヘッダー
//		Created by TAKAHASHI Masafumi
//

#pragma once


#include <d3dx9.h>
#include <d3d9types.h>
#include <windows.h>


//2D頂点フォーマット
typedef struct _D3DTLVERTEX_ {
    D3DXVECTOR3 position; // 座標
	float rhw;
    D3DCOLOR    color, specular;		// 頂点色
    FLOAT       tu, tv;   // UV
}D3DTLVERTEX;
//2Dポリゴン用
#define D3DFVF_2DVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)

//2Dポリゴン(頂点バッファ無し)
class C2DPol9
{
	FLOAT m_fumin, m_fvmin;	//UVの最小値
	FLOAT m_fumax, m_fvmax;	//UVの最大値
	D3DTLVERTEX	ver[4];	//頂点

public:
	C2DPol9()
	{
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};	//コンストラクタ
	~C2DPol9(){};	//デストラクタ

	void SetUV(const float umin, const float vmin, const float umax, const float vmax)
	{
		m_fumin = umin;m_fvmin = vmin;
		m_fumax = umax;m_fvmax = vmax;
	};	//UV値の再設定
	void ResetUV(){
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};	//UV値をデフォルトの値に戻す

	void SetPosition(const D3DXVECTOR3* vPos, const float fWidth, const float fHeight, const D3DCOLOR color);	//頂点セット
	HRESULT Draw(IDirect3DDevice9 * pd3dDevice, LPDIRECT3DTEXTURE9 pTex);	//描画
};

//2Dポリゴン(頂点バッファあり)
class C2DPolVB9
{
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	FLOAT m_fumin, m_fvmin;	//UVの最小値
	FLOAT m_fumax, m_fvmax;	//UVの最大値
	
public:
	C2DPolVB9()
	{
		m_pVB = NULL;
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};		//コンストラクタ
	~C2DPolVB9(){};	//デストラクタ
	
	void SetUV(const float umin, const float vmin, const float umax, const float vmax)
	{
		m_fumin = umin;m_fvmin = vmin;
		m_fumax = umax;m_fvmax = vmax;
	};	//UV値を再設定
	void ResetUV(){
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};	//UV値をデフォルトの値に戻す

	HRESULT Init(IDirect3DDevice9 * pd3dDevice);			//初期化(頂点バッファの作成)
	HRESULT SetPosition(const D3DXVECTOR3* vPos, const float fWidth, const float fHeight, const D3DCOLOR color);	//頂点セット
	HRESULT Draw(IDirect3DDevice9 * pd3dDevice);	//描画
};