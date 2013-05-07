//*==============================================
//SoundFactory.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "sound.h"
#include "soundsprite.h"

//===============================================
//enum
//===============================================
enum eSound
{
	SE_ATTACK_FENCER,
	SE_CRITICAL,
	SE_ATTACK1_MAGI,
	SE_ATTACK2_MAGI,
	SE_HEAL,
	SE_CHARGE_MAGI,
	SE_ATTACK_RANGER,
	SE_POWERUP,
	SE_ATTACK_CON,
	SE_BOMB,
	SE_CHARGE_GUR,
	SE_DEAD,
	SE_MAX,
	
	SND_BGM,
	
};

//===============================================
//class
//===============================================
//[Desc]
//	�T�E���h�f�[�^�����p�N���X
//===============================================
class CSoundFactory
{
	private:
	
	public:
	
		CSoundFactory(void);//�R���X�g���N�^
		virtual ~CSoundFactory(void);//�f�X�g���N�^
		
		static CSoundSprite *Create(eSound sound);//�T�E���h�̐���
};
