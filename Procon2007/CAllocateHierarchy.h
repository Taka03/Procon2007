//
//	CAllocateHierarchy.h
//
#include "gameobject.h"

class CXModel;

//======================================================================
//�@<<<CAllocateHierachy>>>
//	Desc:	�t���[������у��b�V�� �R���e�i �I�u�W�F�N�g�̊��蓖�āA�J�����s���B
//			�����o��ID3DXAllocateHierarchy���瓊������B
//			���̃N���X�͊e�v���̎������`����B
//			�ڍׂ̓w���v�� ID3DXAllocateHierarchy ���Q�ƁB
//======================================================================
class CAllocateHierarchy : public ID3DXAllocateHierarchy, public CGameObject
{
public:
	// ID3DXAllocateHierarchy�C���^�[�t�F�C�X���瓊������֐�

	// �t���[���I�u�W�F�N�g�̊��蓖�ėv��
    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

	// ���b�V���R���e�i�I�u�W�F�N�g�̊��蓖�ėv��
    STDMETHOD(CreateMeshContainer)(THIS_ 
        LPCSTR Name, 
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials, 
        CONST D3DXEFFECTINSTANCE *pEffectInstances, 
        DWORD NumMaterials, 
        CONST DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer);

	// �t���[���I�u�W�F�N�g�̊��蓖�ĉ����v��
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	// ���b�V���R���e�i�̊��蓖�ĉ����v��
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

public:
	// �R���X�g���N�^
	CAllocateHierarchy( CXModel *pModel, LPDIRECT3DDEVICE9 pD3DX9, D3DCOLOR Color );

private:
	// ���f���N���X
	CXModel	*m_pModel;

	// Direct3D�f�o�C�X
	LPDIRECT3DDEVICE9 m_pD3DX9;

	// �u�����h�ő吔
	int m_MaxBlend;
	
	D3DCOLOR m_KeyColor;
};
