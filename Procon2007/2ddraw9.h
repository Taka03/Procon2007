//
//			2D�p�N���X�w�b�_�[
//		Created by TAKAHASHI Masafumi
//

#pragma once


#include <d3dx9.h>
#include <d3d9types.h>
#include <windows.h>


//2D���_�t�H�[�}�b�g
typedef struct _D3DTLVERTEX_ {
    D3DXVECTOR3 position; // ���W
	float rhw;
    D3DCOLOR    color, specular;		// ���_�F
    FLOAT       tu, tv;   // UV
}D3DTLVERTEX;
//2D�|���S���p
#define D3DFVF_2DVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)

//2D�|���S��(���_�o�b�t�@����)
class C2DPol9
{
	FLOAT m_fumin, m_fvmin;	//UV�̍ŏ��l
	FLOAT m_fumax, m_fvmax;	//UV�̍ő�l
	D3DTLVERTEX	ver[4];	//���_

public:
	C2DPol9()
	{
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};	//�R���X�g���N�^
	~C2DPol9(){};	//�f�X�g���N�^

	void SetUV(const float umin, const float vmin, const float umax, const float vmax)
	{
		m_fumin = umin;m_fvmin = vmin;
		m_fumax = umax;m_fvmax = vmax;
	};	//UV�l�̍Đݒ�
	void ResetUV(){
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};	//UV�l���f�t�H���g�̒l�ɖ߂�

	void SetPosition(const D3DXVECTOR3* vPos, const float fWidth, const float fHeight, const D3DCOLOR color);	//���_�Z�b�g
	HRESULT Draw(IDirect3DDevice9 * pd3dDevice, LPDIRECT3DTEXTURE9 pTex);	//�`��
};

//2D�|���S��(���_�o�b�t�@����)
class C2DPolVB9
{
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	FLOAT m_fumin, m_fvmin;	//UV�̍ŏ��l
	FLOAT m_fumax, m_fvmax;	//UV�̍ő�l
	
public:
	C2DPolVB9()
	{
		m_pVB = NULL;
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};		//�R���X�g���N�^
	~C2DPolVB9(){};	//�f�X�g���N�^
	
	void SetUV(const float umin, const float vmin, const float umax, const float vmax)
	{
		m_fumin = umin;m_fvmin = vmin;
		m_fumax = umax;m_fvmax = vmax;
	};	//UV�l���Đݒ�
	void ResetUV(){
		m_fumin = m_fvmin = 0.0f;
		m_fumax = m_fvmax = 1.0f;
	};	//UV�l���f�t�H���g�̒l�ɖ߂�

	HRESULT Init(IDirect3DDevice9 * pd3dDevice);			//������(���_�o�b�t�@�̍쐬)
	HRESULT SetPosition(const D3DXVECTOR3* vPos, const float fWidth, const float fHeight, const D3DCOLOR color);	//���_�Z�b�g
	HRESULT Draw(IDirect3DDevice9 * pd3dDevice);	//�`��
};