//*==============================================
//contractor.h
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
class CContractor :public CCharacter
{
	private:
	
	public:
	
		CContractor();//�R���X�g���N�^
		CContractor(ePlayerType no);//�R���X�g���N�^
		CContractor(ePlayerType no, const char *name);//�R���X�g���N�^
		
		~CContractor();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����	
		
		void Rendering();
		
		void SetAbility();//����\�͂̐ݒ�
		void Burst(CCharacter *target);//��������
		void Guard();//�K�[�h����
		
};

