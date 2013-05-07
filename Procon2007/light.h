//===============================================
//light.h
//===============================================
//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//class
//===============================================
class CLight :public CGameObject
{
	private:
	
		static D3DLIGHT9 m_light;
		static CVector3 m_vPos;	
	
	public:
	
		CLight();//�R���X�g���N�^	
		
		void Init();//������
		void Exec();
		
		static void SetPosition(CVector3 *Pos);//���C�g�̈ʒu�̐ݒ�
		
		static void SetLightParam();//���C�g��Ԃ̐ݒ�
		static bool SetLight();//���C�g�̐ݒ�
};