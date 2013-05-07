//*==============================================
//file.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "file.h"

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	name:�t�@�C����
//===============================================
CFile::CFile(std::string name)
{
	ZeroMemory( &m_FileDat, sizeof(FILEDATA) );
	
	LoadFile(name);
}

//===============================================
//�f�X�g���N�^
//===============================================
CFile::~CFile()
{
	if( m_FileDat.hFile != NULL )
	{
		/*�t�@�C���̏I������*/
		FILE_CLOSE( m_FileDat.hFile );
		
		m_FileDat.hFile = NULL;
	}
}

//===============================================
//�t�@�C���ǂݍ���
//===============================================
//[input]
//	name:�t�@�C����
//[return]
//	HRESULT�l
//===============================================
HRESULT CFile::LoadFile(std::string name)
{
	if( name.empty() )
	{
		return E_FAIL;
	}
	
	m_FileDat.FileName = name;
	
	/*�f�[�^�̓ǂݍ���*/
	m_FileDat.hFile = FILE_OPEN_READ( (LPSTR)(m_FileDat.FileName.c_str() ) );
	
	/*�t�@�C�������ۑ�*/
	FILE_GET_TIME( m_FileDat.hFile, &m_FileDat.CreationTime, &m_FileDat.LastAccessTime, &m_FileDat.LastWriteTime );
	
	/*�t�@�C���T�C�Y�擾*/
	m_FileDat.Size = FILE_GET_SIZE( m_FileDat.hFile );
	
	return S_OK;
}

