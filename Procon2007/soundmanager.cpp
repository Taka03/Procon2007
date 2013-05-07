//*==============================================
//soundmanager.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "soundmanager.h"

//===============================================
//�R���X�g���N�^
//===============================================
CSoundManager::CSoundManager()
{

}



//===============================================
//�f�X�g���N�^
//===============================================
CSoundManager::~CSoundManager()
{
	std::map<std::string, CSound*>::iterator p = m_MapSound.begin();

	while(p != m_MapSound.end())
	{
		RELEASE(p->second);
		p++;
	}

	m_MapSound.clear();

}

//===============================================
//�T�E���h�̓ǂݍ���
//===============================================
//[input]
//	name:�t�@�C����
//[return]
//	HRESULT�l
//===============================================
HRESULT CSoundManager::LoadSound(char *name)
{
	CSound *sound;
	
	std::string theKey(name);
	
	if(m_MapSound.end() != m_MapSound.find(theKey) )
	{
		return E_FAIL;
	} 
	
	bool b;
	
	b = sound->CreateFromFile(name, false);
	
	if(b == false)
	{
		return E_FAIL;
	}
	
	m_MapSound.insert(std::pair<std::string, CSound*>(theKey, sound));
	
	return S_OK;
	
}

//===============================================
//�T�E���h�f�[�^�̍폜
//===============================================
//[input]
//	name:���O
//[return]
//	HRESULT�l
//===============================================
HRESULT CSoundManager::DeleteSound(const char *name)
{
	std::string theKey(name);
	std::map<std::string, CSound*>::iterator p = m_MapSound.find(std::string(theKey));
	
	if(p == m_MapSound.end())  
	{
		return E_FAIL;
	}
	
	RELEASE(p->second);
	
	m_MapSound.erase(theKey);
	return S_OK;

}

//===============================================
//�T�E���h�f�[�^�̎擾
//===============================================
//[input]
//	name:�f�[�^��
//[return]
//	CSound
//===============================================
CSound *CSoundManager::GetSound(const char *name)
{
	std::map<std::string, CSound*>::iterator p = m_MapSound.find(std::string(name) );
	
	if(p == m_MapSound.end())
	{
		return NULL;
	}
	return p->second;

}
