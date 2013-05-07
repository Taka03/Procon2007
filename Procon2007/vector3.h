//*==============================================
//vector3.h
//*==============================================
//二重インクルード防止
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
	
		CVector3(){};//コンストラクタ
		CVector3(const CVector3 &v);//コンストラクタ
		CVector3(const D3DXVECTOR3 &v);//コンストラクタ
		CVector3(float posx, float posy, float posz);//コンストラクタ
		
		void Set(float posx, float posy, float posz);//ベクトルのセット
		

};
