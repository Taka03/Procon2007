//*==============================================
//FileMgr.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "FileMgr.h"

//===============================================
//コンストラクタ
//===============================================
CFileMgr::CFileMgr(void)
{
}

//===============================================
//デストラクタ
//===============================================
CFileMgr::~CFileMgr(void)
{

}

//===============================================
//ファイルの読み込み
//===============================================
//[input]
//	inFileType:ファイルタイプ
//	inFileName:ファイル名
//[return]
//	HRESULT値
//===============================================
CGameObject *CFileMgr::CreateFromFile(eFileType inFileType, std::string inFileName)
{
	char *Buff = (char*)( inFileName.c_str() );
	
	//m_liFile.push_back( Buff );
	
	//m_liFile.unique();
	
	//m_vecFileName.push_back(inFileName);
	//
	//vector<string>::iterator it = m_vecFileName.begin();
	//
	//for( it = m_vecFileName.begin(); it != m_vecFileName.end(); it++ )
	//{
	//m_FileName.insert(inFileName.c_str());
	
	
	switch(inFileType)
	{
		case TEXTURE:
		{
			return new CTexture( inFileName );
			break;
		}
		
		case SOUND:
		{
			return new CSound( inFileName );
			break;
		}
		
		case MODEL:
		{
			return new CXModel( inFileName.c_str() );
			//m_mdlFile.insert( CXModel(inFileName.c_str() ) );
			break;
		}
		
		default:
		{
			return NULL;
			//m_File.insert( CFile(inFileName) );
			break;
		}
	}
	
	return NULL;
	
}

//===============================================
//ファイル名の取得
//===============================================
//[input]
//	inFileName:ファイル名
//[return]
//	string型
//===============================================
string CFileMgr::GetFileName(std::string inFileName)
{
	return inFileName;
}
