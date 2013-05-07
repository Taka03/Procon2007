//*==============================================
//fencer.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"
#include "camera.h"

//===============================================
//class
//===============================================
//[Desc]
//	���m�p�N���X
//===============================================
class CFencer :public CCharacter
{
	private:
	
		//void ProcessCritical();//�N���e�B�J���p�̏���
	
	public:
	
		CFencer();//�R���X�g���N�^
		CFencer(ePlayerType no);//�R���X�g���N�^
		CFencer(ePlayerType no, const char *name);//�R���X�g���N�^
		~CFencer();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		

		void SetAbility();//����\�͂̐ݒ�
		
		void SpecialAttack();//�N���e�B�J���U��
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//�g����
		
		void Rendering();//�����_�����O
		
};