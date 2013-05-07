#include "TextureManager.h"


#define RELEASE(x){if(x != NULL){x->Release(); x = NULL;}}


//=====================================
//�R���X�g���N�^
//=====================================
TextureManager::TextureManager()
{

}

//=====================================
//�f�X�g���N�^
//=====================================
TextureManager::~TextureManager()
{
	std::map<std::string,LPDIRECT3DTEXTURE9>::iterator p = m_MapTexture.begin();

	while(p != m_MapTexture.end())
	{
		RELEASE(p->second);
		p++;
	}

	m_MapTexture.clear();
}


//=====================================
//�e�N�X�`�����쐬����N���X
//=====================================
HRESULT TextureManager::CreateTexture(const char *inFileName,LPDIRECT3DDEVICE9 inDevice)
{
	LPDIRECT3DTEXTURE9 theTexture;
	
	std::string theKey(inFileName);
	//===========================
	//���łɓo�^����Ă��邩��Check
	//===========================
	if(m_MapTexture.end() != m_MapTexture.find(theKey))
	{
		return E_FAIL;
	}

	//===========================
	//�e�N�X�`�����쐬
	//===========================
	HRESULT hr;
	//hr = D3DXCreateTextureFromFileExA(inDevice, inFileName, D3DX_DEFAULT, D3DX_DEFAULT, NULL, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,  &theTexture);
	hr = D3DXCreateTextureFromFileExA(inDevice, inFileName, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,  &theTexture);
	
	if(hr != S_OK)
	{
		return E_FAIL;
	}
	
	m_MapTexture.insert(std::pair<std::string,LPDIRECT3DTEXTURE9>(theKey,theTexture));
	return S_OK;
}


//=====================================
//�e�N�X�`�����擾����N���X
//=====================================
LPDIRECT3DTEXTURE9 TextureManager::GetTexture(const char *inFileName)
{
	std::map<std::string,LPDIRECT3DTEXTURE9>::iterator p = m_MapTexture.find(std::string(inFileName));
	
	if(p == m_MapTexture.end() )
	{
		return NULL;
	}
	
	return p->second;
}

//=====================================
//�e�N�X�`�����폜����N���X
//=====================================
HRESULT TextureManager::DeleteTexture(const char *inFileName)
{
	std::string theKey(inFileName);
	std::map<std::string,LPDIRECT3DTEXTURE9>::iterator p = m_MapTexture.find(std::string(theKey));
	if(p == m_MapTexture.end())  
	{
		return E_FAIL;
	}
	RELEASE(p->second);
	m_MapTexture.erase(theKey);
	return S_OK;
}
