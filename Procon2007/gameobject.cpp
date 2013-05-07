//*==============================================
//gameobject.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//コンストラクタ
//===============================================
CGameObject::CGameObject()
{

}

//===============================================
//デストラクタ
//===============================================
CGameObject::~CGameObject()
{
	
}


//===============================================
//オブジェクトの追加(名前あり)
//===============================================
//[input]
//	object:ゲームオブジェクト
//	priority:管理順番
//	name:データ名
//	autodelete:削除と同時にオブジェクトも削除するか(フラグ)
//[return]
//	なし
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
	
	/*初期化*/
	object->Init();
	
	/*間に入れるところがなければ、最後に追加*/
	objectlist.push_back(ld);
	
}

//===============================================
//オブジェクトの削除
//===============================================
//[input]
//	object:オブジェクト
//[return]
//	なし
//===============================================
void CGameObject::RemoveObject(CGameObject *object)
{
	m_IsVisible = false;
	
	list<ListData>::iterator i;
	
	for(i = objectlist.begin();i != objectlist.end();i++)
	{
		if(i->gameobj == object)
		{
			/*削除データをリストに追加*/
			removelist.push_back(i);
			
			return;
		}
	}
}

//===============================================
//オブジェクト検索
//===============================================
//[input]
//	name:オブジェクト名
//[return]
//	(*i).gameobj:名前の一致したオブジェクト
//	NULL:見つからなかった場合何も返さない
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
//すべてのタスクの実行
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CGameObject::DoAllTasks()
{
	list<ListData>::iterator i;
	
	for(i = objectlist.begin(); i != objectlist.end();i++)
	{
		/*処理*/
		(*i).gameobj->Exec();
		
		///*シーンの描画開始*/
		//Joker3D::BeginScene();
		//
		///*描画*/
		//if( m_IsVisible )
		//{
		//	(*i).gameobj->Draw();
		//}
		//
		///*シーンの描画終了*/
		//Joker3D::EndScene();
	}
	
	if(removelist.size() > 0)
	{
		/*削除一覧にあるデータをまとめて削除*/
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

