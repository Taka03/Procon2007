//*==============================================
//contractor.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "contractor.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CContractor::CContractor()
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	
	m_vPos.Set(0, 30, 0);
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
CContractor::CContractor(ePlayerType no)
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
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_name = "契約者";
	m_Status = 0;
	m_FirstStatus = 0;
	m_CharaType = CONTRACTOR;
	m_Special = BURST;
	m_AttackType = ATTACK;
	
	//m_Target = FENCER;
	m_pTarget = NULL;
	
	m_IsDead = false;
	m_IsEnd = false;
	
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 1);
		m_vRot.Set(0, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		m_name += "1";
	}
	
	else
	{
		m_vPos.Set(2, 0, 1);
		m_vRot.Set(0, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		m_name += "2";
	}
	
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	no:プレイヤー番号
//	name:名前
//[return]
//	なし
//===============================================
CContractor::CContractor(ePlayerType no, const char *name)
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
	
//	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_name = "契約者";
	m_Status = 0;
	m_FirstStatus = 0;
	m_CharaType = CONTRACTOR;
	m_SpecialType = SP_ATTACK;
	m_Special = BURST;
	m_AttackType = ATTACK;
	m_Motion = MOT_STAND;
	
	m_plType = no;

	//m_Target = FENCER;
	m_pTarget = NULL;
	
	
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
	
	
//	m_Anim.clear();

	m_CurAnimID = 0;
		
	m_PreAnimID = m_CurAnimID;
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(-2, 0, 4);
		m_vRot.Set(0, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		m_name += "1";
	}
	
	else
	{
		m_vPos.Set(2, 0, 4);
		m_vRot.Set(0, 0, 0);
		m_vScale.Set(1.0f, 1.0f, 1.0f);
		m_name += "2";
	}
	
	CXModel::Load( Joker::GetDevice(), name, NULL );
	
	numDamage = CTextureFactory::Create(GRP_NUMBER);
	
	Aura = new CEffect("data/aura.x");
	
}



//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CContractor::~CContractor()
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
void CContractor::Init()
{
	//CXModel::Load(Joker::GetDevice(), "data/act_soldier_basic.x", Joker::GetMaxBlend() );
	//CXModel::Load(Joker::GetDevice(), "data/magister_.x", COLOR_WHITE);
	
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CContractor::Exec()
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
		
		Aura->SetPosition(m_vPos);
		
		//if(Aura->GetVariableFlag() )
		//{
		//	Aura->Exec();
		//}
		
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
//レンダリング
//===============================================
void CContractor::Rendering()
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
	
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 8);
	//
	//m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	Render( Joker::GetDevice() );
	
//	Update(0, m_Anim*m_AnimSpeed);
}


//===============================================
//能力の設定
//===============================================
//[input]
//	type:特殊能力タイプ
//[return]
//	なし
//===============================================
void CContractor::SetAbility()
{
	if(m_SpecialType == SP_ATTACK)
	{
		m_Special = BURST;
	}
	
	else
	{
		m_Special = GUARD;
	}
}

//===============================================
//自爆処理
//===============================================
//[input]
//	target:ターゲット
//===============================================
void CContractor::Burst(CCharacter *target)
{
	
}

//===============================================
//防御処理
//===============================================
void CContractor::Guard()
{

}



