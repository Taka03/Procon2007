//*==============================================
//CXMesh.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//struct
//===============================================
typedef struct
{
	float x,y,z;
	float nx,ny,nz;
	float tu0,tv0;
}D3DVERTEX;

//#define D3DFVF_VERTEX 		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//===============================================
//class
//===============================================
class CXMesh : public D3DXMESHCONTAINER
{
	private:
	
		/*���_�o�b�t�@*/
		LPDIRECT3DVERTEXBUFFER9	m_pMeshVB;
		LPDIRECT3DINDEXBUFFER9	m_pMeshIndex;
	
	
	public:
	
		/*�e�N�X�`���z��B�e�N�X�`�������Ȃ�NULL*/
		LPDIRECT3DTEXTURE9*  m_ppTextures; 
	                               
		/*�X�L�����b�V���p*/
		LPD3DXMESH		m_pOrigMesh;
		LPD3DXBUFFER	m_pBoneCombinationBuf;
		D3DXMATRIX**	m_ppBoneMatrixPtrs;
		D3DXMATRIX*		m_pBoneOffsetMatrices;
		
		DWORD			m_NumInfl;
		DWORD			m_iAttributeSW;
		
		DWORD						m_NumAttributeGroups; 
	    LPD3DXATTRIBUTERANGE		m_pAttributeTable;

		/*�e�N�X�`��*/
		LPDIRECT3DTEXTURE9*	m_pTex;

		/*�p�C�v���C���ւ̓��͒��_�f�[�^*/
		D3DVERTEXELEMENT9 pDecl[ MAX_FVF_DECL_SIZE ];

	public:
		
		CXMesh(); //�R���X�g���N�^
		
		virtual ~CXMesh();//�f�X�g���N�^

		void SetName( LPCTSTR Name );//���O��ݒ�
		
		bool ConvertVertex( LPDIRECT3DDEVICE9 pD3DX9);
		

	public:
	
		LPDIRECT3DVERTEXBUFFER9	GetMeshVB() {	return m_pMeshVB;	}
		LPDIRECT3DINDEXBUFFER9	GetMeshIndex() {	return m_pMeshIndex;	}

		DWORD	GetNumAttributeGroups(){	return m_NumAttributeGroups; }
		LPD3DXATTRIBUTERANGE	GetAttributeTable( unsigned int i ){	return &m_pAttributeTable[i];	}
		
		
};