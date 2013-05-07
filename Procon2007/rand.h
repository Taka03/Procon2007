//*==============================================
//rand.h
//*==============================================
#pragma once 

//===============================================
//include
//===============================================
#include "joker.h"

//===============================================
//class
//===============================================
//[Desc]
//	乱数生成クラス
//===============================================
class JRand
{
	protected:
		static Uint32 GenerateInt32( void );				///< 32Bit乱数生成

	public:
		static void Seed( Uint32 Param );					///< 乱数の種を設定
		static Uint32 GetInt32( void );						///< 32Bit乱数を取得
		static Uint64 GetInt64( void );						///< 64Bit乱数を取得
		static Float GetFloat32( void );					///< 32Bit浮動小数点乱数を取得

		static Sint32 GetInt( Sint32 Min, Sint32 Max );		///< Min～Max範囲の整数乱数を取得
		static Float GetFloat( Float Min, Float Max );		///< Min～Max範囲の浮動小数点乱数を取得
};


