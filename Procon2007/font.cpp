//*==============================================
//font.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "font.h"

//===============================================
//define
//===============================================

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CFont::CFont()
{
	m_pFont = NULL;
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	m_Text.clear();
	m_FontColor = COLOR_WHITE;
	Create(16);
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	fontsize:�t�H���g�T�C�Y
//===============================================
CFont::CFont(int fontsize)
{
	m_pFont = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Text.clear();
	
	m_IsVariable = true;
	
	m_FontColor = COLOR_WHITE;
	
	Create(fontsize);
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	fontsize:�t�H���g�T�C�Y
//	name:�t�H���g��
//===============================================
CFont::CFont(int fontsize, LPCSTR name)
{
	m_pFont = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Text.clear();
	
	m_FontColor = COLOR_WHITE;
	
	m_IsVariable = true;
	
	Create( fontsize, name );
}


//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CFont::~CFont()
{
	RELEASE(m_pFont);
}

//===============================================
//�t�H���g����
//===============================================
//[input]	
//	fontsize:�t�H���g�T�C�Y
//[return]
//	�Ȃ�
//===============================================
bool CFont::Create(int fontsize)
{
	RELEASE(m_pFont);
	
	int result = D3DXCreateFont(pD3DDevice, fontsize, NULL, FW_NORMAL, 1, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("MS UI Gothic"), &m_pFont);
	
	return (result == 0) ? false : true;
}

//===============================================
//�t�H���g����
//===============================================
//[input]	
//	fontsize:�t�H���g�T�C�Y
//	name:�t�H���g��
//[return]
//	�Ȃ�
//===============================================
bool CFont::Create(int fontsize, LPCSTR name)
{
	RELEASE(m_pFont);
	
	int result = D3DXCreateFontA(pD3DDevice, fontsize, fontsize, FW_REGULAR, 1, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T(name), &m_pFont);
	
	if(name != NULL)
	{
		name = "MS UI Gothic";
	}
	
	return (result == 0) ? false : true;
}


//===============================================
//�t�H���g�`��
//===============================================
//[input]
//	text:������
//	count:�\��������
//	pRect:�����`��͈�
//	Fotmat:������`��ݒ�
//	color:�t�H���g�J���[
//[return]
//	�Ȃ�
//===============================================
void CFont::Draw(string text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color)
{
	/*�`��J�n*/
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	/*�e�L�X�g�`��*/
	m_pFont->DrawText(pSprite, text.c_str(), count, pRect, format, color);
	
	/*�`��I��*/
	pSprite->End();
}


//===============================================
//�t�H���g�`��
//===============================================
//[input]
//	text:������
//	x:X���W
//	y:Y���W
//	color:�t�H���g�J���[
//[return]
//	�Ȃ�
//===============================================
void CFont::Draw(string text, int x, int y, D3DXCOLOR color)
{
	RECT rect = {x, y, x, y};
	
	Draw(text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
	
}

//===============================================
//�t�H���g�`��
//===============================================
//[input]
//	text:������
//	x:X���W
//	y:Y���W
//	color:�t�H���g�J���[
//[return]
//	�Ȃ�
//===============================================
void CFont::Draw(int x, int y, D3DXCOLOR color)
{
	RECT rect = {x, y, x, y};
	
	Draw(m_Text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
	
}


//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]	
//	�Ȃ�
//===============================================
void CFont::Exec()
{
	if(m_IsVariable)
	{
		if(!m_Text.empty() )
		{
			Draw( (int)(m_vPos.x), (int)(m_vPos.y), m_FontColor);
		}
	}
}

//===============================================
//�t�H���g�ʒu�̐ݒ�
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//===============================================
void CFont::SetPosition(float x, float y)
{
	m_vPos.Set(x, y, 0.0f);
}

//===============================================
//�e�L�X�g�̐ݒ�
//===============================================
//[input]
//	Text:�ݒ肷��e�L�X�g
//===============================================
void CFont::SetText(string text)
{
	m_Text = text;
}

//===============================================
//�t�H���g�J���[�̐ݒ�
//===============================================
//[input]
//	color:�t�H���g�J���[
//===============================================
void CFont::SetFontColor(D3DXCOLOR color)
{
	m_FontColor = color;
}

//===============================================
//���݃t���O�̐ݒ�
//===============================================
//[input]
//	flag:���݃t���O
//===============================================
void CFont::SetVariableFlag(bool flag)
{
	m_IsVariable = flag;
}

//===============================================
//���݃t���O�̎擾
//===============================================
//[return]
//	���݃t���O
//===============================================
bool CFont::GetVariableFlag()
{
	return m_IsVariable;
}





