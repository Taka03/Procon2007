//*==============================================
//magician.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "magician.h"
#include "joypad.h"
#include "debug.h"


//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CMagician::CMagician()
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_vPos.Set(0, 10, 0);
	m_vRot.Set(0, 0, 0);
	m_vScale.Set(1.0f, 1.0f, 1.0f);
	

}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//[return]
//	�Ȃ�
//===============================================
CMagician::CMagician(ePlayerType no)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate);
	
	D3DXQuaternionIdentity(&m_quatModel);
	
	m_name = "���@�g��";
	m_Status = 0;
	m_FirstStatus = 0;
	
	m_Special = ALLMAGIC;
	m_AttackType = ATTACK;
	m_CharaType = MAGICIAN;
	m_pTarget = NULL;
	
	m_IsDead = false;
	m_IsEnd = false;
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 1);
		m_vRot.Set(40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += '1';
	}
	
	else
	{
		m_vPos.Set(2, 0, 1);
		m_vRot.Set(-40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += '2';
	}

	
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//[return]
//	�Ȃ�
//===============================================
CMagician::CMagician(ePlayerType no, const char *name)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	
	for( int i = 0;i < MAX_ANIM;i++ )
	{
		ZeroMemory(&m_Anim[i], sizeof(HIANIMATION_DESC) );
	}
	
	
		
	//for( int i = 0;i < MAX_ANIM;i++ )
	//{
	//	m_pAnimSet[i] = NULL;
	//}
	
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate);
	
	D3DXQuaternionIdentity(&m_quatModel);
	
	m_name = "���@�g��";
	m_Status = 0;
	m_FirstStatus = 0;
	
	
	m_Special = ALLMAGIC;
	m_SpecialType = SP_ATTACK;	
	m_AttackType = ATTACK;
	m_CharaType = MAGICIAN;
	m_pTarget = NULL;
	
	m_Motion = MOT_STAND;
	
	m_FirstFrame = 0;
	m_LastFrame = 62;
	
	m_LastAnimFrame = 0.487f;	
	
	m_IsChangeAnim = false;
	
	m_IsDead = false;
	m_IsEnd = false;
	m_IsSpecial = false;
	m_IsProtected = false;
	m_IsBuildUp = false;
	m_IsAttackEnd = false;
	m_IsBurst = false;
	m_IsCritical = false;
	m_IsCounter = false;
	m_IsGuard = false;
	m_IsCharge = false;
	
	m_plType = no;
	
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_CurAnimID = 0;
		
	m_PreAnimID = m_CurAnimID;
	
//	m_Anim.clear();
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 8);
		m_vRot.Set(0, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += '1';
	}
	
	else
	{
		m_vPos.Set(2, 0, 8);
		m_vRot.Set(0, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += '2';
	}

	CXModel::Load( Joker::GetDevice(), name, NULL );
	
	//Magic = new CEffect("data/magic.x");
	//
	//Burst = new CEffect("data/ef_explosion.x");
	//
	//Fire = new CEffect("data/fireball.x");

//	MagicSquare.Load( Joker::GetDevice(), "data/magic.x", NULL);
	
	//int AnimSet = m_pAnimController->GetNumAnimationSets();
	
	numDamage = CTextureFactory::Create(GRP_NUMBER);
		
}


//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CMagician::~CMagician()
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
void CMagician::Init()
{
//	CXModel::Load(Joker::GetDevice(), "data/magister_stand.x", Joker::GetMaxBlend() );
//	CXModel::Load(Joker::GetDevice(), "data/magister_stand.x", Joker::GetMaxBlend() );
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CMagician::Exec()
{
	m_Anim[m_CurAnimID].AnimPos += 0.005;
		
	if( !m_IsDead )
	{	
		
		Burst->SetScale( CVector3(0.5f, 0.5f, 0.5f) );
		
		/*�A�j���[�V�����̐؂�ւ�*/
		int AnimSetNum = m_pAnimController->GetNumAnimationSets();
		
		for(int i = 0;i < AnimSetNum;i++)
		{
			SetShiftTime(i, 1.0f);
			SetLoopTime(i, 10.0f);
		}
		
		//Heading(m_vRot.y);
		
		Pitching(m_vRot.x);
		
		//Rolling(m_vRot.y);
		
		//Rotation(m_vRot.x, m_vRot.y, m_vRot.z);
		
		D3DXVECTOR3 vAxisX(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vAxisZ(0.0f, 0.0f, 1.0f);
		
		Translation(m_vPos.x, m_vPos.y, m_vPos.z);
		
		Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
		
		SetWorldMatrix();
		
		Render(Joker::GetDevice());
		
		ChangeAnimation(m_Motion);
		
		//if(m_IsChangeAnim)
		//{
		//	m_pAnimController->ResetTime();
		//	
		//	for( int i = 0;i < MOT_MAX;i++ )
		//	{
		//		m_Anim[i].AnimPos = 0.0f;
		//	}
		//	
		//	m_IsChangeAnim = false;
		//}
		
		//LPCSTR Name = m_Anim[m_CurAnimID].pAnimSet->GetName();
		
		m_pAnimController->SetTrackPosition(0, m_Anim[m_CurAnimID].AnimPos);
		
		//Update(0.0f);
		
		//CDebug::DrawString( "m_Position:%f", m_Anim[m_CurAnimID].AnimPos );
		
		Magic->SetPosition(m_vPos);
		
		if(m_IsSpecial)
		{
			Magic->Exec();
		}
		
		numDamage->Exec();
		
		if( Fire->GetVariableFlag() )
		{
			Fire->Exec();
		}
		
		if( Burst->GetVariableFlag() )
		{
			Burst->Exec();
		}
		
	}
	
	Update(m_Anim[m_CurAnimID].fTrackSpeed);
	
	if(m_Status <= 0)
	{
		m_Status = 0;
	}
	
	
	if(m_IsDead)
	{
		m_IsEnd = true;
	}
		
}

//===============================================
//�����_�����O
//===============================================
void CMagician::Rendering()
{
//	m_Anim += 1;

	//Heading(m_vRot.y);
	
	Pitching(m_vRot.x);
	
	//Rolling(m_vRot.y);
	
	//Rotation(m_vRot.x, m_vRot.y, m_vRot.z);
	
	D3DXVECTOR3 vAxisX(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vAxisZ(0.0f, 0.0f, 1.0f);
	
	::D3DXVec3TransformCoord(&vAxisX, &vAxisX, &m_matRotate);
	::D3DXVec3TransformCoord(&vAxisZ, &vAxisZ, &m_matRotate);

	Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	
	Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
	
	SetWorldMatrix();
	
	//Joker::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//Joker::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//Joker::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//Joker::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 8);
	//
	//Joker::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//Joker::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	Render(Joker::GetDevice());
	
//	Update(0, m_Anim*m_AnimSpeed);
}

//===============================================
//�A�j���[�V�����̃Z�b�g
//===============================================
//[input]
//	
//[return]
//
//===============================================
void CMagician::SetAnimation(int animID)
{

}


//===============================================
//�\�͂̐ݒ�
//===============================================
//[input]
//	type:����\�̓^�C�v
//[return]
//	�Ȃ�
//===============================================
void CMagician::SetAbility()
{
	if(m_SpecialType == SP_ATTACK)
	{
		m_Special = ALLMAGIC;
	}
	
	else
	{
		m_Special = RECOVER;
	}
}

//===============================================
//�S�̍U��
//===============================================
void CMagician::SpecialAttack()
{
	
}

//===============================================
//���C�t��
//===============================================
//[input]
//	attacker:�U����
//	target:�񕜑Ώ�
//===============================================
void CMagician::SpecialAssist(CCharacter *attacker, CCharacter *target)
{
	int Recover = 0;
	
	if( !(this->GetEndFlag() ) && !(target->GetEndFlag() ) )
	{
		
		Recover = this->m_Status / 2;
		
		this->m_Status -= Recover;
		
		target->SetStatus(target->GetStatus() + Recover);
		
	}
	
}
