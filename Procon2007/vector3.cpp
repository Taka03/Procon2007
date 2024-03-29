//*==============================================
//vector3.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "vector3.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	v:ベクトル
//[return]
//	なし
//===============================================
CVector3::CVector3(const CVector3 &v)
{
	*this = v;
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	v:ベクトル
//[return]
//	なし
//===============================================
CVector3::CVector3(const D3DXVECTOR3 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	posx:X座標
//  posy:Y座標
//  posz:Z座標
//[return]
//	なし
//===============================================
CVector3::CVector3(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}

//===============================================
//設定
//===============================================
//[input]
//	posx:X座標
//	posy:Y座標
//	posz:Z座標
//[return]
//	なし
//===============================================
void CVector3::Set(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}

