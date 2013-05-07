//
//	CAllocateHierarchy.h
//
#include "gameobject.h"

class CXModel;

//======================================================================
//　<<<CAllocateHierachy>>>
//	Desc:	フレームおよびメッシュ コンテナ オブジェクトの割り当て、開放を行う。
//			メンバはID3DXAllocateHierarchyから投げられる。
//			このクラスは各要求の実装を定義する。
//			詳細はヘルプの ID3DXAllocateHierarchy を参照。
//======================================================================
class CAllocateHierarchy : public ID3DXAllocateHierarchy, public CGameObject
{
public:
	// ID3DXAllocateHierarchyインターフェイスから投げられる関数

	// フレームオブジェクトの割り当て要求
    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

	// メッシュコンテナオブジェクトの割り当て要求
    STDMETHOD(CreateMeshContainer)(THIS_ 
        LPCSTR Name, 
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials, 
        CONST D3DXEFFECTINSTANCE *pEffectInstances, 
        DWORD NumMaterials, 
        CONST DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer);

	// フレームオブジェクトの割り当て解除要求
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	// メッシュコンテナの割り当て解除要求
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

public:
	// コンストラクタ
	CAllocateHierarchy( CXModel *pModel, LPDIRECT3DDEVICE9 pD3DX9, D3DCOLOR Color );

private:
	// モデルクラス
	CXModel	*m_pModel;

	// Direct3Dデバイス
	LPDIRECT3DDEVICE9 m_pD3DX9;

	// ブレンド最大数
	int m_MaxBlend;
	
	D3DCOLOR m_KeyColor;
};
