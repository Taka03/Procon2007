//*==============================================
//ranger.h
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
class CRanger :public CCharacter
{
	private:
	
		//CVector3 m_vPos;//���W
		//CVector3 m_vRot;//�p�x
		//CVector3 m_vScale;//�g�k
		//
		//float m_Anim;//�A�j���[�V����
		//float m_AnimSpeed;//�A�j���[�V�������x
				
	public:
	
		CRanger();//�R���X�g���N�^
		CRanger(ePlayerType no);//�R���X�g���N�^
		CRanger(ePlayerType no, const char *name);//�R���X�g���N�^
		~CRanger();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		void Rendering();//�����_�����O
		
		void SetAbility();//����\�͂̐ݒ�
		void SpecialAttack();//�搧�U��
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//����
};