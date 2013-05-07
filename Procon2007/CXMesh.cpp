//*==============================================
//CXMesh.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "CXMesh.h"

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CXMesh::CXMesh()
{
	/*D3DXMESHCONTAINER �R���̕ϐ���������*/
	ZeroMemory( &MeshData, sizeof( D3DXMESHDATA ) );
	Name			= NULL;
	pMaterials		= NULL;
	pEffects		= NULL;
	NumMaterials	= 0;
	pAdjacency		= NULL;
	pSkinInfo		= NULL;

	/*�����o�ϐ��̏�����*/
	m_ppTextures			= NULL;
	m_pOrigMesh				= NULL;
	m_pAttributeTable		= NULL;
	m_NumAttributeGroups	= 0; 
	m_pBoneCombinationBuf	= NULL;
	m_ppBoneMatrixPtrs		= NULL;
	m_pBoneOffsetMatrices	= NULL;
	
	m_pMeshVB		= NULL;
	m_pMeshIndex	= NULL;

}

//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CXMesh::~CXMesh()
{
	SAFE_DELETE( Name );
	F_RELEASE( MeshData.pMesh );
	SAFE_DELETE_ARRAY( pMaterials );
	SAFE_DELETE( pEffects );
	SAFE_DELETE_ARRAY( pAdjacency );
	F_RELEASE( pSkinInfo );

	if( m_ppTextures )
	{
		for( UINT i = 0; i < NumMaterials; i++ )
		{
			F_RELEASE( m_ppTextures[i] );
		}
	}

	SAFE_DELETE_ARRAY( m_ppTextures );
	F_RELEASE( m_pOrigMesh );
	SAFE_DELETE_ARRAY( m_pAttributeTable );
	F_RELEASE( m_pBoneCombinationBuf );
	SAFE_DELETE_ARRAY( m_ppBoneMatrixPtrs );
	SAFE_DELETE_ARRAY( m_pBoneOffsetMatrices );

	F_RELEASE( m_pMeshVB );
	F_RELEASE( m_pMeshIndex );

}

//===============================================
//���O��ݒ�
//===============================================
//[input]
//	inName:�ݒ肷�閼�O
//[return]
//	�Ȃ�
//===============================================
void CXMesh::SetName( LPCTSTR inName )
{
	if( Name != NULL )
	{
		UINT Length;
		Length = lstrlen( inName ) + 1;
		SAFE_DELETE( Name );
		Name = new TCHAR[Length];
		memcpy( Name, inName, Length * sizeof( TCHAR ) );
	}
}

//===============================================
//���_���̃R���o�[�g
//===============================================
//[input]
//	pD3DX9:Direct3D�f�o�C�X
//[return]
//	HREULT�l
//===============================================
bool CXMesh::ConvertVertex(LPDIRECT3DDEVICE9 pD3DX9)
{
    LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	/*Vertex Buffer�ɃR�s�[����*/
	D3DVERTEX* pSrc;
	D3DVERTEX* pDest;
	LPDIRECT3DINDEXBUFFER9 pSrcIndex;
	WORD* pISrc;
	WORD* pIDest;

	/*VertexBuffer���擾*/
	LPDIRECT3DVERTEXBUFFER9 pVB;
	MeshData.pMesh->GetVertexBuffer(&pVB);

	D3DVERTEXBUFFER_DESC	Desc;
	pVB->GetDesc( &Desc );

	DWORD nMeshVertices	= MeshData.pMesh->GetNumVertices();
	DWORD nMeshFaces	= MeshData.pMesh->GetNumFaces();

	/*���_�o�b�t�@���쐬*/
	pD3DX9->CreateVertexBuffer( Desc.Size, 0, MeshData.pMesh->GetFVF(), D3DPOOL_MANAGED, &m_pMeshVB, NULL );

	/*�C���f�b�N�X�o�b�t�@���쐬*/
	pD3DX9->CreateIndexBuffer( nMeshFaces * 3 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pMeshIndex, NULL );

	/*���_�o�b�t�@���R�s�[*/
	pVB->Lock(0,0,(void**)&pSrc,0);
	m_pMeshVB->Lock(0,0,(void**)&pDest,0);
	CopyMemory( pDest, pSrc, Desc.Size );

	pVB->Unlock();
	pVB->Release();
	m_pMeshVB->Unlock();

	/*�C���f�b�N�X�̃R�s�[*/
	MeshData.pMesh->GetIndexBuffer( &pSrcIndex );
	pSrcIndex->Lock( 0, 0, (void**)&pISrc, 0 );
	m_pMeshIndex->Lock( 0, 0, (void**)&pIDest, 0 );
	CopyMemory( pIDest, pISrc, nMeshFaces * 3 * sizeof( WORD ) );

	pSrcIndex->Unlock();
	m_pMeshIndex->Unlock();
	pSrcIndex->Release();

    return true;
}


