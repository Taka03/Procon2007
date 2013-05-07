//*==============================================
//Effect.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "Effect.h"

//===============================================
//�R���X�g���N�^
//===============================================
CEffect::CEffect(void)
{

}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	name:�f�[�^��
//===============================================
CEffect::CEffect(char *name)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
	//m_vPos.Set(0, 0, 0);
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
	
	m_IsVariable = false;
	
	m_vScale.Set(1.0f, 1.0f, 1.0f);
	
	m_AnimSpeed = 0.0001f;	
	
	m_CurAnimID = 0;
	
	Load(Joker::GetDevice(), name, NULL );
	
}

//===============================================
//�f�X�g���N�^
//===============================================
CEffect::~CEffect(void)
{
	Release();
}

//===============================================
//����
//===============================================
void CEffect::Exec()
{
	//SetPosition(
	
	if(m_IsVariable)
	{
		Translation(m_vPos.x, m_vPos.y, m_vPos.z);
		
		Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
		
		//Heading(m_vRot.x);
		//
		Pitching(m_vRot.x);
		//
		//Rolling(m_vRot.x);
		
		Render(Joker::GetDevice());
		
		m_pAnimController->AdvanceTime(m_AnimSpeed, NULL);
		
		SetWorldMatrix();
	}
	
}

//===============================================
//�ʒu�̐ݒ�
//===============================================
//[input]
//	Pos:�ʒu
//===============================================
void CEffect::SetPosition(CVector3 Pos)
{
	m_vPos = Pos;
}

//===============================================
//�ʒu�̉��Z
//===============================================
//[input]
//	Pos:�ʒu
//===============================================
void CEffect::AddPosition(CVector3 Pos)
{
	m_vPos -= Pos;
}


//===============================================
//���݃t���O�̐ݒ�
//===============================================
//[input]
//	flag:���݃t���O
//===============================================
void CEffect::SetVariableFlag(bool flag)
{
	m_IsVariable = flag;
}

//===============================================
//�g�k���̐ݒ�
//===============================================
//[input]
//	Scale:�g�嗦
//===============================================
void CEffect::SetScale(CVector3 Scale)
{
	m_vScale = Scale;
}

//===============================================
//�g�k���̐ݒ�
//===============================================
//[input]
//	Scale:�g�嗦
//===============================================
void CEffect::SetRotate(CVector3 Rot)
{
	m_vRot = Rot;
}

//===============================================
//���݃t���O�̎擾
//===============================================
//[return]
//	���݃t���O
//===============================================
bool CEffect::GetVariableFlag()
{
	return m_IsVariable;
}











