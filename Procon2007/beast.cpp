//*==============================================
//beast.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "beast.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CBeast::CBeast()
{
//	m_NumBoneMatricesMax	= 0;
//	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
	m_Anim = 0;
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
CBeast::CBeast(ePlayerType no)
{
	//m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
	m_Anim = 0;
	m_AnimSpeed = 0.0001f;
	
	if(no == PLAYER_1)
	{
		m_vPos.Set(0, 20, 0);
		m_vRot.Set(0, 0, 0);
	
	}
	
	else
	{
		m_vPos.Set(100, 20, 0);
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
CBeast::~CBeast()
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
void CBeast::Init()
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
void CBeast::Exec()
{
	
	Update(pD3DDevice, m_Anim*m_AnimSpeed);
	
	Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	
	Rotation(m_vRot.x, m_vRot.y, m_vRot.z);
	
	SetWorldMatrix();
	
	Render(pD3DDevice);
	
}


