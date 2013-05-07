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
//	�t�@�C���Ǘ��p�N���X
//===============================================
class CFileMgr
{
	private:
	
		list<char *> m_liFile;
				
	public:
	
		CFileMgr(void);//�R���X�g���N�^
		//CFileMgr
		~CFileMgr(void);//�f�X�g���N�^
		
		CGameObject *CreateFromFile(eFileType inFileType, std::string inFileName);//�t�@�C���̓ǂݍ���
		string GetFileName(std::string inFileName);//�t�@�C�����̎擾
};
