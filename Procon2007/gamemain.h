//*==============================================
//gamemain.h
//*==============================================
#pragma once

//===============================================
//include 
//===============================================
#include "gameobject.h"
#include "light.h"
#include "rect.h"

//===============================================
//class
//===============================================
class CTaskHead :public CGameObject
{
	private:
	
		DWORD lasttime;
		
	
	protected:
	
		void Init();//������
		void Exec();//����
		
	public:
	
		CRect Rect;
	
		CTaskHead();//�R���X�g���N�^
		~CTaskHead();//�f�X�g���N�^
		
	
		
};

class CTaskKill :public CGameObject
{
	protected:
	
		void Exec();//����
		
	public:
	
		CTaskKill(){};//�R���X�g���N�^
		~CTaskKill(){};//�f�X�g���N�^
		
};