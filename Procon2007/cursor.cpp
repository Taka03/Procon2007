//*==============================================
//cursor.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "cursor.h"
#include "joypad.h"
#include "debug.h"

//===============================================
//コンストラクタ
//===============================================
CCursor::CCursor()
{
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_IsEnd = false;
	
	Cursor = 0;
	
	CursorMax = 0;
	
	next = 0;
	
	//m_CurTex.LoadTexture("data/mouse.bmp");
}

//===============================================
//コンストラクタ
//===============================================
CCursor::CCursor(const char *name)
{
	m_vPos.Set(100.0f, 0.0f, 0.0f);
	
	m_IsEnd = false;
	
	//m_CurTex.LoadTexture(name);
}

//===============================================
//デストラクタ
//===============================================
CCursor::~CCursor()
{
	Release();
}

//===============================================
//初期化
//===============================================
void CCursor::Init()
{
	//m_CurTex.LoadTexture("data/mouse.bmp");
	
	Load(Joker::GetDevice(), "data/act_soldier_basic.x", Joker::GetMaxBlend() );
}

//===============================================
//処理
//===============================================
void CCursor::Exec()
{
	if( !m_IsEnd )
	{
		Translation(m_vPos.x, m_vPos.y, m_vPos.z);
		
		//Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
		
		//Heading(m_vRot.x);
		//
		//Pitching(m_vRot.x);
		//
		//Rolling(m_vRot.x);
		
//		Update(0.000f);
		
		Render(Joker::GetDevice());
		
		SetWorldMatrix();
		
	}

		//m_CurTex.Draw(m_vPos.x, m_vPos.y);
}

//===============================================
//カーソルの位置セット
//===============================================
//[input]
//	player:プレイヤータイプ
//	obj:攻撃対象
//===============================================
void CCursor::SetCursor(ePlayerType player, CCharacter *obj)
{
	if(player == PLAYER_1)
	{
		m_vPos.x = obj->GetPosition().x + 1.0f;
	}
	
	if(player == PLAYER_2)
	{
		m_vPos.x = obj->GetPosition().x - 1.0f;
	}
	
	m_vPos.z = obj->GetPosition().z;
}

//===============================================
//選択終了フラグのセット
//===============================================
//[input]
//	flag:判定フラグ
//===============================================
void CCursor::SetEndFlag(bool flag)
{
	m_IsEnd = flag;
}

//===============================================
//カーソルの位置取得
//===============================================
int CCursor::GetCursor()
{
	return CursorMax;
}

//===============================================
//カーソルの移動
//===============================================
//[input]
//	no:プレイヤー番号
//	num:項目数
//===============================================
void CCursor::MoveCursor(int no, int num)
{
	CJoyPad::CursorWrapUpDown(no, &Cursor, num);
	
	CursorMax = Cursor % MAX_CHARA;
	
}

//===============================================
//攻撃対象の選択
//===============================================
//[input]
//	plType:プレイヤータイプ
//	attacker:攻撃者
//　target:攻撃対象
//===============================================
void CCursor::ChooseCharacter(ePlayerType plType, CCharacter *attacker[], CCharacter *target[])
{
	MoveCursor(plType, MAX_CHARA);
	
	/*攻撃タイプの設定*/
	attacker[next]->SetAttackType(plType);
	
	if(attacker[next]->GetAttackType() == SPECIAL)
	{
		switch(attacker[next]->GetSpecial() )
		{
			/*身代わり*/
			case ALTER:
			{
				/*カーソルのセット*/
				SetCursor(plType, attacker[CursorMax] );
				
				/*ターゲットのセット*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(attacker[CursorMax]);
					attacker[next]->GetTarget()->SetProtectedFlag( true );
					next++;
				}
				
				break;
				
			}
			
			/*回復魔法*/
			case RECOVER:
			{
				/*カーソルのセット*/
				SetCursor(plType, attacker[CursorMax] );
				
				/*ターゲットのセット*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(attacker[CursorMax]);
					next++;
				}
				
				break;
			}
			
			/*強化*/
			case BUILDUP:
			{
				/*カーソルのセット*/
				SetCursor(plType, attacker[CursorMax] );
				
				/*ターゲットのセット*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(attacker[CursorMax]);
					attacker[next]->GetTarget()->SetBuildFlag( true );
					next++;
				}
				
				break;
			}
			
			/*自爆*/
			case BURST:
			{
				
				/*カーソルのセット*/
				SetCursor(plType, target[CursorMax] );
				
				/*ターゲットのセット*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(target[CursorMax]);
					attacker[next]->SetBurstFlag( true );
					next++;
				}
				
				break;
				
			}
			
			/*ガード*/
			case GUARD:
			{
				
			}
			
			/*カウンター*/
			case COUNTER:
			{
				attacker[next]->SetTarget(attacker[next]);
				
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					next++;
				}
					
				break;
			}
			
			/*その他*/
			default:
			{
				/*カーソルのセット*/
				SetCursor(plType, target[CursorMax] );
				
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(target[CursorMax]);
					next++;
				}
				
				break;
			}
			
		}	
	}
	
	else
	{
		/*カーソルのセット*/
		SetCursor(plType, target[CursorMax] );
		
		
		if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
		{
			attacker[next]->SetTarget(target[CursorMax]);
			next++;
		}
	
	}
	
	/*死亡していた場合カウンターを進める*/
	if(attacker[next]->GetDeadFlag() )
	{
		next++;
	}
	
	//if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
	//{
	//	if(m_vPos.z == target->GetPosition().z)
	//	{
	//		attacker[next]->SetTarget(target);
	//	}
	//	
	//	next++;
	//}
	
	if(next > MAX_CHARA - 1)
	{
		this->m_IsEnd = true;	
		
		next = 0;
	}
	
	
	CDebug::DrawString("player%d:%sのターン:Type:%d", plType, attacker[next]->GetName().data(), attacker[next]->GetAttackType() );
	
	
		
}

//===============================================
//攻撃対象の選択
//===============================================
//[input]
//	attacker:攻撃者
//　target:攻撃対象
//===============================================
void CCursor::ChooseCharacter(CCharacter *attacker, CCharacter *target)
{
	if(m_vPos.z == target->GetPosition().z)
	{
		/*戦闘シーンに移動*/
		attacker->SetTarget(target);
	}
		
}


//===============================================
//選択終了フラグの取得
//===============================================
//[return]
//	選択終了フラグの取得
//===============================================
bool CCursor::GetEndFlag()
{
	return m_IsEnd;
}
