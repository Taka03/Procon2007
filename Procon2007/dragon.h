//*==============================================
//dragon.h
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
//	�h���S���p�N���X
//===============================================
class CDragon :public CCharacter
{
	private:
	
		CVector3 m_vPos;//���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
		
		float m_Anim;//�A�j���[�V����
		float m_AnimSpeed;//�A�j���[�V�������x
				
	public:
	
		CDragon();//�R���X�g���N�^
		CDragon(ePlayerType no);//�R���X�g���N�^
		~CDragon();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
};