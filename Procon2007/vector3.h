//*==============================================
//vector3.h
//*==============================================
//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include <d3dx9.h>

//===============================================
//class
//===============================================
class CVector3 :public D3DXVECTOR3
{
	public:
	
		CVector3(){};//�R���X�g���N�^
		CVector3(const CVector3 &v);//�R���X�g���N�^
		CVector3(const D3DXVECTOR3 &v);//�R���X�g���N�^
		CVector3(float posx, float posy, float posz);//�R���X�g���N�^
		
		void Set(float posx, float posy, float posz);//�x�N�g���̃Z�b�g
		

};
