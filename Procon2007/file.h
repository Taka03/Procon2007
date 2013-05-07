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
//�t�@�C���f�[�^
struct FILEDATA
{
	HANDLE hFile;						//�t�@�C���n���h��
	Bool IsPack;						//�p�b�N�t�@�C�����ۂ�
	Uint32 Start;						//�t�@�C���J�n�ʒu
	Uint32 Size;						//�t�@�C���I���ʒu
	FILETIME CreationTime;				//�쐬����
	FILETIME LastAccessTime;			//�ŏI�A�N�Z�X����
	FILETIME LastWriteTime;				//�ŏI�X�V����
	string FileName;					//�t�@�C����
};

//===============================================
//class
//===============================================
//[Desc]
//	�t�@�C���p�N���X
//===============================================
class CFile
{
	private:
	
		FILEDATA m_FileDat;//�t�@�C���f�[�^
	
	public:
	
		CFile(){};//�R���X�g���N�^
		CFile(string name);//�R���X�g���N�^
		~CFile();//�f�X�g���N�^
		
		HRESULT LoadFile(string name);//�t�@�C���ǂݍ���
		
};
