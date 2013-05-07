//*==============================================
//network.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"

#include <winsock.h>

//WinSock���g���̂ɕK�v
#pragma comment( lib, "ws2_32.lib")

//===============================================
//struct
//===============================================

//// �N���C�A���g�̎��`�[���̃f�[�^
struct TEAM
{	
	int status[MAX_CHARA];	// �X�e�[�^�X (=�̗�=�U����=�X�s�[�h)
	int special[MAX_CHARA];	// ����\�͔ԍ�
	int dowhat[MAX_CHARA];	// �s���̎�ށF0�Œʏ�U��
	int doto[MAX_CHARA];		// �ΏہF1�`5�A0�Ŗ��w��
	int protect[MAX_CHARA];	// �g���肳��Ă���t���O
	int trans[MAX_CHARA];	// �����t���O
	int done[MAX_CHARA];		// �s�������t���O
};

//�N���C�A���g���񑗐M�f�[�^
struct tagClientData_First
{
	int status[MAX_CHARA]; //�X�e�[�^�X
	bool special[MAX_CHARA]; //����\��(false:�⏕�n, true:�U���n)
	char teamname[17];//�`�[����
};

// �N���C�A���g���M�f�[�^
struct tagClientData
{				
	int dowhat[MAX_CHARA];	// �s���̎�ށF0�Œʏ�U��
	int doto  [MAX_CHARA];	// �ΏہF1�`5�A0�Ŗ��w��
};

// �T�[�o�[���񑗐M�f�[�^
struct tagServerData_First
{	
	int max_status;		// �X�e�[�^�X�̏��
};

//�T�[�o�[���M�f�[�^
struct tagServerData
{		
	int status[PLAYER_MAX][MAX_CHARA];	// �X�e�[�^�X: [0][x]�����R�A[1][x]���G�R
	int dowhat[PLAYER_MAX][MAX_CHARA];	// �s���̎�ށF0�Œʏ�U���A1�œ���\��
	int doto  [PLAYER_MAX][MAX_CHARA];	// �ΏہF1�`5�A0�Ŗ��w��
	int turn; //�^�[����
};


//===============================================
//class
//===============================================
//[Desc]
//	�l�b�g���[�N�p�N���X
//===============================================
class CNetWork
{
	public:
		//------------------------------------
		//�T�[�o�[�p�v���O����
		//------------------------------------
		class CServer
		{
			private:
			
				//static SOCKET *m_pSock;//�\�P�b�g
				//static SOCKET *m_pClientSock; //�N���C�A���g�̃\�P�b�g
				//static sockaddr_in *m_pOwnAddr; //���g�̎�t�A�h���X
				//static sockaddr_in *m_pClient; //�N���C�A���g�̎�t�A�h���X
				static SOCKET m_pSock[PLAYER_MAX];
				static SOCKET m_pClientSock[PLAYER_MAX];
				static sockaddr_in m_pOwnAddr[PLAYER_MAX];
				static sockaddr_in m_pClient[PLAYER_MAX];
				
				static bool m_IsConnected;//�ڑ�����t���O
				
				static bool m_IsClose[PLAYER_MAX];
				
			private:
			
				static tagClientData_First	m_ClientData_First[PLAYER_MAX];//����N���C�A���g�f�[�^
				static tagClientData		m_ClientData[PLAYER_MAX];//�N���C�A���g�f�[�^
				static tagServerData_First	m_ServerData_First;//����T�[�o�[�f�[�^
				static tagServerData		m_ServerData;//�T�[�o�[�f�[�^
				
			public:
			
				static void SetConnectFlag(bool flag);//�ڑ�����t���O�̐ݒ�
			
								
			public:
			
				static bool Initialize();//������
				static void Finalize();//�I������
				static bool CreateServer();//�T�[�o�[�̍쐬
				static void SendFirstData(int no);//�ŏ��̃f�[�^�̑��M
				static void	RecvFirstData(int no);//�ŏ��̃f�[�^�̎�M
				static void SendData(int no);//�f�[�^�̑��M
				static int RecvData(int no);//�f�[�^�̎�M
				
			public:
				
				static void SetPlayerToServerData(int no, CCharacter *attacker[], CCharacter *target[]);//�T�[�o�[�f�[�^�̐ݒ�
				static void SetTurnToServerData(int turn);
				static void SetClientToPlayerData(int no, CCharacter *attacker[], CCharacter *target[]);//�N���C�A���g�f�[�^�̐ݒ�
				static void SetRecvAddress(u_short port);//��t�A�h���X�̐ݒ�
				
			public:
			
				static bool GetConnectFlag();//�ڑ�����t���O
				static SOCKET GetClientSocket(int no);//�N���C�A���g�\�P�b�g�̎擾
				static tagClientData_First GetFirstClientData(int playerno);//�ŏ��̃N���C�A���g�f�[�^�̎擾
			
		};
};



