//*==============================================
//scenemanager.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "scenemanager.h"
#include "gameobject.h"

#include "gamemain.h"
#include "camera.h"
#include "font.h"
#include "CXModel.h"
#include "joypad.h"
#include "light.h"
#include "sound.h"
#include "character.h"
#include "fencer.h"
#include "magician.h"
#include "ranger.h"
#include "contractor.h"
#include "guardian.h"
#include "field.h"
#include "rendertarget.h"
#include "debug.h"
#include "cursor.h"
#include "charafactory.h"
#include "swap.h"

#include <vector>
#include <algorithm>

//===============================================
//variable
//===============================================
CGameObject *obj = new CGameObject();
CCamera *cam = new CCamera();
CField *field = new CField();

CCharacter model[MAX_CHARA];

//===============================================
//コンストラクタ
//===============================================
CSceneManager::CSceneManager()
{
	m_CurrentScene = SCENE_INIT;
	m_NextScene = SCENE_INIT;
}

//===============================================
//初期化
//===============================================
void CSceneManager::Initialize()
{
	obj->AppendObject(new CTaskHead(), 0, true);
	
	obj->AppendObject(new CJoyPad(), 1, true);

	obj->AppendObject(cam, 2, true);
	
	obj->AppendObject(new CFencer(), 3, true);
	
	//obj->AppendObject(field, 4, true);
	
	obj->AppendObject(new CTaskKill(), INT_MAX, true);
	
	/*次のシーンのセット*/
	SetNextScene(SCENE_MAIN);
	
	/*次のシーンに移動*/
	MoveNextScene();
	
}

//===============================================
//ゲームメイン画面
//===============================================
void CSceneManager::GameMain()
{
	obj->DoAllTasks();	
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
		
		/*メイン画面*/
		case SCENE_MAIN:
		{
			GameMain();
			break;
		}
		
	}
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

