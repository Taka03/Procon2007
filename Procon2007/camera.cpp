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
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
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
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================	
CCamera::~CCamera()
{

}

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCamera::Init()
{
	/*ワールド行列の設定*/
	SetWorldMatrix();
			
	/*射影変換行列の設定*/
	SetProjMatrix(45, F(Joker::m_WinWidth/Joker::m_WinHeight), 0.01f, 1000.0f);
	
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
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
	
	

	/*ビュー変換行列の設定*/	
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
//ワールド変換行列設定
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCamera::SetWorldMatrix()
{
	float ry = 0.0f;
	
	D3DXMatrixRotationY(&m_matWorld, ry);
}

//===============================================
//ビュー変換行列設定
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCamera::SetViewMatrix(CVector3 *pEye, CVector3 *pAt, CVector3 *pUp)
{
	/*ビュー変換行列を作る*/
	D3DXMatrixLookAtLH(&m_matView, pEye, pAt, pUp);
	
	/*ビュー行列設定*/
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	
}

//===============================================
//射影変換行列設定
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCamera::SetProjMatrix(float fov, float Aspect, float znear, float zfar)
{
	/*射影変換行列の設定*/
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(fov), F(Aspect), znear, zfar);//45*PI/180.0f, F(m_WinWidth / m_WinHeight), 0.01f, 1000.0f);
	
	/*プロジェクション行列設定*/
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	
}

//===============================================
//全体の変換行列設定
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCamera::SetWholeMatrix()
{
	m_matWorld *= m_matTrans; 
	
	m_matWorld *= m_matRotate;
	
	m_matWorld *= m_matScale;
	
	/*ワールド行列設定*/
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	
}

//===============================================
//移動
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//	z:Z座標
//[return]
//	なし
//===============================================
void CCamera::Translation(float x, float y, float z)
{
	D3DXMatrixTranslation(&m_matTrans, x, y, z);
	
}

//===============================================
//X方向移動
//===============================================
//[input]
//	x:X座標
//[return]
//	なし
//===============================================
void CCamera::TranslationX(float x)
{
	Translation(x, 0, 0);
}

//===============================================
//Y方向移動
//===============================================
//[input]
//	x:X座標
//[return]
//	なし
//===============================================
void CCamera::TranslationY(float y)
{
	Translation(0, y, 0);
}

//===============================================
//Z方向移動
//===============================================
//[input]
//	x:X座標
//[return]
//	なし
//===============================================
void CCamera::TranslationZ(float z)
{
	Translation(0, 0, z);
}

//===============================================
//回転
//===============================================
//[input]
//	xangle:X角度
//	yangle:Y角度
//	zangle:Z角度
//[return]
//	なし
//===============================================
void CCamera::Rotation(float xangle, float yangle, float zangle)
{
	D3DXMatrixRotationYawPitchRoll(&m_matRotate, xangle, yangle, zangle);
}

//===============================================
//X方向回転
//===============================================
//[input]
//	angle:角度
//[return]
//	なし
//===============================================
void CCamera::RotationX(float angle)
{
	Rotation(angle, 0, 0);
}

//===============================================
//Y方向回転
//===============================================
//[input]
//	angle:角度
//[return]
//	なし
//===============================================
void CCamera::RotationY(float angle)
{
	Rotation(0, angle, 0);
}

//===============================================
//Z方向回転
//===============================================
//[input]
//	angle:角度
//[return]
//	なし
//===============================================
void CCamera::RotationZ(float angle)
{
	Rotation(0, 0, angle);
}

//===============================================
//拡大縮小
//===============================================
//[input]
//	Sx:X方向拡縮
//	Sy:Y方向拡縮
//	Sz:Z方向拡縮
//[return]
//	なし
//===============================================
void CCamera::Scaling(float Sx, float Sy, float Sz)
{
	::D3DXMatrixScaling(&m_matScale, Sx, Sy, Sz);
}

//===============================================
//更新
//===============================================
//[input]
//	なし
//[return]
//	なし
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
//バッファの登録
//===============================================
//[input]
//	なし
//[return]
//	なし
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
//プログラマブル・シェーダーの登録
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCamera::RegistProShader()
{
	pD3DDevice->SetVertexShader(pVertexShader);
	pD3DDevice->SetPixelShader(pPixelShader);
}

//===============================================
//カメラと対象物の距離を設定
//===============================================
//[input]
//	fDist:距離
//[return]
//	HRESULT値
//===============================================
HRESULT CCamera::SetDistance(float fDist)
{
	m_fDistance = fDist;
	
	return UpdateView();
}

//===============================================
//対象物の位置の設定
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//	z:Z座標
//[return]
//	HRESULT値
//===============================================
HRESULT CCamera::SetPosition(float x, float y, float z)
{
	m_vBase.Set(x, y, z);
	
	return UpdateView();
}

//===============================================
//ヘッディング
//===============================================
//[input]
//	angle:角度
//[return]
//	HRESULT値
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
//ピッチング
//===============================================
//[input]
//	angle:角度
//[return]
//	HRESULT値
//===============================================
HRESULT CCamera::Pitching(float angle)
{
	D3DXMATRIX tmp;
	::D3DXMatrixRotationY(&tmp, angle);
	::D3DXVec3TransformCoord(&m_vNormalizeObj, &m_vNormalizeObj, &tmp);
	
	return UpdateView();
}


//===============================================
//目の位置座標の設定
//===============================================
//[input]
//	なし
//[return]
//	HRESULT値
//===============================================
HRESULT CCamera::UpdateView()
{
	::D3DXVec3Scale(&m_vObj, &m_vNormalizeObj, m_fDistance);
	::D3DXVec3Add(&m_vObj, &m_vObj, &m_vBase);
	
	return SetView(m_vObj, m_vBase, m_vUp);
	
	//return SetView(m_vBase,m_vObj,m_vUp);
	
}

//===============================================
//ビュー行列の設定
//===============================================
//[input]
//	vEye:基準位置
//	vAt:見る位置
//	vUp:上からの視点
//[return]
//	HRESULT値
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



