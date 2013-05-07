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
//����������
//===============================================
bool CNetWork::CServer::Initialize()
{
	/*�T�[�o�[�̍쐬*/
	if( !( CreateServer() ) )
	{
		return false;
	}
	
	return true;
}

//===============================================
//�I������
//===============================================
void CNetWork::CServer::Finalize()
{
	/*�ڑ������*/
	for( int i = 0;i < PLAYER_MAX;i++ )	
	{
		if( m_pClientSock[i] != INVALID_SOCKET )
		{
			closesocket( m_pClientSock[i] );
		}
	}
	
	/*�I������*/
	WSACleanup();
}

//===============================================
//�T�[�o�[�̍쐬
//===============================================
//[return]
//	�T�[�o�[�̍쐬�ɐ����������ǂ���
//===============================================
bool CNetWork::CServer::CreateServer()
{
	m_IsConnected = false;
	
	WSADATA wsaData;
	
	int client_addr[PLAYER_MAX] = { sizeof(SOCKADDR) };
	
	/*�J�n����*/
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
		m_pOwnAddr[i].sin_port				= htons( 10000 ); //�|�[�g�ԍ���ݒ�
		
		/*�\�P�b�g���쐬*/
		m_pSock[i] = socket( AF_INET, SOCK_STREAM, 0 ) ;
		
		/*��O����*/
		if( m_pSock[i] == INVALID_SOCKET )
		{
			MESSAGE("�\�P�b�g���쐬�ł��܂���");
			return false;
		}
		
		/*�҂��󂯃\�P�b�g�̍쐬*/
		int IdleSock = bind(m_pSock[i], (struct sockaddr *)(&m_pOwnAddr[i]), sizeof( m_pOwnAddr[i]) );
		
		if(IdleSock != 0)
		{
			MESSAGE("�҂������\�P�b�g�̍쐬�Ɏ��s");
			return false;
		}
		
		const int MAX_CONNECT = 5;//�ő�ڑ���
		
		/*�҂��s��̍쐬*/
		if( listen( m_pSock[i], MAX_CONNECT) != 0 )
		{
			//char Temp[MAX_PATH] = "";
//			vsprintf(Temp ,"%d�̐ڑ��Ɏ��s", i);
			MESSAGE("�ڑ��Ɏ��s");
			return false;
		}
		
		//CDebug::DrawString("%d�Ԗڂ̐ڑ���҂��Ă��܂�", i);
		
		/*�ҋ@���̃\�P�b�g�Őڑ������̂�҂�*/
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
		
		/*�ڑ������*/
		closesocket( m_pSock[i] );
		closesocket( m_pClientSock[i] );
		
		/*�V�����|�[�g���g���ăN���C�A���g����̐ڑ���҂�*/
		client_addr[i] = sizeof(SOCKADDR);
		
		memset( &m_pOwnAddr, 0, sizeof( sockaddr_in ) );
		
		m_pOwnAddr[i].sin_family = AF_INET;
		m_pOwnAddr[i].sin_addr.S_un.S_addr = INADDR_ANY;
		m_pOwnAddr[i].sin_port = htons( port );
		
		/*�\�P�b�g���쐬*/
		m_pSock[i] = socket( AF_INET, SOCK_STREAM, 0 ) ;
		
		/*��O����*/
		if( m_pSock[i] == INVALID_SOCKET )
		{
			MESSAGE("�\�P�b�g���쐬�ł��܂���");
			return false;
		}
		
		/*�҂��󂯃\�P�b�g�̍쐬*/
		IdleSock = bind(m_pSock[i], (struct sockaddr *)(&m_pOwnAddr[i]), sizeof( m_pOwnAddr[i]) );
		
		if(IdleSock != 0)
		{
			MESSAGE("�҂������\�P�b�g�̍쐬�Ɏ��s");
			return false;
		}
		
		/*�҂��s��̍쐬*/
		if( listen( m_pSock[i], MAX_CONNECT) != 0 )
		{
			//char Temp[MAX_PATH] = "";
//			vsprintf(Temp ,"%d�̐ڑ��Ɏ��s", i);
			MESSAGE("�ڑ��Ɏ��s");
			return false;
		}
		
		/*�ҋ@���̃\�P�b�g�Őڑ������̂�҂�*/
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
			
		/*�p�P�b�g���󂯎��Ȃ��Ƃ�*/
		if(Recv == 0)
		{
			break;
		}	
	}
			
	return true;	
}

//===============================================
//�T�[�o�[�f�[�^�̐ݒ�
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//	attacker:�U����
//	target:�Ώ�
//	turn:�^�[����
//===============================================
void CNetWork::CServer::SetPlayerToServerData(int no, CCharacter *attacker[], CCharacter *target[])
{
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		
		switch(attacker[i]->GetTarget()->GetCharaType() )
		{
			/*���m*/
			case FENCER:
			{
				m_ServerData.doto[no][i] = FENCER;
				break;
			}
			
			/*���@�g��*/
			case MAGICIAN:
			{
				m_ServerData.doto[no][i] = MAGICIAN;
				break;
			}
			
			/*�����W���[*/
			case RANGER:
			{
				m_ServerData.doto[no][i] = RANGER;
				break;
			}
			
			/*�_���*/
			case CONTRACTOR:
			{
				m_ServerData.doto[no][i] = CONTRACTOR;
				break;
			}
			
			/*���R�m*/
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
//�T�[�o�[�̃^�[���̐ݒ�
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
//�N���C�A���g�f�[�^�̐ݒ�
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//	attacker:�U����
//	target:�Ώ�
//===============================================
void CNetWork::CServer::SetClientToPlayerData(int no, CCharacter *attacker[], CCharacter *target[])
{
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		/*�U���^�C�v�̐ݒ�*/
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
		//	/*���m*/
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
		//	/*���@�g��*/
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
		//	/*�����W���[*/
		//	case RANGER:
		//	{
		//		attacker[i]->SetTarget( target[RANGER] );
		//		break;
		//	}
		//	
		//	/*�_���*/
		//	case CONTRACTOR:
		//	{
		//		attacker[i]->SetTarget( target[CONTRACTOR] );
		//		break;
		//	}
		//	
		//	/*���R�m*/
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
//��t�A�h���X�̐ݒ�
//===============================================
//[input]
//	port:�|�[�g�ԍ�
//===============================================
void CNetWork::CServer::SetRecvAddress(u_short port)
{
}

//===============================================
//�����f�[�^�̑��M
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//===============================================
void CNetWork::CServer::SendFirstData(int no)
{
	/*�����񑗐M*/
	m_ServerData_First.max_status = MAX_STATUS;
	
	send( m_pClientSock[no], (char *)(&m_ServerData_First), sizeof( tagServerData_First ), 0 );
		
}

//===============================================
//�����f�[�^�̎�M
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//===============================================
void CNetWork::CServer::RecvFirstData(int no)
{
	int Recv = recv( m_pClientSock[no], (char *)(&m_ClientData_First[no]), sizeof( tagClientData_First ), 0 );
		
	/*�p�P�b�g���󂯎��Ȃ��Ƃ�*/
	if(Recv == 0)
	{
//		break;
	}
			
}

//===============================================
//�f�[�^�̑��M
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//===============================================
void CNetWork::CServer::SendData(int no)
{
	send(m_pClientSock[no], (char *)( &m_ServerData ), sizeof( tagServerData ), 0);
}

//===============================================
//�f�[�^�̎�M
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//[return]
//	��M����N���C�A���g�p�P�b�g
//===============================================
int CNetWork::CServer::RecvData(int no)
{
	return recv( m_pClientSock[no], (char *)( &m_ClientData[no]), sizeof( tagClientData ), 0 );
}

//===============================================
//�ڑ�����t���O�̐ݒ�
//===============================================
//[input]
//	flag:�t���O
//===============================================
void CNetWork::CServer::SetConnectFlag(bool flag)
{
	m_IsConnected = flag;
}

//===============================================
//�ڑ�����t���O�̎擾
//===============================================
//[return]
//	�ڑ�����t���O
//===============================================
bool CNetWork::CServer::GetConnectFlag()
{
	return m_IsConnected;
}

//=============================================================================
//�����N���C�A���g�f�[�^�̎擾
//=============================================================================
//[input]
//	playerno:�v���C���[�ԍ�
//[return]
//	�����N���C�A���g�f�[�^
//=============================================================================
tagClientData_First CNetWork::CServer::GetFirstClientData(int playerno)
{
	return m_ClientData_First[playerno];	
}


//===============================================
//�N���C�A���g�\�P�b�g�̎擾
//===============================================
//[input]
//	no:�\�P�b�g�ԍ�
//[return]
//	�N���C�A���g�̃\�P�b�g
//===============================================
SOCKET CNetWork::CServer::GetClientSocket(int no)
{
	return m_pClientSock[no];
}
