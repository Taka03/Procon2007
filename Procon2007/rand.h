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
//	���������N���X
//===============================================
class JRand
{
	protected:
		static Uint32 GenerateInt32( void );				///< 32Bit��������

	public:
		static void Seed( Uint32 Param );					///< �����̎��ݒ�
		static Uint32 GetInt32( void );						///< 32Bit�������擾
		static Uint64 GetInt64( void );						///< 64Bit�������擾
		static Float GetFloat32( void );					///< 32Bit���������_�������擾

		static Sint32 GetInt( Sint32 Min, Sint32 Max );		///< Min�`Max�͈͂̐����������擾
		static Float GetFloat( Float Min, Float Max );		///< Min�`Max�͈͂̕��������_�������擾
};


