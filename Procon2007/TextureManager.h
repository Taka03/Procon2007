#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__


#include <map>
#include <windows.h>
#include <d3dx9.h>
#include <string>

//========================================
//テクスチャを管理するクラスです
//========================================
class TextureManager
{
	public:
		TextureManager();
		~TextureManager();
	private:
		std::map<std::string, LPDIRECT3DTEXTURE9>m_MapTexture;

	public:
		HRESULT CreateTexture(const char *inFileName, LPDIRECT3DDEVICE9 inDevice);
		HRESULT DeleteTexture(const char *inFileName);
		LPDIRECT3DTEXTURE9 GetTexture(const char *inFileName);
};





#endif