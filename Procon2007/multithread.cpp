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
//初期化
//===============================================
//[return]
//	bool値
//===============================================
bool CMultiThread::Initialize()
{
	m_hThread = NULL;
	m_ThreadID = 0;
	
	/*スレッドを作成*/
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StThreadProc, NULL, 0, &m_ThreadID);
	
	return true;
}
	

//===============================================
//マルチスレッド処理
//===============================================
//[input]
//	lpParam
//===============================================
LRESULT CALLBACK CMultiThread::StThreadProc(LPVOID lpParam)
{
	if( CNetWork::CServer::CreateServer() )
	{
		CNetWork::CServer::SetConnectFlag( true );
		
		/*スレッドの終了*/
		::ExitThread( 0 );
		
	}
	
	return 0;
}
