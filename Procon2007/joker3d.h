//*==============================================
//joker3d.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "joker.h"
#include "vector3.h"
#include "2ddraw9.h"

//===============================================
//struct
//===============================================
struct XYZBuffer
{
	CVector3 Pos;
};

struct ColBuffer
{
	D3DCOLOR color;
};

//D3DVERTEXELEMENT9 dec1[] =
//{
//	{0, 0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
//	{1, 0, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
//	D3DDECL_END()
//};

//===============================================
//class
//===============================================
class Joker3D :public Joker
{
	protected:
	
		static LPDIRECT3DVERTEXBUFFER9 pD3DVBXYZBuffer;//XYZBuffer�̒��_�o�b�t�@
		static LPDIRECT3DVERTEXBUFFER9 pD3DVBColBuffer;//ColBuffer�̒��_�o�b�t�@
		static LPDIRECT3DINDEXBUFFER9 pD3DIBuffer;//�C���f�b�N�X�E�o�b�t�@
		static LPDIRECT3DVERTEXSHADER9 pVertexShader; //���_�V�F�[�_�[���󂯎��ϐ�
		static LPDIRECT3DPIXELSHADER9 pPixelShader; //�s�N�Z���V�F�[�_�[���󂯎��ϐ�
		static LPDIRECT3DSURFACE9 pDepthBuffer;//�[�x�o�b�t�@		
		static LPD3DXCONSTANTTABLE pVSConstantTable;//���_�V�F�[�_�[�̒萔�e�[�u��
		static LPD3DXCONSTANTTABLE pPSConstantTable;//�s�N�Z���V�F�[�_�[�̒萔�e�[�u��
		
	public:
	
		static LPDIRECT3DSURFACE9 m_pSurf;//�����_�[�^�[�Q�b�g�p�T�[�t�F�C�X
		static LPDIRECT3DSURFACE9 m_pBackBuffer;//�o�b�N�o�b�t�@�擾�p
		static LPDIRECT3DTEXTURE9 m_pRenderTex;//�����_�[�^�[�Q�b�g�p�e�N�X�`��
		
//		static CTexture *m_pTex;
		
		static D3DVIEWPORT9 m_Client;
		
		static C2DPolVB9 *m_pDrawTex;
	
		Joker3D(){};//�R���X�g���N�^
		~Joker3D(){};//�f�X�g���N�^
	
		static bool CreateVertex();//���_�o�b�t�@�̐���
		static bool CreateIndexVertex();//�C���f�b�N�X�E�o�b�t�@�̐���
		static bool CreateProShader();//�v���O���}�u���V�F�[�_�[�̍쐬
		static bool ShaderCompile();//�V�F�[�_�[�̃R���p�C��
		static bool SetRenderState();//�����_�����O��Ԃ̃Z�b�g
		static bool SetViewPort();//�r���[�|�[�g�̐ݒ�
		//static bool SetViewPort(int x, int y, int width, int height, int maxZ);//�r���[�|�[�g�̐ݒ�
		
		static LPDIRECT3DSURFACE9 GetSurface();//�T�[�t�F�C�X�̎擾
		static bool SetRenderTarget();
		
		static bool BeginScene();//�V�[���̊J�n
		static bool EndScene();//�V�[���̏I��
		
		
		
		static void ReleaseDevice();//�f�o�C�X�̉��
		
};