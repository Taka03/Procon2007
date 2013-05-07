//*==============================================
//scenemanager.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "character.h"
#include "camera.h"
#include "field.h"
#include "cursor.h"
#include "fontsprite.h"
#include "sprite.h"
#include "SoundFactory.h"
#include "soundsprite.h"

#include "network.h"

//===============================================
//using
//===============================================
using namespace std;

//===============================================
//enum
//===============================================
enum eSceneType
{
	SCENE_INIT,//初期化画面
	SCENE_WAIT,//AI待ち画面
	SCENE_CHOOSESPECIAL,//特殊能力選択画面
	SCENE_CHOOSECHARA,//キャラクター選択画面
	SCENE_MAIN,//ゲームメイン画面
	SCENE_BEFOREBATTLE,
	SCENE_BATTLE,//バトル画面
	SCENE_BATTLEEND,//バトル終了画面
	SCENE_RESULT,//結果画面
	SCENE_FINAL,//終了処理画面
	SCENE_MAX,
};


//===============================================
//class
//===============================================
//[Desc]
//	シーン管理用クラス
//===============================================
class CSceneManager
{
	private:
	
		CGameObject obj[SCENE_MAX];
		CCamera *cam;
		//CCamera *battlecam;
	
		CCharacter *model[ALL_CHARA]; 

		CCharacter *pl1_model[MAX_CHARA];
		CCharacter *pl2_model[MAX_CHARA];
		
		//CCharacter *temp_model1[MAX_CHARA + 1];
		//CCharacter *temp_model2[MAX_CHARA + 1];

		CXModel *field;
		CSprite *SprTurn;
		
		//CXModel *
		
		CFontSprite *Status1[MAX_CHARA];//ステータス画像1
		CFontSprite *Status2[MAX_CHARA];//ステータス画像2
		CFontSprite *numStatus1[MAX_CHARA];//ステータス数字1
		CFontSprite *numStatus2[MAX_CHARA];//ステータス数字2
		CFontSprite *capHp[ALL_CHARA];//ステータスの文字
		CFontSprite *caption[CAP_MAX];//ターングラフィック
		CFontSprite *icon[ALL_CHARA];//アイコングラフィック
		CFontSprite *oldIcon[ALL_CHARA];//アイコングラフィック(バックアップ)
		CFontSprite *charaIcon[ALL_CHARA];//キャラアイコングラフィック
		CFontSprite *OldCharaIcon[ALL_CHARA];//キャラアイコングラフィック
		CFont *numTurn;//ターンの数字
		CFontSprite *grpLoading;//ローディング画像
		CFontSprite *grpLargeTurn;//ターン画像
		CFontSprite *numLargeTurn;//ターン番号
		CFontSprite *grpSpecial[SPTYPE_MAX];//特殊能力画像(攻撃ver)
		CFontSprite *grpResult[RESULT_MAX];//結果画像
		
		//CXModel *m_pGrpSys;
		
		CSound *bgm;
		//CSound *se[SE_MAX];
		
		CFont *TeamName[PLAYER_MAX];
//		CFont *TestFont;

		CCursor *cursor[2];
		
		list<int> m_liOrder;//順番
		
		list<int>::iterator m_itr;
		
		int FadeCount;//フェード用カウンタ
		
		bool m_IsAnalog;//操作が手入力かどうか
		bool m_IsAppend;//モデルが導入されているかどうか(戦闘画面用)
		
		bool m_IsBattle; //戦闘判定用
		
		bool m_IsShort;//戦闘短縮用
		
		bool m_IsWin[PLAYER_MAX];//勝利判定フラグ
		
		bool m_IsZKey;
		
		
	private:
	
		eSceneType m_BeforeScene;//前のシーン
		eSceneType m_CurrentScene;//現在のシーン
		eSceneType m_NextScene;//次のシーン
	
		
	public:
	
		CSceneManager();//コンストラクタ
		~CSceneManager(){};//デストラクタ
		
		void Initialize();//初期化
		void WaitAI();//AI待ち画面
		void ChooseSpecial();//特殊能力選択画面
		void ChooseChara();//キャラクター選択画面
		void GameMain();//ゲームメイン
		void BeforeBattle();//戦闘前画面
		void Battle();//戦闘画面
		void BattleEnd();//戦闘終了画面
		void Result();//結果画面
		void Finalize();//終了処理
		
		void Fadein();//フェードイン
		void Fadeout();//フェードアウト
		
		void DrawScene();//シーンの描画
		void DrawScene(eSceneType type);//シーンの描画
		
		void MoveNextScene();//次のシーンに移動
		
		
	public:
		
		eSceneType GetBeforeScene();//前のシーンの取得
		eSceneType GetNextScene();//次のシーンの取得
		
		bool GetAnalogFlag();//アナログフラグの取得
		
	public:
		
		void SetBeforeScene(eSceneType type);//前回のシーンの設定
		void SetNextScene(eSceneType type);//次のシーンの設定
		
};