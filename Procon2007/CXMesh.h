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
	
		/*頂点バッファ*/
		LPDIRECT3DVERTEXBUFFER9	m_pMeshVB;
		LPDIRECT3DINDEXBUFFER9	m_pMeshIndex;
	
	
	public:
	
		/*テクスチャ配列。テクスチャ無しならNULL*/
		LPDIRECT3DTEXTURE9*  m_ppTextures; 
	                               
		/*スキンメッシュ用*/
		LPD3DXMESH		m_pOrigMesh;
		LPD3DXBUFFER	m_pBoneCombinationBuf;
		D3DXMATRIX**	m_ppBoneMatrixPtrs;
		D3DXMATRIX*		m_pBoneOffsetMatrices;
		
		DWORD			m_NumInfl;
		DWORD			m_iAttributeSW;
		
		DWORD						m_NumAttributeGroups; 
	    LPD3DXATTRIBUTERANGE		m_pAttributeTable;

		/*テクスチャ*/
		LPDIRECT3DTEXTURE9*	m_pTex;

		/*パイプラインへの入力頂点データ*/
		D3DVERTEXELEMENT9 pDecl[ MAX_FVF_DECL_SIZE ];

	public:
		
		CXMesh(); //コンストラクタ
		
		virtual ~CXMesh();//デストラクタ

		void SetName( LPCTSTR Name );//名前を設定
		
		bool ConvertVertex( LPDIRECT3DDEVICE9 pD3DX9);
		

	public:
	
		LPDIRECT3DVERTEXBUFFER9	GetMeshVB() {	return m_pMeshVB;	}
		LPDIRECT3DINDEXBUFFER9	GetMeshIndex() {	return m_pMeshIndex;	}

		DWORD	GetNumAttributeGroups(){	return m_NumAttributeGroups; }
		LPD3DXATTRIBUTERANGE	GetAttributeTable( unsigned int i ){	return &m_pAttributeTable[i];	}
		
		
};