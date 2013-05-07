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
//�L�����N�^�[�̐���
//===============================================
//[input]
//	type:�L�����N�^�[�^�C�v
//[return]
//	�L�����N�^�[�f�[�^
//===============================================
CCharacter *CCharaFactory::Create(eCharaType type)
{
	switch(type)
	{
		case FENCER:
		{
			return new CFencer(PLAYER_1);//���m�𐶐�
			break;
		}
		
		case MAGICIAN:
		{
			return new CMagician();//���@�g���𐶐�
			break;
		}
		
		case RANGER:
		{
			return new CRanger();//�����W���[�𐶐�
			break;
		}
		
		case CONTRACTOR:
		{
			return new CContractor();//�_��҂𐶐�
			break;
		}
		
		case GUARDIAN:
		{
			return new CGuardian();//���R�m�𐶐�
			break;
		}
		
		default:
		{
			return NULL; //�Y���Ȃ�
		}
	}
	
	return NULL;
}

//===============================================
//�L�����N�^�[�̐���
//===============================================
//[input]
//	type:�L�����N�^�[�^�C�v
//[return]
//	�L�����N�^�[�f�[�^
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
			return new CFencer(plType, charname[FENCER][plType]);//���m�𐶐�
			break;
		}
		
		case MAGICIAN:
		{
			return new CMagician(plType, charname[MAGICIAN][plType]);//���@�g���𐶐�
			break;
		}
		
		case RANGER:
		{
			return new CRanger(plType, charname[RANGER][plType]);//�����W���[�𐶐�
			break;
		}
		
		case CONTRACTOR:
		{
			return new CContractor(plType, charname[CONTRACTOR][plType]);//�_��҂𐶐�
			break;
		}
		
		case GUARDIAN:
		{
			return new CGuardian(plType, charname[GUARDIAN][plType]);//���R�m�𐶐�
			break;
		}
		
		default:
		{
			return NULL; //�Y���Ȃ�
		}
	}
	
	return NULL;
}