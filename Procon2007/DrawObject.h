//*==============================================
//DrawObject.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//class
//===============================================
//[Desc]
//	�`��p�I�u�W�F�N�g
//===============================================
class CDrawObject :	public CGameObject
{
	protected:
	
		CVector3 m_vPos; //���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
	
	public:
	
		CDrawObject(void);//�R���X�g���N�^
		virtual ~CDrawObject(void);//�f�X�g���N�^
		
		virtual void Init(){};//������
		virtual void Exec(){};//����
		
	public:
	
		CVector3 GetPosition();//�ʒu�̎擾
		CVector3 GetRotate();//��]�p�x�̎擾
		CVector3 GetScale();//�g�k�̎擾
};
