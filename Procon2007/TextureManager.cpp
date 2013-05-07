#include "TextureManager.h"


#define RELEASE(x){if(x != NULL){x->Release(); x = NULL;}}


//=====================================
//コンストラクタ
//=====================================
TextureManager::TextureManager()
{

}

//=====================================
//デストラクタ
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
//テクスチャを作成するクラス
//=====================================
HRESULT TextureManager::CreateTexture(const char *inFileName,LPDIRECT3DDEVICE9 inDevice)
{
	LPDIRECT3DTEXTURE9 theTexture;
	
	std::string theKey(inFileName);
	//===========================
	//すでに登録されているかをCheck
	//===========================
	if(m_MapTexture.end() != m_MapTexture.find(theKey))
	{
		return E_FAIL;
	}

	//===========================
	//テクスチャを作成
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
//テクスチャを取得するクラス
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
//テクスチャを削除するクラス
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
