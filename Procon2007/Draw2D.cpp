//*==============================================
//Draw2D.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "Draw2D.h"

//===============================================
//ˆ—
//===============================================
void CDraw2DInit::Exec()
{
	Joker::GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	
	Joker::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	
}

//===============================================
//ˆ—
//===============================================
void CDraw2DEnd::Exec()
{
	Joker::GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	Joker::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	

}



