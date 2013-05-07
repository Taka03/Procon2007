//*==============================================
//fontsprite.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "font.h"
#include "texture.h"
#include "TextureManager.h"
#include "CXModel.h"

//===============================================
//enum
//===============================================

enum eCaption
{
	GRP_PLAYER1,
	GRP_PLAYER2,
	
	GRP_TURN,
	GRP_TEAM1,
	GRP_TEAM2,
	GRP_CRYSTAL1,
	GRP_CRYSTAL2,
	
	CAP_MAX,
	
	GRP_LOADING,
	GRP_LARGETURN,
	GRP_LARGENUMBER,
	GRP_SPECIAL1,
	GRP_SPECIAL2,
	
	GRP_RESULT1,
	GRP_RESULT2,
	
	GRP_ICON,
	
	GRP_FONT,
	GRP_NUMBER,
	CAP_HP,
	GRP_HP1,
	GRP_HP2,
	
	GRP_MAX,	
	
};

enum eResult
{
	PLAYER1_WIN,
	PLAYER2_WIN,
	RESULT_MAX,
};



//===============================================
//class
//===============================================
//[Desc]
//	�t�H���g�X�v���C�g�p�N���X
//===============================================
class CFontSprite :public CGameObject
{
	private:
		
		CVector3 m_vPos;//�ʒu
		
		eCaption m_Caption;
		
		LPDIRECT3DTEXTURE9 m_pTex;
		
		C2DPol9 *m_pDraw;
		LPDIRECT3DSURFACE9 m_pSurface;
		
		RECT m_Src;//�]������`
		
		TextureManager *m_TexMgr;//�e�N�X�`���Ǘ��p
		CTexture m_Tex;//�e�N�X�`���n���h��
		
		D3DCOLOR m_FontColor;
		
		string m_Text;//�\�����镶��
		char m_pName[17];//�`�[����
		
		eCharaType m_CharaType;//�L�����^�C�v
		ePlayerType m_plType;//�v���C���[�^�C�v
		
		bool m_IsVisible;//�\������t���O
		
	public:
	
		void Init();//������
		void Exec();//����
	
		CFontSprite();//�R���X�g���N�^
		CFontSprite(const char *pFile, eCaption cap);//�R���X�g���N�^
		CFontSprite(LPDIRECT3DTEXTURE9 Tex, eCaption cap, RECT Src);//�R���X�g���N�^
		CFontSprite(const char *pFile, RECT Src); 
		CFontSprite(int fontsize);
		~CFontSprite();//�f�X�g���N�^
		
		HRESULT CreateFontA(int fontsize);//�t�H���g�̐���
		HRESULT GetFontBitMap(char *pData, float x, float y);
		
		void DrawNumber(char *pText, float x, float y);//�����̕`�� 
		void DrawNumber(float x, float y);//�����̕`��
		void DrawSpecialAttack(eSpecial spType);//����\��(�U��ver)�̕\��
		void DrawSpecialAssist(eSpecial spType);//����\��(����ver)�̕\��
		void DrawLargeNumber(float x, float y);//�����̕`�� 
		void DrawWeaponIcon(eCharaType type);//����A�C�R���̕`��
		void DrawCharaIcon(ePlayerType plType, eCharaType type);//�L�����A�C�R���̕`��
		
		void Draw(float x, float y);//�`��
		void DrawFont();//�t�H���g�̕`��
		
		void SetCaption(eCaption cap);//�L���v�V�����̐ݒ�
		void SetRect(RECT Src);//�]�����̐ݒ�
		void SetPosition(float x, float y);//�ʒu�̐ݒ�
		void SetTeamName(char *pText);//�`�[�����̐ݒ�
		void SetText(string Text);//�e�L�X�g�̐ݒ�
		void SetVisibleFlag(bool flag);
		
		void SetCharaType(eCharaType type);//�L�����^�C�v�̐ݒ�
		void SetPlayerType(ePlayerType type);//�v���C���[�^�C�v�̐ݒ�
		
	public:
	
		CVector3 GetPosition();//�ʒu�̎擾
		bool GetVisibleFlag();//�\���t���O�̎擾
		
			
	
		
};