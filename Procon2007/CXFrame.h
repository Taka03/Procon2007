//*==============================================
//CXFrame.h
//*==============================================
#pragma once

#include <d3dx9.h>

//======================================================================
//　<<<フレーム管理クラス>>>
//	Desc : フレーム情報を管理するクラス。D3DXFRAMEを継承する。
//======================================================================
class CXFrame : public D3DXFRAME
{
public:
	// コンストラクタ
	CXFrame();
	// デストラクタ
	~CXFrame();

	// フレーム名を設定
	void SetName( LPCTSTR inName );

public:
	// 変換行列(アニメーション用)
	D3DXMATRIX m_CombinedTransformationMatrix;
	
	
};