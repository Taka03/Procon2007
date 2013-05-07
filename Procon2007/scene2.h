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
	SCENE_INIT,//���������
	SCENE_WAIT,//AI�҂����
	SCENE_CHOOSECHARA,//�L�����N�^�[�I�����
	SCENE_MAIN,//�Q�[�����C�����
	SCENE_BATTLE,//�o�g�����
	SCENE_WINNER,//�����҉��
	SCENE_FINAL,//�I���������
};

//===============================================
//class
//===============================================
//[Desc]
//	�V�[���Ǘ��p�N���X
//===============================================
class CSceneManager
{
	private:
	
		eSceneType m_CurrentScene;//���݂̃V�[��
		eSceneType m_NextScene;//���̃V�[��
	
		
	public:
	
		CSceneManager();//�R���X�g���N�^
		~CSceneManager(){};//�f�X�g���N�^
		
		void Initialize();//������
		void GameMain();//�Q�[�����C��
		void DrawScene();//�V�[���̕`��
		
		eSceneType GetNextScene();//���̃V�[���̎擾
		void SetNextScene(eSceneType type);//���̃V�[���̐ݒ�
		void MoveNextScene();//���̃V�[���Ɉړ�
};