//===============================================
//System.h
//===============================================
#pragma once

//===============================================
//include
//===============================================
#include "CXModel.h"

//===============================================
//class
//===============================================
//[Desc]
//	�V�X�e���O���t�B�b�N	
//===============================================
class CSystem :	public CXModel
{
	private:
	
		CVector3 m_vPos;//���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
		
	public:
		
		CSystem(void);//�R���X�g���N�^
		~CSystem(void);//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
};