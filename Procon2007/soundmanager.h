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
//	�T�E���h�Ǘ��p�N���X
//===============================================
class CSoundManager 
{
	private:
			
		std::map<std::string, CSound*> m_MapSound;//�T�E���h�Ǘ�
		//CSound sound;//�T�E���h�n���h��
	
	public:
		
		CSoundManager();//�R���X�g���N�^
		~CSoundManager();//�f�X�g���N�^
		
		HRESULT LoadSound(char *name);//�T�E���h�̓ǂݍ���
		HRESULT DeleteSound(const char *name);//�T�E���h�̍폜
		CSound *GetSound(const char *name);//�T�E���h�̎擾
		
};