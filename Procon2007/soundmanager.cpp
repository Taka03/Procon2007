//*==============================================
//soundmanager.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "soundmanager.h"

//===============================================
//コンストラクタ
//===============================================
CSoundManager::CSoundManager()
{

}



//===============================================
//デストラクタ
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
//サウンドの読み込み
//===============================================
//[input]
//	name:ファイル名
//[return]
//	HRESULT値
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
//サウンドデータの削除
//===============================================
//[input]
//	name:名前
//[return]
//	HRESULT値
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
//サウンドデータの取得
//===============================================
//[input]
//	name:データ名
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
