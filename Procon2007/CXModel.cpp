//*==============================================
//CXModel.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "CXModel.h"
#include "CXFrame.h"
#include "CAllocateHierarchy.h"
#include "debug.h"

//#include <rmxftmpl.h>	//�����̃t�@�C���ɃC���N���[�h������ƃ����N�G���[
						//D3DRM_XTEMPLATES����extern�錾����ĂȂ��͗l

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CXModel::CXModel()
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	
	for( int i = 0;i < MAX_ANIM;i++ )
	{
		ZeroMemory(&m_Anim[i], sizeof(HIANIMATION_DESC) );
	}
	
	//for( int i = 0;i < MAX_ANIM;i++ )
	//{
	//	m_pAnimSet[i] = NULL;
	//}
	
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matTrans );
	D3DXMatrixIdentity( &m_matScale );
	D3DXMatrixIdentity( &m_matRotate );
	
	D3DXQuaternionIdentity( &m_quatModel );
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	m_vRot.Set(0.0f, 0.0f, 0.0f);
	m_vScale.Set(1.0f, 1.0f, 1.0f);	
}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	name:���O
//[return]
//	�Ȃ�
//===============================================
CXModel::CXModel(const char *name)
{
	m_NumBoneMatricesMax	= 0;
	m_pBoneMatrices			= NULL;
	m_pFrameRoot			= NULL;
	m_pAnimController		= NULL;
	D3DXMatrixIdentity( &m_matWorld );
	
	
	Load(Joker::GetDevice(), name, NULL );
	
	

}


//======================================================================
//�@<<<�f�X�g���N�^>>>
//======================================================================
CXModel::~CXModel()
{
	Release();
}

//===============================================
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CXModel::Init()
{
	
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CXModel::Exec()
{
	
	
//	SetTrackEnable(1, false);
	
}

//===============================================
//X�t�@�C���̓ǂݍ���
//===============================================
//[input]
//	pD3DX9:Direct3D�f�o�C�X
//	pFileName:�t�@�C����
//	MaxBlend:�ő�u�����h��
//[return]
//	�u�[���l
//===============================================
bool CXModel::Load( LPDIRECT3DDEVICE9 pD3DX9, const char *pFileName, D3DCOLOR Color )
{
	// �t���[���y�у��b�V�����蓖�Ă��s���N���X CAllocateHierachy �𐶐�
	// �e�t���[���A���b�V�����蓖�Ă̎�����CAllocateHierachy���ŋL�q
    CAllocateHierarchy Alloc( this, pD3DX9, Color);

    LPD3DXANIMATIONCONTROLLER pAnimControllerTmp;
    
	/*Xfile�̓ǂݍ���*/
    if( FAILED( D3DXLoadMeshHierarchyFromX(
					pFileName, D3DXMESH_MANAGED, pD3DX9,
					&Alloc, NULL, &m_pFrameRoot, &pAnimControllerTmp ) ) )
	{
		CHAR str[128];
		
		wsprintf(str, "%s��������܂���", pFileName);
		
		MESSAGE(str);
		
		// ���s
		return false;
	}

	/*�A�j���[�V���������݂��Ȃ�*/
	if( pAnimControllerTmp == NULL )
	{
		return true;
	}

	// ���֐����l���āA�g���b�N�����A�j���[�V�����Z�b�g���ɑ��₷
	int TracksNum   = pAnimControllerTmp->GetMaxNumTracks();
	int AnimSetsNum = pAnimControllerTmp->GetMaxNumAnimationSets();

	if( TracksNum < AnimSetsNum )
	{
		TracksNum = AnimSetsNum;
	}

	// �A�j���[�V�����R���g���[���[�̃N���[���쐬
	if( FAILED( pAnimControllerTmp->CloneAnimationController(
		pAnimControllerTmp->GetMaxNumAnimationOutputs(),
		AnimSetsNum,
		TracksNum,
		pAnimControllerTmp->GetMaxNumEvents(),
		&m_pAnimController ) ) )
	{
		return false;
	}

	F_RELEASE( pAnimControllerTmp );

	if( AnimSetsNum > 1 )
	{
		
		/*�g���b�N�ɑS�ẴA�j���[�V�����Z�b�g��ǂݍ���*/
		for( int i = 0; i < AnimSetsNum; i++ )
		{
			/*�A�j���[�V�����Z�b�g�̎擾*/
			if( FAILED( m_pAnimController->GetAnimationSet( i, &m_Anim[i].pAnimSet) ) )
			{
				return false;
			}
			
			m_Anim[i].AnimID = i;

			///*�A�j���[�V�����Z�b�g�̐ݒ�*/
			if( FAILED( m_pAnimController->SetTrackAnimationSet( i, m_Anim[i].pAnimSet ) ) )
			{
				return false;
			}
			
			D3DXTRACK_DESC TD;
			
			m_pAnimController->GetTrackDesc(i, &TD);
			
			m_pAnimController->SetTrackDesc(i, &TD);
			
			
//		SAFE_DELETE_ARRAY(AnimData[i]);
			
		}
	}

    if( FAILED( SetupBoneMatrixPointers( m_pFrameRoot ) ) )
	{
		MESSAGE("�{�[���̐ڑ��Ɏ��s");
		
		return false;
	}

	return true;
}

//===============================================
//���������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CXModel::Release()
{
	if( m_pFrameRoot )
	{
		CAllocateHierarchy Alloc( this, NULL, NULL );
		D3DXFrameDestroy( m_pFrameRoot, &Alloc );
		m_pFrameRoot = NULL;
	}

	F_RELEASE( m_pAnimController );
	
	//for( int i = 0;i < MAX_ANIM;i++ )
	//{
	//	F_RELEASE( m_pAnimSet[i] );
	//}
	
	
}

//===============================================
//�����_�����O
//===============================================
//[input]
//	pD3DX9:Direct3D�f�o�C�X
//[return]
//	�Ȃ�
//===============================================
void CXModel::Render( LPDIRECT3DDEVICE9 pD3DX9 )
{
	// ���[�g�t���[�����珇�Ԃɕ`�悵�Ă���
	if( m_pFrameRoot != NULL )
	{
		DrawFrame( pD3DX9, m_pFrameRoot );
	}
}

//===============================================
//�X�L�����b�V���̐���
//===============================================
//[input]
//	pD3DX9:Direct3D�f�o�C�X
//	MaxBlend:���_�u�����h�ő吔
//[return]
//	HRESULT�l
//===============================================
HRESULT CXModel::GenerateSkinnedMesh( LPDIRECT3DDEVICE9 pD3DX9, CXMesh *pCXMeshBase, int MaxBlend )
{
	HRESULT hr = S_OK;
	
	D3DCAPS9 d3dCaps;
	
	pD3DX9->GetDeviceCaps(&d3dCaps);

	/*�X�L�����b�V���ł͖����ꍇ�A���R���o�[�g���s��*/
	if( pCXMeshBase->pSkinInfo == NULL )
	{
		pCXMeshBase->ConvertVertex( pD3DX9);
		return hr;
	}

	//----------------------------------------------
	//�X�L�����b�V���p�̏���
	//----------------------------------------------

	F_RELEASE( pCXMeshBase->MeshData.pMesh );
	F_RELEASE( pCXMeshBase->m_pBoneCombinationBuf );

	/*���b�V���̃N���[���쐬*/
	hr = pCXMeshBase->m_pOrigMesh->CloneMeshFVF(
			D3DXMESH_MANAGED, pCXMeshBase->m_pOrigMesh->GetFVF(),
			pD3DX9, &pCXMeshBase->MeshData.pMesh );

	if( FAILED( hr ) )
	{
		return hr;
	}
	
	/*�����e�[�u�����擾*/
	hr = pCXMeshBase->MeshData.pMesh->GetAttributeTable( NULL, &pCXMeshBase->m_NumAttributeGroups );
	
	if( FAILED( hr ) )
	{
		return hr;
	}

	delete[] pCXMeshBase->m_pAttributeTable;

	pCXMeshBase->m_pAttributeTable = new D3DXATTRIBUTERANGE[ pCXMeshBase->m_NumAttributeGroups ];

	if( !pCXMeshBase->m_pAttributeTable )
	{
		hr = E_OUTOFMEMORY;
		return hr;
	}

	hr = pCXMeshBase->MeshData.pMesh->GetAttributeTable( pCXMeshBase->m_pAttributeTable, NULL );

	if( FAILED( hr ) )
	{
		return hr;
	}
	
	//���̃��b�V���ɂ���ă{�[���s��p�̃��������m��
	if(m_NumBoneMatricesMax < pCXMeshBase->pSkinInfo->GetNumBones() )
	{
		m_NumBoneMatricesMax = pCXMeshBase->pSkinInfo->GetNumBones();
		
		delete []m_pBoneMatrices;
		
		m_pBoneMatrices = new D3DXMATRIXA16[m_NumBoneMatricesMax];
		
		if(!m_pBoneMatrices)
		{
			hr = E_OUTOFMEMORY;
			return hr;
		}

	}

	// NONINDEXED

	/*���_�u�����h�p�ɃR���o�[�g*/
	//hr = pCXMeshBase->pSkinInfo->ConvertToIndexedBlendedMesh(
	//	pCXMeshBase->m_pOrigMesh,
	//	D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
	//	pCXMeshBase->pSkinInfo->GetNumBones(),
	//	pCXMeshBase->pAdjacency,
	//	NULL, NULL, NULL,
	//	&pCXMeshBase->m_NumInfl,
	//	&pCXMeshBase->m_NumAttributeGroups,
	//	&pCXMeshBase->m_pBoneCombinationBuf,
	//	&pCXMeshBase->MeshData.pMesh );

	//if( FAILED( hr ) )
	//{
	//	return false;
	//}

	//LPD3DXBONECOMBINATION rgBoneCombinations	= reinterpret_cast< LPD3DXBONECOMBINATION >( pCXMeshBase->m_pBoneCombinationBuf->GetBufferPointer() );

	////----------------------------------------------
	////�K�؂�BoneCombinationSet��T��
	////----------------------------------------------
	//for( pCXMeshBase->m_iAttributeSW = 0; pCXMeshBase->m_iAttributeSW < pCXMeshBase->m_NumAttributeGroups; pCXMeshBase->m_iAttributeSW ++ )
	//{
	//	DWORD cInfl	= 0;

	//	for( DWORD iInfl = 0; iInfl < pCXMeshBase->m_NumInfl; iInfl ++ )
	//	{
	//		if( rgBoneCombinations[ pCXMeshBase->m_iAttributeSW ].BoneId[ iInfl ] != UINT_MAX )
	//		{
	//			cInfl ++;
	//		}
	//	}

	//	if( cInfl > MaxBlend )
	//	{
	//		break;
	//	}
	//}

	//LPD3DXMESH	pMeshTmp;

	///*FVF���Đݒ肵�āA�N���[������*/
	//hr	= pCXMeshBase->MeshData.pMesh->CloneMeshFVF( pCXMeshBase->MeshData.pMesh->GetOptions(),
	//	( pCXMeshBase->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK ) | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4,
	//	pD3DX9, &pMeshTmp );

	//if( FAILED( hr ) )
	//{
	//	return false;
	//}

	//pCXMeshBase->MeshData.pMesh->Release();
	//pCXMeshBase->MeshData.pMesh	= pMeshTmp;
	//pMeshTmp		= NULL;

	//LPD3DVERTEXELEMENT9 pDeclCur;

	//pCXMeshBase->MeshData.pMesh->GetDeclaration( pCXMeshBase->pDecl );

	//pDeclCur	= pCXMeshBase->pDecl;

	//while( pDeclCur->Stream != 0xff )
	//{
	//	if( (pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) && (pDeclCur->UsageIndex == 0 ) )
	//	{
	//		pDeclCur->Type	= D3DDECLTYPE_D3DCOLOR;
	//	}

	//	pDeclCur ++;
	//}

	//pCXMeshBase->MeshData.pMesh->UpdateSemantics( pCXMeshBase->pDecl );

	//pCXMeshBase->ConvertVertex( pD3DX9 );

    return true;
}

//===============================================
//�t���[���̕`��
//===============================================
//[input]
//	pD3DX9:Direct3D�f�o�C�X
//	pD3DXFrame:�t���[��
//[return]
//	�Ȃ�
//===============================================
void CXModel::DrawFrame( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXFRAME pD3DXFrame )
{
	LPD3DXMESHCONTAINER pD3DXMeshContainer;

	pD3DXMeshContainer = pD3DXFrame->pMeshContainer;

	// �t���[���������Ă��郁�b�V�����Ƃɕ`�揈��
	while( pD3DXMeshContainer )
	{
		// �`��
		DrawMeshContainer( pD3DX9, pD3DXMeshContainer, pD3DXFrame );

		// ���̃��b�V�����擾
		pD3DXMeshContainer = pD3DXMeshContainer->pNextMeshContainer;
	}

	// �Z��t���[��������΁A�Z��t���[����`��
	if( pD3DXFrame->pFrameSibling )
	{
		DrawFrame( pD3DX9, pD3DXFrame->pFrameSibling );
	}

	// �q�t���[��������΁A�q�t���[����`��
	if( pD3DXFrame->pFrameFirstChild )
	{
		DrawFrame( pD3DX9, pD3DXFrame->pFrameFirstChild );
	}
}

//======================================================================
//�@<<< ���b�V���R���e�i��`�� >>>
//	Param : [pD3DXMeshContainer] �`�悷�郁�b�V���R���e�i�̏��
//		  : [pD3DXFrame] �`�悷��t���[���̏��
//======================================================================
void CXModel::DrawMeshContainer( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXMESHCONTAINER pD3DXMeshContainer, LPD3DXFRAME pD3DXFrame )
{
	// ��:���͊댯�ȃL���X�g ���S�ɍs���Ƃ���dynamic_cast���g���B
	CXMesh *pMesh = (CXMesh*)pD3DXMeshContainer;

	// �X�L�����b�V��
	if( pMesh->pSkinInfo != NULL )
	{
		DWORD NumBones = pMesh->pSkinInfo->GetNumBones();
		
		unsigned int iAttrib = 0;
		
		
		for(DWORD i = 0;i < NumBones;i++)
		{
			D3DXMatrixMultiply(&m_pBoneMatrices[i], &pMesh->m_pBoneOffsetMatrices[i], pMesh->m_ppBoneMatrixPtrs[i]);
		}
		
		/*���[���h�s����N���A*/
		D3DXMATRIX Identity;
		D3DXMatrixIdentity(&Identity);
		pD3DX9->SetTransform(D3DTS_WORLD, &Identity);
		
		/*���_�o�b�t�@�����b�N*/
		PBYTE pVerticesSrc;
		PBYTE pVerticesDst;
		
		pMesh->m_pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVerticesSrc);
		pMesh->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pVerticesDst);
		
		/*�X�L�����b�V���̍쐬*/
		pMesh->pSkinInfo->UpdateSkinnedMesh(m_pBoneMatrices, NULL, pVerticesSrc, pVerticesDst);
		
		/*���_�o�b�t�@�̃��b�N������*/
		pMesh->m_pOrigMesh->UnlockVertexBuffer();
		
//		LPD3DXBONECOMBINATION	pBoneComb	= reinterpret_cast< LPD3DXBONECOMBINATION >( pMesh->m_pBoneCombinationBuf->GetBufferPointer() );
		
		
		/*�X�L�����b�V���̕`��*/
		for(UINT i = 0;i < pMesh->m_NumAttributeGroups;i++)
		{
			pD3DX9->SetMaterial( &(pMesh->pMaterials[pMesh->m_pAttributeTable[i].AttribId].MatD3D) );
			pD3DX9->SetTexture(0, pMesh->m_ppTextures[pMesh->m_pAttributeTable[i].AttribId]);
			pMesh->MeshData.pMesh->DrawSubset(pMesh->m_pAttributeTable[i].AttribId);
		}
		
		//
	
	//	/*�X�L�����b�V���p�̏���*/
	//	UINT Material = 0;
	//	unsigned int NumBlend	= 0;
	//	unsigned int iAttrib = 0;
	//	DWORD AttribIdPrev	= UNUSED32;
	//
	//	D3DXMATRIXA16	matTmp;
	//	unsigned int	iMatrixIndex;
	//	unsigned int	iPaletteEntry;
	//	PBYTE pVerticesSrc;
	//	PBYTE pVerticesDst;
	//	
	//	D3DXMATRIX Identity;
	//	
	//	LPD3DXBONECOMBINATION	pBoneComb	= reinterpret_cast< LPD3DXBONECOMBINATION >( pMesh->m_pBoneCombinationBuf->GetBufferPointer() );
	//	
	//	//m_NumBoneMatricesMax = pMesh->pSkinInfo->GetNumBones();
	//	//
	//	//for(DWORD i = 0;i < m_NumBoneMatricesMax;i++)
	//	//{
	//	//	D3DXMatrixMultiply(&m_pBoneMatrices[i], &pMesh->m_pBoneOffsetMatrices[i], pMesh->m_ppBoneMatrixPtrs[i]);
	//	//}
	//	//
	//	//D3DXMatrixIdentity(&Identity);
	//	//
	//	//pD3DX9->SetTransform(D3DTS_WORLD, &Identity);
	//	//
	//	//pMesh->m_pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVerticesSrc);
	//	//
	//	//pMesh->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pVerticesDst);
	//	//
	//	//pMesh->pSkinInfo->UpdateSkinnedMesh(m_pBoneMatrices, NULL, pVerticesSrc, pVerticesDst);
	//	//
	//	//pMesh->m_pOrigMesh->UnlockVertexBuffer();
	//	//pMesh->MeshData.pMesh->UnlockVertexBuffer();

	//	/*�f�t�H���g�� vtx �v���Z�X�ŕ`��*/
	//	for( iAttrib=0; iAttrib < pMesh->GetNumAttributeGroups(); iAttrib++ )
	//	{

	//		/*�u�����h�����v�Z*/
	//		for( DWORD i=0; i < pMesh->m_NumInfl; i++ )
	//		{
	//			if( pBoneComb[ iAttrib ].BoneId[ i ] != UINT_MAX )
	//			{
	//				NumBlend = i;
	//			}
	//		}

	//		/*�u�����h����*/
	//		if( m_MaxBlend >= NumBlend+1 )
	//		{
	//			for( DWORD i=0; i < pMesh->m_NumInfl; i++ )
	//			{
	//				iMatrixIndex =	pBoneComb[ iAttrib ].BoneId[ i ];

	//				if( iMatrixIndex != UINT_MAX )
	//				{
	//					// �A�j���[�V�����s����v�Z
	//					D3DXMatrixMultiply( &matTmp, &pMesh->m_pBoneOffsetMatrices[ iMatrixIndex ], pMesh->m_ppBoneMatrixPtrs[ iMatrixIndex ] );
	//					pD3DX9->SetTransform( D3DTS_WORLDMATRIX(i), &matTmp );
	//				}
	//			}

	//			/*�u�����h����ݒ�*/
	//			pD3DX9->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

	//			if( AttribIdPrev != pBoneComb[ iAttrib ].AttribId || AttribIdPrev == UNUSED32 )
	//			{
	//				pD3DX9->SetMaterial( &pMesh->pMaterials[ pBoneComb[ iAttrib ].AttribId ].MatD3D );
	//				pD3DX9->SetTexture( 0, pMesh->m_ppTextures[ pBoneComb[ iAttrib ].AttribId ] );

	//				AttribIdPrev	= pBoneComb[ iAttrib ].AttribId;
	//			}
	//			
	//			//pMesh->MeshData.pMesh->DrawSubset(iAttrib);

	//			/*���_�u�����h���g���ă��b�V����`��*/
	//			pD3DX9->SetStreamSource( 0, pMesh->GetMeshVB(), 0, D3DXGetFVFVertexSize( pMesh->MeshData.pMesh->GetFVF() ) );
	//			pD3DX9->SetIndices( pMesh->GetMeshIndex() );

	//			pD3DX9->SetFVF( pMesh->MeshData.pMesh->GetFVF() );

	//			pD3DX9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,
	//											0,
	//											pBoneComb[ iAttrib ].VertexStart,
	//											pBoneComb[ iAttrib ].VertexCount,
	//											pBoneComb[ iAttrib ].FaceStart * 3,
	//											pBoneComb[ iAttrib ].FaceCount);
	//		}
	//	}

	//	/*�\�t�g�E�F�A�Œ��_�u�����h*/
	//	if( pMesh->m_iAttributeSW < pMesh->m_NumAttributeGroups )
	//	{
	//		AttribIdPrev	= UNUSED32;
	//		pD3DX9->SetSoftwareVertexProcessing( true );

	//		for( iAttrib = pMesh->m_iAttributeSW; iAttrib < pMesh->m_NumAttributeGroups; iAttrib++ )
	//		{
	//			unsigned int NumBlend	= 0;

	//			// �u�����h���v�Z
	//			for( DWORD i=0; i < pMesh->m_NumInfl; i++ )
	//			{
	//				if( pBoneComb[ iAttrib ].BoneId[ i ] != UINT_MAX )
	//				{
	//					NumBlend = i;
	//				}
	//			}

	//			if( m_MaxBlend >= NumBlend+1 )
	//			{
	//				for( DWORD i=0; i < pMesh->m_NumInfl; i++ )
	//				{
	//					iMatrixIndex =	pBoneComb[ iAttrib ].BoneId[ i ];

	//					if( iMatrixIndex != UINT_MAX )
	//					{
	//						/*�A�j���[�V�����s����v�Z*/
	//						D3DXMatrixMultiply( &matTmp, &pMesh->m_pBoneOffsetMatrices[ iMatrixIndex ], pMesh->m_ppBoneMatrixPtrs[ iMatrixIndex ] );
	//						pD3DX9->SetTransform( D3DTS_WORLDMATRIX(i), &matTmp );
	//					}
	//				}

	//				/*�u�����h����ݒ�*/
	//				pD3DX9->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

	//				if( AttribIdPrev != pBoneComb[ iAttrib ].AttribId || AttribIdPrev == UNUSED32 )
	//				{
	//					pD3DX9->SetMaterial( &pMesh->pMaterials[ pBoneComb[ iAttrib ].AttribId ].MatD3D );
	//					pD3DX9->SetTexture( 0, pMesh->m_ppTextures[ pBoneComb[ iAttrib ].AttribId ] );

	//					AttribIdPrev = pBoneComb[ iAttrib ].AttribId;
	//				}

	//				/*���_�u�����h���g���ă��b�V����`��*/
	//				pD3DX9->SetStreamSource( 0, pMesh->GetMeshVB(), 0, D3DXGetFVFVertexSize( pMesh->MeshData.pMesh->GetFVF() ) );
	//				pD3DX9->SetIndices( pMesh->GetMeshIndex() );

	//				pD3DX9->SetFVF( pMesh->MeshData.pMesh->GetFVF() );

	//				pD3DX9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,
	//												0,
	//												pBoneComb[ iAttrib ].VertexStart,
	//												pBoneComb[ iAttrib ].VertexCount,
	//												pBoneComb[ iAttrib ].FaceStart * 3,
	//												pBoneComb[ iAttrib ].FaceCount);
	//			}
	//		}

	//		pD3DX9->SetSoftwareVertexProcessing( false );

	//	}	// �\�t�g�E�F�A�ł̃u�����h�`�揈�������܂�

	//	/*��n��*/
	//	pD3DX9->SetRenderState( D3DRS_VERTEXBLEND, 0 );

	//	
	}
	
	//----------------------------------------------
	//�X�L�����b�V���ł͖������̏���
	//----------------------------------------------
	else
	{
		// �}�e���A���ʂɃ��b�V���̕`��
		for( DWORD i=0; i<pMesh->NumMaterials; i++ )
		{
			// �A�j���[�V�����s������[���h�s��ɐݒ�
			pD3DX9->SetTransform( D3DTS_WORLD, &( (CXFrame *)pD3DXFrame )->m_CombinedTransformationMatrix );

			pD3DX9->SetMaterial( &pMesh->pMaterials[i].MatD3D );
			
			
			
			pD3DX9->SetTexture( 0, pMesh->m_ppTextures[i] );
			
			pMesh->MeshData.pMesh->DrawSubset(i);

			//LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
			//LPDIRECT3DINDEXBUFFER9  pIB = NULL;

			//// ���_�o�b�t�@��ݒ�
			//pMesh->MeshData.pMesh->GetVertexBuffer( &pVB );
			//pD3DX9->SetStreamSource( 0, pVB, 0, D3DXGetFVFVertexSize(pMesh->MeshData.pMesh->GetFVF()) );

			//// �C���f�b�N�X�o�b�t�@���f�o�C�X�ɐݒ�
			//pMesh->MeshData.pMesh->GetIndexBuffer( &pIB );
			//pD3DX9->SetIndices( pIB );

			//pD3DX9->SetFVF( pMesh->MeshData.pMesh->GetFVF() );

			//// �`��
			//pD3DX9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,
			//								0,
			//								pMesh->GetAttributeTable( i )->VertexStart,
			//								pMesh->GetAttributeTable( i )->VertexCount,
			//								pMesh->GetAttributeTable( i )->FaceStart * 3,
			//								pMesh->GetAttributeTable( i )->FaceCount);

			//// ��n��
			//F_RELEASE( pVB );
			//F_RELEASE( pIB );

		}
	}
}

//===============================================
//�{�[���ϊ�
//===============================================
//[input]
//	pD3DXMeshContainer:���b�V���R���e�i
//[return]
//	�u�[���l
//===============================================
bool CXModel::SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pD3DXMeshContainer )
{
	CXMesh *pMesh = (CXMesh *)pD3DXMeshContainer;

	/*�X�L�����b�V���̂Ƃ��̓{�[���s����Z�b�g*/
	if( pMesh->pSkinInfo != NULL )
	{
		DWORD NumBones = pMesh->pSkinInfo->GetNumBones();
		
		pMesh->m_ppBoneMatrixPtrs = (D3DXMATRIX**)MemoryAlloc(sizeof(D3DXMATRIX*) * NumBones);//new D3DXMATRIX*[NumBones];

		if( !pMesh->m_ppBoneMatrixPtrs )
		{
			MESSAGE("BoneMatrix��������Ȃ�");
			
			return false;
		}

		for( DWORD i = 0; i < NumBones; i++ )
		{
		//	BoneName = pMesh->pSkinInfo->GetBoneName(i);
			
			CXFrame *pCD3DXFrame = (CXFrame*)D3DXFrameFind(
				m_pFrameRoot, pMesh->pSkinInfo->GetBoneName( i ) );

			if( !pCD3DXFrame )
			{
				MESSAGE("�t���[���̖��O�擾�Ɏ��s");
				
				return false;
			}

			pMesh->m_ppBoneMatrixPtrs[i] = &pCD3DXFrame->m_CombinedTransformationMatrix;
		}
	}

	return true;
}

//======================================================================
//�@<<<�{�[���̃Z�b�g�A�b�v>>>
//======================================================================
bool CXModel::SetupBoneMatrixPointers( LPD3DXFRAME pD3DXFrame )
{

	if( pD3DXFrame->pMeshContainer )
	{
		if( FAILED( SetupBoneMatrixPointersOnMesh( pD3DXFrame->pMeshContainer ) ) )
		{
			MESSAGE("�{�[�����b�V���̐ڑ��Ɏ��s");
			
			return false;
		}
	}

	if( pD3DXFrame->pFrameSibling )
	{
		if( FAILED( SetupBoneMatrixPointers( pD3DXFrame->pFrameSibling ) ) )
		{ 
			MESSAGE("�{�[�����b�V���̐ڑ��Ɏ��s");
			
			return false;
		}
	}

	if( pD3DXFrame->pFrameFirstChild )
	{
		if( FAILED( SetupBoneMatrixPointers( pD3DXFrame->pFrameFirstChild ) ) )
		{
			MESSAGE("�{�[�����b�V���̐ڑ��Ɏ��s");
			
			return false;
		}
	}

	return true;
}

//======================================================================
//�@<<<�t���[���̍X�V>>>
//	Desc : ���t���[���A���݂̎��Ԃɍ��킹�ăA�j���[�V�������X�V���Ă���
//		 : �A�j���[�V�����s���CXFrame�N���X�� m_CombinedTransformationMatrix �����o�ɕۑ������
//======================================================================
void CXModel::UpdateFrameMatrices( LPD3DXFRAME pD3DXMesh, LPD3DXMATRIX pParentMatrix )
{
	CXFrame *pCD3DXFrame = (CXFrame*)pD3DXMesh;

	// �e�t���[��������
	if( pParentMatrix )
	{
		// �e�̃A�j���[�V�����ƍ���
		D3DXMatrixMultiply( &pCD3DXFrame->m_CombinedTransformationMatrix, &pCD3DXFrame->TransformationMatrix, pParentMatrix );
	}

	else
	{
		pCD3DXFrame->m_CombinedTransformationMatrix = pCD3DXFrame->TransformationMatrix;
	}

	// �Z��t���[�����X�V
	if( pCD3DXFrame->pFrameSibling )
	{
		UpdateFrameMatrices( pCD3DXFrame->pFrameSibling, pParentMatrix );
	}

	// �q�t���[�����X�V
	if( pCD3DXFrame->pFrameFirstChild )
	{
		UpdateFrameMatrices( pCD3DXFrame->pFrameFirstChild, &pCD3DXFrame->m_CombinedTransformationMatrix );
	}
}

//===============================================
//�A�j���[�V�����̐؂�ւ�
//===============================================
//[input]
//	animID:�A�j��ID
//[return]
//	bool�l
//===============================================
bool CXModel::ChangeAnimation(UINT animID)
{
	/*�w��̃A�j���[�V����ID�̑��݂��`�F�b�N*/
	//if( m_Anim.size() <= animID )
	//{
	//	return false;
	//}
	
	/*���݂̃A�j���[�V�����ƈقȂ邩�`�F�b�N*/
	if( m_CurAnimID == animID )
	{
		return false;
	}
	
	/*���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾*/
	if(m_pAnimController != NULL)
	{
		
		D3DXTRACK_DESC TD;
		m_pAnimController->GetTrackDesc( 0, &TD );
		//
		/////*�A�j���[�V�����Z�b�g���g���b�N1�ɐݒ�*/
		m_pAnimController->SetTrackAnimationSet( 1, m_Anim[m_CurAnimID].pAnimSet );
		m_pAnimController->SetTrackDesc( 1, &TD );
		
		//
		/*�A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�*/
		m_pAnimController->SetTrackAnimationSet( 0, m_Anim[animID].pAnimSet );
		
		/*�g���b�N0�̃X�s�[�h�̐ݒ�*/
		m_pAnimController->SetTrackSpeed( 0, m_Anim[animID].fTrackSpeed );
		
		//m_pAnimController->SetTrackSpeed( 0, AdjustSpeed );
		
		
		/*�g���b�N�̍���������*/
		m_pAnimController->SetTrackEnable( 0, true );
		m_pAnimController->SetTrackEnable( 1, true );
		
	}
		
	/*�E�F�C�g���Ԃ�������*/
	m_Anim[animID].fCurWeight = 0.0f;
	
	/*���݂̃A�j���[�V�����ԍ���؂�ւ�*/
	m_PreAnimID = m_CurAnimID;
	m_CurAnimID = animID;
	
	
	
	return true;
	
}

//===============================================
//���[�v���Ԃ̐ݒ�
//===============================================
//[input]
//	animID:�A�j��ID
//	Time:���[�v����
//[return]
//	bool�l
//===============================================
bool CXModel::SetLoopTime(UINT animID, float Time)
{
	//if( m_Anim.size() <= animID )
	//{
	//	return false;
	//}
	
	float DefTime = (float)( m_Anim[animID].pAnimSet->GetPeriod() );
	m_Anim[animID].fLoopTime = Time;
	
	if(m_Anim[animID].fLoopTime != 0)
	{
		m_Anim[animID].fTrackSpeed = DefTime / m_Anim[animID].fLoopTime;
	}
	
	else
	{
		m_Anim[animID].fTrackSpeed = DefTime / 2.0f;
	}
	
	return true;
	
}

//===============================================
//�V�t�g���Ԃ̐ݒ�
//===============================================
//[input]
//	animID:�A�j��ID
//	Time:�V�t�g����
//[return]
//	bool�l
//===============================================
bool CXModel::SetShiftTime(UINT animID, float Time)
{
	/*�w��̃A�j���[�V����ID�̑��݂��m�F*/
	//if( m_Anim.size() <= animID )
	//{
	//	return false;
	//}
	
	/*�V�t�g���Ԃ�o�^*/
	m_Anim[animID].fShiftTime = Time;
	
	return true;
	
}


//======================================================================
//�@<<<���f���̍X�V>>>
//	Prame  : [Time] �ω���������
//======================================================================
bool CXModel::Update( float Time )
{
	/*���������ۂ��𔻒�*/
	m_Anim[m_CurAnimID].fCurWeight += Time;
	
	//m_pAnimController->ResetTime();
	
	if( m_pAnimController != NULL )
	{
		if(m_Anim[m_CurAnimID].fCurWeight <= m_Anim[m_CurAnimID].fShiftTime )
		{
			m_IsChangeAnim = true;
		
			/*������*/
			float Weight = m_Anim[m_CurAnimID].fCurWeight / m_Anim[m_CurAnimID].fShiftTime;
			
			/*�E�F�C�g��o�^*/
			m_pAnimController->SetTrackWeight( 0, Weight );
			m_pAnimController->SetTrackWeight( 1, 1 - Weight );
		}
		
		else
		{
			m_pAnimController->SetTrackWeight( 0, 1.0f );
			m_pAnimController->SetTrackEnable( 1, false );
		}
		
		/*���Ԃ��X�V*/
		m_pAnimController->AdvanceTime( Time, NULL );
	}
	
	return true;
	
}


//===============================================
//���[���h�s��̐ݒ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CXModel::SetWorldMatrix()
{
	//D3DXMatrixIdentity( &m_matWorld );
	
	::D3DXMatrixMultiply(&m_matScale, &m_matScale, &m_matRotate);
	
	::D3DXMatrixMultiply(&m_matWorld, &m_matScale, &m_matTrans);
	
	//m_matWorld *= m_matTrans;
	//
	//m_matWorld *= m_matRotate;
	//
	//m_matWorld *= m_matScale;
	
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	UpdateFrameMatrices( m_pFrameRoot, &m_matWorld );
}

// �ȉ����[�e�B���e�B�֐��Q
D3DXMATRIX& CXModel::GetWorldMatrix()
{
	return m_matWorld;
}

D3DXMATRIX& CXModel::GetLocalMatrix()
{
	return m_matTrans;
}

//===============================================
//���W�̎擾
//===============================================
//[input]
//	Pos:�擾����x�N�g��
//[return]
//	�Ȃ�
//===============================================
CVector3 CXModel::GetPosition()
{
	return m_vPos;
}

//void CXModel::GetPosition(CVector3 *Pos)
//{
//	Pos->x = m_vPos.x;
//	Pos->y = m_vPos.y;
//	Pos->z = m_vPos.z;
//}

//===============================================
//X���W�̎擾
//===============================================
//[input]
//	�Ȃ�
//[return]
//	X���W
//===============================================
float CXModel::GetPosX()
{
	return m_vPos.x;
}

//===============================================
//Y���W�̎擾
//===============================================
//[input]
//	�Ȃ�
//[return]
//	Y���W
//===============================================
float CXModel::GetPosY()
{
	return m_vPos.y;
}

//===============================================
//Z���W�̎擾
//===============================================
//[input]
//	�Ȃ�
//[return]
//	Z���W
//===============================================
float CXModel::GetPosZ()
{
	return m_vPos.z;
}

//===============================================
//�A�j���[�V�����g���b�N�̉�
//===============================================
//[input]
//	Track:�g���b�N�ԍ�
//	Enable:�Đ�����
//[return]
//	�u�[���l
//===============================================
bool CXModel::SetTrackEnable( DWORD Track, BOOL Enable )
{
	if( FAILED( m_pAnimController->SetTrackEnable( Track, Enable ) ) )
	{
		return false;
	}

	return true;
}

//===============================================
//�A�j���[�V�����g���b�N�X�s�[�h�̐ݒ�
//===============================================
//[input]
//	Track:�g���b�N�ԍ�
//	Speed:�A�j���[�V�����X�s�[�h
//[return]
//	�u�[���l
//===============================================
bool CXModel::SetTrackSpeed( DWORD Track, FLOAT Speed )
{
	if( FAILED( m_pAnimController->SetTrackSpeed( Track, Speed ) ) )
	{
		return false;
	}

	return true;
}

//===============================================
//�A�j���[�V�����g���b�N�̏d��
//===============================================
//[input]
//	Track:�g���b�N�ԍ�
//	Weight:
//[return]
//	�u�[���l
//===============================================
bool CXModel::SetTrackWeight( DWORD Track, FLOAT Weight )
{
	if( FAILED( m_pAnimController->SetTrackWeight( Track, Weight ) ) )
	{
		return false;
	}

	return true;
}

//======================================================================
//�@<<<�X�L�����b�V���̃W�F�l���[�g>>>
//======================================================================
//bool CXModel::GenerateSkinnedMesh( LPDIRECT3DDEVICE9 pD3DX9, CXMesh* pMesh, int MaxBlend )
//{
//	if( !pMesh->GenerateSkinnedMesh( pD3DX9, MaxBlend ) )
//	{
//		return false;
//	}
//
//	if( pMesh->pSkinInfo )
//	{
//		//// ���̃��b�V���ɂ���ă{�[���s��p�̃��������m�ۂ�����Ă��Ȃ��ꍇ�͊m�� ////
//	//	if( m_NumBoneMatricesMax < pMesh->pSkinInfo->GetNumBones() )
//		//{
//		//	m_NumBoneMatricesMax = pMesh->pSkinInfo->GetNumBones();
//
//		//	delete []m_pBoneMatrices;
//		//	m_pBoneMatrices	= new D3DXMATRIXA16[ GetNumBoneMatrixesMax() ];
//
//		//	if( !m_pBoneMatrices )
//		//	{
//		//		return false;
//		//	}
//		//}
//	}
//
//	
//
//	return true;
//}

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
void CXModel::Translation(float x, float y, float z)
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
void CXModel::TranslationX(float x)
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
void CXModel::TranslationY(float y)
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
void CXModel::TranslationZ(float z)
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
void CXModel::Rotation(float xangle, float yangle, float zangle)
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
void CXModel::RotationX(float angle)
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
void CXModel::RotationY(float angle)
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
void CXModel::RotationZ(float angle)
{
	Rotation(0, 0, angle);
}

//===============================================
//�g��k��
//===============================================
//[input]
//	Sx:X�����̊g�k
//	Sy:Y�����̊g�k
//	Sz:Z�����̊g�k
//[return]
//	�Ȃ�
//===============================================
void CXModel::Scaling(float Sx, float Sy, float Sz)
{
	::D3DXMatrixScaling(&m_matScale, Sx, Sy, Sz);
}


//===============================================
//�w�b�f�B���O
//===============================================
//[input]
//	angle:�p�x
//[return]
//	�Ȃ�
//===============================================
void CXModel::Heading(float angle)
{
	m_vRot.x = /*m_matTrans._11;*/m_matWorld._11;
	m_vRot.y = /*m_matTrans._12;*/m_matWorld._12;
	m_vRot.z = /*m_matTrans._13;*/m_matWorld._13;
	
	::D3DXQuaternionRotationAxis(&m_quatModel, &m_vRot, angle);
	::D3DXMatrixRotationQuaternion(&m_matRotate, &m_quatModel);
}

//===============================================
//�s�b�`���O
//===============================================
//[input]
//	angle:�p�x
//[return]
//	�Ȃ�
//===============================================
void CXModel::Pitching(float angle)
{
	m_vRot.x = m_matWorld._21;
	m_vRot.y = m_matWorld._22;
	m_vRot.z = m_matWorld._23;
	
	::D3DXQuaternionRotationAxis(&m_quatModel, &m_vRot, angle);
	::D3DXMatrixRotationQuaternion(&m_matRotate, &m_quatModel);

}

//===============================================
//���[�����O
//===============================================
//[input]
//	angle:�p�x
//[return]
//	�Ȃ�
//===============================================
void CXModel::Rolling(float angle)
{
	m_vRot.x = m_matWorld._31;
	m_vRot.y = m_matWorld._32;
	m_vRot.z = m_matWorld._33;
	
	::D3DXQuaternionRotationAxis(&m_quatModel, &m_vRot, angle);
	::D3DXMatrixRotationQuaternion(&m_matRotate, &m_quatModel);

}


//======================================================================
//�@<<<�t���[�����[�g�擾>>>
//======================================================================
LPD3DXFRAME	CXModel::GetFrameRoot()
{
	return m_pFrameRoot;
}

//======================================================================
//�@<<<�A�j���[�V�����R���g���[���[>>>
//======================================================================
LPD3DXANIMATIONCONTROLLER CXModel::GetAniController()
{
	return m_pAnimController;
}