//*==============================================
//CAllocateHierarchy.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "CAllocateHierarchy.h"
#include "CXModel.h"
#include "CXMesh.h"
#include "CXFrame.h"

//======================================================================
//�@<<<�R���X�g���N�^>>>
//======================================================================
CAllocateHierarchy::CAllocateHierarchy( CXModel *pModel, LPDIRECT3DDEVICE9 pD3DX9, D3DCOLOR Color)
{
	// �����o��������
	this->m_pModel		= pModel;
	this->m_pD3DX9		= pD3DX9;
	this->m_KeyColor	= Color;
}

//======================================================================
//�@<<<�t���[�� �I�u�W�F�N�g�̊��蓖�ėv���̎���>>>
//	Param : [Name] �쐬����t���[���̖��O
//		  : [ppNewFrame] �쐬���ꂽ�t���[�� �I�u�W�F�N�g��Ԃ�
//======================================================================
HRESULT CAllocateHierarchy::CreateFrame( LPCTSTR Name, LPD3DXFRAME *ppNewFrame )
{
	*ppNewFrame = NULL;

	try
	{
		CXFrame *pFrame = new CXFrame;

		// �t���[������ݒ�
		pFrame->SetName( Name );

		// �t���[���I�u�W�F�N�g�̊��蓖�āB
		// CXFrame�N���X�� D3DXFRAME ���p�����Ă���
		*ppNewFrame = ( LPD3DXFRAME )( pFrame );
	}
	catch ( std::bad_alloc& )
	{
		// ������������Ȃ�
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

//======================================================================
//�@<<<���b�V�� �R���e�i �I�u�W�F�N�g�̊��蓖�ėv���̎���>>>
//	Name			 : [in] ���b�V���̖��O
//	pMeshData		 : [in] ���b�V���f�[�^�\���̂ւ̃|�C���^
//	pMaterials		 : [in] ���b�V���Ɏg���}�e���A���̔z��
//	pEffectInstances : [in] ���b�V���Ɏg���G�t�F�N�g�C���X�^���X�̔z��
//	NumMaterials	 : [in] �}�e���A���z����̃}�e���A���̐�
//	pAdjacency		 : [in] ���b�V���̗אڐ��z��
//	pSkinInfo		 : [in] �X�L���f�[�^�����������ꍇ�̃X�L�����b�V���I�u�W�F�N�g�ւ̃|�C���^
//	ppNewMeshContainer : [out, retval] �쐬���ꂽ���b�V���R���e�i��Ԃ�
//======================================================================
HRESULT CAllocateHierarchy::CreateMeshContainer( LPCSTR Name, 
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials, 
        CONST D3DXEFFECTINSTANCE *pEffectInstances, 
        DWORD NumMaterials, 
        CONST DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer) 
{
	HRESULT hr = S_OK;

	*ppNewMeshContainer = NULL;

	// patch meshes ���������͂ł��Ȃ�
	if( pMeshData->Type != D3DXMESHTYPE_MESH )
	{
		return E_FAIL;
	}

	LPD3DXMESH pMesh = pMeshData->pMesh;

	// FVF �ŋL�q���ꂽ���b�V���ȊO�͓ǂ߂�
	if( pMesh->GetFVF() == 0 )
	{
		return E_FAIL;
	}

	UINT NumFaces = pMesh->GetNumFaces();

	// ���b�V���쐬
	CXMesh *pCXMesh	= NULL;
	
	try
	{
		pCXMesh = new CXMesh;
	}
	
	catch ( std::bad_alloc& )
	{
		// ������������Ȃ�
		return E_OUTOFMEMORY;
	}

	// ���O�ݒ�
	pCXMesh->SetName( Name );

	// ���b�V���^�C�v�ݒ�
	pCXMesh->MeshData.Type = D3DXMESHTYPE_MESH;

	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	// �f�o�C�X���擾
	if( FAILED( pMesh->GetDevice( &pD3DDevice ) ) )
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	// X�t�@�C���ɖ@��������������v�Z�ŋ��߂�
	if( !( pMesh->GetFVF() & D3DFVF_NORMAL ) )
	{
		////FVF�ɖ@����ǉ������V�������b�V���ɂ���////
        hr = pMesh->CloneMeshFVF( pMesh->GetOptions(), 
                                  pMesh->GetFVF() | D3DFVF_NORMAL, 
                                  pD3DDevice, &pCXMesh->MeshData.pMesh );

        if( FAILED( hr ) )
		{
			goto e_Exit;
		}

		// �����œn���ꂽ���b�V���ւ̃|�C���^�ɐV�������b�V���ւ̃|�C���^���Z�b�g
		// pMesh�ւ̎Q�Ƃ͂��̎��_�ő��݂��Ȃ��̂ŁA�����ł�release�������Ȃ�
		pMesh = pCXMesh->MeshData.pMesh;

		D3DXComputeNormals( pMesh, NULL );
	}
	
	// �@����������
	else
	{
		// ���t�@�����X�𑝂₷����
		pCXMesh->MeshData.pMesh = pMesh;
		pMesh->AddRef();
	}

	// �}�e���A���p�̃��������m��
	pCXMesh->NumMaterials = max( 1, NumMaterials );

	try
	{
		pCXMesh->pMaterials		= new D3DXMATERIAL[pCXMesh->NumMaterials];
		pCXMesh->m_ppTextures	= new LPDIRECT3DTEXTURE9[pCXMesh->NumMaterials];
		pCXMesh->pAdjacency		= new DWORD[NumFaces * 3];
	}
	
	catch ( std::bad_alloc& )
	{
		// ������������Ȃ�
		goto e_Exit;
	}

	memcpy( pCXMesh->pAdjacency, pAdjacency, sizeof( DWORD ) * NumFaces * 3 );
	memset( pCXMesh->m_ppTextures, 0, sizeof( LPDIRECT3DTEXTURE9 ) * pCXMesh->NumMaterials );

	// �}�e���A���̃R�s�[
	if( NumMaterials > 0 )
	{
		memcpy( pCXMesh->pMaterials, pMaterials, sizeof( D3DXMATERIAL ) * NumMaterials );

		for( UINT i=0; i<NumMaterials; i++ )
		{
			if( pCXMesh->pMaterials[i].pTextureFilename != NULL )
			{
				// �e�N�X�`����ǂݍ���
				if( FAILED( D3DXCreateTextureFromFileEx(
								pD3DDevice, pCXMesh->pMaterials[i].pTextureFilename, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, m_KeyColor, NULL, NULL,
								&pCXMesh->m_ppTextures[i] ) ) )
				{
					
					// �ǂݍ��ݎ��s
					pCXMesh->m_ppTextures[i] = NULL;
				}
				
				pD3DDevice->SetTexture(0, pCXMesh->m_ppTextures[i]);
				pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
				
				pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
				pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
				pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 8);
				
			}
		}
	}
	// �}�e���A���������̂œK���ɃZ�b�g
	else
	{
		pCXMesh->pMaterials[0].pTextureFilename = NULL;
		memset( &pCXMesh->pMaterials[0].MatD3D, 0, sizeof( D3DMATERIAL9 ) );
		pCXMesh->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pCXMesh->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pCXMesh->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pCXMesh->pMaterials[0].MatD3D.Specular = pCXMesh->pMaterials[0].MatD3D.Diffuse;
	}

	// �����X�L���`����X�t�@�C�����������̏���
	if( pSkinInfo != NULL )
	{
		/* �X�L�����b�V���p�̏���*/

		/*pSkinInfo �� pMesh ���Z�b�g*/
		pCXMesh->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();
		
		pCXMesh->m_pOrigMesh = pMesh;
		pMesh->AddRef();

		/* Bone Offset Matrices �ۑ��p�̃��������m��*/
		UINT NumBones = pSkinInfo->GetNumBones();

		try
		{
			pCXMesh->m_pBoneOffsetMatrices = new D3DXMATRIX[NumBones];
		}
		
		catch ( std::bad_alloc& )
		{
			// ������������Ȃ�
			goto e_Exit;
		}

		/*Bone Offset Matrices �ǂݍ���*/
		for( UINT i = 0; i < NumBones; i++ )
		{
			//memcpy(&pCXMesh->m_pBoneOffsetMatrices[i], pCXMesh->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX) );
			pCXMesh->m_pBoneOffsetMatrices[i] = *(pCXMesh->pSkinInfo->GetBoneOffsetMatrix( i ) );			
		}
		
		// �W�F�l���[�g����
		hr = m_pModel->GenerateSkinnedMesh( m_pD3DX9, pCXMesh, m_MaxBlend );

		if( FAILED( hr ) )
		{
			goto e_Exit;
		}
		
	}

	// ���b�V���R���e�i�̊��蓖�āB
	// CXMesh�N���X�� D3DXMESHCONTAINER ���p�����Ă���
	*ppNewMeshContainer = pCXMesh;

	pCXMesh = NULL;

e_Exit:
	// �J������
	F_RELEASE( pD3DDevice );

	if( pCXMesh != NULL )
	{
		DestroyMeshContainer( pCXMesh );
	}

	return hr;
}

//======================================================================
//�@<<<�t���[���j��>>>
//	pFrameToFree : [in] ���蓖�Ă���������t���[���ւ̃|�C���^
//======================================================================
HRESULT CAllocateHierarchy::DestroyFrame( LPD3DXFRAME pFrameToFree )
{
	CXFrame *pCXFrame = (CXFrame*)pFrameToFree;

	SAFE_DELETE( pCXFrame );

	return S_OK; 
}

//======================================================================
//�@<<<���b�V���j��>>>
//	pMeshContainerToFree : [in] ���蓖�Ă��������郁�b�V�� �R���e�i �I�u�W�F�N�g�ւ̃|�C���^
//======================================================================
HRESULT CAllocateHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER pCXMeshBase )
{
	CXMesh *pCXMesh = (CXMesh*)pCXMeshBase;
	SAFE_DELETE( pCXMesh );

	return S_OK;
}
