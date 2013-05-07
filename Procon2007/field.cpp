//*==============================================
//field.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "field.h"
#include "joypad.h"
#include "debug.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CField::CField()
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
	
	m_vPos.Set(0, -1, 0);
	m_vRot.Set(0, 0, 0);
	
	m_vScale.Set(1.0f, 1.0f, 1.0f);
	
}

//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CField::~CField()
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
void CField::Init()
{
	//CXModel::Load(Joker::GetDevice(), "height_field.x", Joker::GetMaxBlend() );
	//CXModel::Load(Joker::GetDevice(), "data/ground.x", COLOR_WHITE);
	CXModel::Load(Joker::GetDevice(), "data/field_test3.x", NULL);
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CField::Exec()
{
	//::D3DXVec3TransformCoord(&vAxisX, &vAxisX, &m_matRotate);
	//::D3DXVec3TransformCoord(&vAxisZ, &vAxisZ, &m_matRotate);
	
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	//{
	//	m_vPos -= vAxisX*0.1f;
	//	//m_Anim += 1.0f;
	//}
	//
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	//{
	//	m_vPos += vAxisX*0.1f;
	//	//m_Anim += 1.0f;
	//}	
	//
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_UP) )
	//{
	//	m_vPos -= vAxisZ * 0.1f;
	//	//m_vPos.z -= 0.1f;
	//	//m_Anim += 1.0f;
	//}
	//
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_DOWN) )
	//{
	//	m_vPos += vAxisZ * 0.1f;
	//	//m_vPos.z += 0.1f;
	//	//m_Anim += 1.0f;
	//}
	
	
	//if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_02) )
	//{
	//	m_vRot.x += 0.1f;
	//}
	
//	Update(0.000f);
	
	Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	
	Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
	
	Heading(m_vRot.x);
	
	Pitching(m_vRot.x);
	
	Rolling(m_vRot.x);
	
	Render(Joker::GetDevice());
	
	SetWorldMatrix();
}

//===============================================
//座標の取得
//===============================================
//[input]
//	なし
//[return]
//	座標
//===============================================
CVector3 CField::GetPosition()
{
	return m_vPos;
}




