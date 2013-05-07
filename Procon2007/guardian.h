//*==============================================
//guardian.h
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
class CGuardian :public CCharacter
{
	private:
	
	public:
	
		CGuardian();//�R���X�g���N�^
		CGuardian(ePlayerType no);//�R���X�g���N�^
		CGuardian(ePlayerType no, const char *name);//�R���X�g���N�^
		~CGuardian();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		void Rendering();//�����_�����O
		
		void SetAbility();//����\�͂̐ݒ�
		void SpecialAttack();//���ߍU��
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//�J�E���^�[
};