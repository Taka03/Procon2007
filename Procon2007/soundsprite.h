//*==============================================
//soundsprite.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "sound.h"

//===============================================
//class
//===============================================
//[Desc]
//	サウンドスプライト用クラス
//===============================================
class CSoundSprite :public CSound
{
	private:
	
		CSound m_Snd;//サウンドハンドル
	
	public:
	
		CSoundSprite(){};//コンストラクタ
		CSoundSprite(char *name);//コンストラクタ
		~CSoundSprite();//デストラクタ
		
		void Init(){};//初期化
		void Exec();//処理
	
		
};