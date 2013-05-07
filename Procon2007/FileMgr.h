//*==============================================
//FileMgr.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "file.h"
#include "sound.h"
#include "texture.h"
#include "gameobject.h"
#include "CXModel.h"
#include <map>
#include <set>
#include <iostream>
#include <iomanip>

//===============================================
//enum
//===============================================
enum eFileType
{
	TEXTURE,
	SOUND,
	MODEL,
};

//===============================================
//class
//===============================================
//[Desc]
//	ファイル管理用クラス
//===============================================
class CFileMgr
{
	private:
	
		list<char *> m_liFile;
				
	public:
	
		CFileMgr(void);//コンストラクタ
		//CFileMgr
		~CFileMgr(void);//デストラクタ
		
		CGameObject *CreateFromFile(eFileType inFileType, std::string inFileName);//ファイルの読み込み
		string GetFileName(std::string inFileName);//ファイル名の取得
};
