//*==============================================
//file.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "file.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	name:ファイル名
//===============================================
CFile::CFile(std::string name)
{
	ZeroMemory( &m_FileDat, sizeof(FILEDATA) );
	
	LoadFile(name);
}

//===============================================
//デストラクタ
//===============================================
CFile::~CFile()
{
	if( m_FileDat.hFile != NULL )
	{
		/*ファイルの終了処理*/
		FILE_CLOSE( m_FileDat.hFile );
		
		m_FileDat.hFile = NULL;
	}
}

//===============================================
//ファイル読み込み
//===============================================
//[input]
//	name:ファイル名
//[return]
//	HRESULT値
//===============================================
HRESULT CFile::LoadFile(std::string name)
{
	if( name.empty() )
	{
		return E_FAIL;
	}
	
	m_FileDat.FileName = name;
	
	/*データの読み込み*/
	m_FileDat.hFile = FILE_OPEN_READ( (LPSTR)(m_FileDat.FileName.c_str() ) );
	
	/*ファイル時刻保存*/
	FILE_GET_TIME( m_FileDat.hFile, &m_FileDat.CreationTime, &m_FileDat.LastAccessTime, &m_FileDat.LastWriteTime );
	
	/*ファイルサイズ取得*/
	m_FileDat.Size = FILE_GET_SIZE( m_FileDat.hFile );
	
	return S_OK;
}

