//*==============================================
//charafactory.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "charafactory.h"
#include "fencer.h"
#include "magician.h"
#include "ranger.h"
#include "contractor.h"
#include "guardian.h"

//===============================================
//キャラクターの生成
//===============================================
//[input]
//	type:キャラクタータイプ
//[return]
//	キャラクターデータ
//===============================================
CCharacter *CCharaFactory::Create(eCharaType type)
{
	switch(type)
	{
		case FENCER:
		{
			return new CFencer(PLAYER_1);//剣士を生成
			break;
		}
		
		case MAGICIAN:
		{
			return new CMagician();//魔法使いを生成
			break;
		}
		
		case RANGER:
		{
			return new CRanger();//レンジャーを生成
			break;
		}
		
		case CONTRACTOR:
		{
			return new CContractor();//契約者を生成
			break;
		}
		
		case GUARDIAN:
		{
			return new CGuardian();//守護騎士を生成
			break;
		}
		
		default:
		{
			return NULL; //該当なし
		}
	}
	
	return NULL;
}

//===============================================
//キャラクターの生成
//===============================================
//[input]
//	type:キャラクタータイプ
//[return]
//	キャラクターデータ
//===============================================
CCharacter *CCharaFactory::Create(eCharaType chara, ePlayerType plType)
{
	char *charname[MAX_CHARA + 1][PLAYER_MAX] =
	{
		"data/fencer.x", "data/fencer2.x",
		"data/magister.x", "data/magister2.x",
		"data/ranger.x", "data/ranger2.x",
		"data/contractor.x", "data/contractor2.x",
		"data/guardian.x", "data/guardian2.x",
	};
	
	switch(chara)
	{
		case FENCER:
		{
			return new CFencer(plType, charname[FENCER][plType]);//剣士を生成
			break;
		}
		
		case MAGICIAN:
		{
			return new CMagician(plType, charname[MAGICIAN][plType]);//魔法使いを生成
			break;
		}
		
		case RANGER:
		{
			return new CRanger(plType, charname[RANGER][plType]);//レンジャーを生成
			break;
		}
		
		case CONTRACTOR:
		{
			return new CContractor(plType, charname[CONTRACTOR][plType]);//契約者を生成
			break;
		}
		
		case GUARDIAN:
		{
			return new CGuardian(plType, charname[GUARDIAN][plType]);//守護騎士を生成
			break;
		}
		
		default:
		{
			return NULL; //該当なし
		}
	}
	
	return NULL;
}