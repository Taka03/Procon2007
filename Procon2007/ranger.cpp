//*==============================================
//ranger.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "ranger.h"
#include "joypad.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CRanger::CRanger()
{
//	m_NumBoneMatricesMax	= 0;
//	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_vPos.Set(0, 20, 0);
	m_vRot.Set(0, 0, 0);

}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	no:プレイヤー番号
//[return]
//	なし
//===============================================
CRanger::CRanger(ePlayerType no)
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
	
	m_name = "レンジャー";
	m_Status = 0;
	m_FirstStatus = 0;
	m_Special = FIRST_ATTACK;
	m_AttackType = ATTACK;
	m_CharaType = RANGER;
	m_pTarget = NULL;
	
	m_IsDead = false;
	m_IsEnd = false;
	m_IsProtected = false;
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
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
	
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	no:プレイヤー番号
//	name:ファイル名
//[return]
//	なし
//===============================================
CRanger::CRanger(ePlayerType no, const char *name)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	
	for( int i = 0;i < MAX_ANIM;i++ )
	{
		ZeroMemory(&m_Anim[i], sizeof(HIANIMATION_DESC) );
	}
	
	
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate );
	
	D3DXQuaternionIdentity(&m_quatModel);
	
	m_name = "レンジャー";
	m_Status = 0;
	m_FirstStatus = 0;
	m_Special = FIRST_ATTACK;
	m_SpecialType = SP_ATTACK;	
	m_AttackType = ATTACK;
	m_CharaType = RANGER;
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
	
	
//	m_Anim = 0;
	m_AnimSpeed = 1;

	m_CurAnimID = 0;
		
	m_PreAnimID = m_CurAnimID;
	
	
//	m_Anim.clear();
	
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 6);
		m_vRot.Set(40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += "1";
	}
	
	else
	{
		m_vPos.Set(2, 0, 6);
		m_vRot.Set(-40, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		
		m_name += "2";
	}
	
	CXModel::Load( Joker::GetDevice(), name, NULL );
	
	numDamage = CTextureFactory::Create(GRP_NUMBER);
	
}


//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CRanger::~CRanger()
{
	Release();
}

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CRanger::Init()
{
	//CXModel::Load(Joker::GetDevice(), "data/act_soldier_basic.x", Joker::GetMaxBlend() );
	//CXModel::Load(Joker::GetDevice(), "data/magister_stand.x", Joker::GetMaxBlend() );
	
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CRanger::Exec()
{
	m_Anim[m_CurAnimID].AnimPos += 0.005;
		
	if( !m_IsDead )
	{	
		
		/*アニメーションの切り替え*/
		int AnimSetNum = m_pAnimController->GetNumAnimationSets();
		
		for(int i = 0;i < AnimSetNum;i++)
		{
			SetShiftTime(i, 1.0f);
			SetLoopTime(i, 10.0f);
		}
		
		//m_Anim++;
		
		//Heading(m_vRot.y);
		
		Pitching(m_vRot.x);
		
		//Rolling(m_vRot.y);
		
		//Rotation(m_vRot.x, m_vRot.y, m_vRot.z);
		
		D3DXVECTOR3 vAxisX(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vAxisZ(0.0f, 0.0f, 1.0f);
		
		Translation(m_vPos.x, m_vPos.y, m_vPos.z);
		
		Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
		
		SetWorldMatrix();
		
		//Update(m_Anim[m_CurAnimID].fTrackSpeed);
		
		Render(Joker::GetDevice());
		
		ChangeAnimation(m_Motion);
		
		//m_pAnimController->SetTrackPosition(0, m_position);
		//
		//m_position += 0.0001f;
		//
		//if(m_position >= 20.01)
		//{
		//	m_position = 20.006;
		//}
		
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
		
	//	CDebug::DrawString( "m_Position:%f", m_Anim[m_CurAnimID].AnimPos );
		
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
//レンダリング
//===============================================
void CRanger::Rendering()
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
	
//	Update(m_AnimSpeed);
}

//===============================================
//能力の設定
//===============================================
//[input]
//	type:特殊能力タイプ
//[return]
//	なし
//===============================================
void CRanger::SetAbility()
{
	if(m_SpecialType == SP_ATTACK)
	{
		m_Special = FIRST_ATTACK;
	}
	
	else
	{
		m_Special = BUILDUP;
	}
}

//===============================================
//先制攻撃
//===============================================
void CRanger::SpecialAttack()
{
	
}

//===============================================
//強化
//===============================================
//[input]
//	attacker:攻撃者
//	target:強化対象
//===============================================
void CRanger::SpecialAssist(CCharacter *attacker, CCharacter *target)
{

}



