//*==============================================
//CXFrame.h
//*==============================================
#pragma once

#include <d3dx9.h>

//======================================================================
//�@<<<�t���[���Ǘ��N���X>>>
//	Desc : �t���[�������Ǘ�����N���X�BD3DXFRAME���p������B
//======================================================================
class CXFrame : public D3DXFRAME
{
public:
	// �R���X�g���N�^
	CXFrame();
	// �f�X�g���N�^
	~CXFrame();

	// �t���[������ݒ�
	void SetName( LPCTSTR inName );

public:
	// �ϊ��s��(�A�j���[�V�����p)
	D3DXMATRIX m_CombinedTransformationMatrix;
	
	
};