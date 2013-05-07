//*==============================================
//network.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"

#include <winsock.h>

//WinSockを使うのに必要
#pragma comment( lib, "ws2_32.lib")

//===============================================
//struct
//===============================================

//// クライアントの持つチームのデータ
struct TEAM
{	
	int status[MAX_CHARA];	// ステータス (=体力=攻撃力=スピード)
	int special[MAX_CHARA];	// 特殊能力番号
	int dowhat[MAX_CHARA];	// 行動の種類：0で通常攻撃
	int doto[MAX_CHARA];		// 対象：1～5、0で無指定
	int protect[MAX_CHARA];	// 身代わりされているフラグ
	int trans[MAX_CHARA];	// 強化フラグ
	int done[MAX_CHARA];		// 行動完了フラグ
};

//クライアント初回送信データ
struct tagClientData_First
{
	int status[MAX_CHARA]; //ステータス
	bool special[MAX_CHARA]; //特殊能力(false:補助系, true:攻撃系)
	char teamname[17];//チーム名
};

// クライアント送信データ
struct tagClientData
{				
	int dowhat[MAX_CHARA];	// 行動の種類：0で通常攻撃
	int doto  [MAX_CHARA];	// 対象：1～5、0で無指定
};

// サーバー初回送信データ
struct tagServerData_First
{	
	int max_status;		// ステータスの上限
};

//サーバー送信データ
struct tagServerData
{		
	int status[PLAYER_MAX][MAX_CHARA];	// ステータス: [0][x]が自軍、[1][x]が敵軍
	int dowhat[PLAYER_MAX][MAX_CHARA];	// 行動の種類：0で通常攻撃、1で特殊能力
	int doto  [PLAYER_MAX][MAX_CHARA];	// 対象：1～5、0で無指定
	int turn; //ターン数
};


//===============================================
//class
//===============================================
//[Desc]
//	ネットワーク用クラス
//===============================================
class CNetWork
{
	public:
		//------------------------------------
		//サーバー用プログラム
		//------------------------------------
		class CServer
		{
			private:
			
				//static SOCKET *m_pSock;//ソケット
				//static SOCKET *m_pClientSock; //クライアントのソケット
				//static sockaddr_in *m_pOwnAddr; //自身の受付アドレス
				//static sockaddr_in *m_pClient; //クライアントの受付アドレス
				static SOCKET m_pSock[PLAYER_MAX];
				static SOCKET m_pClientSock[PLAYER_MAX];
				static sockaddr_in m_pOwnAddr[PLAYER_MAX];
				static sockaddr_in m_pClient[PLAYER_MAX];
				
				static bool m_IsConnected;//接続判定フラグ
				
				static bool m_IsClose[PLAYER_MAX];
				
			private:
			
				static tagClientData_First	m_ClientData_First[PLAYER_MAX];//初回クライアントデータ
				static tagClientData		m_ClientData[PLAYER_MAX];//クライアントデータ
				static tagServerData_First	m_ServerData_First;//初回サーバーデータ
				static tagServerData		m_ServerData;//サーバーデータ
				
			public:
			
				static void SetConnectFlag(bool flag);//接続判定フラグの設定
			
								
			public:
			
				static bool Initialize();//初期化
				static void Finalize();//終了処理
				static bool CreateServer();//サーバーの作成
				static void SendFirstData(int no);//最初のデータの送信
				static void	RecvFirstData(int no);//最初のデータの受信
				static void SendData(int no);//データの送信
				static int RecvData(int no);//データの受信
				
			public:
				
				static void SetPlayerToServerData(int no, CCharacter *attacker[], CCharacter *target[]);//サーバーデータの設定
				static void SetTurnToServerData(int turn);
				static void SetClientToPlayerData(int no, CCharacter *attacker[], CCharacter *target[]);//クライアントデータの設定
				static void SetRecvAddress(u_short port);//受付アドレスの設定
				
			public:
			
				static bool GetConnectFlag();//接続判定フラグ
				static SOCKET GetClientSocket(int no);//クライアントソケットの取得
				static tagClientData_First GetFirstClientData(int playerno);//最初のクライアントデータの取得
			
		};
};



