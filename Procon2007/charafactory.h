//*==============================================
//charafactory.h
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
//	�L�����N�^�[�����p�N���X
//===============================================
class CCharaFactory
{
	private:
	
	public:
	
		CCharaFactory(){};//�R���X�g���N�^
		~CCharaFactory(){};//�f�X�g���N�^
		
		static CCharacter *Create(eCharaType type);//�L�����N�^�[�̐���
		static CCharacter *Create(eCharaType chara, ePlayerType plType);//�L�����N�^�[�̐���
};