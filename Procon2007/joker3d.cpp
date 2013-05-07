//*==============================================
//joker3d.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joker3d.h"

LPDIRECT3DVERTEXBUFFER9 Joker3D::pD3DVBXYZBuffer;//XYZBufferの頂点バッファ
LPDIRECT3DVERTEXBUFFER9 Joker3D::pD3DVBColBuffer;//ColBufferの頂点バッファ
LPDIRECT3DINDEXBUFFER9 Joker3D::pD3DIBuffer;//インデックス・バッファ
LPDIRECT3DVERTEXSHADER9 Joker3D::pVertexShader; //頂点シェーダーを受け取る変数
LPDIRECT3DPIXELSHADER9 Joker3D::pPixelShader; //ピクセルシェーダーを受け取る変数
LPD3DXCONSTANTTABLE Joker3D::pVSConstantTable;//頂点シェーダーの定数テーブル
LPD3DXCONSTANTTABLE Joker3D::pPSConstantTable;//ピクセルシェーダーの定数テーブル
LPDIRECT3DSURFACE9 Joker3D::pDepthBuffer;//深度バッファ
LPDIRECT3DSURFACE9 Joker3D::m_pSurf = NULL;
LPDIRECT3DSURFACE9 Joker3D::m_pBackBuffer = NULL;
LPDIRECT3DTEXTURE9 Joker3D::m_pRenderTex = NULL;
C2DPolVB9		   *Joker3D::m_pDrawTex;	

D3DVIEWPORT9	Joker3D::m_Client;




//===============================================
//頂点バッファの生成
//===============================================
//[input]
//	なし
//[return]
//
//===============================================
bool Joker3D::CreateVertex()
{
	HRESULT hr;
	
	hr = pD3DDevice->CreateVertexBuffer(sizeof(XYZBuffer)*8, 0, 0, D3DPOOL_MANAGED, &pD3DVBXYZBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	hr = pD3DDevice->CreateVertexBuffer(sizeof(ColBuffer)*8, 0, 0, D3DPOOL_MANAGED, &pD3DVBColBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	XYZBuffer *pXYZBuffer;
	
	/*全体をロックする*/
	hr = pD3DVBXYZBuffer->Lock(0, 0, (LPVOID*)&pXYZBuffer, 0);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	pXYZBuffer[0].Pos.Set(1.0f, 1.0f, 1.0f);
	pXYZBuffer[1].Pos.Set(1.0f, 1.0f, 1.0f);
	pXYZBuffer[2].Pos.Set(1.0f, -1.0f, 1.0f);
	pXYZBuffer[3].Pos.Set(1.0f, -1.0f, -1.0f);
	pXYZBuffer[4].Pos.Set(-1.0f, 1.0f, 1.0f);
	pXYZBuffer[5].Pos.Set(-1.0f, 1.0f, -1.0f);
	pXYZBuffer[6].Pos.Set(-1.0f, -1.0f, 1.0f);
	pXYZBuffer[7].Pos.Set(-1.0f, -1.0f, -1.0f);
	
	/*ロック解除*/
	pD3DVBXYZBuffer->Unlock();
	
	ColBuffer *pColBuffer;
	
	hr = pD3DVBColBuffer->Lock(0, 0, (LPVOID*)&pColBuffer, 0);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	//pColBuffer[0] = D3DCOLOR_XRGB(0xff, 0xff, 0xff);
	//pColBuffer[1] = D3DCOLOR_XRGB(0xff, 0xff, 0x00);
	//pColBuffer[2] = D3DCOLOR_XRGB(0xff, 0x00, 0xff);
	//pColBuffer[3] = D3DCOLOR_XRGB(0xff, 0x00, 0x00);
	//pColBuffer[4] = D3DCOLOR_XRGB(0x00, 0xff, 0xff);
	//pColBuffer[5] = D3DCOLOR_XRGB(0x00, 0xff, 0x00); 
	//pColBuffer[6] = D3DCOLOR_XRGB(0x00, 0x00, 0xff);
	//pColBuffer[7] = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
	
	pD3DVBColBuffer->Unlock();
	
	return true;
	
};

//===============================================
//頂点バッファの書き込み
//===============================================
//[input]
//	なし
//[return]
//
//===============================================
bool Joker3D::CreateIndexVertex()
{
	
	HRESULT hr;
	
	/*インデックスバッファの生成*/
	hr = pD3DDevice->CreateIndexBuffer(36 * 2, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pD3DIBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	DWORD *pIndex;
	
	/*ロックする*/
	hr = pD3DIBuffer->Lock(0, 0, (LPVOID*)&pIndex, 0);
	
	int IndexTbl[36] =
	{
		0, 3, 1, 
		0, 2, 3, 
		0, 5, 4, 
		0, 1, 5,
		4, 2, 0,
		4, 6, 2,
		5, 6, 4,
		5, 7, 6,
		3, 6, 7,
		3, 2, 6,
		1, 7, 5,
		1, 3, 7,
	};
	
	for(int i = 0;i < 35;i++)
	{
		pIndex[i] = IndexTbl[i];
	}
	
	/*ロックを解除する*/
	pD3DIBuffer->Unlock();
	
	return true;
	
}

//===============================================
//シーンの描画開始
//===============================================
//[input]
//	なし
//[return]
//	ブール値
//===============================================
bool Joker3D::BeginScene()
{
	pD3DDevice->BeginScene();
	
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f, 0);
	
	return true;
}

//===============================================
//シーンの描画終了
//===============================================
//[input]
//	なし
//[return]
//	ブール値
//===============================================
bool Joker3D::EndScene()
{
	pD3DDevice->EndScene();
	
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
	return true;
}


//===============================================
//シェーダーのコンパイル
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
bool Joker3D::ShaderCompile()
{
	LPD3DXBUFFER pCode;
	
	HRESULT hr; 
	
	/*頂点シェーダのコンパイル*/
	hr = D3DXCompileShaderFromFile("Shader.txt", NULL, NULL, "VertexShader_Main", "vs_2_0", 0, &pCode, NULL, &pVSConstantTable);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	/*頂点シェーダーの生成*/
	hr = pD3DDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &pVertexShader);
	
	F_RELEASE(pCode);
	
	if(FAILED(hr) )
	{
		return false;//エラー
	}
	
	/*ピクセル・シェーダーのコンパイル*/
	hr = D3DXCompileShaderFromFile("Shader.txt", NULL, NULL, "PixelShader_Main", "ps_2_0", 0, &pCode, NULL, &pPSConstantTable);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	/*ピクセルシェーダーの生成*/
	hr = pD3DDevice->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &pPixelShader);
	
	F_RELEASE(pCode);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	return true;
}

//===============================================
//レンダリング状態のセット
//===============================================
//[input]
//	なし
//[return]
//
//===============================================
bool Joker3D::SetRenderState()
{
	HRESULT hr;
	
	hr = pD3DDevice->CreateDepthStencilSurface(m_WinWidth, m_WinHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &pDepthBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	/*深度バッファをデバイスに設定*/
	pD3DDevice->SetDepthStencilSurface(pDepthBuffer);
	
	/*Zバッファを有効にする*/
	hr = pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	hr = pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	
	/*背景をカリング*/
	hr = pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	return true;
}

//===============================================
//ビューポートの設定
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
bool Joker3D::SetViewPort()
{
	HRESULT hr;
	
	pD3DDevice->GetViewport(&m_Client);
	
	D3DVIEWPORT9 vp;
	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= m_WinWidth;
	vp.Height	= m_WinHeight;
	vp.MinZ		= 0.0f;
	vp.MaxZ		= 1.0f;
	hr = pD3DDevice->SetViewport(&vp);
	
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, COLOR_BLUE, 0.0f, 0);
	
	if(FAILED(hr) )
	{
		MESSAGE("ビューポートの設定に失敗");
		
		return false;
	}
	
	return true;
}

//===============================================
//サーフェイスの取得
//===============================================
//[return]
//	バックバッファ
//===============================================
LPDIRECT3DSURFACE9 Joker3D::GetSurface()
{
	return m_pSurf;
}

//===============================================
//レンダリングターゲットの設定
//===============================================
//[input]
//	なし
//[return]
//	bool値
//===============================================
bool Joker3D::SetRenderTarget()
{
	pD3DDevice->SetRenderTarget(0, m_pSurf);
	
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f, 0);
	
	pD3DDevice->SetRenderTarget(0, m_pBackBuffer);
	
	pD3DDevice->SetTexture(0, m_pRenderTex);
	
	m_pDrawTex->Draw(pD3DDevice);
	
	pD3DDevice->SetTexture(0, NULL);
	
	return true;
}

//===============================================
//デバイスの解放
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void Joker3D::ReleaseDevice()
{
		F_RELEASE(pD3DVBXYZBuffer);//XYZBufferの頂点バッファ
		F_RELEASE(pD3DVBColBuffer);//ColBufferの頂点バッファ
		//F_RELEASE(pD3DIBuffer);//インデックス・バッファ
		F_RELEASE(pVertexShader); //頂点シェーダーを受け取る変数
		F_RELEASE(pPixelShader); //ピクセルシェーダーを受け取る変数
		F_RELEASE(pVSConstantTable);//頂点シェーダーの定数テーブル
		F_RELEASE(pPSConstantTable);//ピクセルシェーダーの定数テーブル
		F_RELEASE(pDepthBuffer);
		F_RELEASE(m_pSurf);

}