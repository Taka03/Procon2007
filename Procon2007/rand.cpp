//*==============================================
//rand.cpp
//*==============================================

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.keio.ac.jp/matumoto/emt.html
   email: matumoto@math.keio.ac.jp
*/

//===============================================
//include
//===============================================
#include "rand.h"

//--------------------------------------------------------------------------------------------
// CONST
//--------------------------------------------------------------------------------------------
static const Uint32 N			= 624UL;
static const Uint32 M			= 397UL;
static const Uint32 MATRIX_A		= 0x9908B0DFUL;
static const Uint32 UPPER_MASK	= 0x80000000UL;
static const Uint32 LOWER_MASK	= 0x7FFFFFFFUL;


//--------------------------------------------------------------------------------------------
// VARIABLE
//--------------------------------------------------------------------------------------------
static Uint32 MersenneTwister[N];
static Sint32 MersenneTwisterCount = N + 1;

//--------------------------------------------------------------------------------------------
/**
	32Bit整数乱数生成

	@param	乱数値
*/
//--------------------------------------------------------------------------------------------
Uint32 JRand::GenerateInt32( void )
{
    Uint32 Mag01[2] = { 0x00000000UL, MATRIX_A };
    Uint32 Param;

    if ( MersenneTwisterCount >= N )
	{
        Sint32 kk = 0;

		while ( kk < N - M )
		{
            Param = (MersenneTwister[kk] & UPPER_MASK) | (MersenneTwister[kk+1] & LOWER_MASK);
            MersenneTwister[kk] = MersenneTwister[kk + M] ^ (Param >> 1) ^ Mag01[Param & 0x01];

			kk++;
		}

		while ( kk < N - 1 )
		{
            Param = (MersenneTwister[kk] & UPPER_MASK) | (MersenneTwister[kk + 1] & LOWER_MASK);
            MersenneTwister[kk] = MersenneTwister[kk + (M - N)] ^ (Param >> 1) ^ Mag01[Param & 0x00000001UL];

			kk++;
		}

		Param = (MersenneTwister[N - 1]&UPPER_MASK) | (MersenneTwister[0] & LOWER_MASK);
        MersenneTwister[N - 1] = MersenneTwister[M-1] ^ (Param >> 1) ^ Mag01[Param & 0x00000001UL];

        MersenneTwisterCount = 0;
    }
  
    Param = MersenneTwister[MersenneTwisterCount++];

    /* Tempering */
    Param ^= (Param >> 11);
    Param ^= (Param <<  7) & 0x9D2C5680UL;
    Param ^= (Param << 15) & 0xEFC60000UL;
    Param ^= (Param >> 18);

    return Param;
}

//--------------------------------------------------------------------------------------------
/**
	乱数のシード値を設定します。

	@param	シード値
*/
//--------------------------------------------------------------------------------------------
void JRand::Seed( Uint32 Param )
{
    MersenneTwister[0] = Param & 0xFFFFFFFFUL;
    for ( MersenneTwisterCount = 1; MersenneTwisterCount < N; MersenneTwisterCount++ )
	{
        MersenneTwister[MersenneTwisterCount] = (1812433253UL * (MersenneTwister[MersenneTwisterCount-1] ^ (MersenneTwister[MersenneTwisterCount-1] >> 30)) + MersenneTwisterCount); 
        MersenneTwister[MersenneTwisterCount] &= 0xFFFFFFFFUL;
    }
}

//--------------------------------------------------------------------------------------------
/**
	64Bit整数乱数を取得します。

	@return 乱数値
*/
//--------------------------------------------------------------------------------------------
Uint32 JRand::GetInt32( void )
{
    return GenerateInt32();
}

//--------------------------------------------------------------------------------------------
/**
	64Bit整数乱数を取得します。

	@return 乱数値
*/
//--------------------------------------------------------------------------------------------
Uint64 JRand::GetInt64( void )
{
	Uint64 a = GenerateInt32();
	Uint64 b = GenerateInt32();

	return (a << 32) | b;
}

//--------------------------------------------------------------------------------------------
/**
	32Bit浮動小数点乱数を取得します。

	@return 乱数値
*/
//--------------------------------------------------------------------------------------------
Float JRand::GetFloat32( void )
{
	const Uint32 RANDOM_MAX	= 100000000;

    return toF(GenerateInt32() % (RANDOM_MAX+1)) / toF(RANDOM_MAX);
}

//--------------------------------------------------------------------------------------------
/**
	指定範囲内の整数乱数を取得します。

	@param Min [in] 最小値
	@param Max [in] 最大値

	@return 乱数値
*/
//--------------------------------------------------------------------------------------------
Sint32 JRand::GetInt( Sint32 Min, Sint32 Max )
{
	Sint32 a = (Sint32)(GetInt32() >> 1);

	return Min + (a % (Max + 1 - Min));
}

//--------------------------------------------------------------------------------------------
/**
	指定範囲内の浮動小数点乱数を取得します。

	@param Min [in] 最小値
	@param Max [in] 最大値

	@return 乱数値
*/
//--------------------------------------------------------------------------------------------
Float JRand::GetFloat( Float Min, Float Max )
{
	Float a = GetFloat32();

	return Min + (a * (Max - Min));
}

