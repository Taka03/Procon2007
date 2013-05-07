//*==============================================
//CXFrame.cpp
//*==============================================

#include "CXFrame.h"
#include "joker.h"

//======================================================================
//�@<<<�R���X�g���N�^>>>
//======================================================================
CXFrame::CXFrame()
{
	// D3DXFRAME �R���̕ϐ���������
	D3DXMatrixIdentity( &TransformationMatrix );
	Name				= NULL;
	pMeshContainer		= NULL;
	pFrameSibling		= NULL;
	pFrameFirstChild	= NULL;

	// �����o�ϐ�������
	D3DXMatrixIdentity( &m_CombinedTransformationMatrix );
}

//======================================================================
//�@<<<�f�X�g���N�^>>>
//======================================================================
CXFrame::~CXFrame()
{
	SAFE_DELETE( Name );
}

//======================================================================
//�@<<<���O�ݒ�>>>
//======================================================================
void CXFrame::SetName( LPCTSTR inName )
{
	if( inName != NULL )
	{
		UINT Length;
		Length = lstrlen( inName ) + 1;
		SAFE_DELETE( Name );
		Name = new TCHAR[Length];
		memcpy( Name, inName, Length * sizeof( TCHAR ) );
	}
}