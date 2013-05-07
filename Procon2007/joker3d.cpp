//*==============================================
//joker3d.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joker3d.h"

LPDIRECT3DVERTEXBUFFER9 Joker3D::pD3DVBXYZBuffer;//XYZBuffer�̒��_�o�b�t�@
LPDIRECT3DVERTEXBUFFER9 Joker3D::pD3DVBColBuffer;//ColBuffer�̒��_�o�b�t�@
LPDIRECT3DINDEXBUFFER9 Joker3D::pD3DIBuffer;//�C���f�b�N�X�E�o�b�t�@
LPDIRECT3DVERTEXSHADER9 Joker3D::pVertexShader; //���_�V�F�[�_�[���󂯎��ϐ�
LPDIRECT3DPIXELSHADER9 Joker3D::pPixelShader; //�s�N�Z���V�F�[�_�[���󂯎��ϐ�
LPD3DXCONSTANTTABLE Joker3D::pVSConstantTable;//���_�V�F�[�_�[�̒萔�e�[�u��
LPD3DXCONSTANTTABLE Joker3D::pPSConstantTable;//�s�N�Z���V�F�[�_�[�̒萔�e�[�u��
LPDIRECT3DSURFACE9 Joker3D::pDepthBuffer;//�[�x�o�b�t�@
LPDIRECT3DSURFACE9 Joker3D::m_pSurf = NULL;
LPDIRECT3DSURFACE9 Joker3D::m_pBackBuffer = NULL;
LPDIRECT3DTEXTURE9 Joker3D::m_pRenderTex = NULL;
C2DPolVB9		   *Joker3D::m_pDrawTex;	

D3DVIEWPORT9	Joker3D::m_Client;




//===============================================
//���_�o�b�t�@�̐���
//===============================================
//[input]
//	�Ȃ�
//[return]
//
//===============================================
bool Joker3D::CreateVertex()
{
	HRESULT hr;
	
	hr = pD3DDevice->CreateVertexBuffer(sizeof(XYZBuffer)*8, 0, 0, D3DPOOL_MANAGED, &pD3DVBXYZBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	hr = pD3DDevice->CreateVertexBuffer(sizeof(ColBuffer)*8, 0, 0, D3DPOOL_MANAGED, &pD3DVBColBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	XYZBuffer *pXYZBuffer;
	
	/*�S�̂����b�N����*/
	hr = pD3DVBXYZBuffer->Lock(0, 0, (LPVOID*)&pXYZBuffer, 0);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	pXYZBuffer[0].Pos.Set(1.0f, 1.0f, 1.0f);
	pXYZBuffer[1].Pos.Set(1.0f, 1.0f, 1.0f);
	pXYZBuffer[2].Pos.Set(1.0f, -1.0f, 1.0f);
	pXYZBuffer[3].Pos.Set(1.0f, -1.0f, -1.0f);
	pXYZBuffer[4].Pos.Set(-1.0f, 1.0f, 1.0f);
	pXYZBuffer[5].Pos.Set(-1.0f, 1.0f, -1.0f);
	pXYZBuffer[6].Pos.Set(-1.0f, -1.0f, 1.0f);
	pXYZBuffer[7].Pos.Set(-1.0f, -1.0f, -1.0f);
	
	/*���b�N����*/
	pD3DVBXYZBuffer->Unlock();
	
	ColBuffer *pColBuffer;
	
	hr = pD3DVBColBuffer->Lock(0, 0, (LPVOID*)&pColBuffer, 0);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	//pColBuffer[0] = D3DCOLOR_XRGB(0xff, 0xff, 0xff);
	//pColBuffer[1] = D3DCOLOR_XRGB(0xff, 0xff, 0x00);
	//pColBuffer[2] = D3DCOLOR_XRGB(0xff, 0x00, 0xff);
	//pColBuffer[3] = D3DCOLOR_XRGB(0xff, 0x00, 0x00);
	//pColBuffer[4] = D3DCOLOR_XRGB(0x00, 0xff, 0xff);
	//pColBuffer[5] = D3DCOLOR_XRGB(0x00, 0xff, 0x00); 
	//pColBuffer[6] = D3DCOLOR_XRGB(0x00, 0x00, 0xff);
	//pColBuffer[7] = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
	
	pD3DVBColBuffer->Unlock();
	
	return true;
	
};

//===============================================
//���_�o�b�t�@�̏�������
//===============================================
//[input]
//	�Ȃ�
//[return]
//
//===============================================
bool Joker3D::CreateIndexVertex()
{
	
	HRESULT hr;
	
	/*�C���f�b�N�X�o�b�t�@�̐���*/
	hr = pD3DDevice->CreateIndexBuffer(36 * 2, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pD3DIBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	DWORD *pIndex;
	
	/*���b�N����*/
	hr = pD3DIBuffer->Lock(0, 0, (LPVOID*)&pIndex, 0);
	
	int IndexTbl[36] =
	{
		0, 3, 1, 
		0, 2, 3, 
		0, 5, 4, 
		0, 1, 5,
		4, 2, 0,
		4, 6, 2,
		5, 6, 4,
		5, 7, 6,
		3, 6, 7,
		3, 2, 6,
		1, 7, 5,
		1, 3, 7,
	};
	
	for(int i = 0;i < 35;i++)
	{
		pIndex[i] = IndexTbl[i];
	}
	
	/*���b�N����������*/
	pD3DIBuffer->Unlock();
	
	return true;
	
}

//===============================================
//�V�[���̕`��J�n
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�u�[���l
//===============================================
bool Joker3D::BeginScene()
{
	pD3DDevice->BeginScene();
	
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f, 0);
	
	return true;
}

//===============================================
//�V�[���̕`��I��
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�u�[���l
//===============================================
bool Joker3D::EndScene()
{
	pD3DDevice->EndScene();
	
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
	return true;
}


//===============================================
//�V�F�[�_�[�̃R���p�C��
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
bool Joker3D::ShaderCompile()
{
	LPD3DXBUFFER pCode;
	
	HRESULT hr; 
	
	/*���_�V�F�[�_�̃R���p�C��*/
	hr = D3DXCompileShaderFromFile("Shader.txt", NULL, NULL, "VertexShader_Main", "vs_2_0", 0, &pCode, NULL, &pVSConstantTable);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	/*���_�V�F�[�_�[�̐���*/
	hr = pD3DDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &pVertexShader);
	
	F_RELEASE(pCode);
	
	if(FAILED(hr) )
	{
		return false;//�G���[
	}
	
	/*�s�N�Z���E�V�F�[�_�[�̃R���p�C��*/
	hr = D3DXCompileShaderFromFile("Shader.txt", NULL, NULL, "PixelShader_Main", "ps_2_0", 0, &pCode, NULL, &pPSConstantTable);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	/*�s�N�Z���V�F�[�_�[�̐���*/
	hr = pD3DDevice->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &pPixelShader);
	
	F_RELEASE(pCode);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	return true;
}

//===============================================
//�����_�����O��Ԃ̃Z�b�g
//===============================================
//[input]
//	�Ȃ�
//[return]
//
//===============================================
bool Joker3D::SetRenderState()
{
	HRESULT hr;
	
	hr = pD3DDevice->CreateDepthStencilSurface(m_WinWidth, m_WinHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &pDepthBuffer, NULL);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	/*�[�x�o�b�t�@���f�o�C�X�ɐݒ�*/
	pD3DDevice->SetDepthStencilSurface(pDepthBuffer);
	
	/*Z�o�b�t�@��L���ɂ���*/
	hr = pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	hr = pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	
	/*�w�i���J�����O*/
	hr = pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
	if(FAILED(hr) )
	{
		return false;
	}
	
	return true;
}

//===============================================
//�r���[�|�[�g�̐ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
bool Joker3D::SetViewPort()
{
	HRESULT hr;
	
	pD3DDevice->GetViewport(&m_Client);
	
	D3DVIEWPORT9 vp;
	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= m_WinWidth;
	vp.Height	= m_WinHeight;
	vp.MinZ		= 0.0f;
	vp.MaxZ		= 1.0f;
	hr = pD3DDevice->SetViewport(&vp);
	
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, COLOR_BLUE, 0.0f, 0);
	
	if(FAILED(hr) )
	{
		MESSAGE("�r���[�|�[�g�̐ݒ�Ɏ��s");
		
		return false;
	}
	
	return true;
}

//===============================================
//�T�[�t�F�C�X�̎擾
//===============================================
//[return]
//	�o�b�N�o�b�t�@
//===============================================
LPDIRECT3DSURFACE9 Joker3D::GetSurface()
{
	return m_pSurf;
}

//===============================================
//�����_�����O�^�[�Q�b�g�̐ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	bool�l
//===============================================
bool Joker3D::SetRenderTarget()
{
	pD3DDevice->SetRenderTarget(0, m_pSurf);
	
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f, 0);
	
	pD3DDevice->SetRenderTarget(0, m_pBackBuffer);
	
	pD3DDevice->SetTexture(0, m_pRenderTex);
	
	m_pDrawTex->Draw(pD3DDevice);
	
	pD3DDevice->SetTexture(0, NULL);
	
	return true;
}

//===============================================
//�f�o�C�X�̉��
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void Joker3D::ReleaseDevice()
{
		F_RELEASE(pD3DVBXYZBuffer);//XYZBuffer�̒��_�o�b�t�@
		F_RELEASE(pD3DVBColBuffer);//ColBuffer�̒��_�o�b�t�@
		//F_RELEASE(pD3DIBuffer);//�C���f�b�N�X�E�o�b�t�@
		F_RELEASE(pVertexShader); //���_�V�F�[�_�[���󂯎��ϐ�
		F_RELEASE(pPixelShader); //�s�N�Z���V�F�[�_�[���󂯎��ϐ�
		F_RELEASE(pVSConstantTable);//���_�V�F�[�_�[�̒萔�e�[�u��
		F_RELEASE(pPSConstantTable);//�s�N�Z���V�F�[�_�[�̒萔�e�[�u��
		F_RELEASE(pDepthBuffer);
		F_RELEASE(m_pSurf);

}