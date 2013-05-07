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
	
		void Init();//初期化
		void Exec();//処理
		
	public:
	
		CRect Rect;
	
		CTaskHead();//コンストラクタ
		~CTaskHead();//デストラクタ
		
	
		
};

class CTaskKill :public CGameObject
{
	protected:
	
		void Exec();//処理
		
	public:
	
		CTaskKill(){};//コンストラクタ
		~CTaskKill(){};//デストラクタ
		
};