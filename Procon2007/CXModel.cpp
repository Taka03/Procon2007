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

//#include <rmxftmpl.h>	//複数のファイルにインクルードさせるとリンクエラー
						//D3DRM_XTEMPLATES等がextern宣言されてない模様

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
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
//コンストラクタ
//===============================================
//[input]
//	name:名前
//[return]
//	なし
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
//　<<<デストラクタ>>>
//======================================================================
CXModel::~CXModel()
{
	Release();
}

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CXModel::Init()
{
	
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CXModel::Exec()
{
	
	
//	SetTrackEnable(1, false);
	
}

//===============================================
//Xファイルの読み込み
//===============================================
//[input]
//	pD3DX9:Direct3Dデバイス
//	pFileName:ファイル名
//	MaxBlend:最大ブレンド数
//[return]
//	ブール値
//===============================================
bool CXModel::Load( LPDIRECT3DDEVICE9 pD3DX9, const char *pFileName, D3DCOLOR Color )
{
	// フレーム及びメッシュ割り当てを行うクラス CAllocateHierachy を生成
	// 各フレーム、メッシュ割り当ての実装はCAllocateHierachy内で記述
    CAllocateHierarchy Alloc( this, pD3DX9, Color);

    LPD3DXANIMATIONCONTROLLER pAnimControllerTmp;
    
	/*Xfileの読み込み*/
    if( FAILED( D3DXLoadMeshHierarchyFromX(
					pFileName, D3DXMESH_MANAGED, pD3DX9,
					&Alloc, NULL, &m_pFrameRoot, &pAnimControllerTmp ) ) )
	{
		CHAR str[128];
		
		wsprintf(str, "%sが見つかりません", pFileName);
		
		MESSAGE(str);
		
		// 失敗
		return false;
	}

	/*アニメーションが存在しない*/
	if( pAnimControllerTmp == NULL )
	{
		return true;
	}

	// 利便性を考えて、トラック数をアニメーションセット数に増やす
	int TracksNum   = pAnimControllerTmp->GetMaxNumTracks();
	int AnimSetsNum = pAnimControllerTmp->GetMaxNumAnimationSets();

	if( TracksNum < AnimSetsNum )
	{
		TracksNum = AnimSetsNum;
	}

	// アニメーションコントローラーのクローン作成
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
		
		/*トラックに全てのアニメーションセットを読み込む*/
		for( int i = 0; i < AnimSetsNum; i++ )
		{
			/*アニメーションセットの取得*/
			if( FAILED( m_pAnimController->GetAnimationSet( i, &m_Anim[i].pAnimSet) ) )
			{
				return false;
			}
			
			m_Anim[i].AnimID = i;

			///*アニメーションセットの設定*/
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
		MESSAGE("ボーンの接続に失敗");
		
		return false;
	}

	return true;
}

//===============================================
//メモリ解放
//===============================================
//[input]
//	なし
//[return]
//	なし
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
//レンダリング
//===============================================
//[input]
//	pD3DX9:Direct3Dデバイス
//[return]
//	なし
//===============================================
void CXModel::Render( LPDIRECT3DDEVICE9 pD3DX9 )
{
	// ルートフレームから順番に描画していく
	if( m_pFrameRoot != NULL )
	{
		DrawFrame( pD3DX9, m_pFrameRoot );
	}
}

//===============================================
//スキンメッシュの生成
//===============================================
//[input]
//	pD3DX9:Direct3Dデバイス
//	MaxBlend:頂点ブレンド最大数
//[return]
//	HRESULT値
//===============================================
HRESULT CXModel::GenerateSkinnedMesh( LPDIRECT3DDEVICE9 pD3DX9, CXMesh *pCXMeshBase, int MaxBlend )
{
	HRESULT hr = S_OK;
	
	D3DCAPS9 d3dCaps;
	
	pD3DX9->GetDeviceCaps(&d3dCaps);

	/*スキンメッシュでは無い場合、即コンバートを行う*/
	if( pCXMeshBase->pSkinInfo == NULL )
	{
		pCXMeshBase->ConvertVertex( pD3DX9);
		return hr;
	}

	//----------------------------------------------
	//スキンメッシュ用の処理
	//----------------------------------------------

	F_RELEASE( pCXMeshBase->MeshData.pMesh );
	F_RELEASE( pCXMeshBase->m_pBoneCombinationBuf );

	/*メッシュのクローン作成*/
	hr = pCXMeshBase->m_pOrigMesh->CloneMeshFVF(
			D3DXMESH_MANAGED, pCXMeshBase->m_pOrigMesh->GetFVF(),
			pD3DX9, &pCXMeshBase->MeshData.pMesh );

	if( FAILED( hr ) )
	{
		return hr;
	}
	
	/*属性テーブルを取得*/
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
	
	//他のメッシュによってボーン行列用のメモリが確保
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

	/*頂点ブレンド用にコンバート*/
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
	////適切なBoneCombinationSetを探す
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

	///*FVFを再設定して、クローン生成*/
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
//フレームの描画
//===============================================
//[input]
//	pD3DX9:Direct3Dデバイス
//	pD3DXFrame:フレーム
//[return]
//	なし
//===============================================
void CXModel::DrawFrame( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXFRAME pD3DXFrame )
{
	LPD3DXMESHCONTAINER pD3DXMeshContainer;

	pD3DXMeshContainer = pD3DXFrame->pMeshContainer;

	// フレームが持っているメッシュごとに描画処理
	while( pD3DXMeshContainer )
	{
		// 描画
		DrawMeshContainer( pD3DX9, pD3DXMeshContainer, pD3DXFrame );

		// 次のメッシュを取得
		pD3DXMeshContainer = pD3DXMeshContainer->pNextMeshContainer;
	}

	// 兄弟フレームがあれば、兄弟フレームを描画
	if( pD3DXFrame->pFrameSibling )
	{
		DrawFrame( pD3DX9, pD3DXFrame->pFrameSibling );
	}

	// 子フレームがあれば、子フレームを描画
	if( pD3DXFrame->pFrameFirstChild )
	{
		DrawFrame( pD3DX9, pD3DXFrame->pFrameFirstChild );
	}
}

//======================================================================
//　<<< メッシュコンテナを描画 >>>
//	Param : [pD3DXMeshContainer] 描画するメッシュコンテナの情報
//		  : [pD3DXFrame] 描画するフレームの情報
//======================================================================
void CXModel::DrawMeshContainer( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXMESHCONTAINER pD3DXMeshContainer, LPD3DXFRAME pD3DXFrame )
{
	// 注:実は危険なキャスト 安全に行うときはdynamic_castを使う。
	CXMesh *pMesh = (CXMesh*)pD3DXMeshContainer;

	// スキンメッシュ
	if( pMesh->pSkinInfo != NULL )
	{
		DWORD NumBones = pMesh->pSkinInfo->GetNumBones();
		
		unsigned int iAttrib = 0;
		
		
		for(DWORD i = 0;i < NumBones;i++)
		{
			D3DXMatrixMultiply(&m_pBoneMatrices[i], &pMesh->m_pBoneOffsetMatrices[i], pMesh->m_ppBoneMatrixPtrs[i]);
		}
		
		/*ワールド行列をクリア*/
		D3DXMATRIX Identity;
		D3DXMatrixIdentity(&Identity);
		pD3DX9->SetTransform(D3DTS_WORLD, &Identity);
		
		/*頂点バッファをロック*/
		PBYTE pVerticesSrc;
		PBYTE pVerticesDst;
		
		pMesh->m_pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVerticesSrc);
		pMesh->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pVerticesDst);
		
		/*スキンメッシュの作成*/
		pMesh->pSkinInfo->UpdateSkinnedMesh(m_pBoneMatrices, NULL, pVerticesSrc, pVerticesDst);
		
		/*頂点バッファのロックを解除*/
		pMesh->m_pOrigMesh->UnlockVertexBuffer();
		
//		LPD3DXBONECOMBINATION	pBoneComb	= reinterpret_cast< LPD3DXBONECOMBINATION >( pMesh->m_pBoneCombinationBuf->GetBufferPointer() );
		
		
		/*スキンメッシュの描画*/
		for(UINT i = 0;i < pMesh->m_NumAttributeGroups;i++)
		{
			pD3DX9->SetMaterial( &(pMesh->pMaterials[pMesh->m_pAttributeTable[i].AttribId].MatD3D) );
			pD3DX9->SetTexture(0, pMesh->m_ppTextures[pMesh->m_pAttributeTable[i].AttribId]);
			pMesh->MeshData.pMesh->DrawSubset(pMesh->m_pAttributeTable[i].AttribId);
		}
		
		//
	
	//	/*スキンメッシュ用の処理*/
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

	//	/*デフォルトの vtx プロセスで描画*/
	//	for( iAttrib=0; iAttrib < pMesh->GetNumAttributeGroups(); iAttrib++ )
	//	{

	//		/*ブレンド数を計算*/
	//		for( DWORD i=0; i < pMesh->m_NumInfl; i++ )
	//		{
	//			if( pBoneComb[ iAttrib ].BoneId[ i ] != UINT_MAX )
	//			{
	//				NumBlend = i;
	//			}
	//		}

	//		/*ブレンド処理*/
	//		if( m_MaxBlend >= NumBlend+1 )
	//		{
	//			for( DWORD i=0; i < pMesh->m_NumInfl; i++ )
	//			{
	//				iMatrixIndex =	pBoneComb[ iAttrib ].BoneId[ i ];

	//				if( iMatrixIndex != UINT_MAX )
	//				{
	//					// アニメーション行列を計算
	//					D3DXMatrixMultiply( &matTmp, &pMesh->m_pBoneOffsetMatrices[ iMatrixIndex ], pMesh->m_ppBoneMatrixPtrs[ iMatrixIndex ] );
	//					pD3DX9->SetTransform( D3DTS_WORLDMATRIX(i), &matTmp );
	//				}
	//			}

	//			/*ブレンド数を設定*/
	//			pD3DX9->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

	//			if( AttribIdPrev != pBoneComb[ iAttrib ].AttribId || AttribIdPrev == UNUSED32 )
	//			{
	//				pD3DX9->SetMaterial( &pMesh->pMaterials[ pBoneComb[ iAttrib ].AttribId ].MatD3D );
	//				pD3DX9->SetTexture( 0, pMesh->m_ppTextures[ pBoneComb[ iAttrib ].AttribId ] );

	//				AttribIdPrev	= pBoneComb[ iAttrib ].AttribId;
	//			}
	//			
	//			//pMesh->MeshData.pMesh->DrawSubset(iAttrib);

	//			/*頂点ブレンドを使ってメッシュを描画*/
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

	//	/*ソフトウェアで頂点ブレンド*/
	//	if( pMesh->m_iAttributeSW < pMesh->m_NumAttributeGroups )
	//	{
	//		AttribIdPrev	= UNUSED32;
	//		pD3DX9->SetSoftwareVertexProcessing( true );

	//		for( iAttrib = pMesh->m_iAttributeSW; iAttrib < pMesh->m_NumAttributeGroups; iAttrib++ )
	//		{
	//			unsigned int NumBlend	= 0;

	//			// ブレンド数計算
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
	//						/*アニメーション行列を計算*/
	//						D3DXMatrixMultiply( &matTmp, &pMesh->m_pBoneOffsetMatrices[ iMatrixIndex ], pMesh->m_ppBoneMatrixPtrs[ iMatrixIndex ] );
	//						pD3DX9->SetTransform( D3DTS_WORLDMATRIX(i), &matTmp );
	//					}
	//				}

	//				/*ブレンド数を設定*/
	//				pD3DX9->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

	//				if( AttribIdPrev != pBoneComb[ iAttrib ].AttribId || AttribIdPrev == UNUSED32 )
	//				{
	//					pD3DX9->SetMaterial( &pMesh->pMaterials[ pBoneComb[ iAttrib ].AttribId ].MatD3D );
	//					pD3DX9->SetTexture( 0, pMesh->m_ppTextures[ pBoneComb[ iAttrib ].AttribId ] );

	//					AttribIdPrev = pBoneComb[ iAttrib ].AttribId;
	//				}

	//				/*頂点ブレンドを使ってメッシュを描画*/
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

	//	}	// ソフトウェアでのブレンド描画処理ここまで

	//	/*後始末*/
	//	pD3DX9->SetRenderState( D3DRS_VERTEXBLEND, 0 );

	//	
	}
	
	//----------------------------------------------
	//スキンメッシュでは無い時の処理
	//----------------------------------------------
	else
	{
		// マテリアル別にメッシュの描画
		for( DWORD i=0; i<pMesh->NumMaterials; i++ )
		{
			// アニメーション行列をワールド行列に設定
			pD3DX9->SetTransform( D3DTS_WORLD, &( (CXFrame *)pD3DXFrame )->m_CombinedTransformationMatrix );

			pD3DX9->SetMaterial( &pMesh->pMaterials[i].MatD3D );
			
			
			
			pD3DX9->SetTexture( 0, pMesh->m_ppTextures[i] );
			
			pMesh->MeshData.pMesh->DrawSubset(i);

			//LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
			//LPDIRECT3DINDEXBUFFER9  pIB = NULL;

			//// 頂点バッファを設定
			//pMesh->MeshData.pMesh->GetVertexBuffer( &pVB );
			//pD3DX9->SetStreamSource( 0, pVB, 0, D3DXGetFVFVertexSize(pMesh->MeshData.pMesh->GetFVF()) );

			//// インデックスバッファをデバイスに設定
			//pMesh->MeshData.pMesh->GetIndexBuffer( &pIB );
			//pD3DX9->SetIndices( pIB );

			//pD3DX9->SetFVF( pMesh->MeshData.pMesh->GetFVF() );

			//// 描画
			//pD3DX9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,
			//								0,
			//								pMesh->GetAttributeTable( i )->VertexStart,
			//								pMesh->GetAttributeTable( i )->VertexCount,
			//								pMesh->GetAttributeTable( i )->FaceStart * 3,
			//								pMesh->GetAttributeTable( i )->FaceCount);

			//// 後始末
			//F_RELEASE( pVB );
			//F_RELEASE( pIB );

		}
	}
}

//===============================================
//ボーン変換
//===============================================
//[input]
//	pD3DXMeshContainer:メッシュコンテナ
//[return]
//	ブール値
//===============================================
bool CXModel::SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pD3DXMeshContainer )
{
	CXMesh *pMesh = (CXMesh *)pD3DXMeshContainer;

	/*スキンメッシュのときはボーン行列をセット*/
	if( pMesh->pSkinInfo != NULL )
	{
		DWORD NumBones = pMesh->pSkinInfo->GetNumBones();
		
		pMesh->m_ppBoneMatrixPtrs = (D3DXMATRIX**)MemoryAlloc(sizeof(D3DXMATRIX*) * NumBones);//new D3DXMATRIX*[NumBones];

		if( !pMesh->m_ppBoneMatrixPtrs )
		{
			MESSAGE("BoneMatrixが見つからない");
			
			return false;
		}

		for( DWORD i = 0; i < NumBones; i++ )
		{
		//	BoneName = pMesh->pSkinInfo->GetBoneName(i);
			
			CXFrame *pCD3DXFrame = (CXFrame*)D3DXFrameFind(
				m_pFrameRoot, pMesh->pSkinInfo->GetBoneName( i ) );

			if( !pCD3DXFrame )
			{
				MESSAGE("フレームの名前取得に失敗");
				
				return false;
			}

			pMesh->m_ppBoneMatrixPtrs[i] = &pCD3DXFrame->m_CombinedTransformationMatrix;
		}
	}

	return true;
}

//======================================================================
//　<<<ボーンのセットアップ>>>
//======================================================================
bool CXModel::SetupBoneMatrixPointers( LPD3DXFRAME pD3DXFrame )
{

	if( pD3DXFrame->pMeshContainer )
	{
		if( FAILED( SetupBoneMatrixPointersOnMesh( pD3DXFrame->pMeshContainer ) ) )
		{
			MESSAGE("ボーンメッシュの接続に失敗");
			
			return false;
		}
	}

	if( pD3DXFrame->pFrameSibling )
	{
		if( FAILED( SetupBoneMatrixPointers( pD3DXFrame->pFrameSibling ) ) )
		{ 
			MESSAGE("ボーンメッシュの接続に失敗");
			
			return false;
		}
	}

	if( pD3DXFrame->pFrameFirstChild )
	{
		if( FAILED( SetupBoneMatrixPointers( pD3DXFrame->pFrameFirstChild ) ) )
		{
			MESSAGE("ボーンメッシュの接続に失敗");
			
			return false;
		}
	}

	return true;
}

//======================================================================
//　<<<フレームの更新>>>
//	Desc : 毎フレーム、現在の時間に合わせてアニメーションを更新していく
//		 : アニメーション行列はCXFrameクラスの m_CombinedTransformationMatrix メンバに保存される
//======================================================================
void CXModel::UpdateFrameMatrices( LPD3DXFRAME pD3DXMesh, LPD3DXMATRIX pParentMatrix )
{
	CXFrame *pCD3DXFrame = (CXFrame*)pD3DXMesh;

	// 親フレームがある
	if( pParentMatrix )
	{
		// 親のアニメーションと合成
		D3DXMatrixMultiply( &pCD3DXFrame->m_CombinedTransformationMatrix, &pCD3DXFrame->TransformationMatrix, pParentMatrix );
	}

	else
	{
		pCD3DXFrame->m_CombinedTransformationMatrix = pCD3DXFrame->TransformationMatrix;
	}

	// 兄弟フレームを更新
	if( pCD3DXFrame->pFrameSibling )
	{
		UpdateFrameMatrices( pCD3DXFrame->pFrameSibling, pParentMatrix );
	}

	// 子フレームを更新
	if( pCD3DXFrame->pFrameFirstChild )
	{
		UpdateFrameMatrices( pCD3DXFrame->pFrameFirstChild, &pCD3DXFrame->m_CombinedTransformationMatrix );
	}
}

//===============================================
//アニメーションの切り替え
//===============================================
//[input]
//	animID:アニメID
//[return]
//	bool値
//===============================================
bool CXModel::ChangeAnimation(UINT animID)
{
	/*指定のアニメーションIDの存在をチェック*/
	//if( m_Anim.size() <= animID )
	//{
	//	return false;
	//}
	
	/*現在のアニメーションと異なるかチェック*/
	if( m_CurAnimID == animID )
	{
		return false;
	}
	
	/*現在のアニメーションセットの設定値を取得*/
	if(m_pAnimController != NULL)
	{
		
		D3DXTRACK_DESC TD;
		m_pAnimController->GetTrackDesc( 0, &TD );
		//
		/////*アニメーションセットをトラック1に設定*/
		m_pAnimController->SetTrackAnimationSet( 1, m_Anim[m_CurAnimID].pAnimSet );
		m_pAnimController->SetTrackDesc( 1, &TD );
		
		//
		/*アニメーションセットをトラック0に設定*/
		m_pAnimController->SetTrackAnimationSet( 0, m_Anim[animID].pAnimSet );
		
		/*トラック0のスピードの設定*/
		m_pAnimController->SetTrackSpeed( 0, m_Anim[animID].fTrackSpeed );
		
		//m_pAnimController->SetTrackSpeed( 0, AdjustSpeed );
		
		
		/*トラックの合成を許可*/
		m_pAnimController->SetTrackEnable( 0, true );
		m_pAnimController->SetTrackEnable( 1, true );
		
	}
		
	/*ウェイト時間を初期化*/
	m_Anim[animID].fCurWeight = 0.0f;
	
	/*現在のアニメーション番号を切り替え*/
	m_PreAnimID = m_CurAnimID;
	m_CurAnimID = animID;
	
	
	
	return true;
	
}

//===============================================
//ループ時間の設定
//===============================================
//[input]
//	animID:アニメID
//	Time:ループ時間
//[return]
//	bool値
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
//シフト時間の設定
//===============================================
//[input]
//	animID:アニメID
//	Time:シフト時間
//[return]
//	bool値
//===============================================
bool CXModel::SetShiftTime(UINT animID, float Time)
{
	/*指定のアニメーションIDの存在を確認*/
	//if( m_Anim.size() <= animID )
	//{
	//	return false;
	//}
	
	/*シフト時間を登録*/
	m_Anim[animID].fShiftTime = Time;
	
	return true;
	
}


//======================================================================
//　<<<モデルの更新>>>
//	Prame  : [Time] 変化した時間
//======================================================================
bool CXModel::Update( float Time )
{
	/*合成中か否かを判定*/
	m_Anim[m_CurAnimID].fCurWeight += Time;
	
	//m_pAnimController->ResetTime();
	
	if( m_pAnimController != NULL )
	{
		if(m_Anim[m_CurAnimID].fCurWeight <= m_Anim[m_CurAnimID].fShiftTime )
		{
			m_IsChangeAnim = true;
		
			/*合成中*/
			float Weight = m_Anim[m_CurAnimID].fCurWeight / m_Anim[m_CurAnimID].fShiftTime;
			
			/*ウェイトを登録*/
			m_pAnimController->SetTrackWeight( 0, Weight );
			m_pAnimController->SetTrackWeight( 1, 1 - Weight );
		}
		
		else
		{
			m_pAnimController->SetTrackWeight( 0, 1.0f );
			m_pAnimController->SetTrackEnable( 1, false );
		}
		
		/*時間を更新*/
		m_pAnimController->AdvanceTime( Time, NULL );
	}
	
	return true;
	
}


//===============================================
//ワールド行列の設定
//===============================================
//[input]
//	なし
//[return]
//	なし
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

// 以下ユーティリティ関数群
D3DXMATRIX& CXModel::GetWorldMatrix()
{
	return m_matWorld;
}

D3DXMATRIX& CXModel::GetLocalMatrix()
{
	return m_matTrans;
}

//===============================================
//座標の取得
//===============================================
//[input]
//	Pos:取得するベクトル
//[return]
//	なし
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
//X座標の取得
//===============================================
//[input]
//	なし
//[return]
//	X座標
//===============================================
float CXModel::GetPosX()
{
	return m_vPos.x;
}

//===============================================
//Y座標の取得
//===============================================
//[input]
//	なし
//[return]
//	Y座標
//===============================================
float CXModel::GetPosY()
{
	return m_vPos.y;
}

//===============================================
//Z座標の取得
//===============================================
//[input]
//	なし
//[return]
//	Z座標
//===============================================
float CXModel::GetPosZ()
{
	return m_vPos.z;
}

//===============================================
//アニメーショントラックの可否
//===============================================
//[input]
//	Track:トラック番号
//	Enable:再生判定
//[return]
//	ブール値
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
//アニメーショントラックスピードの設定
//===============================================
//[input]
//	Track:トラック番号
//	Speed:アニメーションスピード
//[return]
//	ブール値
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
//アニメーショントラックの重み
//===============================================
//[input]
//	Track:トラック番号
//	Weight:
//[return]
//	ブール値
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
//　<<<スキンメッシュのジェネレート>>>
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
//		//// 他のメッシュによってボーン行列用のメモリが確保しきれていない場合は確保 ////
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
//移動
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//	z:Z座標
//[return]
//	なし
//===============================================
void CXModel::Translation(float x, float y, float z)
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
void CXModel::TranslationX(float x)
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
void CXModel::TranslationY(float y)
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
void CXModel::TranslationZ(float z)
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
void CXModel::Rotation(float xangle, float yangle, float zangle)
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
void CXModel::RotationX(float angle)
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
void CXModel::RotationY(float angle)
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
void CXModel::RotationZ(float angle)
{
	Rotation(0, 0, angle);
}

//===============================================
//拡大縮小
//===============================================
//[input]
//	Sx:X方向の拡縮
//	Sy:Y方向の拡縮
//	Sz:Z方向の拡縮
//[return]
//	なし
//===============================================
void CXModel::Scaling(float Sx, float Sy, float Sz)
{
	::D3DXMatrixScaling(&m_matScale, Sx, Sy, Sz);
}


//===============================================
//ヘッディング
//===============================================
//[input]
//	angle:角度
//[return]
//	なし
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
//ピッチング
//===============================================
//[input]
//	angle:角度
//[return]
//	なし
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
//ローリング
//===============================================
//[input]
//	angle:角度
//[return]
//	なし
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
//　<<<フレームルート取得>>>
//======================================================================
LPD3DXFRAME	CXModel::GetFrameRoot()
{
	return m_pFrameRoot;
}

//======================================================================
//　<<<アニメーションコントローラー>>>
//======================================================================
LPD3DXANIMATIONCONTROLLER CXModel::GetAniController()
{
	return m_pAnimController;
}