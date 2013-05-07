//*==============================================
//beast.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"

//===============================================
//class
//===============================================
//[Desc]
//	�b�p�N���X
//===============================================
class CBeast :public CCharacter
{
	private:
	
		CVector3 m_vPos;//���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
		
		float m_Anim;//�A�j���[�V����
		float m_AnimSpeed;//�A�j���[�V�������x
				
	public:
	
		CBeast();//�R���X�g���N�^
		CBeast(ePlayerType no);//�R���X�g���N�^
		~CBeast();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����	
};