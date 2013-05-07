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
//　<<<コンストラクタ>>>
//======================================================================
CAllocateHierarchy::CAllocateHierarchy( CXModel *pModel, LPDIRECT3DDEVICE9 pD3DX9, D3DCOLOR Color)
{
	// メンバを初期化
	this->m_pModel		= pModel;
	this->m_pD3DX9		= pD3DX9;
	this->m_KeyColor	= Color;
}

//======================================================================
//　<<<フレーム オブジェクトの割り当て要求の実装>>>
//	Param : [Name] 作成するフレームの名前
//		  : [ppNewFrame] 作成されたフレーム オブジェクトを返す
//======================================================================
HRESULT CAllocateHierarchy::CreateFrame( LPCTSTR Name, LPD3DXFRAME *ppNewFrame )
{
	*ppNewFrame = NULL;

	try
	{
		CXFrame *pFrame = new CXFrame;

		// フレーム名を設定
		pFrame->SetName( Name );

		// フレームオブジェクトの割り当て。
		// CXFrameクラスは D3DXFRAME を継承している
		*ppNewFrame = ( LPD3DXFRAME )( pFrame );
	}
	catch ( std::bad_alloc& )
	{
		// メモリが足りない
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

//======================================================================
//　<<<メッシュ コンテナ オブジェクトの割り当て要求の実装>>>
//	Name			 : [in] メッシュの名前
//	pMeshData		 : [in] メッシュデータ構造体へのポインタ
//	pMaterials		 : [in] メッシュに使うマテリアルの配列
//	pEffectInstances : [in] メッシュに使うエフェクトインスタンスの配列
//	NumMaterials	 : [in] マテリアル配列内のマテリアルの数
//	pAdjacency		 : [in] メッシュの隣接性配列
//	pSkinInfo		 : [in] スキンデータが見つかった場合のスキンメッシュオブジェクトへのポインタ
//	ppNewMeshContainer : [out, retval] 作成されたメッシュコンテナを返す
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

	// patch meshes を扱う事はできない
	if( pMeshData->Type != D3DXMESHTYPE_MESH )
	{
		return E_FAIL;
	}

	LPD3DXMESH pMesh = pMeshData->pMesh;

	// FVF で記述されたメッシュ以外は読めぬ
	if( pMesh->GetFVF() == 0 )
	{
		return E_FAIL;
	}

	UINT NumFaces = pMesh->GetNumFaces();

	// メッシュ作成
	CXMesh *pCXMesh	= NULL;
	
	try
	{
		pCXMesh = new CXMesh;
	}
	
	catch ( std::bad_alloc& )
	{
		// メモリが足りない
		return E_OUTOFMEMORY;
	}

	// 名前設定
	pCXMesh->SetName( Name );

	// メッシュタイプ設定
	pCXMesh->MeshData.Type = D3DXMESHTYPE_MESH;

	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	// デバイスを取得
	if( FAILED( pMesh->GetDevice( &pD3DDevice ) ) )
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	// Xファイルに法線が無かったら計算で求める
	if( !( pMesh->GetFVF() & D3DFVF_NORMAL ) )
	{
		////FVFに法線を追加した新しいメッシュにする////
        hr = pMesh->CloneMeshFVF( pMesh->GetOptions(), 
                                  pMesh->GetFVF() | D3DFVF_NORMAL, 
                                  pD3DDevice, &pCXMesh->MeshData.pMesh );

        if( FAILED( hr ) )
		{
			goto e_Exit;
		}

		// 引数で渡されたメッシュへのポインタに新しいメッシュへのポインタをセット
		// pMeshへの参照はこの時点で存在しないので、ここではreleaseをかけない
		pMesh = pCXMesh->MeshData.pMesh;

		D3DXComputeNormals( pMesh, NULL );
	}
	
	// 法線があった
	else
	{
		// リファレンスを増やすだけ
		pCXMesh->MeshData.pMesh = pMesh;
		pMesh->AddRef();
	}

	// マテリアル用のメモリを確保
	pCXMesh->NumMaterials = max( 1, NumMaterials );

	try
	{
		pCXMesh->pMaterials		= new D3DXMATERIAL[pCXMesh->NumMaterials];
		pCXMesh->m_ppTextures	= new LPDIRECT3DTEXTURE9[pCXMesh->NumMaterials];
		pCXMesh->pAdjacency		= new DWORD[NumFaces * 3];
	}
	
	catch ( std::bad_alloc& )
	{
		// メモリが足りない
		goto e_Exit;
	}

	memcpy( pCXMesh->pAdjacency, pAdjacency, sizeof( DWORD ) * NumFaces * 3 );
	memset( pCXMesh->m_ppTextures, 0, sizeof( LPDIRECT3DTEXTURE9 ) * pCXMesh->NumMaterials );

	// マテリアルのコピー
	if( NumMaterials > 0 )
	{
		memcpy( pCXMesh->pMaterials, pMaterials, sizeof( D3DXMATERIAL ) * NumMaterials );

		for( UINT i=0; i<NumMaterials; i++ )
		{
			if( pCXMesh->pMaterials[i].pTextureFilename != NULL )
			{
				// テクスチャを読み込む
				if( FAILED( D3DXCreateTextureFromFileEx(
								pD3DDevice, pCXMesh->pMaterials[i].pTextureFilename, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, m_KeyColor, NULL, NULL,
								&pCXMesh->m_ppTextures[i] ) ) )
				{
					
					// 読み込み失敗
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
	// マテリアルが無いので適当にセット
	else
	{
		pCXMesh->pMaterials[0].pTextureFilename = NULL;
		memset( &pCXMesh->pMaterials[0].MatD3D, 0, sizeof( D3DMATERIAL9 ) );
		pCXMesh->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pCXMesh->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pCXMesh->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pCXMesh->pMaterials[0].MatD3D.Specular = pCXMesh->pMaterials[0].MatD3D.Diffuse;
	}

	// ワンスキン形式のXファイルだった時の処理
	if( pSkinInfo != NULL )
	{
		/* スキンメッシュ用の処理*/

		/*pSkinInfo と pMesh をセット*/
		pCXMesh->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();
		
		pCXMesh->m_pOrigMesh = pMesh;
		pMesh->AddRef();

		/* Bone Offset Matrices 保存用のメモリを確保*/
		UINT NumBones = pSkinInfo->GetNumBones();

		try
		{
			pCXMesh->m_pBoneOffsetMatrices = new D3DXMATRIX[NumBones];
		}
		
		catch ( std::bad_alloc& )
		{
			// メモリが足りない
			goto e_Exit;
		}

		/*Bone Offset Matrices 読み込み*/
		for( UINT i = 0; i < NumBones; i++ )
		{
			//memcpy(&pCXMesh->m_pBoneOffsetMatrices[i], pCXMesh->pSkinInfo->GetBoneOffsetMatrix(i), sizeof(D3DMATRIX) );
			pCXMesh->m_pBoneOffsetMatrices[i] = *(pCXMesh->pSkinInfo->GetBoneOffsetMatrix( i ) );			
		}
		
		// ジェネレート処理
		hr = m_pModel->GenerateSkinnedMesh( m_pD3DX9, pCXMesh, m_MaxBlend );

		if( FAILED( hr ) )
		{
			goto e_Exit;
		}
		
	}

	// メッシュコンテナの割り当て。
	// CXMeshクラスは D3DXMESHCONTAINER を継承している
	*ppNewMeshContainer = pCXMesh;

	pCXMesh = NULL;

e_Exit:
	// 開放処理
	F_RELEASE( pD3DDevice );

	if( pCXMesh != NULL )
	{
		DestroyMeshContainer( pCXMesh );
	}

	return hr;
}

//======================================================================
//　<<<フレーム破棄>>>
//	pFrameToFree : [in] 割り当てを解除するフレームへのポインタ
//======================================================================
HRESULT CAllocateHierarchy::DestroyFrame( LPD3DXFRAME pFrameToFree )
{
	CXFrame *pCXFrame = (CXFrame*)pFrameToFree;

	SAFE_DELETE( pCXFrame );

	return S_OK; 
}

//======================================================================
//　<<<メッシュ破棄>>>
//	pMeshContainerToFree : [in] 割り当てを解除するメッシュ コンテナ オブジェクトへのポインタ
//======================================================================
HRESULT CAllocateHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER pCXMeshBase )
{
	CXMesh *pCXMesh = (CXMesh*)pCXMeshBase;
	SAFE_DELETE( pCXMesh );

	return S_OK;
}
