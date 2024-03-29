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
//	¶¬NX
//===============================================
class JRand
{
	protected:
		static Uint32 GenerateInt32( void );				///< 32Bit¶¬

	public:
		static void Seed( Uint32 Param );					///< ÌíðÝè
		static Uint32 GetInt32( void );						///< 32Bitðæ¾
		static Uint64 GetInt64( void );						///< 64Bitðæ¾
		static Float GetFloat32( void );					///< 32Bit®¬_ðæ¾

		static Sint32 GetInt( Sint32 Min, Sint32 Max );		///< Min`MaxÍÍÌ®ðæ¾
		static Float GetFloat( Float Min, Float Max );		///< Min`MaxÍÍÌ®¬_ðæ¾
};


