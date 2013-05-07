//*==============================================
//file.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//struct
//===============================================
//ファイルデータ
struct FILEDATA
{
	HANDLE hFile;						//ファイルハンドル
	Bool IsPack;						//パックファイルか否か
	Uint32 Start;						//ファイル開始位置
	Uint32 Size;						//ファイル終了位置
	FILETIME CreationTime;				//作成日時
	FILETIME LastAccessTime;			//最終アクセス日時
	FILETIME LastWriteTime;				//最終更新日時
	string FileName;					//ファイル名
};

//===============================================
//class
//===============================================
//[Desc]
//	ファイル用クラス
//===============================================
class CFile
{
	private:
	
		FILEDATA m_FileDat;//ファイルデータ
	
	public:
	
		CFile(){};//コンストラクタ
		CFile(string name);//コンストラクタ
		~CFile();//デストラクタ
		
		HRESULT LoadFile(string name);//ファイル読み込み
		
};
