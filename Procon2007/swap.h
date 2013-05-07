//*==============================================
//swap.h
//*==============================================
#pragma once

#include "character.h"
//===============================================
//template
//===============================================
//[Desc]
//	スワップ用テンプレート
//===============================================
//template <typename T>
//T Swap(T num1, T num2)
//{
//	T temp;
//	
//	temp = num1;
//	num1 = num2;
//	num2 = temp;
//	
//	return temp;
//}

CCharacter* Swap(CCharacter *chara1, CCharacter *chara2)
{
	CCharacter* tChara; 
	
	tChara = chara1;
	
	chara1 = chara2;
	
	chara2 = tChara;
	
	return tChara;
}
