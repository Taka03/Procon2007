//*==============================================
//multithread.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "multithread.h"
#include "network.h"

//===============================================
//variable
//===============================================
HANDLE CMultiThread::m_hThread = NULL;
DWORD CMultiThread::m_ThreadID = 0;

//===============================================
//������
//===============================================
//[return]
//	bool�l
//===============================================
bool CMultiThread::Initialize()
{
	m_hThread = NULL;
	m_ThreadID = 0;
	
	/*�X���b�h���쐬*/
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StThreadProc, NULL, 0, &m_ThreadID);
	
	return true;
}
	

//===============================================
//�}���`�X���b�h����
//===============================================
//[input]
//	lpParam
//===============================================
LRESULT CALLBACK CMultiThread::StThreadProc(LPVOID lpParam)
{
	if( CNetWork::CServer::CreateServer() )
	{
		CNetWork::CServer::SetConnectFlag( true );
		
		/*�X���b�h�̏I��*/
		::ExitThread( 0 );
		
	}
	
	return 0;
}
