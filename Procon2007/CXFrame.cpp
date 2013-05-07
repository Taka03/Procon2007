//*==============================================
//CXFrame.cpp
//*==============================================

#include "CXFrame.h"
#include "joker.h"

//======================================================================
//　<<<コンストラクタ>>>
//======================================================================
CXFrame::CXFrame()
{
	// D3DXFRAME 由来の変数を初期化
	D3DXMatrixIdentity( &TransformationMatrix );
	Name				= NULL;
	pMeshContainer		= NULL;
	pFrameSibling		= NULL;
	pFrameFirstChild	= NULL;

	// メンバ変数初期化
	D3DXMatrixIdentity( &m_CombinedTransformationMatrix );
}

//======================================================================
//　<<<デストラクタ>>>
//======================================================================
CXFrame::~CXFrame()
{
	SAFE_DELETE( Name );
}

//======================================================================
//　<<<名前設定>>>
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