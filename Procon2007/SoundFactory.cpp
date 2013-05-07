//*==============================================
//SoundFactory.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "SoundFactory.h"

//===============================================
//コンストラクタ
//===============================================
CSoundFactory::CSoundFactory(void)
{

}

//===============================================
//デストラクタ
//===============================================
CSoundFactory::~CSoundFactory(void)
{

}

//===============================================
//サウンドの生成
//===============================================
//[input]
//	sound:サウンドタイプ
//[return]
//	CSoundSprite
//===============================================
CSoundSprite *CSoundFactory::Create(eSound sound)
{
	char *name[SE_MAX] =
	{
		"data/swordman_attack.WAV",
		"data/swordman_critical.WAV",
		"data/magister_attack1.WAV",
		"data/magister_attack2.WAV",
		"data/magister_heal.WAV",
		"data/magister_charge.WAV",
		"data/ranger_attack.WAV",
		"data/ranger_powerup.WAV",
		"data/contractor_attack.WAV",
		"data/contractor_bomb.WAV",
		"data/guardner_charge.WAV",
		"data/all_dead.WAV",
	};
	
	switch(sound)
	{
		case SE_ATTACK_FENCER:
		{
			return new CSoundSprite(name[sound]);
			break;
		
		}
		
		case SE_CRITICAL:
		{
			return new CSoundSprite(name[sound]);
			break;
		
		}
		
		case SE_ATTACK1_MAGI:
		{
			return new CSoundSprite(name[sound]);
			break;
		
		}
		
		case SE_ATTACK2_MAGI:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_HEAL:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_CHARGE_MAGI:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_ATTACK_RANGER:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_POWERUP:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_ATTACK_CON:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
	
		case SE_BOMB:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_CHARGE_GUR:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		case SE_DEAD:
		{
			return new CSoundSprite(name[sound]);
			break;
		}
		
		default:
		{
			return NULL;
			break;
		}
		
	}
	
	return NULL;
}
