//*==============================================
//multithread.h
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
//	�}���`�X���b�h�p�N���X
//===============================================
class CMultiThread
{
	private:
		
		static HANDLE m_hThread;//�X���b�h�̃n���h��
		static DWORD  m_ThreadID;//�X���b�hID
		
	public:
	
		static bool Initialize();//������
		static LRESULT CALLBACK StThreadProc(LPVOID lpParam);//�X���b�h�����֐�
		
};