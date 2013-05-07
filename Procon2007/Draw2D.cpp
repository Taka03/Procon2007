//*==============================================
//Draw2D.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "Draw2D.h"

//===============================================
//����
//===============================================
void CDraw2DInit::Exec()
{
	Joker::GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	
	Joker::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	
}

//===============================================
//����
//===============================================
void CDraw2DEnd::Exec()
{
	Joker::GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	Joker::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	

}



