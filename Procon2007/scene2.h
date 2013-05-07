//*==============================================
//scenemanager.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include <iostream>
#include <list>

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
	SCENE_CHOOSECHARA,//キャラクター選択画面
	SCENE_MAIN,//ゲームメイン画面
	SCENE_BATTLE,//バトル画面
	SCENE_WINNER,//勝利者画面
	SCENE_FINAL,//終了処理画面
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
	
		eSceneType m_CurrentScene;//現在のシーン
		eSceneType m_NextScene;//次のシーン
	
		
	public:
	
		CSceneManager();//コンストラクタ
		~CSceneManager(){};//デストラクタ
		
		void Initialize();//初期化
		void GameMain();//ゲームメイン
		void DrawScene();//シーンの描画
		
		eSceneType GetNextScene();//次のシーンの取得
		void SetNextScene(eSceneType type);//次のシーンの設定
		void MoveNextScene();//次のシーンに移動
};