//*==============================================
//Sysyem.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "System.h"

//===============================================
//コンストラクタ
//===============================================
CSystem::CSystem(void)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;

	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate);
	
	//vAxisX.Set(1.0f, 0.0f, 0.0f);
	//vAxisZ.Set(0.0f, 0.0f, 1.0f);
	
	m_vPos.Set(0, 30, 0);
	m_vRot.Set(0, 0, 0);
	
	m_vScale.Set(3.0f, 3.0f, 3.0f);

}

//===============================================
//デストラクタ
//===============================================
CSystem::~CSystem(void)
{
	Release();
}

//===============================================
//初期化
//===============================================
void CSystem::Init()
{
	CXModel::Load(Joker::GetDevice(), "data/system_graphic.x", NULL);
}	

//===============================================
//処理
//===============================================
void CSystem::Exec()
{
	Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	
	Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
	
	Heading(m_vRot.x);
	
	Pitching(m_vRot.x);
	
	Rolling(m_vRot.x);
	
	Render(Joker::GetDevice());
	
	SetWorldMatrix();

}


