//*==============================================
//texture.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "texture.h"

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CTexture::CTexture()
{
	m_pTex = NULL;
	m_pSurface = NULL;
	
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	name:�f�[�^��
//[return]
//	�Ȃ�
//===============================================
CTexture::CTexture(LPCTSTR name)
{
	m_pTex = NULL;
	m_pSurface = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Width = 0;
	m_Height = 0;
	
	m_Src.left = 0;
	m_Src.right = 0;
	m_Src.top = 0;
	m_Src.bottom = 0;
	
	LoadTexture(name);
	
	
	//LoadTextureEx(name);
}

//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CTexture::~CTexture()
{
	RELEASE(m_pTex);
}

//===============================================
//�e�N�X�`���ǂݍ���
//===============================================
//[input]
//	name:�f�[�^��
//[return]
//	bool�l
//===============================================
bool CTexture::LoadTexture(LPCTSTR name)
{
	RELEASE(m_pTex);
	
	bool b = SUCCEEDED(D3DXCreateTextureFromFile(pD3DDevice, name, &m_pTex) );
	
	//if(FAILED(hr) )
	//{
	//	char Buff[256];
	//	sprintf(Buff, "%s��������܂���", name);
	//	MESSAGE(Buff);
	//	
	//	return false;
	//}
	
	
	return b;
}

//===============================================
//�e�N�X�`���ǂݍ���
//===============================================
//[input]
//	Tex:�e�N�X�`��
//[return]
//	bool�l
//===============================================
bool CTexture::LoadTexture(LPDIRECT3DTEXTURE9 Tex)
{
	m_pTex = Tex;
	
	return true;
	
}

//===============================================
//�e�N�X�`���Ǎ���
//===============================================
//[input]
//	name:�f�[�^��
//[return]
//	bool�l
//===============================================
bool CTexture::LoadTextureEx(LPCTSTR name)
{
	HRESULT hr = NULL;
	m_pTex = NULL;
	m_pSurface = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	//D3DSURFACE_DESC Desc;
	//
	//m_pBackBuffer->GetDesc(&Desc);
	//
	//if( FAILED(hr) )
	//{
	//	return false;
	//}
	
	m_Width = 0;
	m_Height = 0;
	
	D3DXIMAGE_INFO ImageInfo;
	
	hr = D3DXGetImageInfoFromFile(name, &ImageInfo);
	
	m_Width = ImageInfo.Width;
	m_Height = ImageInfo.Height;
	
	//hr = pD3DDevice->CreateOffscreenPlainSurface(m_Width, m_Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pSurface, NULL);
	
	//if(FAILED(hr) )
	//{
	//	return false;
	//}
	//
	//m_Dest.Set(m_vPos.x, m_vPos.y, (float)m_Width, (float)m_Height);
	//
	//m_Src.Set(0, 0, m_Width, m_Height);
	//
	//hr = D3DXLoadSurfaceFromFileA(m_pSurface, NULL, NULL, name, NULL, D3DX_FILTER_NONE, 0, NULL); 
	
	//if( FAILED(hr) )
	//{
	//	return false;
	//}
	
	hr = D3DXCreateTextureFromFileExA(Joker::GetDevice(), name, m_Width, m_Height, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_pTex);
	
	if( FAILED(hr) )
	{
		CHAR str[128];
		
		wsprintf(str, "%s��������܂���", name);
		
		MESSAGE(str);

		return false;
	}
	
	D3DSURFACE_DESC Desc;
	
	m_pTex->GetLevelDesc(0, &Desc);
	
	m_Width = (int)Desc.Width;
	m_Height = (int)Desc.Height;
	
	return true;
}

//===============================================
//�`��
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//===============================================
void CTexture::Draw(float x, float y)
{
	/*�X�v���C�g�`��J�n*/
	pSprite->Begin(NULL);
	
	m_vPos.Set(x, y, 0.0f);
	
	//m_pSurface->
	
	m_Poly.SetPosition(&m_vPos, (float)(m_Width), (float)(m_Height), NULL );
	
	m_Poly.Draw(Joker::GetDevice(), m_pRenderTex );
	
	/*�X�v���C�g�`��I��*/
	pSprite->End();
	
}


//===============================================
//�`��
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//	z:Z���W
//[return]
//	�Ȃ�
//===============================================
void CTexture::Draw(float x, float y, float z)
{
	/*�X�v���C�g�`��J�n*/
	pSprite->Begin(NULL);
	
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	
	/*�`��*/
	pSprite->Draw(m_pTex, NULL, NULL, &vec, 0xFFFFFFFF);
	
	/*�X�v���C�g�`��I��*/
	pSprite->End();
	
}



//===============================================
//�`��
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//	z:Z���W
//	rect
//[return]
//	�Ȃ�
//===============================================
void CTexture::Draw(float x, float y, float z, RECT Src)
{
	/*�X�v���C�g�`��J�n*/
	pSprite->Begin(D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_ALPHABLEND);
	
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	
	/*�`��*/
	pSprite->Draw(m_pTex, &Src, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &vec, 0xFFFFFFFF);
	
	/*�X�v���C�g�`��I��*/
	pSprite->End();
	
}



//===============================================
//�`��
//===============================================
//[input]
//	Tex:�e�N�X�`���n���h��
//	x:X���W
//	y;Y���W
//===============================================
void CTexture::Draw(LPDIRECT3DTEXTURE9 Tex, float x, float y)
{
	m_pTex = Tex;
	
	/*�X�v���C�g�`��J�n*/
	pSprite->Begin(NULL);
	
	D3DXVECTOR3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = 0.0f;
	
	/*�`��*/
	pSprite->Draw(m_pTex, NULL, NULL, &vec, 0xFFFFFFFF);
	
	/*�X�v���C�g�`��I��*/
	pSprite->End();

}

//===============================================
//�`��
//===============================================
//[input]
//	pos:���W
//	Src:�`�挳
//===============================================
void CTexture::Draw(CVector3 pos, RECT Src)
{
	/*�X�v���C�g�`��J�n*/
	pSprite->Begin(D3DXSPRITE_SORT_TEXTURE);
	
	/*�`��*/
	pSprite->Draw(m_pTex, &Src, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &pos, 0xFFFFFFFF);
	
	/*�X�v���C�g�`��I��*/
	pSprite->End();
}


//===============================================
//�`��
//===============================================
void CTexture::Draw()
{
	/*�X�v���C�g�`��J�n*/
	pSprite->Begin(NULL);
	
	/*�`��*/
	pSprite->Draw(m_pTex, &m_Src, NULL, &m_vPos, NULL);
	
	/*�X�v���C�g�`��I��*/
	pSprite->End();
	
}

//===============================================
//�`���̈�̐ݒ�
//===============================================
//[input]
//	Rect:�ݒ肷���`
//===============================================
void CTexture::SetDstRect(RECT Rect)
{
	m_Dest = Rect;
}

//===============================================
//�`�挳��`
//===============================================
//[input]
//	Rect:�ݒ肷���`
//===============================================
void CTexture::SetSrcRect(RECT Rect)
{
	m_Src = Rect;
}

//===============================================
//�`��ʒu�̐ݒ�
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//	z:Z���W
//===============================================
void CTexture::SetPosition(float x, float y, float z)
{
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CTexture::Exec()
{
	Draw();
}
