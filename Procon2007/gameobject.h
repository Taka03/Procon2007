//*==============================================
//gameobject.h
//*==============================================

//二重インクルード防止
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
	string name;//管理名称
	CGameObject* gameobj;//オブジェクトのポインタ
	bool autodelete;//リスト削除と同時にオブジェクトも削除
};

//===============================================
//class
//===============================================
class CGameObject :public Joker3D
{
	private:
	
		list<ListData> objectlist;//格納リスト
		list<list<ListData>::iterator> removelist;//削除リスト
		
	protected:
	
		bool m_IsVisible;//表示判定フラグ
	
	public:
	
		CGameObject();//コンストラクタ
		virtual ~CGameObject();//デストラクタ
		
		virtual void Init(){};//初期
		virtual void Exec(){};//処理
		virtual void Draw(){};//描画
		
		void DoAllTasks();//タスクの実行
		
		void AppendObject(CGameObject *object, string name, bool autodelete);//オブジェクトの追加
		
		void RemoveObject(CGameObject *object);//オブジェクトの削除
		
		CGameObject *FindObject(string name);//オブジェクトの検索
		
};
