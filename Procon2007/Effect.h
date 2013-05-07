//*==============================================
//Effect.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "CXModel.h"

//===============================================
//class
//===============================================
//[Desc]
//	�G�t�F�N�g�p�N���X
//===============================================
class CEffect :	public CXModel
{
	private:
	
		CVector3 m_vPos;//�ʒu
		CVector3 m_vRot;//�p�x
		
		CVector3 m_vScale;//�g�k
		
		float m_AnimSpeed;//�A�j���[�V�������x
		
		bool m_IsVariable;//�\���t���O
		
	public:
		
		CEffect(void);//�R���X�g���N�^
		CEffect(char *name);//�R���X�g���N�^
		virtual ~CEffect(void);//�f�X�g���N�^
		
		void Exec();//����
		
		void SetPosition(CVector3 Pos);//�ʒu�̐ݒ�
		void AddPosition(CVector3 Pos);//�ʒu�̉��Z
		void SetVariableFlag(bool flag);//�\���t���O�̐ݒ�
		void SetScale(CVector3 Scale);//�g�k���̐ݒ�
		void SetRotate(CVector3 Rot);
	
	public:
	
	
	
		bool GetVariableFlag();//�\���t���O�̐ݒ�
};
