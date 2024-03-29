//*==============================================
//sprite.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "texture.h"

//===============================================
//class
//===============================================
//[Desc]
//	スプライト用クラス
//===============================================
class CSprite :public CTexture
{
	private:
	
		CTexture m_Tex;//テクスチャハンドル
		
	public:
	
		CSprite(){};//コンストラクタ
		CSprite(const char *name);//コンストラクタ
		~CSprite();//デストラクタ
		
		void Init(){};//初期化
		void Exec();//処理
		
		void Draw(float x, float y);
};