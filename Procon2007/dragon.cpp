//*==============================================
//dragon.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "dragon.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CDragon::CDragon()
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	m_vPos.Set(0, 50, 0);
	m_vRot.Set(0, 0, 0);
	m_vScale.Set(2, 1, 1); 
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	no:プレイヤー番号
//[return]
//	なし
//===============================================
CDragon::CDragon(ePlayerType no)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(0, 50, 0);
		m_vRot.Set(0, 0, 0);
	
	}
	
	else
	{
		m_vPos.Set(100, 50, 0);
		m_vRot.Set(0, 0, 0);
	}
	


}

//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CDragon::~CDragon()
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
void CDragon::Init()
{
	CXModel::Load(Joker::GetDevice(), "data/act_soldier_basic.x", Joker::GetMaxBlend() );
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CDragon::Exec()
{
	
	Update(pD3DDevice, m_Anim*m_AnimSpeed);
	
	Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	
	Rotation(m_vRot.x, m_vRot.y, m_vRot.z);
	
	Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
	
	SetWorldMatrix();
	
	Render(pD3DDevice);
	
}


