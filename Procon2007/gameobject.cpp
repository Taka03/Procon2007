//*==============================================
//gameobject.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//�R���X�g���N�^
//===============================================
CGameObject::CGameObject()
{

}

//===============================================
//�f�X�g���N�^
//===============================================
CGameObject::~CGameObject()
{
	
}


//===============================================
//�I�u�W�F�N�g�̒ǉ�(���O����)
//===============================================
//[input]
//	object:�Q�[���I�u�W�F�N�g
//	priority:�Ǘ�����
//	name:�f�[�^��
//	autodelete:�폜�Ɠ����ɃI�u�W�F�N�g���폜���邩(�t���O)
//[return]
//	�Ȃ�
//===============================================
void CGameObject::AppendObject(CGameObject *object, string name,  bool autodelete)
{
	if(object == NULL)
	{
		return;
	}
	
	m_IsVisible = true;
	
	ListData ld;
	
	ld.name = name;
	
	ld.gameobj = object;
	ld.autodelete = autodelete;
	
	/*������*/
	object->Init();
	
	/*�Ԃɓ����Ƃ��낪�Ȃ���΁A�Ō�ɒǉ�*/
	objectlist.push_back(ld);
	
}

//===============================================
//�I�u�W�F�N�g�̍폜
//===============================================
//[input]
//	object:�I�u�W�F�N�g
//[return]
//	�Ȃ�
//===============================================
void CGameObject::RemoveObject(CGameObject *object)
{
	m_IsVisible = false;
	
	list<ListData>::iterator i;
	
	for(i = objectlist.begin();i != objectlist.end();i++)
	{
		if(i->gameobj == object)
		{
			/*�폜�f�[�^�����X�g�ɒǉ�*/
			removelist.push_back(i);
			
			return;
		}
	}
}

//===============================================
//�I�u�W�F�N�g����
//===============================================
//[input]
//	name:�I�u�W�F�N�g��
//[return]
//	(*i).gameobj:���O�̈�v�����I�u�W�F�N�g
//	NULL:������Ȃ������ꍇ�����Ԃ��Ȃ�
//===============================================
CGameObject *CGameObject::FindObject(string name)
{
	list<ListData>::iterator i;
	
	for( i = objectlist.begin(); i != objectlist.end();i++ )
	{
		if(strcmp( i->name.c_str(), name.c_str() ) == 0)
		{
			return i->gameobj;
		}
	}
	
	return NULL;
}

//===============================================
//���ׂẴ^�X�N�̎��s
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CGameObject::DoAllTasks()
{
	list<ListData>::iterator i;
	
	for(i = objectlist.begin(); i != objectlist.end();i++)
	{
		/*����*/
		(*i).gameobj->Exec();
		
		///*�V�[���̕`��J�n*/
		//Joker3D::BeginScene();
		//
		///*�`��*/
		//if( m_IsVisible )
		//{
		//	(*i).gameobj->Draw();
		//}
		//
		///*�V�[���̕`��I��*/
		//Joker3D::EndScene();
	}
	
	if(removelist.size() > 0)
	{
		/*�폜�ꗗ�ɂ���f�[�^���܂Ƃ߂č폜*/
		list<list<ListData>::iterator>::iterator j;
		
		for(j = removelist.begin();j != removelist.end();j++)
		{
			if( (**j).autodelete == true)
			{
				delete (**j).gameobj;
			}
			
			objectlist.erase(*j);
		}
		
		removelist.clear();
	}
}

