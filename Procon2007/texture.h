//*==============================================
//texture.h
//*==============================================

//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "2ddraw9.h"

//===============================================
//struct
//===============================================

//===============================================
//class
//===============================================
class CTexture : public CGameObject
{
	private:
	
		LPDIRECT3DTEXTURE9 m_pTex;//�e�N�X�`���n���h��
		LPDIRECT3DSURFACE9 m_pSurface;//�T�[�t�F�C�X�n���h��
		
		RECT m_Dest;//�`���
		RECT m_Src;//�`�挳
		
		int m_Width;//��
		int m_Height;//����
		
		C2DPol9 m_Poly;//�`��
		
	protected:
	
		CVector3 m_vPos;//�ʒu
		
	public:
	
		CTexture();//�R���X�g���N�^
		CTexture(LPCTSTR name);//�R�� �X�g���N�^
		~CTexture();
		
		bool LoadTexture(LPCTSTR name);//�e�N�X�`���ǂݍ���
		bool LoadTexture(LPDIRECT3DTEXTURE9 Tex);//�e�N�X�`���ǂݍ���
		bool LoadTextureEx(LPCTSTR name);//�e�N�X�`���ǂݍ���
		void Draw(float x, float y);//�`��
		void Draw(LPDIRECT3DTEXTURE9 Tex, float x, float y);//�`��
		void Draw(float x, float y, float z);//�`��
		//void Draw(float x, float y);//�`��
		void Draw(float x, float y, float z, RECT Src);//�`��
		void Draw(CVector3 pos, RECT Src);//�`��
		void Draw();//�`��
		
		void Init(){};
		void Exec();
		
		LPDIRECT3DTEXTURE9 GetTexture()
		{
			return m_pTex;
		}
		
		LPDIRECT3DSURFACE9 GetSurface()
		{
			return m_pSurface;
		}
		
		const int GetWidth()
		{
			return m_Width;
		}
		
		const int GetHeight()
		{
			return m_Height;
		}
		
		void SetPosition(float x, float y, float z);//�ʒu�̐ݒ�
		
		void SetDstRect(RECT Rect);//�`���ݒ�
		void SetSrcRect(RECT Rect);//�`�挳�ݒ�
	
};