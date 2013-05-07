//*==============================================
//character.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "character.h"
#include "joypad.h"
#include "debug.h"
#include "rand.h"
#include "font.h"

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CCharacter::CCharacter()
{
	m_Status = 0;
	m_OldStatus = 0;
	m_FirstStatus = 0;
	
	m_Special = CRITICAL;
	m_AttackType = ATTACK;
	//m_Target = FENCER;
	m_pTarget = NULL;
	//m_pCursor = NULL;
	m_name.clear();
	
	m_IsDead = false;
	m_IsEnd = false;
	m_IsAttackEnd = false;
	m_IsSpecial = false;
	m_IsProtected = false;
	m_IsBuildUp = false;
	m_IsBurst = false;
	
	m_AnimTime = 0.000f;
	
	for( int i = 0;i < SE_MAX;i++ )
	{
		se[i] = CSoundFactory::Create( (eSound)(i) );
	}
	
	
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	type:�^�C�v
//[return]
//	�Ȃ�
//===============================================
CCharacter::CCharacter(int type)
{
	m_Status = 0;
	m_OldStatus = 0;
	m_FirstStatus = 0;
	
	m_name.clear();
	m_Special = CRITICAL;
	m_AttackType = ATTACK;
	//m_Target = FENCER;
	m_pTarget = NULL;
//	m_pCursor = NULL;

	m_IsDead = false;
	m_IsEnd = false;
	m_IsSpecial = false;
	
	Burst = new CEffect("data/ef_explosion.x");
	
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	type:�L�����N�^�[�^�C�v
//	plType:�v���C���[�^�C�v
//[return]
//	�Ȃ�
//===============================================
CCharacter::CCharacter(eCharaType type, ePlayerType plType)
{
	//switch(type)
	//{
	//	this = new 
	//}
}

//===============================================
//�f�X�g���N�^
//===============================================
CCharacter::~CCharacter()
{
	Release();
}

//===============================================
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCharacter::Init()
{
	
}

//===============================================
//����
//===============================================
//[input]
//
//[return]
//
//===============================================
void CCharacter::Exec()
{

}

//===============================================
//���ʉ��̓ǂݍ���
//===============================================
void CCharacter::LoadSe()
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
	
	//for( int i = 0;i < SE_MAX;i++ )
	//{
	//	se[i] = new CSound(name[i], i);
	//}
}

//===============================================
//���ʉ��̒�~
//===============================================
//[input]
//	index:�C���f�b�N�X
//===============================================
void CCharacter::PlaySe(int index)
{
	se[index]->Play(index, 0, 0);
}


//===============================================
//���ʉ��̒�~
//===============================================
//[input]
//	index:�C���f�b�N�X
//===============================================
void CCharacter::StopSe(int index)
{
	if( se[index]->IsPlay(index) )
	{
		se[index]->Stop(index);
	}
}

//===============================================
//�ړ�
//===============================================
//[input]
//	target:�ړ��Ώې�
//===============================================
void CCharacter::Move(CCharacter *target)
{
	if(this->GetCharaType() == FENCER)
	{
		Attack(target, 2, GetLastAnimFrame() / 2 - 0.1);
	}
	
	else if(this->GetCharaType() == GUARDIAN)
	{
		Attack(target, 2, GetLastAnimFrame() / 2);
	}
	
	else if( this->GetCharaType() == RANGER)
	{
		Attack(target, 1, GetLastAnimFrame() / 2 - 0.2);
	}	
	
	else if( this->GetCharaType() == CONTRACTOR )
	{
		Attack(target, 1, GetLastAnimFrame() / 2 - 0.1);
	}
	

	
}

//===============================================
//�U��
//===============================================
//[input]
//	target:�U���Ώې�
//	moveoffset:�ړ��␳�l
//	motoffset:���[�V�����␳�l
//===============================================
void CCharacter::Attack(CCharacter *target, int moveoffset, double motoffset)
{
	if(m_plType == PLAYER_1)
	{
		if(m_vPos.x >= target->m_vPos.x - moveoffset)
		{
			SetMotion( MOT_ATTACK );
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
			//{
			//	this->SetCurrentAnimPos( this->GetLastAnimFrame() );
			//}
			
			CalcDamage( target, motoffset );
		}
					
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
			
			
			//
			//if( this->GetCharaType() == FENCER)
			//{
			//	if( !(m_IsCritical) )
			//	{
			//		this->PlaySe(SE_ATTACK_FENCER);
			//		
			//	}
			//	
			//	else
			//	{
			//		this->PlaySe(SE_CRITICAL);
			//		//se[SE_CRITICAL]->Play(SE_CRITICAL, 1, 0);
			//		
			//	}
			//}
			//
			//else if( this->GetCharaType() == RANGER )
			//{
			//	this->PlaySe(SE_ATTACK_RANGER);
			//	//se[SE_ATTACK_RANGER]->Play(SE_ATTACK_RANGER, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == CONTRACTOR )
			//{
			//	this->PlaySe(SE_ATTACK_CON);
			//	//se[SE_ATTACK_CON]->Play(SE_ATTACK_CON, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == GUARDIAN )
			//{
			//	this->PlaySe(SE_ATTACK_FENCER);
			//	//se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
			//	
			//}
			//
			
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
			//{
			//	this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
			//}
		
	}
	
	else
	{
		if(m_vPos.x <= target->m_vPos.x + moveoffset)
		{
			
			this->SetMotion(MOT_ATTACK);
			
			//if( this->GetCharaType() == FENCER)
			//{
			//	if( !(m_IsCritical) )
			//	{
			//		this->PlaySe(SE_ATTACK_FENCER);
			//		
			//	}
			//	
			//	else
			//	{
			//		this->PlaySe(SE_CRITICAL);
			//		//se[SE_CRITICAL]->Play(SE_CRITICAL, 1, 0);
			//		
			//	}
			//}
			//
			//else if( this->GetCharaType() == RANGER )
			//{
			//	this->PlaySe(SE_ATTACK_RANGER);
			//	//se[SE_ATTACK_RANGER]->Play(SE_ATTACK_RANGER, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == CONTRACTOR )
			//{
			//	this->PlaySe(SE_ATTACK_CON);
			//	//se[SE_ATTACK_CON]->Play(SE_ATTACK_CON, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == GUARDIAN )
			//{
			//	this->PlaySe(SE_ATTACK_FENCER);
			//	//se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
			//	
			//}
			
			//}
			CalcDamage( target, motoffset);
			
			//target->numDamage->SetVariableFlag( false );
			
		}
		
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
	}	

}

//===============================================
//�U��
//===============================================
//[input]
//	target:�U���Ώې�
//	moveoffset:�ړ��␳�l
//	motoffset:���[�V�����␳�l
//===============================================
void CCharacter::BurstS(CCharacter *target, int moveoffset, double motoffset)
{
	if(m_plType == PLAYER_1)
	{
		if(m_vPos.x >= target->m_vPos.x - moveoffset)
		{
			if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
			{
				this->SetCurrentAnimPos( this->GetLastAnimFrame() );
				
				if(this->GetBurstFlag() )
				{
					this->PlaySe(SE_BOMB);
				}
				
			}
			
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
			//{
			//	this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
			//}
			CalcDamage( target, motoffset );
		}
					
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
		
	}
	
	else
	{
		if(m_vPos.x <= target->m_vPos.x + moveoffset)
		{
			
			//this->SetMotion(MOT_ATTACK);
			
			if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
			{
				this->SetCurrentAnimPos( this->GetLastAnimFrame() );
				
				if(this->GetBurstFlag() )
				{
					this->PlaySe(SE_BOMB);
				}
				
			}
			
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
			//{
			//	this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
			//}
			CalcDamage( target, motoffset);
			
			//target->numDamage->SetVariableFlag( false );
			
		}
		
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
		
			
/*			if( this->GetMotion() == MOT_ATTACK )
			{
				if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
				{
					this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
				}
				
				if(this->GetCurrentAnim().AnimPos >= motoffset) 
				{
					CalcDamage( target );
				
					if( this->GetCharaType() == FENCER)
					{
						if( !(m_IsCritical) )
						{
							se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
							
						}
						
						else
						{
							se[SE_CRITICAL]->Play(SE_CRITICAL, 1, 0);
							
						}
					}
					
					else if( this->GetCharaType() == RANGER )
					{
						se[SE_ATTACK_RANGER]->Play(SE_ATTACK_RANGER, 1, 0);
						
					}
					
					else if( this->GetCharaType() == CONTRACTOR )
					{
						se[SE_ATTACK_CON]->Play(SE_ATTACK_CON, 1, 0);
						
					}
					
					else if( this->GetCharaType() == GUARDIAN )
					{
						se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
						
					}
					
				}
				
			}
			
		}*/
		
	}	

}

//===============================================
//���@�U��
//===============================================
//[input]
//	target:�U���Ώې�
//===============================================
void CCharacter::MagicAttack(CCharacter *target)
{	
	this->SetMotion(MOT_MOVE);
	
	if(!Fire->GetVariableFlag() )
	{
		Fire->SetPosition(this->m_vPos);
		
		if(this->GetPlayerType() == PLAYER_1 )
		{
			Fire->SetRotate(CVector3(GET_ANGLE(45), 0, 0) );
		}
		
		else
		{
			Fire->SetRotate(CVector3(GET_ANGLE(-45), 0, 0) );
		}
	}
	
	Fire->SetVariableFlag(true);
	
	CVector3 vDirection = this->GetPosition() - target->GetPosition();
	
	
		
	Fire->AddPosition(vDirection * 0.03f);
		
	if(this->GetCurrentAnim().AnimPos >= GetLastAnimFrame() )
	{
		
		
		this->SetMotion(MOT_ATTACK);
		
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() / 3)
		{
			this->SetCurrentAnimPos(this->GetLastAnimFrame() / 3);
		}
		
		this->PlaySe(SE_ATTACK1_MAGI);
		this->PlaySe(SE_ATTACK2_MAGI);
		
		this->CalcDamage(target, GetLastAnimFrame() / 2 );
		
	}
}

//===============================================
//���@�S�̍U��
//===============================================
//[input]
//	target:�U���Ώې�
//===============================================
void CCharacter::MagicAllAttack(CCharacter *target[])
{
	this->SetMotion(MOT_MOVE);
	
	if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame())
	{
	
		this->SetMotion(MOT_ATTACK);
		
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			//Burst->SetVariableFlag(true);
			
			this->SetCurrentAnimPos(this->GetLastAnimFrame() );
		}
		
		//CVector3 Pos(target[2]->GetPosition
		
		Burst->SetPosition(target[2]->GetPosition() );
		
		//this->Burst
		
		this->CalcDamage(target);
			
		
	}
}

//===============================================
//�g����
//===============================================
//[input]
//	target:�g�����
//===============================================
void CCharacter::Alternate(CCharacter *target[])
{
	this->SetTarget( target[FENCER] );
}


//===============================================
//�񕜖��@
//===============================================
//[input]
//	target:�񕜑Ώې�
//===============================================
void CCharacter::Recover(CCharacter *target)
{
	if( this->GetPlayerType() == PLAYER_1 )
	{
		this->numDamage->SetPosition(100, 200);
		target->numDamage->SetPosition(400, 200);
		this->numDamage->SetVisibleFlag( true );
		target->numDamage->SetVisibleFlag( true );
	}
	
	else
	{
		this->numDamage->SetPosition(400, 200);
		target->numDamage->SetPosition(100, 200);
		
		this->numDamage->SetVisibleFlag( true );
		target->numDamage->SetVisibleFlag( true );
		
	}
	
	this->SetMotion(MOT_MOVE);
	
	int Recover = this->GetStatus() / 2;//�񕜗�
	
	if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
	{
		this->SetMotion( MOT_ATTACK );
		
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			this->SetCurrentAnimPos(this->GetLastAnimFrame() );
			
			//if(m_IsAttackEnd)
			//{
			//	this->StopSe(SE_HEAL);
			//}
			
			//this->SetEndFlag( true );
		}
		
	}
	
	if(!m_IsAttackEnd)
	{
		if(!(target->GetDeadFlag() ) )
		{
			target->m_Status += Recover;
			
			this->m_Status -= Recover;
		}
		
		this->PlaySe(SE_HEAL);
	}
	
	
	this->SetAttackEndFlag( true );
	
}

//===============================================
//����
//===============================================
//[input]
//	target:�����Ώې�
//===============================================
void CCharacter::BuildUp(CCharacter *target)
{
	this->SetMotion(MOT_SPECIAL);
	
	if( !(this->GetAttackEndFlag() ) )
	{
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() * 2)		
		{
			this->SetCurrentAnimPos(this->GetLastAnimFrame() * 2);
			
		}
		
		target->SetBuildFlag(true);
		
	}
	
	this->SetAttackEndFlag( true );
	
}






//===============================================
//�A�j���[�V�����̐؂�ւ�
//===============================================
//void CCharacter::ChangeAnimation()
//{
//	switch(m_Motion)
//	{
//		/*�������[�V����*/
//		case MOT_STAND:
//		{
//			m_FirstFrame = 3;
//			
//			m_LastFrame = 62;		
//			
//			break;
//		}
//		
//		/*�ړ����[�V����*/
//		case MOT_MOVE:
//		{
//			m_FirstFrame = 63;
//			
//			m_LastFrame = 126;
//			
//			break;
//		}
//		
//		/*�U�����[�V����*/
//		case MOT_ATTACK:
//		{
//			m_FirstFrame = 127;
//			
//			m_LastFrame = 188;
//			
//			break;
//		}
//		
//		/*�_���[�W���[�V����*/
//		case MOT_DAMAGE:
//		{
//			m_FirstFrame = 210;
//			
//			m_LastFrame = 272;
//			
//			break;
//		}
//		
//		/*���S���[�V����*/
//		case MOT_DEAD:
//		{
//			m_FirstFrame = 273;
//			
//			m_LastFrame = 333;
//			
//			break;
//		}
//	}
//}

//===============================================
//�ʒu���W�̎擾
//===============================================
//[return]
//	�ʒu���W
//===============================================
CVector3 CCharacter::GetPosition()
{
	return m_vPos;
}

//===============================================
//�X�e�[�^�X�̎擾
//===============================================
//[return]
//	�X�e�[�^�X
//===============================================
int CCharacter::GetStatus()
{
	return m_Status;
}

//===============================================
//�Â��X�e�[�^�X�̎擾
//===============================================
//[return]
//	�Â��X�e�[�^�X
//===============================================
int CCharacter::GetOldStatus()
{
	return m_OldStatus;
}


//===============================================
//�����X�e�[�^�X�̎擾
//===============================================
//[return]
//	�����X�e�[�^�X
//===============================================
int CCharacter::GetFirstStatus()
{
	return m_FirstStatus;
}

//===============================================
//�U���Ώۂ̎擾
//===============================================
//[return]
//	�U���Ώ�
//===============================================
CCharacter *CCharacter::GetTarget()
{
	return m_pTarget;
}

//===============================================
//���S�t���O�̎擾
//===============================================
//[return]
//	���S�t���O
//===============================================
bool CCharacter::GetDeadFlag()
{
	return m_IsDead;
}

//===============================================
//�s���I���t���O�̎擾
//===============================================
//[return]
//	�s���I���t���O
//===============================================
bool CCharacter::GetEndFlag()
{
	return m_IsEnd;
}	

//===============================================
//�N���e�B�J���t���O�̎擾
//===============================================
//[return]
//	�N���e�B�J���t���O
//===============================================
bool CCharacter::GetCriticalFlag()
{
	return m_IsCritical;
}	

//===============================================
//�����߁��t���O�̎擾
//===============================================
//[return]
//	�����߁��t���O
//===============================================
bool CCharacter::GetChargeFlag()
{
	return m_IsCharge;
}	


//===============================================
//�U���I���t���O�̎擾
//===============================================
//[return]
//	�U���I���t���O
//===============================================
bool CCharacter::GetAttackEndFlag()
{
	return m_IsAttackEnd;
}

//===============================================
//����\�͔���t���O�̎擾
//===============================================
//[return]
//	����\�͔���t���O�̎擾
//===============================================
bool CCharacter::GetSpecialFlag()
{
	return m_IsSpecial;
}

//===============================================
//��������t���O�̎擾
//===============================================
//[return]
//	��������t���O�̎擾
//===============================================
bool CCharacter::GetBuildFlag()
{
	return m_IsBuildUp;
}

//===============================================
//�g���蔻��t���O�̎擾
//===============================================
//[return]
//	�g���蔻��t���O�̎擾
//===============================================
bool CCharacter::GetProtectedFlag()
{
	return m_IsProtected;
}

//===============================================
//�o�[�X�g�t���O�̐ݒ�
//===============================================
//[input]
//	flag:�o�[�X�g�t���O
//===============================================
bool CCharacter::GetBurstFlag()
{
	return m_IsBurst;
}

//===============================================
//�h��t���O�̎擾
//===============================================
//[return]
//	�h��t���O
//===============================================
bool CCharacter::GetGuardFlag()
{
	return m_IsGuard;
}	

//===============================================
//�J�E���^�[�t���O�̎擾
//===============================================
//[return]
//	�J�E���^�[�t���O
//===============================================
bool CCharacter::GetCounterFlag()
{
	return m_IsCounter;
}	


//===============================================
//�L�����^�C�v�̎擾
//===============================================
//[return]
//	�L�����^�C�v
//===============================================
eCharaType CCharacter::GetCharaType()
{
	return m_CharaType;
}

//===============================================
//�U���^�C�v�̎擾
//===============================================
//[return]
//	�U���^�C�v
//===============================================
eAttackType CCharacter::GetAttackType()
{
	return m_AttackType;
}

//===============================================
//����\�͂̎擾
//===============================================
//[return]
//	����\��
//===============================================
eSpecial CCharacter::GetSpecial()
{
	return m_Special;
}

//===============================================
//����\�̓^�C�v�̎擾
//===============================================
//[return]
//	����\�̓^�C�v
//===============================================
eSpecialType CCharacter::GetSpecialType()
{
	return m_SpecialType;
}

//===============================================
//�L�����̖��O�̎擾
//===============================================
//[return]
//	�L�����̖��O
//===============================================
string CCharacter::GetName()
{
	return m_name.c_str();
}

//===============================================
//���݂̃A�j���[�V�����\���̂̎擾
//===============================================
//[return]
//	���݂̃A�j���[�V�����\����
//===============================================
HIANIMATION_DESC CCharacter::GetCurrentAnim()
{
	return m_Anim[m_CurAnimID];
}


//===============================================
//���[�V�����̎擾
//===============================================
//[return]
//	���[�V����
//===============================================
eMotion CCharacter::GetMotion()
{
	return m_Motion;
}

//===============================================
//���[�V�����̎擾
//===============================================
//[return]
//	���[�V����
//===============================================
ePlayerType CCharacter::GetPlayerType()
{
	return m_plType;
}


//===============================================
//�ŏ��̃t���[�����̎擾
//===============================================
//[return]
//	�ŏ��̃t���[��
//===============================================
float CCharacter::GetFirstFrame()
{
	return m_FirstFrame;
}

//===============================================
//�Ō�̃t���[�����̎擾
//===============================================
//[return]
//	�Ō�̃t���[��
//===============================================
float CCharacter::GetLastFrame()
{
	return m_LastFrame;
}

//===============================================
//�A�j���[�V�����̍Ō�̃t���[���擾
//===============================================
//[return]
//	�A�j���[�V�����̍Ō�̃t���[��
//===============================================
double CCharacter::GetLastAnimFrame()
{
	return m_LastAnimFrame;
}

//===============================================
//�ʒu�̐ݒ�
//===============================================
//[input]
//	posx:X���W
//	posy:Y���W
//	posz:Z���W
//===============================================
void CCharacter::SetPosition(float posx, float posy, float posz)
{
	m_vPos.x = posx;
	m_vPos.y = posy;
	m_vPos.z = posz;
}

//===============================================
//�p�x�̐ݒ�
//===============================================
//[input]
//	xangle:X�p�x
//	yagle:Y�p�x
//	zangle:Z�p�x
//===============================================
void CCharacter::SetRotate(float xangle, float yangle, float zangle)
{
	m_vRot.x = xangle;
	m_vRot.y = yangle;
	m_vRot.z = zangle;
}


//===============================================
//�X�e�[�^�X�̐ݒ�
//===============================================
//[input]
//	status:�ݒ肷��X�e�[�^�X
//===============================================
void CCharacter::SetStatus(int status)
{
	m_Status = status;
	m_OldStatus = status;
	m_FirstStatus = status;
}

//===============================================
//�J�[�\���̈ʒu�Z�b�g
//===============================================
//[input]
//	player:�v���C���[�^�C�v
//	obj:�U���Ώ�
//===============================================
void CCharacter::SetCursor(ePlayerType plType, CCharacter *obj)
{
	/*�J�[�\���̈ʒu�Z�b�g*/
	//m_pCursor->SetCursor(plType, obj);
}

//===============================================
//�Â��X�e�[�^�X�̐ݒ�
//===============================================
void CCharacter::SetOldStatus()
{
	m_OldStatus = m_Status;
}

//===============================================
//�U���Ώۂ̐ݒ�
//===============================================
//[input]
//	obj:�U���Ώ�
//===============================================
void CCharacter::SetTarget(CCharacter *obj)
{
	m_pTarget = obj;
}

//===============================================
//�U���^�C�v�̐ݒ�(�U�������ꂩ)
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//===============================================
void CCharacter::SetAttackType(ePlayerType no)
{
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	{
		m_AttackType = ATTACK;	
	}
	
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	{
		m_AttackType = SPECIAL;
	}
	
	//CDebug::DrawString("Type:%d", m_AttackType);
	
}

//===============================================
//�U���^�C�v�̐ݒ�(AI�p)
//===============================================
//[input]
//	type:�U���^�C�v
//===============================================
void CCharacter::SetAttackType_AI(int type)
{
	if(type == 0)
	{
		m_AttackType = ATTACK;
	}
	
	if(type == 1)
	{
		m_AttackType = SPECIAL;
	}
}

//===============================================
//����\�̓^�C�v�̐ݒ�(�U���n������n��)
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//===============================================
void CCharacter::SetSpecialType(ePlayerType no)
{
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	{
		m_SpecialType = SP_ATTACK;
	}
	
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	{
		m_SpecialType = SP_ASSIST;
	}
}

//===============================================
//����\�̓^�C�v�̐ݒ�(�U���n������n��)
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//===============================================
void CCharacter::SetSpecialType_AI(bool type)
{
	if(type == false ) 
	{
		m_SpecialType = SP_ATTACK;
	}
	
	else
	{
		m_SpecialType = SP_ASSIST;
	}
}


//===============================================
//���S�t���O�̐ݒ�
//===============================================
//[input]
//	flag:���S�������ǂ���
//===============================================
void CCharacter::SetDeadFlag(bool flag)
{
	m_IsDead = flag;
}

//===============================================
//�N���e�B�J���t���O�̐ݒ�
//===============================================
//[input]
//	flag:�N���e�B�J���t���O
//===============================================
void CCharacter::SetCriticalFlag(bool flag)
{
	m_IsCritical = flag;
}


//===============================================
//�����t���O�̐ݒ�
//===============================================
//[input]
//	flag:�����������ǂ���
//===============================================
void CCharacter::SetBuildFlag(bool flag)
{
	m_IsBuildUp = flag;
}

//===============================================
//�g����t���O�̐ݒ�
//===============================================
//[input]
//	flag:�g���肵�����ǂ���
//===============================================
void CCharacter::SetProtectedFlag(bool flag)
{
	m_IsProtected = flag;
}

//===============================================
//�s���I���t���O�̐ݒ�
//===============================================
//[input]
//	flag:�s���I���������ǂ���
//===============================================
void CCharacter::SetBurstFlag(bool flag)
{
	m_IsBurst = flag;
}

//===============================================
//�s���I���t���O�̐ݒ�
//===============================================
//[input]
//	flag:�s���I���������ǂ���
//===============================================
void CCharacter::SetEndFlag(bool flag)
{
	m_IsEnd = flag;
}

//===============================================
//�s���I���t���O�̐ݒ�
//===============================================
//[input]
//	flag:�s���I���������ǂ���
//===============================================
void CCharacter::SetAttackEndFlag(bool flag)
{
	m_IsAttackEnd = flag;
}

//===============================================
//����\�̓t���O�̐ݒ�
//===============================================
//[input]
//	flag:����\�̓t���O
//===============================================
void CCharacter::SetSpecialFlag(bool flag)
{
	m_IsSpecial = flag;
}

//===============================================
//�`���[�W�t���O�̐ݒ�
//===============================================
//[input]
//	flag:�`���[�W�t���O
//===============================================
void CCharacter::SetChargeFlag(bool flag)
{
	m_IsCharge= flag;
}

//===============================================
//�J�E���^�[�t���O�̐ݒ�
//===============================================
//[input]
//	flag:�J�E���^�[�t���O
//===============================================
void CCharacter::SetCounterFlag(bool flag)
{
	m_IsCounter= flag;
}

//===============================================
//�K�[�h�t���O�̐ݒ�
//===============================================
//[input]
//	flag:�K�[�h�t���O
//===============================================
void CCharacter::SetGuardFlag(bool flag)
{
	m_IsGuard = flag;
}

//===============================================
//���[�V�����̐ݒ�
//===============================================
//[input]
//	motion:�ݒ肷�郂�[�V����
//===============================================
void CCharacter::SetMotion(eMotion motion)
{
	if(m_Motion != MOT_DEAD)
	{
		m_Motion = motion;
	}
}

//===============================================
//�A�j���[�V�����̐ݒ�
//===============================================
//[input]
//	animID:�A�j���[�V����ID
//===============================================
void CCharacter::SetAnimation(int animID)
{
	//m_pAnimController->RegisterAnimationSet
	//m_pAnimController->GetAnimationSet(animID, 
}

//===============================================
//���݂̃A�j���[�V�����ʒu�̐ݒ�
//===============================================
//[input]
//	pos:�ʒu
//===============================================
void CCharacter::SetCurrentAnimPos(double pos)
{
	m_Anim[m_CurAnimID].AnimPos = pos;
}



//===============================================
//�X�e�[�^�X�̑���
//===============================================
//[input]
//	status:�X�e�[�^�X
//===============================================
void CCharacter::CalcStatus(int status)
{
	m_Status += status;
}

//===============================================
//�_���[�W�ʂ̌v�Z
//===============================================
//[input]
//	target:�U���Ώ�
//[return]
//	�_���[�W
//===============================================
int CCharacter::CalcDamage(CCharacter *target[])
{
	int Damage = 0;//�_���[�W
	
	int Attack = this->GetStatus() / 3; //�U����
	
	int OldAttack = Attack;
	
	int DeadCharaNum = 0;//���S�L������
	
	this->m_IsSpecial = true;
	
	if(this->GetPlayerType() == PLAYER_1 )
	{
		this->numDamage->SetPosition(200.0, 200 );
		
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			target[i]->numDamage->SetPosition( F(400), F(200 + i * 50) );
			target[i]->numDamage->SetVisibleFlag( true );
		}
	}
	
	else 
	{
		this->numDamage->SetPosition(400, 200 );
		
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			target[i]->numDamage->SetPosition( F(100), F(200 + i * 50) );
			target[i]->numDamage->SetVisibleFlag( true );
		}
	}
	
	if( !(this->m_IsEnd) && !(this->m_IsAttackEnd) )
	{
		/*���S�L�����𑝂₷*/
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			if(target[i]->GetDeadFlag() )
			{
				DeadCharaNum ++;
			}	
		
		}
		
		int LiveCharaNum = MAX_CHARA - DeadCharaNum;//�����L������
		
		/*��������Ă���ꍇ*/
		if(this->GetBuildFlag() )
		{
			Attack *= 3;
		}
		
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			
			/*�K�[�f�B�A��*/
			if(target[i]->GetCharaType() == GUARDIAN)
			{
				/*�J�E���^�[*/
				if( target[i]->m_IsCounter )
				{
					target[i]->SetMotion(MOT_ATTACK);
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
				}
				
				else
				{
					Damage = Attack / LiveCharaNum;
					
					target[i]->m_Status -= Damage;
					
				}
			}
			
			else if( target[i]->GetCharaType() == CONTRACTOR )
			{
				if( target[i]->m_IsGuard )
				{
					Attack /= 10;
					
					Damage = Attack / LiveCharaNum;
					
					target[i]->m_Status -= Damage;
					
					char temp[MAX_PATH] = "";
				
					wsprintf(temp, "%d", Damage);
				
					string Str;
					
					Str = temp;
					
					target[i]->numDamage->SetText(Str);
					
					target[i]->SetMotion( MOT_SPECIAL );
					
					//target[i]->Aura->SetVariableFlag( true );
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
						
					
				}
				
				else
				{
					Damage = Attack / LiveCharaNum;
					
					target[i]->m_Status -= Damage;
				
				
				}
			
			}
			
			else
			{
				Damage = Attack / LiveCharaNum;
				
				target[i]->m_Status -= Damage;
				
				char temp[MAX_PATH] = "";
			
				wsprintf(temp, "%d", Damage);
			
				string Str;
				
				Str = temp;
				
				target[i]->numDamage->SetText(Str);
				
				
			}
			
		}		
		
		this->m_IsAttackEnd = true;
		
	}
	
	CDebug::DrawString("�S�̍U��:%d", Damage );
	
	//----------------------------------------------
	//���[�V�����̐ݒ�
	//----------------------------------------------
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		if(target[i]->GetStatus() > 0)
		{
			if(target[i]->GetCharaType() == GUARDIAN )
			{
				/*�J�E���^�[*/
				if( target[i]->m_IsCounter )
				{
					target[i]->SetMotion(MOT_ATTACK);
					
					target[i]->PlaySe(SE_ATTACK_FENCER);
						
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						//target->StopSe(SE_ATTACK_FENCER);
						
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
						
				}
			}
			
			else if( target[i]->GetCharaType() == CONTRACTOR )
			{
				/*�h����*/
				if( target[i]->m_IsGuard )
				{
					target[i]->SetMotion( MOT_SPECIAL );
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
					
				}
			}
			
			else
			{
				target[i]->SetMotion( MOT_DAMAGE );

				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
				}
			}
		}
		
		else
		{
			/*�J�E���^�[*/
			if( target[i]->m_IsCounter )
			{
				target[i]->SetMotion(MOT_ATTACK);
				
				target[i]->PlaySe(SE_ATTACK_FENCER);
				
					
				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					//target[i]->StopSe(SE_ATTACK_FENCER);
					
					target[i]->SetMotion(MOT_DEAD);
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos(target[i]->GetLastAnimFrame() );
					}
				}
					
			}
			
			/*�h����*/
			else if( target[i]->m_IsGuard )
			{
				target[i]->SetMotion( MOT_SPECIAL );
				
				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					target[i]->SetMotion(MOT_DEAD);
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos(target[i]->GetLastAnimFrame() );
					}
				}
				
			}
			
			else
			{
				target[i]->SetMotion( MOT_DEAD );
				
				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
				}
			}
			
		}
	}
	
	//	
	//	

	//	
	//	
	//	
	//	/*�J�E���^�[�t���O*/
	//	if( target[GUARDIAN]->GetCounterFlag() )
	//	{
	//		int CounterDamage = OldAttack / 2;
	//		
	//		this->m_Status -= CounterDamage;
	//		
	//		char temp[MAX_PATH] = "";
	//	
	//		wsprintf(temp, "%d", CounterDamage);
	//	
	//		string Str;
	//		
	//		Str = temp;
	//		
	//		this->numDamage->SetText(Str);
	//		
	//		this->numDamage->SetVisibleFlag(true);
	//		
	//		Damage = OldAttack / LiveCharaNum;
	//		
	//		target[GUARDIAN]->m_Status -= Damage;
	//		
	//		wsprintf(temp, "%d", Damage);
	//	
	//		Str = temp;
	//		
	//		target[GUARDIAN]->numDamage->SetText(Str);
	//		
	//	}
	//	
	//	else
	//	{
	//		Damage = Attack / LiveCharaNum;
	//		
	//		target[GUARDIAN]->m_Status -= Damage;
	//		
	//		char temp[MAX_PATH] = "";
	//		
	//		wsprintf(temp, "%d", Damage);
	//	
	//		string Str = temp;
	//		
	//		target[GUARDIAN]->numDamage->SetText(Str);
	//		
	//	
	//	}
	//	
	//	//int NormalDamage = OldAttack / LiveCharaNum;
	//	
	//	for( int i = 0;i < MAX_CHARA;i++ )
	//	{
	//		if( target[i]->GetCharaType() == CONTRACTOR )
	//		{
	//		
	//		}
	//		
	//		else if(target[i]->GetCharaType() == GUARDIAN )
	//		{
	//		
	//		}
	//		
	//		else
	//		{
	//			Damage = OldAttack / LiveCharaNum;
	//			
	//			target[i]->m_Status -= Damage;
	//			
	//			char temp[MAX_PATH] = " ";
	//			
	//			wsprintf(temp, "%d", Damage);
	//		
	//			string Str = temp;
	//			
	//			target[i]->numDamage->SetText(Str);
	//			
	//		}
	//	}
	//	
	//	
	//	this->m_IsAttackEnd = true;
	//
	//}
	//
	//for( int i = 0;i < MAX_CHARA;i++ )
	//{
	//	if(target[i]->GetStatus() > 0)
	//	{
	//		target[i]->SetMotion( MOT_DAMAGE );
	//		
	//		if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
	//		{
	//			target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
	//		}
	//	
	//	}
	//	
	//	else
	//	{
	//		target[i]->SetMotion( MOT_DEAD );
	//		
	//		if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
	//		{
	//			target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
	//		}
	//	
	//	}
	//}
	
	
	
	return Damage;
		
}

//===============================================
//�_���[�W�ʂ̌v�Z
//===============================================
//[input]
//	target:�U���Ώ�
//[return]
//	�_���[�W
//===============================================
int CCharacter::CalcDamage(CCharacter *target, double motoffset)
{
	int Damage = 0;//�_���[�W
	
	int Attack = this->GetStatus() / 3;//�U����

	const int FIX_DAMAGE = 10;//�Œ�_���[�W��
	
	if(this->GetPlayerType() == PLAYER_1 )
	{
		numDamage->SetPosition(400, 200);
	}
	
	else
	{
		numDamage->SetPosition(200, 200);
	}
	
	//if( target->GetPlayerType() == PLAYER_1 )
	//{
	//	target->numDamage->SetPosition( 400, 100 );
	//}
	//
	//else
	//{
	//	target->numDamage->SetPosition( 100, 100 );
	//}
	
	long rnd = JRand::GetInt(0, 1);
	
	if( this->GetCharaType() == FENCER ) 
	{
		/*�N���e�B�J����Ԃ̎�*/
		if(this->GetSpecialFlag() )
		{
			rnd = JRand::GetInt(0, 1);
			if(rnd == 0)
			{
				Attack *= 2;
				m_IsCritical = true;
			}
		}
	}
	
	if( this->GetCharaType() == RANGER )
	{
		if( this->GetAttackType() == SPECIAL )
		{
			if( this->GetSpecial() == FIRST_ATTACK )
			{
				Attack /= 2;
			}
			
		}
	}
	
	if( this->GetCharaType() == CONTRACTOR )
	{
		if( this->GetBurstFlag() )
		{
			Attack = this->GetOldStatus();
		}
	
	}
	
	if( target->GetCharaType() == CONTRACTOR )
	{
		/*�h����*/
		if( target->m_IsGuard )
		{
			Attack /= 10;
		}
	}
	
	
	if( this->GetCharaType() == GUARDIAN )
	{
		if( this->m_IsCharge )
		{
			Attack *= 2;
		}

	}
	
	/*������Ԃ̎�*/
	if(this->GetBuildFlag() )
	{
		Attack *= 3;
	}
	
	if( this->GetPlayerType() == PLAYER_1 )
	{
		this->numDamage->SetPosition( 400, 300 );
	}
	
	else
	{
		this->numDamage->SetPosition( 100, 200 );
	}
	
	this->numDamage->SetVisibleFlag(true);
	
	if( !(this->m_IsEnd) && !(this->m_IsAttackEnd) )
	{
		//------------------------------------
		//���[�V�����̐ݒ�
		//------------------------------------		
		
		Damage = Attack + FIX_DAMAGE; 

		target->m_Status -= Damage;
		
		char temp[MAX_PATH] = "";
		
		wsprintf(temp, "%d", Damage);
		
		string Str;
		
		Str = temp;
		
		this->numDamage->SetText(Str);
		
		if( target->GetCharaType() == GUARDIAN )
		{
			/*�J�E���^�[*/
			if( target->m_IsCounter )
			{
				int CounterDamage = Attack / 2;
				
				this->m_Status -= CounterDamage;
				
				//CDebug::DrawString("%s��%d�̃J�E���^�[�_���[�W", this->GetName().data(), CounterDamage);
			}
		
		}
		
		
		/*����*/
		if(this->GetBurstFlag() )
		{
			this->CalcStatus(-5000);
			
			this->SetBurstFlag( false );
		}
		
		this->m_IsAttackEnd = true;
		
	}
	
	if(this->GetCurrentAnim().AnimPos >= motoffset )
	{
		if(target->GetStatus() > 0)
		{
			/*�J�E���^�[*/
			if( target->m_IsCounter )
			{
				target->SetMotion(MOT_ATTACK);
				
				target->PlaySe(SE_ATTACK_FENCER);
					
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					//target->StopSe(SE_ATTACK_FENCER);
					
					
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
					
			}
			
			/*�h����*/
			else if( target->m_IsGuard )
			{
				target->SetMotion( MOT_SPECIAL );
				
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
				
			}
			
			else
			{
				target->SetMotion( MOT_DAMAGE );

				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
			}
		}
		
		else
		{
			/*�J�E���^�[*/
			if( target->m_IsCounter )
			{
				target->SetMotion(MOT_ATTACK);
				
				target->PlaySe(SE_ATTACK_FENCER);
				
					
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					//target->StopSe(SE_ATTACK_FENCER);
					
					target->SetMotion(MOT_DEAD);
					
					if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
					{
						target->SetCurrentAnimPos(target->GetLastAnimFrame() );
					}
				}
					
			}
			
			/*�h����*/
			else if( target->m_IsGuard )
			{
				target->SetMotion( MOT_SPECIAL );
				
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetMotion(MOT_DEAD);
					
					if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
					{
						target->SetCurrentAnimPos(target->GetLastAnimFrame() );
					}
				}
				
			}
			
			else
			{
				target->SetMotion( MOT_DEAD );
				
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
			}
			
		}

	}

	return Damage;
		
}

//===============================================
//�_���[�W���[�V����
//===============================================
//[input]
//	target:�Ώ�
//===============================================
void CCharacter::DamageMotion(CCharacter *target[])
{
	if(this->GetMotion() == MOT_ATTACK)			
	{
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			if( this->GetPlayerType() == PLAYER_1 )
			{
				for( int i = 5;i < ALL_CHARA;i++ )
				{
					if( target[i]->GetMotion() != MOT_DEAD )
					{
						target[i]->SetMotion(MOT_DAMAGE);
					}
				}
			}
			
			else
			{
				for( int i = 0;i < MAX_CHARA;i++ )
				{
					if( target[i]->GetMotion() != MOT_DEAD )
					{
						target[i]->SetMotion(MOT_DAMAGE);
					}
				}
			}
		
		}
	}
	
}

//===============================================
//�_���[�W���[�V����
//===============================================
//[input]
//	target:�Ώ�
//===============================================
void CCharacter::DamageMotion(CCharacter *target)
{
	if(this->GetMotion() == MOT_ATTACK)			
	{
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			if( this->GetPlayerType() == PLAYER_1 )
			{
				if( target->GetMotion() != MOT_DEAD )
				{
					target->SetMotion(MOT_DAMAGE);
				}
				
			}
			
			else
			{
				if( target->GetMotion() != MOT_DEAD )
				{
					target->SetMotion(MOT_DAMAGE);
				}
			}
		
		}
	}
	
}


//===============================================
//���S���[�V����
//===============================================
//[input]
//	target:�Ώ�
//===============================================
void CCharacter::DeadMotion(CCharacter *target)
{
	//if(target->GetStatus() <= 0)
	//{
	//	target->SetMotion(MOT_DEAD);
	//}
}


//===============================================
//�L�����N�^�[�̑I��
//===============================================
//[input]
//	target:�U���Ώ�
//===============================================
void CCharacter::ChooseCharacter(CCharacter *target)
{
	//m_pCursor->ChooseCharacter(this, target);
}


//===============================================
//�L�����̓���ւ�
//===============================================
//[input]
//	target:�ΏۂƂ���L����
//===============================================
int CCharacter::Swap(CCharacter attacker, CCharacter target)
{
	int temp;
	
	temp = attacker.m_Status;
	attacker.SetStatus(target.m_Status);
	target.SetStatus(temp);
	
	return temp;
}

//void CCharacter::Swap(CCharacter *target1, CCharacter *target2)
//{
//	CCharacter temp;
//	
//	temp = *target1;
//	
//	*target1 = *target2;
//	
//	*target2 = temp;
//}





	


