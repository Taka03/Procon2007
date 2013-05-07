//*==============================================
//golem.h
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
//	�S�[�����p�N���X
//===============================================
class CGolem :public CCharacter
{
	private:
	
		CVector3 m_vPos;//���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
		
		float m_Anim;//�A�j���[�V����
		float m_AnimSpeed;//�A�j���[�V�������x
				
	public:
	
		CGolem();//�R���X�g���N�^
		CGolem(ePlayerType no);//�R���X�g���N�^
		
		~CGolem();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����		
};

