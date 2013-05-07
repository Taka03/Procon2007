//*==============================================
//scenemanager.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "scenemanager.h"
#include "multithread.h"

#include "gamemain.h"
#include "font.h"
#include "CXModel.h"
#include "joypad.h"
#include "light.h"
#include "fencer.h"
#include "magician.h"
#include "ranger.h"
#include "contractor.h"
#include "guardian.h"
#include "debug.h"
#include "charafactory.h"
#include "TextureFactory.h"
#include "rand.h"

#include <vector>
#include <algorithm>
#include <set>
#include <queue>

//===============================================
//variable
//===============================================
int g_Turn = 0;//ターン数

//===============================================
//コンストラクタ
//===============================================
CSceneManager::CSceneManager()
{
	m_IsAnalog = false;
	
	m_IsZKey = true;
	
	cam = new CCamera();
	//battlecam = new CCamera();
	
//	m_pGrpSys = new CSystem();
	
	if(m_IsAnalog)
	{
		for( int i = 0;i < PLAYER_MAX;i++ )
		{
			cursor[i] = new CCursor();
		}
	}
	
	m_IsBattle = false;
	
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		m_IsWin[i] = false;
	}
	
	FadeCount = 0;
	
	m_itr = m_liOrder.begin();
	
	m_BeforeScene = SCENE_INIT;
	m_CurrentScene = SCENE_INIT;
	m_NextScene = SCENE_INIT;
	
	m_IsAppend = false;
	
}

//===============================================
//初期化
//===============================================
void CSceneManager::Initialize()
{
	m_IsAppend = false;
	
	
	
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		m_IsWin[i] = false;
	}
	
	
	field = new CField();
	
	field->Init();
	
	grpLoading = CTextureFactory::Create(GRP_LOADING);
	
	cam->Init();
	
	g_Turn = 0;
	
	if(Joker::GetDevice() == NULL)
	{
		MessageBox(NULL, "pD3DDeviceが見つからない", "Base", MB_OK | MB_ICONSTOP);
	}
	
	/*レンダリング状態のセット*/
	Joker3D::SetRenderState();
	
	/*ビューポートの設定*/
	Joker3D::SetViewPort();
	
	/*マルチスレッドの初期化*/
	if(!m_IsAnalog)
	{
		CMultiThread::Initialize();
		
		CNetWork::CServer::SetConnectFlag( false );
		
	}
	
	static int total_status[PLAYER_MAX] = {0};//ステータスの合計値
	
	/*キャラクターデータの生成*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i] = CCharaFactory::Create( (eCharaType)i, PLAYER_1 );
		pl2_model[i] = CCharaFactory::Create( (eCharaType)i, PLAYER_2 ); 
		//temp_model1[i] = CCharaFactory::Create( (eCharaType)i, PLAYER_1 );
		//temp_model2[i] = CCharaFactory::Create( (eCharaType)i, PLAYER_2 );
	}
	
	//----------------------------------------------------------------------------
	//システムグラフィック
	//----------------------------------------------------------------------------
	
	/*ステータスの生成*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		Status1[i] = CTextureFactory::Create(GRP_HP1);
		Status2[i] = CTextureFactory::Create(GRP_HP2);
		numStatus1[i] = CTextureFactory::Create(GRP_NUMBER);
		numStatus2[i] = CTextureFactory::Create(GRP_NUMBER);
	}
	
	/*ステータスの文字*/
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		capHp[i] = CTextureFactory::Create(CAP_HP);
	}
	
	for( int i = 0;i < CAP_MAX;i++ )
	{
		caption[i] = CTextureFactory::Create( (eCaption)(i) );
	}
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		icon[i] = CTextureFactory::Create(GRP_ICON);//CTextureFactory::Create(GRP_ICON);
		charaIcon[i] = CTextureFactory::Create(GRP_ICON);
	}
	
	grpLargeTurn = CTextureFactory::Create(GRP_LARGETURN);
	numLargeTurn = CTextureFactory::Create(GRP_LARGENUMBER);
	
	for( int i = 0;i < SPTYPE_MAX;i++ )
	{
		grpSpecial[i] = CTextureFactory::Create( (eCaption)(11 + i) );
	}
	
	for( int i = 0;i < RESULT_MAX;i++ )
	{
		grpResult[i] = CTextureFactory::Create( (eCaption)(13 + i) );
	}
	
	numTurn = new CFont(30, "Inalphabet");//CTextureFactory::Create(GRP_NUMBER);

	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		TeamName[i] = new CFont(20, "Inalphabet");//(50, "tahoma");
	}
	
	//----------------------------------------------------------------------------
	//サウンドデータ
	//----------------------------------------------------------------------------
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i]->LoadSe();
		pl2_model[i]->LoadSe();
	}
	
	bgm = new CSound("data/BGM.ogg");
	
	//----------------------------------------------------------------------------
	//モデルデータの設定
	//----------------------------------------------------------------------------
	
	/*アナログの場合*/
	if(m_IsAnalog)
	{
		/*ステータスのセット*/
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			pl1_model[i]->SetStatus(1000 + i * 100);
			pl2_model[i]->SetStatus(1000 + i * 200);
		}
	}
	
	/*合計ステータスの計算*/
	for( int i = 0;i < MAX_CHARA;i++ ) 
	{
		total_status[PLAYER_1] += pl1_model[i]->GetStatus();
		total_status[PLAYER_2] += pl2_model[i]->GetStatus();
	}
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i]->SetPosition( -2, 0, (float)(i*2) );
		pl1_model[i]->SetRotate( GET_ANGLE(45), 0, 0 );
		pl2_model[i]->SetPosition(  2, 0, (float)(i*2) );
		pl2_model[i]->SetRotate( GET_ANGLE(-45), 0, 0 );
	}
	
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		TeamName[i]->SetPosition(F(i*420 + 40), 525);
	}
	
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		model[i] = pl1_model[i];
		model[i+5] = pl2_model[i];
	}
	
	/*カーソルの初期位置をセット*/
	if(m_IsAnalog)
	{
		cursor[PLAYER_1]->SetCursor( PLAYER_1, pl2_model[FENCER] );
		cursor[PLAYER_2]->SetCursor( PLAYER_2, pl1_model[FENCER] );
	}
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i]->SetDeadFlag( false );
		pl1_model[i]->SetEndFlag( false );
		pl2_model[i]->SetDeadFlag( false );
		pl2_model[i]->SetEndFlag( false );
		//temp_model1[i]->SetDeadFlag( false );
		//temp_model2[i]->SetDeadFlag( false );
		//temp_model1[i]->SetEndFlag( false );
		//temp_model2[i]->SetEndFlag( false );
	}
	
	
	//----------------------------------------------------------------------------
	//オブジェクトの追加
	//----------------------------------------------------------------------------
	
	/*次のシーンのセット*/
	if(m_IsAnalog)
	{
		SetNextScene(SCENE_CHOOSESPECIAL);
	}
	
	else
	{
		SetNextScene(SCENE_WAIT);
	}
	
	/*描画の開始*/
	Joker3D::BeginScene();
	
	Joker3D::EndScene();
	
	/*次のシーンに移動*/
	MoveNextScene();
	
}

//===============================================
//AI待ち画面
//===============================================
void CSceneManager::WaitAI()
{
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		icon[i]->SetPosition( F(525 + i * 50), 0 );
		icon[i]->SetPlayerType(PLAYER_1);
		icon[i+5]->SetPosition( F(525 + i * 50), 50 );
		icon[i+5]->SetPlayerType(PLAYER_2);
	}
	
	
	
	/*2つのモデルを連結する*/
	for(int i = 0;i < MAX_CHARA;i++ )
	{
		model[i] = pl1_model[i];
		model[i + 5] = pl2_model[i];
	}
	
	SetNextScene(SCENE_CHOOSECHARA);
	
	Joker3D::BeginScene();
	
	grpLoading->Exec();
	
	Joker3D::EndScene();
	
	//bgm = new CSound("data/swordman_attack.wav");
	
	//bgm->Stop();
	
	if( CNetWork::CServer::GetConnectFlag() )
	{
		/*受信データの設定*/
		for(int i = 0;i < MAX_CHARA;i++ )
		{
			pl1_model[i]->SetStatus( CNetWork::CServer::GetFirstClientData(PLAYER_1).status[i] );
			
			pl2_model[i]->SetStatus( CNetWork::CServer::GetFirstClientData(PLAYER_2).status[i] );
			
			pl1_model[i]->SetSpecialType_AI( CNetWork::CServer::GetFirstClientData(PLAYER_1).special[i] );
			pl2_model[i]->SetSpecialType_AI( CNetWork::CServer::GetFirstClientData(PLAYER_2).special[i] );
			
		}
		
		bgm->Play(SND_BGM, 1, 0);
		
		MoveNextScene();
	}
}

//===============================================
//特殊能力選択画面
//===============================================
void CSceneManager::ChooseSpecial()
{
	static int next = 0;
	static int next2 = 0;

	if(m_IsAnalog)
	{
		pl1_model[next]->SetSpecialType(PLAYER_1);
		pl2_model[next2]->SetSpecialType(PLAYER_2);
	
		if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
		{
			next++;
		}
		
		if(CJoyPad::GetState(1, PAD_STATE_PUSH, PAD_BUTTON_01) )
		{
			next2++;
		}
	}
	
	SetNextScene(SCENE_CHOOSECHARA);
	
	/*特殊能力の設定*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i]->SetAbility();
		pl2_model[i]->SetAbility();
	}
	
	if(next == MAX_CHARA - 1 && next2 == MAX_CHARA - 1)
	{
		next = 0;
		next2 = 0;
		MoveNextScene();
	}
	
	if( next >= MAX_CHARA )
	{
		next = MAX_CHARA - 1;
	}
	
	if( next2 >= MAX_CHARA )
	{
		next2 = MAX_CHARA - 1;	
	}
	
	Joker3D::BeginScene();
	
	Joker3D::EndScene();
	
	CDebug::DrawString( "p1[%s]Type:%d", pl1_model[next]->GetName().data(), pl1_model[next]->GetSpecialType() );
	CDebug::DrawString( "p2[%s]Type:%d", pl2_model[next2]->GetName().data(), pl2_model[next2]->GetSpecialType() );
	
}

//===============================================
//キャラクター選択画面
//===============================================
void CSceneManager::ChooseChara()
{
	//----------------------------------------------
	//ブレンドモードの設定
	//----------------------------------------------
	Joker::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Joker::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	
	numLargeTurn->SetPosition(grpLargeTurn->GetPosition().x + 370, grpLargeTurn->GetPosition().y + 100);
	
	
	/*特殊能力の設定*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i]->SetAbility();
		pl2_model[i]->SetAbility();
	}
	
	/*チーム名の設定*/
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		char *Buff = "";
		
		Buff = CNetWork::CServer::GetFirstClientData(i).teamname;
		
		string Str = Buff;
		
		TeamName[i]->SetText(Str);
	}
	
	
	/*座標の設定*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		float charaZPos[MAX_CHARA] = {8, 5, 2, -1, -3 };
		float fontXPos[MAX_CHARA] = {160, 130, 100, 70, 40};
		float fontXPos2[MAX_CHARA] = {554, 584, 614, 644, 674 };
		//float fontYPos[MAX_CHARA] = {128, 150, 200, 270, 390};
		
		pl1_model[i]->SetPosition( -2, 0, charaZPos[i] );
		Status1[i]->SetPosition( fontXPos[i], F(128 + i*64) );
		pl2_model[i]->SetPosition(  2, 0, charaZPos[i] );
		Status2[i]->SetPosition( fontXPos2[i], F(128 + i*64) );
		
		char Buff[MAX_PATH] = "";
		
		wsprintf( Buff, "%d", pl1_model[i]->GetStatus() );
		
		string Str = Buff;
		
		numStatus1[i]->SetText(Str);
		
		numStatus1[i]->SetPosition( F(fontXPos[i] + 15), F(142 + i * 64) );
		
		wsprintf( Buff, "%d", pl2_model[i]->GetStatus() );
		
		Str = Buff;
		
		numStatus2[i]->SetText(Str);
		
		numStatus2[i]->SetPosition( F(fontXPos2[i] + 15), F(142 + i * 64) );		
		
		//pl1_model[i]->SetPosition( 0, 0, 0 );
		//pl2_model[i]->SetPosition(  0, 0, 0 );
		
	}
	
	numTurn->SetPosition(380, 80);
	
	//Fadeout();
	
	//cam->SetPosition(0, 2, 0);
	
//	Joker::GetDevice()->SetRenderState(


	SetBeforeScene(SCENE_CHOOSECHARA);
	
	/*どちらかのキャラが全員死亡していた場合*/
	//if( pl1_model[0]->GetDeadFlag() && pl1_model[1]->GetDeadFlag() && pl1_model[2]->GetDeadFlag() && pl1_model[3]->GetDeadFlag() && pl1_model[4]->GetDeadFlag() ||
	//	pl2_model[0]->GetDeadFlag() && pl2_model[1]->GetDeadFlag() && pl2_model[2]->GetDeadFlag() && pl2_model[3]->GetDeadFlag() && pl2_model[4]->GetDeadFlag() )
	//{
	//	/*終了画面をセット*/
	//	SetNextScene(SCENE_FINAL);
	//	
	//	MoveNextScene();
	//}
	
	cam->Exec();
	
	Joker3D::BeginScene();
	
	field->Exec();
	
	grpLargeTurn->Exec();
	
	numLargeTurn->Exec();
	
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		model[i]->Exec();
	}
	
	
	//bgm->Play(-1, 0);
	
//	m_pSound[SND_BGM]->Play(-1, 3);
	
	Joker3D::EndScene();
	
	
	
	/*次のシーンをセット*/
	SetNextScene(SCENE_MAIN);
	
	
	if(m_IsAnalog)
	{
		/*キャラクター選択*/
		if( !(cursor[PLAYER_1]->GetEndFlag() ) )
		{
			cursor[PLAYER_1]->ChooseCharacter( PLAYER_1, pl1_model, pl2_model);
		}
		
		if( !(cursor[PLAYER_2]->GetEndFlag() ) )
		{
			cursor[PLAYER_2]->ChooseCharacter( PLAYER_2, pl2_model, pl1_model);
		}
		
		if(cursor[PLAYER_1]->GetEndFlag() && cursor[PLAYER_2]->GetEndFlag() )
		{
			/*次のシーンに移動*/
			MoveNextScene();
		}
		
	}
	
	else
	{
		/*初期エラー防止*/
		CNetWork::CServer::SetClientToPlayerData(PLAYER_1, pl1_model, pl2_model);	
		
		CNetWork::CServer::SetClientToPlayerData(PLAYER_2, pl2_model, pl1_model);	
		
		/*データ送信の設定*/
		CNetWork::CServer::SetPlayerToServerData(PLAYER_1, pl1_model, pl2_model);

		CNetWork::CServer::SendData(PLAYER_1);
		
		CNetWork::CServer::SetPlayerToServerData(PLAYER_2, pl2_model, pl1_model);
		
		CNetWork::CServer::SendData(PLAYER_2);
		
		int Turn = g_Turn + 1;
		
		/*ターンの設定*/
		char Buff[MAX_PATH] = "";
		
		wsprintf(Buff, "%d", Turn);
		
		string Str = Buff;
		
		numTurn->SetText( Str );
		
		numLargeTurn->SetText( Str );
		
		/*データの受信*/
		for( int i = 0;i < PLAYER_MAX;i++ )
		{
			/*データの受信*/
			int rev = CNetWork::CServer::RecvData(i);
			
			/*切断*/
			if( rev == 0 )
			{
				break;
			}
			
			/*受信データの設定*/
			CNetWork::CServer::SetClientToPlayerData(i, pl1_model, pl2_model);
			
		}
		
		//Uint64 NowTime = Joker::GetSystemTimeSecond();
		//
		//Uint64 OldTime = NowTime;
		
		static int count = 0;
		
		//if(Joker::GetSystemTime() - NowTime > 10)
		//{
		
		//if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
		//{
		//if(Joker::GetSystemTimeSecond() - OldTime > 3000)
		//{
		if(m_IsZKey)
		{
			if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				/*ターンの設定*/
				CNetWork::CServer::SetTurnToServerData(g_Turn);

				/*次のシーンに移動*/
				MoveNextScene();
			
			}
		}
		
		else
		{
			if(++count > 30)
			{
				count = 0;
				
				/*ターンの設定*/
				CNetWork::CServer::SetTurnToServerData(g_Turn);
				
				
				/*次のシーンに移動*/
				MoveNextScene();
			}
		}
		//}
		//}
	}
	
	
	//CDebug::DrawString("ターン数:%d", Turn);
	//CDebug::DrawString("相手へのダメージ:%d", pl1_model[next]->CalcDamage(pl2_model[Cur % MAX_CHARA]) );			
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		//CDebug::DrawString("pl1[%s]_Dead:%d", pl1_model[i]->GetName().data(), pl1_model[i]->GetDeadFlag() );
		
		CDebug::DrawString("pl1[%s]_status:%d:Type:%d", pl1_model[i]->GetName().data(), pl1_model[i]->GetStatus(), pl1_model[i]->GetSpecialType() );
		CDebug::DrawString("pl2[%s]_status:%d:Type:%d", pl2_model[i]->GetName().data(), pl2_model[i]->GetStatus(), pl2_model[i]->GetSpecialType() );
	}
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		//CDebug::DrawString("pl1[%d]_target:%d", i, pl1_model[i]->GetTarget()->GetStatus() );
	}
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		oldIcon[i] = icon[i];
		OldCharaIcon[i] = charaIcon[i];
	}
	
		

}

//===============================================
//ゲームメイン画面
//===============================================
void CSceneManager::GameMain()
{
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		model[i]->SetRotate(GET_ANGLE(45), 0, 0);
		model[i + 5]->SetRotate(GET_ANGLE(-45), 0, 0);
	}
	
	if(model[MAGICIAN]->Burst->GetVariableFlag() )
	{
		model[MAGICIAN]->Burst->SetVariableFlag( false );
	}
	
	if(model[MAGICIAN]->Fire->GetVariableFlag() )
	{
		model[MAGICIAN]->Fire->SetVariableFlag( false );
	}
	
	if(model[MAGICIAN + 5]->Burst->GetVariableFlag() )
	{
		model[MAGICIAN]->Burst->SetVariableFlag( false );
	}
	
	if(model[MAGICIAN + 5]->Fire->GetVariableFlag() )
	{
		model[MAGICIAN]->Fire->SetVariableFlag( false );
	}
	
	
	
	//----------------------------------------------
	//ブレンドモードの設定
	//----------------------------------------------
	Joker::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Joker::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		float charaZPos[MAX_CHARA] = {8, 5, 2, -1, -3 };
		float fontXPos[MAX_CHARA] = {160, 130, 100, 70, 40};
		float fontXPos2[MAX_CHARA] = {554, 584, 614, 644, 674 };
		//float fontYPos[MAX_CHARA] = {128, 150, 200, 270, 390};
		
		pl1_model[i]->SetPosition( -2, 0, charaZPos[i] );
		Status1[i]->SetPosition( fontXPos[i], F(128 + i*64) );
		pl2_model[i]->SetPosition(  2, 0, charaZPos[i] );
		Status2[i]->SetPosition( fontXPos2[i], F(128 + i*64) );
		
		char Buff[MAX_PATH] = "";
		
		wsprintf( Buff, "%d", pl1_model[i]->GetStatus() );
		
		string Str = Buff;
		
		numStatus1[i]->SetText(Str);
		
		numStatus1[i]->SetPosition(fontXPos[i] + 15, F(142 + i * 64 ) );
		
		wsprintf( Buff, "%d", pl2_model[i]->GetStatus() );
		
		Str = Buff;
		
		numStatus2[i]->SetText(Str);
		
		numStatus2[i]->SetPosition( fontXPos2[i] + 15, F(142 + i * 64) );		
		
		//pl1_model[i]->SetPosition( 0, 0, 0 );
		//pl2_model[i]->SetPosition(  0, 0, 0 );
		
	}	
	
	
	//JRand::Seed(
	
	
	if(!cam->m_IsMove)
	{
		cam->SetPosition(-0.1f, 2.0f, -1.1f);
	}

	
	/*座標の設定*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		float charaZPos[MAX_CHARA] = {8, 5, 2, -1, -3 };
		float fontXPos[MAX_CHARA] = {160, 130, 100, 70, 40};
		float fontXPos2[MAX_CHARA] = {554, 584, 614, 644, 674 };
		//float fontYPos[MAX_CHARA] = {128, 150, 200, 270, 390};
		
		pl1_model[i]->SetPosition( -2, 0, charaZPos[i] );
		Status1[i]->SetPosition( fontXPos[i], F(128 + i*64) );
		pl2_model[i]->SetPosition(  2, 0, charaZPos[i] );
		Status2[i]->SetPosition( fontXPos2[i], F(128 + i*64) );
		
		//pl1_model[i]->SetPosition( 0, 0, 0 );
		//pl2_model[i]->SetPosition(  0, 0, 0 );
		
	}
	
	/*HP文字位置設定*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		float XPos[MAX_CHARA] = {170, 140, 110, 80, 50};
		float XPos2[MAX_CHARA] = {644, 674, 704, 734, 764};
		
		capHp[i]->SetPosition( XPos[i], F(128 + i * 64) );
		capHp[i + 5]->SetPosition( XPos2[i], F(128 + i * 64) );
	}
	
	//cam->SetPosition(0, 2, 0);
	
	m_liOrder.clear();
	
	if(m_IsAnalog)
	{
		for( int i = 0;i < PLAYER_MAX;i++ )
		{
			cursor[i]->SetEndFlag(false);
		}
	}
	
	/*ステータスのバックアップ*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		pl1_model[i]->SetOldStatus();
		pl2_model[i]->SetOldStatus();
	}
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		model[i] = pl1_model[i];
		model[i+5] = pl2_model[i];
	}
	
	set<int> sStatus;//ソート用ステータス
	int status[ALL_CHARA+1];//常用ステータス
	multiset<int> modeldata;//モデルデータ
	
	int status1[MAX_CHARA + 1];
	int status2[MAX_CHARA + 1];
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		status1[i] = pl1_model[i]->GetStatus();
		status2[i] = pl2_model[i]->GetStatus();
	}
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		status[i] = model[i]->GetStatus();
	}
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		if(pl1_model[i]->GetAttackType() == SPECIAL)
		{
			switch(pl1_model[i]->GetSpecial() )
			{
				/*先制攻撃*/
				case FIRST_ATTACK:
				{
					const int FAST = 5000;
					status1[i] = FAST;
					
					break;
				}
				
				/*溜め攻撃*/
				case CHARGE_ATTACK:
				{
					status1[i] /= 2;
					break;
				}
			}
		}
		
		if( pl2_model[i]->GetAttackType() == SPECIAL )
		{
			switch(pl2_model[i]->GetSpecial() )
			{
				/*先制攻撃*/
				case FIRST_ATTACK:
				{
					const int FAST = 5000;
					status2[i] = FAST;
					
					break;
				}
				
				/*溜め攻撃*/
				case CHARGE_ATTACK:
				{
					status2[i] /= 2;
					break;
				}
				
			}
		}
	}
	
	int rand = JRand::GetInt(0, 1);
	
	for(int i = 0;i < MAX_CHARA;i++ )
	{
		status[i] = status1[i];
		status[i + 5] = status2[i];
	}
	
	for( int i = 0;i < ALL_CHARA - 1;i++ )
	{
		for( int j = i + 1;j < ALL_CHARA;j++ )
		{
			if( status[i] == status[j] )
			{
				rand = JRand::GetInt(1, 11);
				
				if(rand >= 1 && rand <= 5)
				{
					status[i] += rand;
				}
				
				else
				{
					status[j] += rand;
				}
			}
			
		}
	}
		
		
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		sStatus.insert( status[i] );
	}
	
	set<int>::reverse_iterator it = sStatus.rbegin();
	
	for( it = sStatus.rbegin();it != sStatus.rend();it++ )
	{
		CDebug::DrawString("status:%d", *it);
	}
	
	for( it = sStatus.rbegin();it != sStatus.rend();it++ )
	{
		for( int i = 0;i < ALL_CHARA;i++ )
		{
			if( *it == status[i])
			{
				m_liOrder.push_back(i);
				
				m_liOrder.unique();
				
			}
			
		}
		
	}
	
	//for( int i = 0;i < ALL_CHARA;i++ )
	//{
	//	if( model[i]-)
	//	{
	//	
	//	}
	//}
	
	list<int>::iterator it2 = m_liOrder.begin();
	
	Joker3D::BeginScene();
	
	
	for( it2 = m_liOrder.begin();it2 != m_liOrder.end(); )
	{
		for( int i = 0;i < ALL_CHARA;i++ )	
		{
			charaIcon[i] = OldCharaIcon[*it2];
			
			/*アイコンの並べ替え*/
			icon[i] = oldIcon[*it2];
			
			it2++;
		}
	}
	
	it2 = m_liOrder.begin();
		
	static int next = 0;
	
	if(model[next]->GetEndFlag() )
	{
		next++;
	}
	
	charaIcon[next]->SetPosition(25, 25);
	
	charaIcon[next + 1]->SetPosition(125, 25);
	
	//charaIcon[next]->DrawCharaIcon( model[next]->GetPlayerType(), model[next]->GetCharaType() );

	//charaIcon[next+1]->DrawCharaIcon( model[next + 1]->GetPlayerType(), model[next + 1]->GetCharaType() );
	//
	/*アイコンの位置の設定*/
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		icon[i]->SetPosition( F(525 + i * 50), 0 );
		icon[i+5]->SetPosition( F(525 + i * 50), 50 );
	}
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		//icon[i]->DrawWeaponIcon(model[i]->GetCharaType() );
		//icon[i+5]->DrawWeaponIcon(model[i]->GetCharaType() );
	}
	//
	cam->Exec();
	
	field->Exec();
	
	for( int i = 0;i < PLAYER_MAX;i++ )
	{
		TeamName[i]->Exec();
		//TeamName[i]->DrawFont();
	}
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		model[i]->Exec();
	}
	
	for( int i = 0;i < CAP_MAX;i++ )
	{
		caption[i]->Exec();
	}
	
	numTurn->SetPosition(380, 80);
	
	
	numTurn->Exec();
	
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		Status1[i]->Exec();
		Status2[i]->Exec();
		numStatus1[i]->Exec();
		numStatus2[i]->Exec();
	}
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		capHp[i]->Exec();
	}
	
	Joker3D::EndScene();
	
	for( int i = 0;i < ALL_CHARA;i++ )	
	{
		if( model[i]->GetAttackType() == SPECIAL )
		{
			if( model[i]->GetSpecial() == BURST )
			{
				model[i]->SetBurstFlag( true );
			}
			
			else if( model[i]->GetSpecial() == ALTER )
			{
				if( !(model[i]->GetDeadFlag() ))
				{
					model[i]->GetTarget()->SetProtectedFlag(true);
				}
			}
			
			else if( model[i]->GetSpecial() == GUARD )
			{
				model[i]->SetGuardFlag( true );
			}
			
			else if( model[i]->GetSpecial() == CHARGE_ATTACK )
			{
				model[i]->SetChargeFlag( true );
			}
			
			else if( model[i]->GetSpecial() == COUNTER )
			{
				if( !(model[i]->GetDeadFlag() ))
				{
					model[i]->SetCounterFlag( true );
				}
			}
		}
	}

	//for( it2 = m_liOrder.begin();it2 != m_liOrder.end();it2++ )
	//{
	//	CDebug::DrawString("order:%d", *it2);
	//}
	
	for( int i = 0;i < ALL_CHARA;i++ )
	{
		if( model[i]->GetMotion() != MOT_DEAD )
		{
			model[i]->SetMotion(MOT_STAND);
		}
	}
	
	static int count = 0;
		
	/*メイン画面に戻る*/
	
	/*どちらかのキャラが全員死亡していた場合*/
	if( pl1_model[0]->GetDeadFlag() && pl1_model[1]->GetDeadFlag() && pl1_model[2]->GetDeadFlag() && pl1_model[3]->GetDeadFlag() && pl1_model[4]->GetDeadFlag() ||
		pl2_model[0]->GetDeadFlag() && pl2_model[1]->GetDeadFlag() && pl2_model[2]->GetDeadFlag() && pl2_model[3]->GetDeadFlag() && pl2_model[4]->GetDeadFlag() )
	{
		/*終了画面をセット*/
		for(int i = 0;i < MAX_CHARA;i++ )
		{
			if(pl1_model[i]->GetDeadFlag() )
			{
				m_IsWin[PLAYER_2] = true;
			}
			
			if(pl2_model[i]->GetDeadFlag() )
			{
				m_IsWin[PLAYER_1] = true;
			}
		}
		
		next = 0;
		
		SetNextScene(SCENE_RESULT);
		
		Uint64 NowTime = Joker::GetSystemTimeSecond();
		
		Uint64 OldTime = NowTime;
		
		static int count = 0;
		
		if(m_IsZKey)
		{
			if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				/*次のシーンに移動*/
				MoveNextScene();
			
			}
		}
		
		else
		{
			if(++count > 30)
			{
				count = 0;
				
				/*ターンの設定*/
				CNetWork::CServer::SetTurnToServerData(g_Turn);
				
				
				/*次のシーンに移動*/
				MoveNextScene();
			}
		}
		
	}
	
	else if( model[0]->GetEndFlag() && model[1]->GetEndFlag() && model[2]->GetEndFlag() && model[3]->GetEndFlag() && model[4]->GetEndFlag() &&
			 model[5]->GetEndFlag() && model[6]->GetEndFlag() && model[7]->GetEndFlag() && model[8]->GetEndFlag() && model[9]->GetEndFlag() )/*pl1_model[i]->GetEndFlag() && pl2_model[i]->GetEndFlag() )*/
	{
		for( int i = 0;i < ALL_CHARA;i++ )
		{
			model[i]->SetEndFlag( false );
			model[i]->SetAttackEndFlag( false );
			model[i]->SetProtectedFlag( false );
			model[i]->SetBuildFlag( false );
			model[i]->SetChargeFlag( false );
			model[i]->SetCounterFlag( false );
			model[i]->SetCriticalFlag( false );
			model[i]->SetGuardFlag( false );
		}
		
		next = 0;
			
		g_Turn++;
			
		SetNextScene(SCENE_CHOOSECHARA);
		
		MoveNextScene();
			
			//pl1_model[i]->SetEndFlag( false );
			
			//pl2_model[i]->SetEndFlag( false );
			
	}
	
	else
	{
		for( int i = 0;i < ALL_CHARA;i++ )
		{
			model[i]->numDamage->SetVisibleFlag( false );
			
		}
		
		//model[ 
		
		
		
		SetNextScene( SCENE_BEFOREBATTLE );
		
		Uint64 NowTime = Joker::GetSystemTimeSecond();
		
		Uint64 OldTime = NowTime;
		
		
		//for( int i = 0;i < ALL_CHARA;i++ )
		//{
		//	model[i]->numDamage->SetVisibleFlag( false );
		//}
	
		//if(Joker::GetSystemTime() - NowTime > 20)
		//{
		
		//if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
		//{
		//	/*次のシーンに移動*/
		//	MoveNextScene();
		//}
		
		static int count = 0;
		
		if(m_IsZKey)
		{
			if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				/*ターンの設定*/
				CNetWork::CServer::SetTurnToServerData(g_Turn);

				/*次のシーンに移動*/
				MoveNextScene();
			
			}
		}
		
		else
		{
			if(++count > 30)
			{
				count = 0;
				
				/*ターンの設定*/
				CNetWork::CServer::SetTurnToServerData(g_Turn);
				
				
				/*次のシーンに移動*/
				MoveNextScene();
			}
		}
		
		//if( Joker::GetSystemTimeSecond() - NowTime > 3000)
		//{
		//	/*次のシーンに移動*/
		//	MoveNextScene();
		//}
		
		//}
		
	}
	
}

//===============================================
//戦闘前画面
//===============================================
void CSceneManager::BeforeBattle()
{
	
	SetNextScene(SCENE_BATTLE);
	
	list<int>::iterator it = m_liOrder.begin();
	
	for( it = m_liOrder.begin();it != m_liOrder.end(); )
	{
		if(model[*it]->GetEndFlag() )
		{
			it++;
		}
		
		else
		{
			break;
		}
	}
	
	Joker3D::BeginScene();
	
	
	field->Exec();
	
	
	model[*it]->Exec();
	
	//if( model[*it]->GetTarget()->GetDeadFlag() )
	//{
	//	model[*it]->SetEndFlag(true);
	//	
	//	SetNextScene(SCENE_MAIN);
	//	
	//	MoveNextScene();
	//}
	
	if(model[*it]->GetAttackType() == SPECIAL )
	{
		if( model[*it]->GetSpecial() == ALLMAGIC )
		{
			if( model[*it]->GetPlayerType() == PLAYER_1 )
			{
				for( int i = 5;i < ALL_CHARA;i++ )
				{
					model[i]->Exec();
				}
			}
			
			else
			{
				for( int i = 0;i < MAX_CHARA;i++ )
				{
					model[i]->Exec();
				}
			}
		}
		
		else
		{
			model[*it]->GetTarget()->Exec();
		}
		
	}
	
	else
	{
		model[*it]->GetTarget()->Exec();
	}
	
	if(model[*it]->GetTarget()->GetProtectedFlag() )
	{
		if( model[*it]->GetPlayerType() == PLAYER_2 )
		{
			model[FENCER]->Exec();
		}
		
		else
		{
			model[FENCER + 5]->Exec();
		}
	}
	
	Joker3D::EndScene();
	
	Uint64 NowTime = Joker::GetSystemTimeSecond();
	
	Uint64 OldTime = NowTime;

	//if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	//{
	//if( Joker::GetSystemTimeSecond() - NowTime > 10000)
	//{
	//	/*次のシーンに移動*/
	//	MoveNextScene();
	//}
	////}
	
		if(m_IsZKey)
		{
			if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
			{
				/*ターンの設定*/
				CNetWork::CServer::SetTurnToServerData(g_Turn);

				/*次のシーンに移動*/
				MoveNextScene();
			
			}
		}
		
		//else
		//{
		//	if(++count > 30)
		//	{
		//		count = 0;
		//		
		//		/*ターンの設定*/
		//		CNetWork::CServer::SetTurnToServerData(g_Turn);
		//		
		//		
		//		/*次のシーンに移動*/
		//		MoveNextScene();
		//	}
		//}
	
	
}

//===============================================
//戦闘画面
//===============================================
void CSceneManager::Battle()
{
	int Damage = 0;//ダメージ
	
	SetBeforeScene(SCENE_BATTLE);
	
	SetNextScene(SCENE_BATTLEEND);
	
	list<int>::iterator it = m_liOrder.begin();
	
	for( it = m_liOrder.begin();it != m_liOrder.end(); )
	{
		if(model[*it]->GetEndFlag() )
		{
			it++;
		}
		
		else
		{
			break;
		}
	}
	
	CDebug::DrawString("*it:%d", *it);
	
	
	//----------------------------------------------
	//キャラの位置設定
	//----------------------------------------------
	if( !(m_IsAppend) )
	{
		for( int i = 0;i < ALL_CHARA;i++ )
		{
			model[i]->SetCurrentAnimPos(0.0f);
		}
		
		
		/*プレイヤー1の場合*/
		if(model[*it]->GetPlayerType() == PLAYER_1)
		{
			if( model[*it]->GetAttackType() == SPECIAL )
			{
				if(model[*it]->GetSpecial() == ALLMAGIC)
				{
					model[*it]->SetRotate( GET_ANGLE(45), 0, 0 );
					model[*it]->GetTarget()->SetRotate( GET_ANGLE(-45), 0, 0 );
				
				}
				
				else if(model[*it]->GetSpecial() == RECOVER)
				{
				
				}
				
				else if(model[*it]->GetSpecial() == BUILDUP)
				{
				
				}
				
				else
				{
					model[*it]->SetRotate( GET_ANGLE(45), 0, 0 );
					model[*it]->GetTarget()->SetRotate( GET_ANGLE(-45), 0, 0 );
			
					model[*it]->SetPosition( -4, 0, 6 );
				
					model[*it]->GetTarget()->SetPosition(  3, 0, 6 );
					
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[FENCER]->SetRotate(GET_ANGLE(45), 0, 0);
						model[FENCER]->SetPosition( 4, 0, 6);
					}
					
				}
			}
			
			else
			{
				
				model[*it]->SetPosition( -4, 0, 6 );
			
				model[*it]->GetTarget()->SetPosition(  3, 0, 6 );
				
				if(model[*it]->GetTarget()->GetProtectedFlag() )
				{
					model[FENCER]->SetRotate(GET_ANGLE(45), 0, 0);
					
					model[FENCER]->SetPosition( 2, 0, 6);
				}
				
			}
			
				
		}
		
		/*プレイヤー2の場合*/
		else
		{
			
			
			if( model[*it]->GetAttackType() == SPECIAL )
			{
				if(model[*it]->GetSpecial() == ALLMAGIC)
				{
					model[*it]->SetRotate( GET_ANGLE(-45), 0, 0 );
					model[*it]->GetTarget()->SetRotate( GET_ANGLE(45), 0, 0 );
				
				}
				
				else if(model[*it]->GetSpecial() == RECOVER)
				{
				
				}
				
				else if(model[*it]->GetSpecial() == BUILDUP)
				{
				
				}
				
				else
				{
					model[*it]->SetRotate( GET_ANGLE(-45), 0, 0 );
					model[*it]->GetTarget()->SetRotate( GET_ANGLE(45), 0, 0 );
					
					
					model[*it]->SetPosition( 4, 0, 6 );
					
					model[*it]->GetTarget()->SetPosition( -3, 0, 6 );

					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[FENCER + 5]->SetRotate( GET_ANGLE(45), 0, 0 );
						
						model[FENCER + 5]->SetPosition( -2, 0, 6);
					}
					
				}
			}
			
			else
			{
				model[*it]->SetPosition( 4, 0, 6 );
			
				model[*it]->GetTarget()->SetPosition( -3, 0, 6 );
				
				if(model[*it]->GetTarget()->GetProtectedFlag() )
				{
					
					model[FENCER + 5]->SetRotate( GET_ANGLE(45), 0, 0 );
					
					model[FENCER+5]->SetPosition( -2, 0, 6);
				}
				
			}
		
		}
		
		m_IsAppend = true;
	}
	
	//----------------------------------------------
	//カメラの位置設定
	//----------------------------------------------
	if( model[*it]->GetAttackType() == ATTACK )
	{
		if( model[*it]->GetCharaType() == MAGICIAN )
		{
			cam->SetPosition(-0.1f, 2.0f, -1.1f);
		}
		
		else
		{
			cam->SetPosition(model[*it]->GetPosition().x, model[*it]->GetPosition().y, model[*it]->GetPosition().z + 2);
		}
	
	}
	
	else
	{
		switch( model[*it]->GetSpecial() )
		{
			
			case CRITICAL:
			{
				cam->SetPosition(model[*it]->GetPosition().x, model[*it]->GetPosition().y, model[*it]->GetPosition().z + 2);
				
				break;
			}
			
			case ALLMAGIC:
			{
				cam->SetPosition(-0.1f, 2.0f, -1.1f);
				
				break;
			}
			
			case FIRST_ATTACK:
			{
				
			}
			
			case BURST:
			{
				
			}
			
			case CHARGE_ATTACK:
			{
				cam->SetPosition(model[*it]->GetPosition().x, model[*it]->GetPosition().y, model[*it]->GetPosition().z + 2);
				
				break;
			}
			
			case ALTER:
			{
				
			}
			
			case RECOVER:
			{

			}
			
			case BUILDUP:
			{
				cam->SetPosition(-0.1f, 2.0f, -1.1f);
				
				break;
			}
			
			case GUARD:
			{
			
			}
			
			case COUNTER:
			{
				cam->SetPosition(model[*it]->GetPosition().x, model[*it]->GetPosition().y, model[*it]->GetPosition().z + 2);
				break;
			
			}
		}
	}
	
	
	//----------------------------------------------
	//描画開始
	//----------------------------------------------
	
	Joker3D::BeginScene();
	
	cam->Exec();
	
	field->Exec();
	
	model[*it]->Exec();
	
	if(model[*it]->GetAttackType() == SPECIAL)
	{
		if( model[*it]->GetSpecialType() == SP_ATTACK )
		{
			grpSpecial[SP_ATTACK]->SetPosition(100, 400);
			
			if( model[*it]->GetCharaType() == FENCER )
			{
				if( model[*it]->GetCriticalFlag() )
				{
					grpSpecial[SP_ATTACK]->DrawSpecialAttack(CRITICAL);
				}
				
			}
			
			else
			{
				grpSpecial[SP_ATTACK]->DrawSpecialAttack(model[*it]->GetSpecial() );
			}
		}
		
		else if( model[*it]->GetSpecialType() == SP_ASSIST)
		{
			grpSpecial[SP_ASSIST]->SetPosition(100, 400);
			
			grpSpecial[SP_ASSIST]->DrawSpecialAssist(model[*it]->GetSpecial() );
			
			
			//if(model[*it]->GetCharaType() == CONTRACTOR)
			//{
			//	//if(model[*it]->GetTarget()->GetProtectedFlag() )
			//	//{
			//	//	grpSpecial[SP_ASSIST]->DrawSpecialAssist(ALTER);
			//	//}
			//	//
			//	if(model[*it]->GetCounterFlag() )
			//	{
			//		grpSpecial[SP_ASSIST]->DrawSpecialAssist(COUNTER);
			//	}
			//	
			//}
			//
			//else if( model[*it]->GetCharaType() == GUARDIAN )
			//{
			//	//if(model[*it]->GetTarget()->GetProtectedFlag() )
			//	//{
			//	//	grpSpecial[SP_ASSIST]->DrawSpecialAssist(ALTER);
			//	//
			//	//}
			//	
			//	if(model[*it]->GetGuardFlag() )
			//	{
			//		grpSpecial[SP_ASSIST]->DrawSpecialAssist(GUARD);
			//	}
			//}
			//
			//else if( model[*it]->GetCharaType() == RANGER )
			//{
			//	if( model[*it]->GetAttackType() == SPECIAL )
			//	{
			//		if( model[*it]->GetSpecial() == BUILDUP )
			//		{
			//			grpSpecial[SP_ASSIST]->DrawSpecialAssist(BUILDUP);
			//		}
			//	}
			//}
			//
			//else if( model[*it]->GetCharaType() == MAGICIAN )
			//{
			//	if( model[*it]->GetAttackType() == SPECIAL )
			//	{
			//		if( model[*it]->GetSpecial() == RECOVER )
			//		{
			//			grpSpecial[SP_ASSIST]->DrawSpecialAssist(RECOVER);
			//		}
			//	}
			//}
			//
			//else
			//{
			//	//if(model[*it]->GetTarget()->GetProtectedFlag() )
			//	//{
			//	//	grpSpecial[SP_ASSIST]->DrawSpecialAssist(ALTER);
			//	//}
			//	//
			//	//else
			//	//{
			//		grpSpecial[SP_ASSIST]->DrawSpecialAssist(model[*it]->GetSpecial() );
			//	//}
			//}
		}
	}
	
	if(model[*it]->GetAttackType() == SPECIAL)
	{
		if( model[*it]->GetSpecial() == ALLMAGIC )
		{
			if(model[*it]->GetPlayerType() == PLAYER_1)
			{
				for( int i = 5;i < ALL_CHARA;i++ )
				{
					model[i]->Exec();
				}
			}
			
			else
			{
				for( int i = 0;i < MAX_CHARA;i++ )
				{
					model[i]->Exec();
				}
			
			}
		}
		
		else 
		{
			model[*it]->GetTarget()->Exec();
		}
	}
	
	else
	{
		model[*it]->GetTarget()->Exec();
	}
	
	if(model[*it]->GetTarget()->GetProtectedFlag() )
	{
		if(model[*it]->GetPlayerType() == PLAYER_2 )
		{
			model[FENCER]->Exec();
		}
		
		else
		{
			model[FENCER + 5]->Exec();
		}
	}
	
	Joker3D::EndScene();
	
	//----------------------------------------------
	//キャラクターごとの処理
	//----------------------------------------------
	if( model[*it]->GetAttackType() == ATTACK )
	{
		switch( model[*it]->GetCharaType() )
		{
			case FENCER:
			{
				
				model[*it]->Attack( model[*it]->GetTarget(), 2, model[*it]->GetLastAnimFrame() / 2 + 0.1);
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
					
						model[*it]->Alternate(pl1_model);
					}
				}
				
				break;
			}
			
			case MAGICIAN:
			{
				model[*it]->MagicAttack( model[*it]->GetTarget() );
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl1_model);
					}
				}
				
				break;
			}
			
			case RANGER:
			{
				model[*it]->Attack(model[*it]->GetTarget(), 1, model[*it]->GetLastAnimFrame() / 2);
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl1_model);
					}
				}
				
				
				break;
			}
			
			case CONTRACTOR:
			{
				model[*it]->Attack(model[*it]->GetTarget(), 1, model[*it]->GetLastAnimFrame() / 2);
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl1_model);
					}
				}
				
				
				break;
			}
			
			case GUARDIAN:
			{
				model[*it]->Attack(model[*it]->GetTarget(), 2, model[*it]->GetLastAnimFrame() / 2);
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{

						model[*it]->Alternate(pl1_model);
					}
				}
				
				break;
			}
			
		}
	
	}
	
	else
	{
		switch( model[*it]->GetSpecial() )
		{
			
			case CRITICAL:
			{
				
				model[*it]->Attack( model[*it]->GetTarget(), 2, model[*it]->GetLastAnimFrame() / 2 - 0.1);
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{

						model[*it]->Alternate(pl1_model);
					}
				}
				
				
				break;
			}
			
			case ALLMAGIC:
			{
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					model[*it]->MagicAllAttack( pl2_model );
				}
				
				else
				{
					model[*it]->MagicAllAttack( pl1_model );
				}
				break;
			}
			
			case FIRST_ATTACK:
			{
				model[*it]->Attack( model[*it]->GetTarget(), 1, model[*it]->GetLastAnimFrame() / 2 - 0.1);
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{

						model[*it]->Alternate(pl1_model);
					}
				}
				
				break;
			}
			
			case BURST:
			{
				model[*it]->BurstS( model[*it]->GetTarget(), 1, model[*it]->GetLastAnimFrame() / 2 - 0.1 );
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{

						model[*it]->Alternate(pl1_model);
					}
				}
				
				break;
			}
			
			case CHARGE_ATTACK:
			{
				model[*it]->Attack( model[*it]->GetTarget(), 2, model[*it]->GetLastAnimFrame() / 2 - 0.1 );
				
				if(model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl2_model);
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						model[*it]->Alternate(pl1_model);
					}
				}
				
				break;
			}
			
			case ALTER:
			{
				
				//model[*it]->SetEndFlag( true );
				break;
			}
			
			case RECOVER:
			{
				if( model[*it]->GetTarget()->GetCharaType() == MAGICIAN )
				{
					if( model[*it]->GetPlayerType() == PLAYER_1 )
					{
						if(model[*it]->GetTarget()->GetProtectedFlag() )
						{
							if(model[*it]->GetTarget()->GetCharaType() == MAGICIAN)
							{
								model[*it]->Alternate(pl1_model);
							}
						}
					}
					
					else
					{
						if(model[*it]->GetTarget()->GetProtectedFlag() )
						{
							if(model[*it]->GetTarget()->GetCharaType() == MAGICIAN)
							{
								model[*it]->Alternate(pl2_model);
							}
						}
					}
				}
				
				model[*it]->Recover(model[*it]->GetTarget() );
				break;
			
			}
			
			case BUILDUP:
			{
				if( model[*it]->GetPlayerType() == PLAYER_1 )
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						if(model[*it]->GetTarget()->GetCharaType() == RANGER)
						{
							model[*it]->Alternate(pl1_model);
						}
					}
				}
				
				else
				{
					if(model[*it]->GetTarget()->GetProtectedFlag() )
					{
						if(model[*it]->GetTarget()->GetCharaType() == RANGER)
						{
							model[*it]->Alternate(pl2_model);
						}
					}
					
				}
				
				model[*it]->BuildUp(model[*it]->GetTarget() );
				break;
			}
			
			case GUARD:
			{
				
				break;
			}
			
			case COUNTER:
			{
				
				break;
			}
		}
	}	
	
	//------------------------------------
	//次のシーンに移るための条件
	//------------------------------------	
	//if(model[*it]->GetAttackType() == SPECIAL)
	//{
	//	if(model[*it]->GetSpecial() == ALLMAGIC)
	//	{
	//		if(model[*it]->GetPlayerType() == PLAYER_1)
	//		{
	//			for( int i = 5;i < ALL_CHARA;i++ )
	//			{
	//				if( model[i]->GetMotion() == MOT_DEAD )
	//				{
	//					if(model[i]->GetCurrentAnim().AnimPos >= model[i]->GetLastAnimFrame() )
	//					{
	//						model[i]->SetCurrentAnimPos(model[i]->GetLastAnimFrame() );
	//						
	//						model[i]->SetDeadFlag( true );
	//						
	//					}
	//				}
	//				
	//				else if(model[i]->GetMotion() == MOT_DAMAGE)
	//				{
	//					if(model[i]->GetCurrentAnim().AnimPos >= model[i]->GetLastAnimFrame() )
	//					{
	//						model[i]->SetCurrentAnimPos(model[i]->GetLastAnimFrame() );
	//					}
	//				}	
	//			}
	//			
	//			model[*it]->SetEndFlag(true);
	//		}
	//		
	//		else
	//		{
	//			for( int i = 0;i < MAX_CHARA;i++ )
	//			{
	//				if( model[i]->GetMotion() == MOT_DEAD )
	//				{
	//					if(model[i]->GetCurrentAnim().AnimPos >= model[i]->GetLastAnimFrame() )
	//					{
	//						model[i]->SetCurrentAnimPos(model[i]->GetLastAnimFrame() );
	//						
	//						model[i]->SetDeadFlag( true );
	//						
	//					}
	//				}
	//				
	//				else if(model[i]->GetMotion() == MOT_DAMAGE)
	//				{
	//					if(model[i]->GetCurrentAnim().AnimPos >= model[i]->GetLastAnimFrame() )
	//					{
	//						model[i]->SetCurrentAnimPos(model[i]->GetLastAnimFrame() );
	//					}
	//				}	
	//				
	//				model[*it]->SetEndFlag(true);
	//			}
	//		
	//		}
	//	}
	//	
	//	else
	//	{
	//		if( model[*it]->GetTarget()->GetMotion() == MOT_DEAD )
	//		{
	//			if( model[*it]->GetTarget()->GetCurrentAnim().AnimPos >= model[*it]->GetTarget()->GetLastAnimFrame() )
	//			{
	//				model[*it]->GetTarget()->SetCurrentAnimPos(model[*it]->GetTarget()->GetLastAnimFrame() );
	//				
	//				model[*it]->GetTarget()->SetDeadFlag( true );
	//				
	//				model[*it]->SetEndFlag( true );
	//				
	//			}
	//		}
	//		
	//		else if(model[*it]->GetTarget()->GetMotion() == MOT_DAMAGE)
	//		{
	//			
	//			if( model[*it]->GetCurrentAnim().AnimPos >= model[*it]->GetLastAnimFrame() )
	//			{
	//				//model[*it]->SetCurrentAnimPos(model[*it]->GetLastAnimFrame() );
	//				
	//				model[*it]->SetEndFlag( true );
	//				
	//			}
	//			
	//		}
	//	}
	//	
	//}
	//
	//else
	//{
	//	if( model[*it]->GetTarget()->GetMotion() == MOT_DEAD )
	//	{
	//		if( model[*it]->GetTarget()->GetCurrentAnim().AnimPos >= model[*it]->GetTarget()->GetLastAnimFrame() )
	//		{
	//			model[*it]->GetTarget()->SetCurrentAnimPos(model[*it]->GetTarget()->GetLastAnimFrame() );
	//			
	//			model[*it]->PlaySe( SE_DEAD );
	//			
	//			model[*it]->GetTarget()->SetDeadFlag( true );
	//			
	//			model[*it]->SetEndFlag( true );
	//			
	//		}
	//	}
	//	
	//	else if(model[*it]->GetTarget()->GetMotion() == MOT_DAMAGE)
	//	{
	//		
	//		if( model[*it]->GetCurrentAnim().AnimPos >= model[*it]->GetLastAnimFrame() )
	//		{
	//			//model[*it]->SetCurrentAnimPos(model[*it]->GetLastAnimFrame() );
	//			
	//			model[*it]->SetEndFlag( true );
	//			
	//		}
	//		
	//	}
	//}
	//
	//if(model[*it]->GetTarget()->GetDeadFlag() )
	//{
	//	if( m_IsAppend )
	//	{
	//		m_IsAppend = false;
	//	}
	//	
	//	MoveNextScene();
	//
	//}
	//
	//else if( model[*it]->GetEndFlag() )
	//{
	//	if( m_IsAppend )
	//	{
	//		m_IsAppend = false;
	//	}
	//	
	//	MoveNextScene();
	//}
	//if( model[*it]->GetTarget()->GetMotion() == MOT_DEAD )
	//{
	//	if(model[*it]->GetTarget()->GetCurrentAnim().AnimPos == model[*it]->GetTarget()->GetLastAnimFrame() )
	//	{
	//		model[*it]->SetEndFlag( true );
	//	}
	//}
	//
	//else if( model[*it]->GetTarget()->GetMotion() == MOT_DAMAGE )
	//{
	//	if(model[*it]->GetTarget()->GetCurrentAnim().AnimPos == model[*it]->GetTarget()->GetLastAnimFrame() )
	//	{
	//		model[*it]->SetEndFlag( true );
	//	}
	//}
	//
	//
	//if(model[*it]->GetEndFlag() )
	//{
	//	if( m_IsAppend )
	//	{
	//		m_IsAppend = false;
	//	}
	//	
	//	MoveNextScene();
	//}
	
	if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
	
	//Uint64 NowTime = Joker::GetSystemTimeSecond();
	//
	//Uint64 OldTime = NowTime;
	//
	//static int count = 0;
	
		model[*it]->SetEndFlag( true );
		
		if( m_IsAppend )
		{
			m_IsAppend = false;
		}
		
		for( int i = 0;i < ALL_CHARA;i++ )
		{
			if(model[i]->GetStatus() <= 0)
			{
				model[i]->SetDeadFlag( true );
			}
		}
		
		MoveNextScene();
	}
	//}			
	
	//if(Joker::GetSystemTime() - NowTime > 500)
	//{
		//if(m_IsAppend)
		//{
		//	m_IsAppend = false;
		//}
		//
		//model[*it]->SetEndFlag( true );
		//MoveNextScene();
	//}

}

//===============================================
//戦闘終了画面
//===============================================
void CSceneManager::BattleEnd()
{
	SetNextScene(SCENE_MAIN);
	
	MoveNextScene();
		
	
}

//===============================================
//結果画面
//===============================================
void CSceneManager::Result()
{
	SetNextScene(SCENE_FINAL);
	
	Joker3D::BeginScene();
	
	if(m_IsWin[PLAYER_1])
	{
		grpResult[PLAYER1_WIN]->Exec();
	}
	
	if(m_IsWin[PLAYER_2])
	{
		grpResult[PLAYER2_WIN]->Exec();
	}
	
	Joker3D::EndScene();
	
	//
	if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		MoveNextScene();
	}
		
	
}


//===============================================
//終了画面
//===============================================
void CSceneManager::Finalize()
{
	if( !(m_IsAnalog) )
	{
		bgm->Stop(SND_BGM);
		CNetWork::CServer::Finalize();
	}
	
	
	SetBeforeScene(SCENE_FINAL);

	SetNextScene(SCENE_INIT);
	
	//for( int i = 0;i < ALL_CHARA;i++ )
	//{
	//		
	//}
	
	delete field;
	
	//for( int i = 0;i < MAX_CHARA;i++ )
	//{
	//	//obj[SCENE_MAIN].RemoveObject(Status1[i]);
	//	//obj[SCENE_MAIN].RemoveObject(Status2[i]);
	//	//obj[SCENE_MAIN].RemoveObject(numStatus1[i]);
	//	//obj[SCENE_MAIN].RemoveObject(numStatus2[i]);

	//}
	//
	///*ステータスの文字*/
	//for( int i = 0;i < ALL_CHARA;i++ )
	//{
	//	//obj[SCENE_MAIN].RemoveObject(capHp[i]);
	//}
	//
	//for( int i = 0;i < CAP_MAX - 5;i++ )
	//{
	//	//obj[SCENE_MAIN].RemoveObject(caption[i]);
	//}
	
	//obj[SCENE_MAIN].RemoveObject(numTurn);
	
	//obj[SCENE_MAIN].RemoveObject(bgm);
	
//	m_pSound[SND_BGM]->Stop();
	
	
	CDebug::DrawString("プレイヤーの勝利");
	
	MoveNextScene();
	
		
	//delete obj[SCENE_MAIN];
}

//===============================================
//フェードイン
//===============================================
void CSceneManager::Fadein()
{
	FadeCount--;
	
	if(FadeCount < 0)
	{
		FadeCount = 0;
	}
	
	Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET,  D3DCOLOR_ARGB(0, FadeCount, FadeCount, FadeCount), 1.0f, 0);
	
	//Joker::GetDevice()->ColorFill(Joker3D::GetSurface(), NULL, D3DCOLOR_ARGB(FadeCount, FadeCount, FadeCount, FadeCount) );
}

//===============================================
//フェードアウト
//===============================================
void CSceneManager::Fadeout()
{
	FadeCount++;
	
	if(FadeCount > 255)
	{
		FadeCount = 255;
	}
	
	Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(FadeCount, FadeCount, FadeCount, FadeCount), 1.0f, 0);
	
	//Joker::GetDevice()->ColorFill(Joker3D::GetSurface(), NULL, D3DCOLOR_ARGB(FadeCount, FadeCount, FadeCount, FadeCount) );
	
}



//===============================================
//シーンの描画
//===============================================
void CSceneManager::DrawScene()
{
	switch(m_CurrentScene)
	{
		/*初期化画面*/
		case SCENE_INIT:
		{
			Initialize();
			break;
		}
		
		/*AI待ち画面*/
		case SCENE_WAIT:
		{
			//obj[SCENE_WAIT].DoAllTasks();
			WaitAI();
			break;
		}
		
		case SCENE_CHOOSESPECIAL:
		{
			//obj[SCENE_CHOOSESPECIAL].DoAllTasks();
			ChooseSpecial();
			break;
		}
		
		case SCENE_CHOOSECHARA:
		{
			//obj[SCENE_CHOOSECHARA].DoAllTasks();
			ChooseChara();
			break;
		}
		
		/*メイン画面*/
		case SCENE_MAIN:
		{
			//obj[SCENE_MAIN].DoAllTasks();
			GameMain();
			break;
		}
		
		case SCENE_BEFOREBATTLE:
		{
			BeforeBattle();
			break;
		}
		
		/*戦闘画面*/
		case SCENE_BATTLE:
		{
			//obj[SCENE_BATTLE].DoAllTasks();
			Battle();
			break;
		}
		
		/*戦闘終了画面*/
		case SCENE_BATTLEEND:
		{
			BattleEnd();
			break;
		}
		
		/*結果画面*/
		case SCENE_RESULT:
		{
			Result();
			break;
		}
		
		/*終了処理画面*/
		case SCENE_FINAL:
		{
			Finalize();
			break;
		}
	}
}

//===============================================
//シーンの描画
//===============================================
void CSceneManager::DrawScene(eSceneType type)
{
	m_CurrentScene = type;
	
	switch(m_CurrentScene)
	{
		/*初期化画面*/
		case SCENE_INIT:
		{
			Initialize();
			break;
		}
		
		/*AI待ち画面*/
		case SCENE_WAIT:
		{
			obj[SCENE_WAIT].DoAllTasks();
			WaitAI();
			break;
		}
		
		case SCENE_CHOOSESPECIAL:
		{
			obj[SCENE_CHOOSESPECIAL].DoAllTasks();
			ChooseSpecial();
			break;
		}
		
		case SCENE_CHOOSECHARA:
		{
			obj[SCENE_CHOOSECHARA].DoAllTasks();
			ChooseChara();
			break;
		}
		
		/*メイン画面*/
		case SCENE_MAIN:
		{
			obj[SCENE_MAIN].DoAllTasks();
			GameMain();
			break;
		}
		
		/*戦闘画面*/
		case SCENE_BATTLE:
		{
			obj[SCENE_BATTLE].DoAllTasks();
			Battle();
			break;
		}
		
		/*戦闘終了画面*/
		case SCENE_BATTLEEND:
		{
			BattleEnd();
			break;
		}
		
		/*終了処理画面*/
		case SCENE_FINAL:
		{
			Finalize();
			break;
		}
	}
}

//===============================================
//手入力判定フラグ
//===============================================
//[return]
//	手入力かどうか
//===============================================
bool CSceneManager::GetAnalogFlag()
{
	return m_IsAnalog;
}

//===============================================
//前のシーンの取得
//===============================================
//[return]
//	前のシーン
//===============================================
eSceneType CSceneManager::GetBeforeScene()
{
	return m_BeforeScene;
}

//===============================================
//次のシーンの取得
//===============================================
//[return]
//	次のシーン
//===============================================
eSceneType CSceneManager::GetNextScene()
{
	return m_NextScene;
}

//===============================================
//
//===============================================
//[input]
//
//===============================================
void CSceneManager::SetBeforeScene(eSceneType type)
{
	m_BeforeScene = type;
}

//===============================================
//次のシーンの設定
//===============================================
//[input]
//	type:次のシーンの種類
//===============================================
void CSceneManager::SetNextScene(eSceneType type)
{
	m_NextScene = type;
} 

//===============================================
//次のシーンに移動
//===============================================
void CSceneManager::MoveNextScene()
{
	m_CurrentScene = m_NextScene;
}

