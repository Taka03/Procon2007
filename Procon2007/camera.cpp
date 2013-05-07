//*==============================================
//camera.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "camera.h"
#include "joypad.h"
#include "debug.h"
#include "light.h"

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CCamera::CCamera()
{
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
	m_vScale.Set(1.0f, 1.0f,1.0f);
	
	//m_vBase.Set(0.0f, 2.0f, 0.0f);
	//m_vNormalizeObj.Set(0.0f, -0.5f, 0.9f);
	//m_vObj.Set(-0.2f, 10.0f, -15.0f);
	
	m_vBase.Set(-0.1f, 2.0f, -1.1f);
	m_vNormalizeObj.Set(0.0f, -0.5f, 0.9f);
	m_vObj.Set(-0.6f, 10.0f, -10.0f);
	
	m_IsMove = false;
	
	m_vEye.Set(0.0f, 20.0f, -10.0f);
	m_vAt.Set(0.0f, 0.0f, 0.0f);
	m_vUp.Set(0.0f, 1.0f, 0.0f);
	
	m_fDistance = -10.0f;
	
	::D3DXMatrixIdentity(&m_matWorld);
	::D3DXMatrixIdentity(&m_matView);
	::D3DXMatrixIdentity(&m_matProj);
	
	::D3DXMatrixIdentity(&m_matTrans);
	::D3DXMatrixIdentity(&m_matRotate);
	::D3DXMatrixIdentity(&m_matScale);
}

//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================	
CCamera::~CCamera()
{

}

//===============================================
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::Init()
{
	/*���[���h�s��̐ݒ�*/
	SetWorldMatrix();
			
	/*�ˉe�ϊ��s��̐ݒ�*/
	SetProjMatrix(45, F(Joker::m_WinWidth/Joker::m_WinHeight), 0.01f, 1000.0f);
	
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::Exec()
{
	CVector3 vAxisX(1.0f, 0.0f, 0.0f);
	CVector3 vAxisY(0.0f, 1.0f, 0.0f);
	CVector3 vAxisZ(0.0f, 0.0f, 1.0f);
	
	//::D3DXVec3TransformCoord(&vAxisX, &vAxisX, &m_matView);
	//::D3DXVec3TransformCoord(&vAxisZ, &vAxisZ, &m_matView);
	
	//Update();
	
	if(m_IsMove)
	{
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_UP) )
		{
			//m_vNormalizeObj += vAxisZ * 0.1f;
			m_vBase += vAxisZ * 0.1f;
			//m_vObj += vAxisZ * 0.1f;
			//m_vEye += vAxisZ * 0.1f;
			//m_vAt  += vAxisZ * 0.1f;
		}
		
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_DOWN) )
		{
			//m_vNormalizeObj -= vAxisZ * 0.1f;
			m_vBase -= vAxisZ * 0.1f;
			//m_vObj -= vAxisZ * 0.1f;
			//m_vEye -= vAxisZ * 0.1f;
			//m_vAt  -= vAxisZ * 0.1f;
		}
		
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_LEFT) )
		{
			m_vBase -= vAxisX * 0.1f;
			//m_vAt  -= vAxisX * 0.1f;
		}
		
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
		{
			m_vBase += vAxisX * 0.1f;
			//m_vAt  += vAxisX * 0.1f;
		}
		//
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_03) )
		{
			m_vBase += vAxisY * 0.1f;
	//		m_vEye += vAxisY * 0.1f;
	//		m_vAt  += vAxisY * 0.1f;
		}
		
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_04) )
		{
			m_vBase -= vAxisY * 0.1f;
	//		m_vEye -= vAxisY * 0.1f;
	//		m_vAt  -= vAxisY * 0.1f;
		}
	}
	
	Update();
	
	

	/*�r���[�ϊ��s��̐ݒ�*/	
	//SetViewMatrix(&m_vEye, &m_vAt, &m_vUp);
	
	//CVector3 vec(m_vObj.x, m_vObj.y, -10.0f);
	
	CDebug::DrawString("m_vBase:x:%f:y:%f:z:%f", m_vBase.x, m_vBase.y, m_vBase.z);
	CDebug::DrawString("m_vNor:x:%f:y:%f:z:%f", m_vNormalizeObj.x, m_vNormalizeObj.y, m_vNormalizeObj.z);
	CDebug::DrawString("m_vObj:x:%f:y:%f:z:%f", m_vObj.x, m_vObj.y, m_vObj.z);
	
	CLight::SetPosition(&m_vNormalizeObj);
	
	CLight::SetLightParam();
	
	CLight::SetLight();
	
	
	
	//SetWholeMatrix();
}
	
//===============================================
//���[���h�ϊ��s��ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::SetWorldMatrix()
{
	float ry = 0.0f;
	
	D3DXMatrixRotationY(&m_matWorld, ry);
}

//===============================================
//�r���[�ϊ��s��ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::SetViewMatrix(CVector3 *pEye, CVector3 *pAt, CVector3 *pUp)
{
	/*�r���[�ϊ��s������*/
	D3DXMatrixLookAtLH(&m_matView, pEye, pAt, pUp);
	
	/*�r���[�s��ݒ�*/
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	
}

//===============================================
//�ˉe�ϊ��s��ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::SetProjMatrix(float fov, float Aspect, float znear, float zfar)
{
	/*�ˉe�ϊ��s��̐ݒ�*/
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(fov), F(Aspect), znear, zfar);//45*PI/180.0f, F(m_WinWidth / m_WinHeight), 0.01f, 1000.0f);
	
	/*�v���W�F�N�V�����s��ݒ�*/
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	
}

//===============================================
//�S�̂̕ϊ��s��ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::SetWholeMatrix()
{
	m_matWorld *= m_matTrans; 
	
	m_matWorld *= m_matRotate;
	
	m_matWorld *= m_matScale;
	
	/*���[���h�s��ݒ�*/
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	
}

//===============================================
//�ړ�
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//	z:Z���W
//[return]
//	�Ȃ�
//===============================================
void CCamera::Translation(float x, float y, float z)
{
	D3DXMatrixTranslation(&m_matTrans, x, y, z);
	
}

//===============================================
//X�����ړ�
//===============================================
//[input]
//	x:X���W
//[return]
//	�Ȃ�
//===============================================
void CCamera::TranslationX(float x)
{
	Translation(x, 0, 0);
}

//===============================================
//Y�����ړ�
//===============================================
//[input]
//	x:X���W
//[return]
//	�Ȃ�
//===============================================
void CCamera::TranslationY(float y)
{
	Translation(0, y, 0);
}

//===============================================
//Z�����ړ�
//===============================================
//[input]
//	x:X���W
//[return]
//	�Ȃ�
//===============================================
void CCamera::TranslationZ(float z)
{
	Translation(0, 0, z);
}

//===============================================
//��]
//===============================================
//[input]
//	xangle:X�p�x
//	yangle:Y�p�x
//	zangle:Z�p�x
//[return]
//	�Ȃ�
//===============================================
void CCamera::Rotation(float xangle, float yangle, float zangle)
{
	D3DXMatrixRotationYawPitchRoll(&m_matRotate, xangle, yangle, zangle);
}

//===============================================
//X������]
//===============================================
//[input]
//	angle:�p�x
//[return]
//	�Ȃ�
//===============================================
void CCamera::RotationX(float angle)
{
	Rotation(angle, 0, 0);
}

//===============================================
//Y������]
//===============================================
//[input]
//	angle:�p�x
//[return]
//	�Ȃ�
//===============================================
void CCamera::RotationY(float angle)
{
	Rotation(0, angle, 0);
}

//===============================================
//Z������]
//===============================================
//[input]
//	angle:�p�x
//[return]
//	�Ȃ�
//===============================================
void CCamera::RotationZ(float angle)
{
	Rotation(0, 0, angle);
}

//===============================================
//�g��k��
//===============================================
//[input]
//	Sx:X�����g�k
//	Sy:Y�����g�k
//	Sz:Z�����g�k
//[return]
//	�Ȃ�
//===============================================
void CCamera::Scaling(float Sx, float Sy, float Sz)
{
	::D3DXMatrixScaling(&m_matScale, Sx, Sy, Sz);
}

//===============================================
//�X�V
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::Update()
{
	if(m_IsMove)
	{
		if(CJoyPad::GetState(1, PAD_STATE_HOLD, PAD_DIR_UP) )
		{
			m_fDistance += 0.1f;
		}
		
		if(CJoyPad::GetState(1, PAD_STATE_HOLD, PAD_DIR_DOWN) )
		{
			m_fDistance -= 0.1f;
		}
		
		if(CJoyPad::GetState(1, PAD_STATE_HOLD, PAD_DIR_LEFT) )
		{
			Pitching(0.01f);
		}
		
		if(CJoyPad::GetState(1, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
		{
			Pitching(-0.01f);
		}
		
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_01) )
		{
			Heading(0.01f);
		}
		
		if(CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_02) )
		{
			Heading(-0.01f);
		}
	}
		
		
	UpdateView();
	
	SetDistance(m_fDistance);
	
}

//===============================================
//�o�b�t�@�̓o�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::RegistBuffer()
{
	CreateVertex();
	CreateIndexVertex();
	ShaderCompile();
	
	pD3DDevice->SetStreamSource(0, pD3DVBXYZBuffer, 0, sizeof(XYZBuffer) );
	pD3DDevice->SetStreamSource(1, pD3DVBColBuffer, 0, sizeof(ColBuffer) );
	
	pD3DDevice->SetIndices(pD3DIBuffer);
	
}

//===============================================
//�v���O���}�u���E�V�F�[�_�[�̓o�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CCamera::RegistProShader()
{
	pD3DDevice->SetVertexShader(pVertexShader);
	pD3DDevice->SetPixelShader(pPixelShader);
}

//===============================================
//�J�����ƑΏە��̋�����ݒ�
//===============================================
//[input]
//	fDist:����
//[return]
//	HRESULT�l
//===============================================
HRESULT CCamera::SetDistance(float fDist)
{
	m_fDistance = fDist;
	
	return UpdateView();
}

//===============================================
//�Ώە��̈ʒu�̐ݒ�
//===============================================
//[input]
//	x:X���W
//	y:Y���W
//	z:Z���W
//[return]
//	HRESULT�l
//===============================================
HRESULT CCamera::SetPosition(float x, float y, float z)
{
	m_vBase.Set(x, y, z);
	
	return UpdateView();
}

//===============================================
//�w�b�f�B���O
//===============================================
//[input]
//	angle:�p�x
//[return]
//	HRESULT�l
//===============================================
HRESULT CCamera::Heading(float angle)
{
	D3DXQUATERNION tQua;
	D3DXMATRIX tmp;
	
	::D3DXQuaternionRotationAxis(&tQua, &D3DXVECTOR3(-m_vNormalizeObj.z, 0, m_vNormalizeObj.x), angle);
	::D3DXMatrixRotationQuaternion(&tmp, &tQua);
	::D3DXVec3TransformCoord(&m_vNormalizeObj, &m_vNormalizeObj, &tmp);
	
	return UpdateView();
}

//===============================================
//�s�b�`���O
//===============================================
//[input]
//	angle:�p�x
//[return]
//	HRESULT�l
//===============================================
HRESULT CCamera::Pitching(float angle)
{
	D3DXMATRIX tmp;
	::D3DXMatrixRotationY(&tmp, angle);
	::D3DXVec3TransformCoord(&m_vNormalizeObj, &m_vNormalizeObj, &tmp);
	
	return UpdateView();
}


//===============================================
//�ڂ̈ʒu���W�̐ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	HRESULT�l
//===============================================
HRESULT CCamera::UpdateView()
{
	::D3DXVec3Scale(&m_vObj, &m_vNormalizeObj, m_fDistance);
	::D3DXVec3Add(&m_vObj, &m_vObj, &m_vBase);
	
	return SetView(m_vObj, m_vBase, m_vUp);
	
	//return SetView(m_vBase,m_vObj,m_vUp);
	
}

//===============================================
//�r���[�s��̐ݒ�
//===============================================
//[input]
//	vEye:��ʒu
//	vAt:����ʒu
//	vUp:�ォ��̎��_
//[return]
//	HRESULT�l
//===============================================
HRESULT CCamera::SetView(CVector3 &vEye, CVector3 &vAt, CVector3 &vUp)
{
	m_vEye = vEye;
	m_vAt = vAt;
	m_vUp = vUp;
	
	D3DXMatrixLookAtLH(&m_matView, &vEye, &vAt, &vUp);
	
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	
	return S_OK;
}



