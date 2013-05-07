//*==============================================
//soundmanager.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "sound.h"
#include <map>

//===============================================
//class
//===============================================
//[Desc]
//	サウンド管理用クラス
//===============================================
class CSoundManager 
{
	private:
			
		std::map<std::string, CSound*> m_MapSound;//サウンド管理
		//CSound sound;//サウンドハンドル
	
	public:
		
		CSoundManager();//コンストラクタ
		~CSoundManager();//デストラクタ
		
		HRESULT LoadSound(char *name);//サウンドの読み込み
		HRESULT DeleteSound(const char *name);//サウンドの削除
		CSound *GetSound(const char *name);//サウンドの取得
		
};