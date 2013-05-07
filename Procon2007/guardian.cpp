//*==============================================
//guardian.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "guardian.h"

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CGuardian::CGuardian()
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_vPos.Set(0, 50, 0);
	m_vRot.Set(0, 0, 0);
	m_vScale.Set(2, 1, 1); 
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//[return]
//	�Ȃ�
//===============================================
CGuardian::CGuardian(ePlayerType no)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate);
	
	D3DXQuaternionIdentity( &m_quatModel );
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_name = "���R�m";
	m_Status = 10000;
	m_FirstStatus = 0;
	m_Special = CHARGE_ATTACK;
	m_AttackType = ATTACK;
	m_CharaType = GUARDIAN;
	m_pTarget = NULL;
	
	m_IsDead = false;
	m_IsEnd = false;

	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 4);
		m_vRot.Set(40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += "1";
	}
	
	else
	{
		m_vPos.Set(2, 0, 4);
		m_vRot.Set(-40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += "2";
	}
	
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//	name:�t�@�C����
//[return]
//	�Ȃ�
//===============================================
CGuardian::CGuardian(ePlayerType no, const char *name)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate);
	
	D3DXQuaternionIdentity( &m_quatModel );
	
	for( int i = 0;i < MAX_ANIM;i++ )
	{
		ZeroMemory(&m_Anim[i], sizeof(HIANIMATION_DESC) );
	}
	
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_name = "���R�m";
	m_Status = 10000;
	m_FirstStatus = 0;
	m_Special = CHARGE_ATTACK;
	m_AttackType = ATTACK;
	m_CharaType = GUARDIAN;
	m_SpecialType = SP_ATTACK;	
	
	m_pTarget = NULL;
	m_Motion = MOT_STAND;
	
	m_plType = no;
	
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
	
	
	m_CurAnimID = 0;
		
	m_PreAnimID = m_CurAnimID;
	
	
//	m_Anim.clear();
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 2);
		m_vRot.Set(40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += "1";
	}
	
	else
	{
		m_vPos.Set(2, 0, 2);
		m_vRot.Set(-40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += "2";
	}
	
	CXModel::Load( Joker::GetDevice(), name, NULL );
	
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
CGuardian::~CGuardian()
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
void CGuardian::Init()
{
	//CXModel::Load(Joker::GetDevice(), "data/magister_stand.x", Joker::GetMaxBlend() );
	
	//CXModel::Load(Joker::GetDevice(), "data/act_soldier_basic.x", Joker::GetMaxBlend() );
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CGuardian::Exec()
{
	m_Anim[m_CurAnimID].AnimPos += 0.005;
		
	if( !m_IsDead )
	{	
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
		
		LPCSTR Name = m_Anim[m_CurAnimID].pAnimSet->GetName();
		
		m_pAnimController->SetTrackPosition(0, m_Anim[m_CurAnimID].AnimPos);
		
		numDamage->Exec();
		
		
		//Update(0.0f);
		
		
		//CDebug::DrawString( "m_Position:%f", m_Anim[m_CurAnimID].AnimPos );
		
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
void CGuardian::Rendering()
{
	m_Anim[m_CurAnimID].AnimPos += 0.005;
		
	if( !m_IsDead )
	{	
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
		
		Render( Joker::GetDevice() );
		
		ChangeAnimation(m_Motion);
		
		LPCSTR Name = m_Anim[m_CurAnimID].pAnimSet->GetName();
		
		m_pAnimController->SetTrackPosition(0, m_Anim[m_CurAnimID].AnimPos);
		
		//Update(0.0f);
		
		Update(m_Anim[m_CurAnimID].fTrackSpeed);
		
		//CDebug::DrawString( "m_Position:%f", m_Anim[m_CurAnimID].AnimPos );
		
	}
	
	if(m_IsDead)
	{
		m_IsEnd = true;
	}
	
}



//===============================================
//�\�͂̐ݒ�
//===============================================
//[input]
//	type:����\�̓^�C�v
//[return]
//	�Ȃ�
//===============================================
void CGuardian::SetAbility()
{
	if(m_SpecialType == SP_ATTACK)
	{
		m_Special = CHARGE_ATTACK;
	}
	
	else
	{
		m_Special = COUNTER;
	}
}

//===============================================
//���ߍU��
//===============================================
void CGuardian::SpecialAttack()
{

}


//===============================================
//�J�E���^�[
//===============================================
void CGuardian::SpecialAssist(CCharacter *attacker, CCharacter *target)
{

}

