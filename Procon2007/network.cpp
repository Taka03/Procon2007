//*==============================================
//network.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "network.h"
#include "debug.h"

//===============================================
//variable
//===============================================
SOCKET CNetWork::CServer::m_pSock[PLAYER_MAX];
SOCKET CNetWork::CServer::m_pClientSock[PLAYER_MAX];
sockaddr_in CNetWork::CServer::m_pOwnAddr[PLAYER_MAX];
sockaddr_in CNetWork::CServer::m_pClient[PLAYER_MAX];

bool CNetWork::CServer::m_IsConnected = false;

tagClientData_First CNetWork::CServer::m_ClientData_First[PLAYER_MAX];
tagClientData		CNetWork::CServer::m_ClientData[PLAYER_MAX];
tagServerData_First	CNetWork::CServer::m_ServerData_First;
tagServerData		CNetWork::CServer::m_ServerData;

//===============================================
//初期化処理
//===============================================
bool CNetWork::CServer::Initialize()
{
	/*サーバーの作成*/
	if( !( CreateServer() ) )
	{
		return false;
	}
	
	return true;
}

//===============================================
//終了処理
//===============================================
void CNetWork::CServer::Finalize()
{
	/*接続を閉じる*/
	for( int i = 0;i < PLAYER_MAX;i++ )	
	{
		if( m_pClientSock[i] != INVALID_SOCKET )
		{
			closesocket( m_pClientSock[i] );
		}
	}
	
	/*終了処理*/
	WSACleanup();
}

//===============================================
//サーバーの作成
//===============================================
//[return]
//	サーバーの作成に成功したかどうか
//===============================================
bool CNetWork::CServer::CreateServer()
{
	m_IsConnected = false;
	
	WSADATA wsaData;
	
	int client_addr[PLAYER_MAX] = { sizeof(SOCKADDR) };
	
	/*開始処理*/
	if( WSAStartup( MAKEWORD(2, 0), &wsaData ) != 0)
	{
		return false;
	}
	
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		client_addr[i] = sizeof(SOCKADDR);
		
		memset( &m_pOwnAddr[i], 0, sizeof( sockaddr_in ) );
		m_pOwnAddr[i].sin_family			= AF_INET;
		m_pOwnAddr[i].sin_addr.S_un.S_addr  = INADDR_ANY;
		m_pOwnAddr[i].sin_port				= htons( 10000 ); //ポート番号を設定
		
		/*ソケットを作成*/
		m_pSock[i] = socket( AF_INET, SOCK_STREAM, 0 ) ;
		
		/*例外処理*/
		if( m_pSock[i] == INVALID_SOCKET )
		{
			MESSAGE("ソケットが作成できません");
			return false;
		}
		
		/*待ち受けソケットの作成*/
		int IdleSock = bind(m_pSock[i], (struct sockaddr *)(&m_pOwnAddr[i]), sizeof( m_pOwnAddr[i]) );
		
		if(IdleSock != 0)
		{
			MESSAGE("待ちうけソケットの作成に失敗");
			return false;
		}
		
		const int MAX_CONNECT = 5;//最大接続数
		
		/*待ち行列の作成*/
		if( listen( m_pSock[i], MAX_CONNECT) != 0 )
		{
			//char Temp[MAX_PATH] = "";
//			vsprintf(Temp ,"%dの接続に失敗", i);
			MESSAGE("接続に失敗");
			return false;
		}
		
		//CDebug::DrawString("%d番目の接続を待っています", i);
		
		/*待機中のソケットで接続されるのを待つ*/
		for(;;)
		{
			m_pClientSock[i] = accept( m_pSock[i], (struct sockaddr *)(&m_pClient[i]), &client_addr[i] );
			
			if(m_pClientSock[i] != INVALID_SOCKET)
			{
				break;
			}
			
			Sleep(100);
			
		}
		
		int port = 10001 + i;
		
		send( m_pClientSock[i], (const char*)(&port), sizeof(int), 0 );
		
		/*接続を閉じる*/
		closesocket( m_pSock[i] );
		closesocket( m_pClientSock[i] );
		
		/*新しいポートを使ってクライアントからの接続を待つ*/
		client_addr[i] = sizeof(SOCKADDR);
		
		memset( &m_pOwnAddr, 0, sizeof( sockaddr_in ) );
		
		m_pOwnAddr[i].sin_family = AF_INET;
		m_pOwnAddr[i].sin_addr.S_un.S_addr = INADDR_ANY;
		m_pOwnAddr[i].sin_port = htons( port );
		
		/*ソケットを作成*/
		m_pSock[i] = socket( AF_INET, SOCK_STREAM, 0 ) ;
		
		/*例外処理*/
		if( m_pSock[i] == INVALID_SOCKET )
		{
			MESSAGE("ソケットが作成できません");
			return false;
		}
		
		/*待ち受けソケットの作成*/
		IdleSock = bind(m_pSock[i], (struct sockaddr *)(&m_pOwnAddr[i]), sizeof( m_pOwnAddr[i]) );
		
		if(IdleSock != 0)
		{
			MESSAGE("待ちうけソケットの作成に失敗");
			return false;
		}
		
		/*待ち行列の作成*/
		if( listen( m_pSock[i], MAX_CONNECT) != 0 )
		{
			//char Temp[MAX_PATH] = "";
//			vsprintf(Temp ,"%dの接続に失敗", i);
			MESSAGE("接続に失敗");
			return false;
		}
		
		/*待機中のソケットで接続されるのを待つ*/
		for(;;)
		{
			m_pClientSock[i] = accept( m_pSock[i], (struct sockaddr *)(&m_pClient[i]), &client_addr[i] ) ;
			
			if(m_pClientSock[i] != INVALID_SOCKET)
			{
				break;
			}
			
			Sleep(100);
		}
		
		SendFirstData(i);
		
	}		
	
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		int Recv = recv( m_pClientSock[i], (char *)(&m_ClientData_First[i]), sizeof( tagClientData_First ), 0 );
			
		/*パケットが受け取れないとき*/
		if(Recv == 0)
		{
			break;
		}	
	}
			
	return true;	
}

//===============================================
//サーバーデータの設定
//===============================================
//[input]
//	no:プレイヤー番号
//	attacker:攻撃者
//	target:対象
//	turn:ターン数
//===============================================
void CNetWork::CServer::SetPlayerToServerData(int no, CCharacter *attacker[], CCharacter *target[])
{
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		
		switch(attacker[i]->GetTarget()->GetCharaType() )
		{
			/*剣士*/
			case FENCER:
			{
				m_ServerData.doto[no][i] = FENCER;
				break;
			}
			
			/*魔法使い*/
			case MAGICIAN:
			{
				m_ServerData.doto[no][i] = MAGICIAN;
				break;
			}
			
			/*レンジャー*/
			case RANGER:
			{
				m_ServerData.doto[no][i] = RANGER;
				break;
			}
			
			/*契約者*/
			case CONTRACTOR:
			{
				m_ServerData.doto[no][i] = CONTRACTOR;
				break;
			}
			
			/*守護騎士*/
			case GUARDIAN:
			{
				m_ServerData.doto[no][i] = GUARDIAN;
				break;
			}
		}
		
		m_ServerData.dowhat[no][i] = attacker[i]->GetAttackType();
		
		m_ServerData.status[PLAYER_1][i] = attacker[i]->GetStatus();
		m_ServerData.status[PLAYER_2][i] = target[i]->GetStatus();

	}
	
}

//===============================================
//サーバーのターンの設定
//===============================================
//[input]
//
//[return]
//
//===============================================
void CNetWork::CServer::SetTurnToServerData(int turn)
{
	m_ServerData.turn = turn;
}

//===============================================
//クライアントデータの設定
//===============================================
//[input]
//	no:プレイヤー番号
//	attacker:攻撃者
//	target:対象
//===============================================
void CNetWork::CServer::SetClientToPlayerData(int no, CCharacter *attacker[], CCharacter *target[])
{
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		/*攻撃タイプの設定*/
		attacker[i]->SetAttackType_AI(m_ClientData[no].dowhat[i]);
		
		if( attacker[i]->GetAttackType() == SPECIAL )
		{
			switch(attacker[i]->GetSpecial() )
			{
				case CRITICAL:
				{

				}
				
				case ALLMAGIC:
				{

				}
				
				case FIRST_ATTACK:
				{
					attacker[i]->SetTarget(target[m_ClientData[no].doto[i] ] );
					break;				
				
				}
				
				case BURST:
				{
					attacker[i]->SetTarget(target[m_ClientData[no].doto[i] ] );
					break;
					
				}
				
				case CHARGE_ATTACK:
				{
					attacker[i]->SetTarget(target[m_ClientData[no].doto[i] ] );
					
					break;
				}
				
				case ALTER:
				{
					attacker[i]->SetTarget(attacker[m_ClientData[no].doto[i] ] );
					
					break;
				}
				
				case RECOVER:
				{
					attacker[i]->SetTarget(attacker[m_ClientData[no].doto[i] ] );
					
					break;
				
				}
				
				case BUILDUP:
				{
					attacker[i]->SetTarget(attacker[m_ClientData[no].doto[i] ] );
					
					break;
				
				}
				
				case GUARD:
				{
					attacker[i]->SetTarget(target[m_ClientData[no].doto[i] ] );
					break;
				}
				
				case COUNTER:
				{
					attacker[i]->SetTarget(target[ m_ClientData[no].doto[i] ] );
					break;
				}
			}
		}
		
		else
		{
			attacker[i]->SetTarget(target[m_ClientData[no].doto[i] ] );
		}
			
		//switch(m_ClientData[no].doto[i])
		//{
		//	/*剣士*/
		//	case FENCER:
		//	{
		//		if( attacker[i]->GetAttackType() == SPECIAL )
		//		{
		//			if( attacker[i]->GetSpecial() == CRITICAL)
		//			{
		//				attacker[i]->SetTarget( target[FENCER] );
		//			}
		//			
		//			else if( attacker[i]->GetSpecial() == ALTER )
		//			{
		//				
		//			}
		//			
		//			else
		//			{
		//				attacker[i]->SetTarget( attacker[FENCER] );
		//			}
		//		}
		//		
		//		else
		//		{
		//			attacker[i]->SetTarget( target[FENCER] );
		//		}
		//		
		//		break;
		//	}
		//	
		//	/*魔法使い*/
		//	case MAGICIAN:
		//	{
		//		if( attacker[i]->GetAttackType() == SPECIAL )
		//		{
		//			if( attacker[i]->GetSpecial() == ALLMAGIC)
		//			{
		//				attacker[i]->SetTarget( target[MAGICIAN );
		//			}
		//			
		//			else
		//			{
		//				attacker[i]->SetTarget( attacker[MAGICIAN] );
		//			}
		//		}
		//		
		//		else
		//		{
		//			attacker[i]->SetTarget( target[MAGICIAN] );
		//		}
		//		break;
		//	}
		//	
		//	/*レンジャー*/
		//	case RANGER:
		//	{
		//		attacker[i]->SetTarget( target[RANGER] );
		//		break;
		//	}
		//	
		//	/*契約者*/
		//	case CONTRACTOR:
		//	{
		//		attacker[i]->SetTarget( target[CONTRACTOR] );
		//		break;
		//	}
		//	
		//	/*守護騎士*/
		//	case GUARDIAN:
		//	{
		//		attacker[i]->SetTarget( target[GUARDIAN] );
		//		break;
		//	}
		//	
		//}
	}		
}



//===============================================
//受付アドレスの設定
//===============================================
//[input]
//	port:ポート番号
//===============================================
void CNetWork::CServer::SetRecvAddress(u_short port)
{
}

//===============================================
//初期データの送信
//===============================================
//[input]
//	no:プレイヤー番号
//===============================================
void CNetWork::CServer::SendFirstData(int no)
{
	/*初回情報送信*/
	m_ServerData_First.max_status = MAX_STATUS;
	
	send( m_pClientSock[no], (char *)(&m_ServerData_First), sizeof( tagServerData_First ), 0 );
		
}

//===============================================
//初期データの受信
//===============================================
//[input]
//	no:プレイヤー番号
//===============================================
void CNetWork::CServer::RecvFirstData(int no)
{
	int Recv = recv( m_pClientSock[no], (char *)(&m_ClientData_First[no]), sizeof( tagClientData_First ), 0 );
		
	/*パケットが受け取れないとき*/
	if(Recv == 0)
	{
//		break;
	}
			
}

//===============================================
//データの送信
//===============================================
//[input]
//	no:プレイヤー番号
//===============================================
void CNetWork::CServer::SendData(int no)
{
	send(m_pClientSock[no], (char *)( &m_ServerData ), sizeof( tagServerData ), 0);
}

//===============================================
//データの受信
//===============================================
//[input]
//	no:プレイヤー番号
//[return]
//	受信するクライアントパケット
//===============================================
int CNetWork::CServer::RecvData(int no)
{
	return recv( m_pClientSock[no], (char *)( &m_ClientData[no]), sizeof( tagClientData ), 0 );
}

//===============================================
//接続判定フラグの設定
//===============================================
//[input]
//	flag:フラグ
//===============================================
void CNetWork::CServer::SetConnectFlag(bool flag)
{
	m_IsConnected = flag;
}

//===============================================
//接続判定フラグの取得
//===============================================
//[return]
//	接続判定フラグ
//===============================================
bool CNetWork::CServer::GetConnectFlag()
{
	return m_IsConnected;
}

//=============================================================================
//初期クライアントデータの取得
//=============================================================================
//[input]
//	playerno:プレイヤー番号
//[return]
//	初期クライアントデータ
//=============================================================================
tagClientData_First CNetWork::CServer::GetFirstClientData(int playerno)
{
	return m_ClientData_First[playerno];	
}


//===============================================
//クライアントソケットの取得
//===============================================
//[input]
//	no:ソケット番号
//[return]
//	クライアントのソケット
//===============================================
SOCKET CNetWork::CServer::GetClientSocket(int no)
{
	return m_pClientSock[no];
}
