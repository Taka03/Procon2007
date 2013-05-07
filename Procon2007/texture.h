//*==============================================
//texture.h
//*==============================================

//二重インクルード防止
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "2ddraw9.h"

//===============================================
//struct
//===============================================

//===============================================
//class
//===============================================
class CTexture : public CGameObject
{
	private:
	
		LPDIRECT3DTEXTURE9 m_pTex;//テクスチャハンドル
		LPDIRECT3DSURFACE9 m_pSurface;//サーフェイスハンドル
		
		RECT m_Dest;//描画先
		RECT m_Src;//描画元
		
		int m_Width;//幅
		int m_Height;//高さ
		
		C2DPol9 m_Poly;//描画
		
	protected:
	
		CVector3 m_vPos;//位置
		
	public:
	
		CTexture();//コンストラクタ
		CTexture(LPCTSTR name);//コン ストラクタ
		~CTexture();
		
		bool LoadTexture(LPCTSTR name);//テクスチャ読み込み
		bool LoadTexture(LPDIRECT3DTEXTURE9 Tex);//テクスチャ読み込み
		bool LoadTextureEx(LPCTSTR name);//テクスチャ読み込み
		void Draw(float x, float y);//描画
		void Draw(LPDIRECT3DTEXTURE9 Tex, float x, float y);//描画
		void Draw(float x, float y, float z);//描画
		//void Draw(float x, float y);//描画
		void Draw(float x, float y, float z, RECT Src);//描画
		void Draw(CVector3 pos, RECT Src);//描画
		void Draw();//描画
		
		void Init(){};
		void Exec();
		
		LPDIRECT3DTEXTURE9 GetTexture()
		{
			return m_pTex;
		}
		
		LPDIRECT3DSURFACE9 GetSurface()
		{
			return m_pSurface;
		}
		
		const int GetWidth()
		{
			return m_Width;
		}
		
		const int GetHeight()
		{
			return m_Height;
		}
		
		void SetPosition(float x, float y, float z);//位置の設定
		
		void SetDstRect(RECT Rect);//描画先設定
		void SetSrcRect(RECT Rect);//描画元設定
	
};