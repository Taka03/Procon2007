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
//�R���X�g���N�^
//===============================================
CSceneManager::CSceneManager()
{
	m_CurrentScene = SCENE_INIT;
	m_NextScene = SCENE_INIT;
}

//===============================================
//������
//===============================================
void CSceneManager::Initialize()
{
	obj->AppendObject(new CTaskHead(), 0, true);
	
	obj->AppendObject(new CJoyPad(), 1, true);

	obj->AppendObject(cam, 2, true);
	
	obj->AppendObject(new CFencer(), 3, true);
	
	//obj->AppendObject(field, 4, true);
	
	obj->AppendObject(new CTaskKill(), INT_MAX, true);
	
	/*���̃V�[���̃Z�b�g*/
	SetNextScene(SCENE_MAIN);
	
	/*���̃V�[���Ɉړ�*/
	MoveNextScene();
	
}

//===============================================
//�Q�[�����C�����
//===============================================
void CSceneManager::GameMain()
{
	obj->DoAllTasks();	
}

//===============================================
//�V�[���̕`��
//===============================================
void CSceneManager::DrawScene()
{
	switch(m_CurrentScene)
	{
		/*���������*/
		case SCENE_INIT:
		{
			Initialize();
			break;
		}
		
		/*���C�����*/
		case SCENE_MAIN:
		{
			GameMain();
			break;
		}
		
	}
}

//===============================================
//���̃V�[���̎擾
//===============================================
//[return]
//	���̃V�[��
//===============================================
eSceneType CSceneManager::GetNextScene()
{
	return m_NextScene;
}

//===============================================
//���̃V�[���̐ݒ�
//===============================================
//[input]
//	type:���̃V�[���̎��
//===============================================
void CSceneManager::SetNextScene(eSceneType type)
{
	m_NextScene = type;
} 

//===============================================
//���̃V�[���Ɉړ�
//===============================================
void CSceneManager::MoveNextScene()
{
	m_CurrentScene = m_NextScene;
}

