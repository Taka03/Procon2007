//*==============================================
//font.h
//*==============================================
//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//class
//===============================================
class CFont :public CGameObject
{
	private:
	
		CVector3 m_vPos;//�ʒu
		D3DXCOLOR m_FontColor;//�t�H���g�J���[
		
		LPD3DXFONT m_pFont;//�t�H���g�n���h��
		string m_Text;
		//LPCTSTR m_pText;//�e�L�X�g
		
		bool m_IsVariable;//�\������t���O
		
	protected:
	
		
	public:
	
		CFont();//�R���X�g���N�^
		CFont(int fontsize);//�R���X�g���N�^
		CFont(int fontsize, LPCSTR name);//�R���X�g���N�^
		~CFont();//�f�X�g���N�^
		
		void Init(){};//������
		void Exec();//����
		
		bool Create(int fontsize);//�t�H���g����
		bool Create(int fontsize, LPCSTR name);//�t�H���g����
		
		void Draw(string text, int x, int y, D3DXCOLOR color);//�`��
		void Draw(string text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color);//�`��
		void Draw(int x, int y, D3DXCOLOR color);
		
		const LPD3DXFONT GetD3DXFont()
		{
			return m_pFont;
		}
		
		void SetPosition(float x, float y);//�ʒu�̐ݒ�
		void SetText(string text);//�\�����镶���̃Z�b�g
		void SetFontColor(D3DXCOLOR color);//�t�H���g�J���[�̃Z�b�g
		
		void SetVariableFlag(bool flag);//�\������t���O�̐ݒ�
		
	public:
	
		bool GetVariableFlag();//�\������t���O�̎擾
};

