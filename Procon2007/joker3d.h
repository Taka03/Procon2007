//*==============================================
//joker3d.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "joker.h"
#include "vector3.h"
#include "2ddraw9.h"

//===============================================
//struct
//===============================================
struct XYZBuffer
{
	CVector3 Pos;
};

struct ColBuffer
{
	D3DCOLOR color;
};

//D3DVERTEXELEMENT9 dec1[] =
//{
//	{0, 0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
//	{1, 0, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
//	D3DDECL_END()
//};

//===============================================
//class
//===============================================
class Joker3D :public Joker
{
	protected:
	
		static LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;//XYZBufferの頂点バッファ
		static LPDIRECT3DVERTEXBUFFER9 pD3DVBColBuffer;//ColBufferの頂点バッファ
		static LPDIRECT3DINDEXBUFFER9 pD3DIBuffer;//インデックス・バッファ
		static LPDIRECT3DVERTEXSHADER9 pVertexShader; //頂点シェーダーを受け取る変数
		static LPDIRECT3DPIXELSHADER9 pPixelShader; //ピクセルシェーダーを受け取る変数
		static LPDIRECT3DSURFACE9 pDepthBuffer;//深度バッファ		
		static LPD3DXCONSTANTTABLE pVSConstantTable;//頂点シェーダーの定数テーブル
		static LPD3DXCONSTANTTABLE pPSConstantTable;//ピクセルシェーダーの定数テーブル
		
	public:
	
		static LPDIRECT3DSURFACE9 m_pSurf;//レンダーターゲット用サーフェイス
		static LPDIRECT3DSURFACE9 m_pBackBuffer;//バックバッファ取得用
		static LPDIRECT3DTEXTURE9 m_pRenderTex;//レンダーターゲット用テクスチャ
		
//		static CTexture *m_pTex;
		
		static D3DVIEWPORT9 m_Client;
		
		static C2DPolVB9 *m_pDrawTex;
	
		Joker3D(){};//コンストラクタ
		~Joker3D(){};//デストラクタ
	
		static bool CreateVertex();//頂点バッファの生成
		static bool CreateIndexVertex();//インデックス・バッファの生成
		static bool CreateProShader();//プログラマブルシェーダーの作成
		static bool ShaderCompile();//シェーダーのコンパイル
		static bool SetRenderState();//レンダリング状態のセット
		static bool SetViewPort();//ビューポートの設定
		//static bool SetViewPort(int x, int y, int width, int height, int maxZ);//ビューポートの設定
		
		static LPDIRECT3DSURFACE9 GetSurface();//サーフェイスの取得
		static bool SetRenderTarget();
		
		static bool BeginScene();//シーンの開始
		static bool EndScene();//シーンの終了
		
		
		
		static void ReleaseDevice();//デバイスの解放
		
};