//*==============================================
//magician.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"
#include "Effect.h"

//===============================================
//class
//===============================================
//[Desc]
//	���@�g���p�N���X
//===============================================
class CMagician :public CCharacter
{
	private:
	
		CEffect *Magic;
					
	public:
	
		CMagician();//�R���X�g���N�^
		CMagician(ePlayerType no);//�R���X�g���N�^
		CMagician(ePlayerType no, const char *name);//�R���X�g���N�^
		~CMagician();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		void Rendering();//�����_�����O
		
		void SetAbility();//����\�͂̐ݒ�
		void SpecialAttack();//�S�̍U��
		void SpecialAssist(CCharacter *attacker, CCharacter *target);//���C�t��
		
		void SetAnimation(int animID);
		
		void DrawEffect();
};