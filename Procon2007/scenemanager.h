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
	SCENE_INIT,//���������
	SCENE_WAIT,//AI�҂����
	SCENE_CHOOSESPECIAL,//����\�͑I�����
	SCENE_CHOOSECHARA,//�L�����N�^�[�I�����
	SCENE_MAIN,//�Q�[�����C�����
	SCENE_BEFOREBATTLE,
	SCENE_BATTLE,//�o�g�����
	SCENE_BATTLEEND,//�o�g���I�����
	SCENE_RESULT,//���ʉ��
	SCENE_FINAL,//�I���������
	SCENE_MAX,
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
		
		CFontSprite *Status1[MAX_CHARA];//�X�e�[�^�X�摜1
		CFontSprite *Status2[MAX_CHARA];//�X�e�[�^�X�摜2
		CFontSprite *numStatus1[MAX_CHARA];//�X�e�[�^�X����1
		CFontSprite *numStatus2[MAX_CHARA];//�X�e�[�^�X����2
		CFontSprite *capHp[ALL_CHARA];//�X�e�[�^�X�̕���
		CFontSprite *caption[CAP_MAX];//�^�[���O���t�B�b�N
		CFontSprite *icon[ALL_CHARA];//�A�C�R���O���t�B�b�N
		CFontSprite *oldIcon[ALL_CHARA];//�A�C�R���O���t�B�b�N(�o�b�N�A�b�v)
		CFontSprite *charaIcon[ALL_CHARA];//�L�����A�C�R���O���t�B�b�N
		CFontSprite *OldCharaIcon[ALL_CHARA];//�L�����A�C�R���O���t�B�b�N
		CFont *numTurn;//�^�[���̐���
		CFontSprite *grpLoading;//���[�f�B���O�摜
		CFontSprite *grpLargeTurn;//�^�[���摜
		CFontSprite *numLargeTurn;//�^�[���ԍ�
		CFontSprite *grpSpecial[SPTYPE_MAX];//����\�͉摜(�U��ver)
		CFontSprite *grpResult[RESULT_MAX];//���ʉ摜
		
		//CXModel *m_pGrpSys;
		
		CSound *bgm;
		//CSound *se[SE_MAX];
		
		CFont *TeamName[PLAYER_MAX];
//		CFont *TestFont;

		CCursor *cursor[2];
		
		list<int> m_liOrder;//����
		
		list<int>::iterator m_itr;
		
		int FadeCount;//�t�F�[�h�p�J�E���^
		
		bool m_IsAnalog;//���삪����͂��ǂ���
		bool m_IsAppend;//���f������������Ă��邩�ǂ���(�퓬��ʗp)
		
		bool m_IsBattle; //�퓬����p
		
		bool m_IsShort;//�퓬�Z�k�p
		
		bool m_IsWin[PLAYER_MAX];//��������t���O
		
		bool m_IsZKey;
		
		
	private:
	
		eSceneType m_BeforeScene;//�O�̃V�[��
		eSceneType m_CurrentScene;//���݂̃V�[��
		eSceneType m_NextScene;//���̃V�[��
	
		
	public:
	
		CSceneManager();//�R���X�g���N�^
		~CSceneManager(){};//�f�X�g���N�^
		
		void Initialize();//������
		void WaitAI();//AI�҂����
		void ChooseSpecial();//����\�͑I�����
		void ChooseChara();//�L�����N�^�[�I�����
		void GameMain();//�Q�[�����C��
		void BeforeBattle();//�퓬�O���
		void Battle();//�퓬���
		void BattleEnd();//�퓬�I�����
		void Result();//���ʉ��
		void Finalize();//�I������
		
		void Fadein();//�t�F�[�h�C��
		void Fadeout();//�t�F�[�h�A�E�g
		
		void DrawScene();//�V�[���̕`��
		void DrawScene(eSceneType type);//�V�[���̕`��
		
		void MoveNextScene();//���̃V�[���Ɉړ�
		
		
	public:
		
		eSceneType GetBeforeScene();//�O�̃V�[���̎擾
		eSceneType GetNextScene();//���̃V�[���̎擾
		
		bool GetAnalogFlag();//�A�i���O�t���O�̎擾
		
	public:
		
		void SetBeforeScene(eSceneType type);//�O��̃V�[���̐ݒ�
		void SetNextScene(eSceneType type);//���̃V�[���̐ݒ�
		
};