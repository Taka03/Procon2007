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
//	サウンドデータ生成用クラス
//===============================================
class CSoundFactory
{
	private:
	
	public:
	
		CSoundFactory(void);//コンストラクタ
		virtual ~CSoundFactory(void);//デストラクタ
		
		static CSoundSprite *Create(eSound sound);//サウンドの生成
};
