//*==============================================
//gameobject.h
//*==============================================

//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include "joker3d.h"


//===============================================
//variable
//===============================================
class CGameObject;

//===============================================
//struct
//===============================================
struct ListData
{
	string name;//�Ǘ�����
	CGameObject* gameobj;//�I�u�W�F�N�g�̃|�C���^
	bool autodelete;//���X�g�폜�Ɠ����ɃI�u�W�F�N�g���폜
};

//===============================================
//class
//===============================================
class CGameObject :public Joker3D
{
	private:
	
		list<ListData> objectlist;//�i�[���X�g
		list<list<ListData>::iterator> removelist;//�폜���X�g
		
	protected:
	
		bool m_IsVisible;//�\������t���O
	
	public:
	
		CGameObject();//�R���X�g���N�^
		virtual ~CGameObject();//�f�X�g���N�^
		
		virtual void Init(){};//����
		virtual void Exec(){};//����
		virtual void Draw(){};//�`��
		
		void DoAllTasks();//�^�X�N�̎��s
		
		void AppendObject(CGameObject *object, string name, bool autodelete);//�I�u�W�F�N�g�̒ǉ�
		
		void RemoveObject(CGameObject *object);//�I�u�W�F�N�g�̍폜
		
		CGameObject *FindObject(string name);//�I�u�W�F�N�g�̌���
		
};
