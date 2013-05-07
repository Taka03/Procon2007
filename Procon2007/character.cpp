//*==============================================
//character.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "character.h"
#include "joypad.h"
#include "debug.h"
#include "rand.h"
#include "font.h"

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CCharacter::CCharacter()
{
	m_Status = 0;
	m_OldStatus = 0;
	m_FirstStatus = 0;
	
	m_Special = CRITICAL;
	m_AttackType = ATTACK;
	//m_Target = FENCER;
	m_pTarget = NULL;
	//m_pCursor = NULL;
	m_name.clear();
	
	m_IsDead = false;
	m_IsEnd = false;
	m_IsAttackEnd = false;
	m_IsSpecial = false;
	m_IsProtected = false;
	m_IsBuildUp = false;
	m_IsBurst = false;
	
	m_AnimTime = 0.000f;
	
	for( int i = 0;i < SE_MAX;i++ )
	{
		se[i] = CSoundFactory::Create( (eSound)(i) );
	}
	
	
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	type:タイプ
//[return]
//	なし
//===============================================
CCharacter::CCharacter(int type)
{
	m_Status = 0;
	m_OldStatus = 0;
	m_FirstStatus = 0;
	
	m_name.clear();
	m_Special = CRITICAL;
	m_AttackType = ATTACK;
	//m_Target = FENCER;
	m_pTarget = NULL;
//	m_pCursor = NULL;

	m_IsDead = false;
	m_IsEnd = false;
	m_IsSpecial = false;
	
	Burst = new CEffect("data/ef_explosion.x");
	
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	type:キャラクタータイプ
//	plType:プレイヤータイプ
//[return]
//	なし
//===============================================
CCharacter::CCharacter(eCharaType type, ePlayerType plType)
{
	//switch(type)
	//{
	//	this = new 
	//}
}

//===============================================
//デストラクタ
//===============================================
CCharacter::~CCharacter()
{
	Release();
}

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CCharacter::Init()
{
	
}

//===============================================
//処理
//===============================================
//[input]
//
//[return]
//
//===============================================
void CCharacter::Exec()
{

}

//===============================================
//効果音の読み込み
//===============================================
void CCharacter::LoadSe()
{
	char *name[SE_MAX] =
	{
		"data/swordman_attack.WAV",
		"data/swordman_critical.WAV",
		"data/magister_attack1.WAV",
		"data/magister_attack2.WAV",
		"data/magister_heal.WAV",
		"data/magister_charge.WAV",
		"data/ranger_attack.WAV",
		"data/ranger_powerup.WAV",
		"data/contractor_attack.WAV",
		"data/contractor_bomb.WAV",
		"data/guardner_charge.WAV",
		"data/all_dead.WAV",
	};
	
	//for( int i = 0;i < SE_MAX;i++ )
	//{
	//	se[i] = new CSound(name[i], i);
	//}
}

//===============================================
//効果音の停止
//===============================================
//[input]
//	index:インデックス
//===============================================
void CCharacter::PlaySe(int index)
{
	se[index]->Play(index, 0, 0);
}


//===============================================
//効果音の停止
//===============================================
//[input]
//	index:インデックス
//===============================================
void CCharacter::StopSe(int index)
{
	if( se[index]->IsPlay(index) )
	{
		se[index]->Stop(index);
	}
}

//===============================================
//移動
//===============================================
//[input]
//	target:移動対象先
//===============================================
void CCharacter::Move(CCharacter *target)
{
	if(this->GetCharaType() == FENCER)
	{
		Attack(target, 2, GetLastAnimFrame() / 2 - 0.1);
	}
	
	else if(this->GetCharaType() == GUARDIAN)
	{
		Attack(target, 2, GetLastAnimFrame() / 2);
	}
	
	else if( this->GetCharaType() == RANGER)
	{
		Attack(target, 1, GetLastAnimFrame() / 2 - 0.2);
	}	
	
	else if( this->GetCharaType() == CONTRACTOR )
	{
		Attack(target, 1, GetLastAnimFrame() / 2 - 0.1);
	}
	

	
}

//===============================================
//攻撃
//===============================================
//[input]
//	target:攻撃対象先
//	moveoffset:移動補正値
//	motoffset:モーション補正値
//===============================================
void CCharacter::Attack(CCharacter *target, int moveoffset, double motoffset)
{
	if(m_plType == PLAYER_1)
	{
		if(m_vPos.x >= target->m_vPos.x - moveoffset)
		{
			SetMotion( MOT_ATTACK );
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
			//{
			//	this->SetCurrentAnimPos( this->GetLastAnimFrame() );
			//}
			
			CalcDamage( target, motoffset );
		}
					
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
			
			
			//
			//if( this->GetCharaType() == FENCER)
			//{
			//	if( !(m_IsCritical) )
			//	{
			//		this->PlaySe(SE_ATTACK_FENCER);
			//		
			//	}
			//	
			//	else
			//	{
			//		this->PlaySe(SE_CRITICAL);
			//		//se[SE_CRITICAL]->Play(SE_CRITICAL, 1, 0);
			//		
			//	}
			//}
			//
			//else if( this->GetCharaType() == RANGER )
			//{
			//	this->PlaySe(SE_ATTACK_RANGER);
			//	//se[SE_ATTACK_RANGER]->Play(SE_ATTACK_RANGER, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == CONTRACTOR )
			//{
			//	this->PlaySe(SE_ATTACK_CON);
			//	//se[SE_ATTACK_CON]->Play(SE_ATTACK_CON, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == GUARDIAN )
			//{
			//	this->PlaySe(SE_ATTACK_FENCER);
			//	//se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
			//	
			//}
			//
			
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
			//{
			//	this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
			//}
		
	}
	
	else
	{
		if(m_vPos.x <= target->m_vPos.x + moveoffset)
		{
			
			this->SetMotion(MOT_ATTACK);
			
			//if( this->GetCharaType() == FENCER)
			//{
			//	if( !(m_IsCritical) )
			//	{
			//		this->PlaySe(SE_ATTACK_FENCER);
			//		
			//	}
			//	
			//	else
			//	{
			//		this->PlaySe(SE_CRITICAL);
			//		//se[SE_CRITICAL]->Play(SE_CRITICAL, 1, 0);
			//		
			//	}
			//}
			//
			//else if( this->GetCharaType() == RANGER )
			//{
			//	this->PlaySe(SE_ATTACK_RANGER);
			//	//se[SE_ATTACK_RANGER]->Play(SE_ATTACK_RANGER, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == CONTRACTOR )
			//{
			//	this->PlaySe(SE_ATTACK_CON);
			//	//se[SE_ATTACK_CON]->Play(SE_ATTACK_CON, 1, 0);
			//	
			//}
			//
			//else if( this->GetCharaType() == GUARDIAN )
			//{
			//	this->PlaySe(SE_ATTACK_FENCER);
			//	//se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
			//	
			//}
			
			//}
			CalcDamage( target, motoffset);
			
			//target->numDamage->SetVariableFlag( false );
			
		}
		
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
	}	

}

//===============================================
//攻撃
//===============================================
//[input]
//	target:攻撃対象先
//	moveoffset:移動補正値
//	motoffset:モーション補正値
//===============================================
void CCharacter::BurstS(CCharacter *target, int moveoffset, double motoffset)
{
	if(m_plType == PLAYER_1)
	{
		if(m_vPos.x >= target->m_vPos.x - moveoffset)
		{
			if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
			{
				this->SetCurrentAnimPos( this->GetLastAnimFrame() );
				
				if(this->GetBurstFlag() )
				{
					this->PlaySe(SE_BOMB);
				}
				
			}
			
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
			//{
			//	this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
			//}
			CalcDamage( target, motoffset );
		}
					
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
		
	}
	
	else
	{
		if(m_vPos.x <= target->m_vPos.x + moveoffset)
		{
			
			//this->SetMotion(MOT_ATTACK);
			
			if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
			{
				this->SetCurrentAnimPos( this->GetLastAnimFrame() );
				
				if(this->GetBurstFlag() )
				{
					this->PlaySe(SE_BOMB);
				}
				
			}
			
			
			//if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
			//{
			//	this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
			//}
			CalcDamage( target, motoffset);
			
			//target->numDamage->SetVariableFlag( false );
			
		}
		
		else
		{
			this->SetMotion(MOT_MOVE);
			
			CVector3 vDirection;
			
			vDirection = this->GetPosition() - target->GetPosition();
			
			m_vPos -= vDirection * 0.03f;	
		
		}
		
			
/*			if( this->GetMotion() == MOT_ATTACK )
			{
				if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame()  - 0.01)
				{
					this->SetCurrentAnimPos(this->GetLastAnimFrame()  - 0.01);
				}
				
				if(this->GetCurrentAnim().AnimPos >= motoffset) 
				{
					CalcDamage( target );
				
					if( this->GetCharaType() == FENCER)
					{
						if( !(m_IsCritical) )
						{
							se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
							
						}
						
						else
						{
							se[SE_CRITICAL]->Play(SE_CRITICAL, 1, 0);
							
						}
					}
					
					else if( this->GetCharaType() == RANGER )
					{
						se[SE_ATTACK_RANGER]->Play(SE_ATTACK_RANGER, 1, 0);
						
					}
					
					else if( this->GetCharaType() == CONTRACTOR )
					{
						se[SE_ATTACK_CON]->Play(SE_ATTACK_CON, 1, 0);
						
					}
					
					else if( this->GetCharaType() == GUARDIAN )
					{
						se[SE_ATTACK_FENCER]->Play(SE_ATTACK_FENCER, 1, 0);
						
					}
					
				}
				
			}
			
		}*/
		
	}	

}

//===============================================
//魔法攻撃
//===============================================
//[input]
//	target:攻撃対象先
//===============================================
void CCharacter::MagicAttack(CCharacter *target)
{	
	this->SetMotion(MOT_MOVE);
	
	if(!Fire->GetVariableFlag() )
	{
		Fire->SetPosition(this->m_vPos);
		
		if(this->GetPlayerType() == PLAYER_1 )
		{
			Fire->SetRotate(CVector3(GET_ANGLE(45), 0, 0) );
		}
		
		else
		{
			Fire->SetRotate(CVector3(GET_ANGLE(-45), 0, 0) );
		}
	}
	
	Fire->SetVariableFlag(true);
	
	CVector3 vDirection = this->GetPosition() - target->GetPosition();
	
	
		
	Fire->AddPosition(vDirection * 0.03f);
		
	if(this->GetCurrentAnim().AnimPos >= GetLastAnimFrame() )
	{
		
		
		this->SetMotion(MOT_ATTACK);
		
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() / 3)
		{
			this->SetCurrentAnimPos(this->GetLastAnimFrame() / 3);
		}
		
		this->PlaySe(SE_ATTACK1_MAGI);
		this->PlaySe(SE_ATTACK2_MAGI);
		
		this->CalcDamage(target, GetLastAnimFrame() / 2 );
		
	}
}

//===============================================
//魔法全体攻撃
//===============================================
//[input]
//	target:攻撃対象先
//===============================================
void CCharacter::MagicAllAttack(CCharacter *target[])
{
	this->SetMotion(MOT_MOVE);
	
	if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame())
	{
	
		this->SetMotion(MOT_ATTACK);
		
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			//Burst->SetVariableFlag(true);
			
			this->SetCurrentAnimPos(this->GetLastAnimFrame() );
		}
		
		//CVector3 Pos(target[2]->GetPosition
		
		Burst->SetPosition(target[2]->GetPosition() );
		
		//this->Burst
		
		this->CalcDamage(target);
			
		
	}
}

//===============================================
//身代わり
//===============================================
//[input]
//	target:身代わり先
//===============================================
void CCharacter::Alternate(CCharacter *target[])
{
	this->SetTarget( target[FENCER] );
}


//===============================================
//回復魔法
//===============================================
//[input]
//	target:回復対象先
//===============================================
void CCharacter::Recover(CCharacter *target)
{
	if( this->GetPlayerType() == PLAYER_1 )
	{
		this->numDamage->SetPosition(100, 200);
		target->numDamage->SetPosition(400, 200);
		this->numDamage->SetVisibleFlag( true );
		target->numDamage->SetVisibleFlag( true );
	}
	
	else
	{
		this->numDamage->SetPosition(400, 200);
		target->numDamage->SetPosition(100, 200);
		
		this->numDamage->SetVisibleFlag( true );
		target->numDamage->SetVisibleFlag( true );
		
	}
	
	this->SetMotion(MOT_MOVE);
	
	int Recover = this->GetStatus() / 2;//回復量
	
	if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
	{
		this->SetMotion( MOT_ATTACK );
		
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			this->SetCurrentAnimPos(this->GetLastAnimFrame() );
			
			//if(m_IsAttackEnd)
			//{
			//	this->StopSe(SE_HEAL);
			//}
			
			//this->SetEndFlag( true );
		}
		
	}
	
	if(!m_IsAttackEnd)
	{
		if(!(target->GetDeadFlag() ) )
		{
			target->m_Status += Recover;
			
			this->m_Status -= Recover;
		}
		
		this->PlaySe(SE_HEAL);
	}
	
	
	this->SetAttackEndFlag( true );
	
}

//===============================================
//強化
//===============================================
//[input]
//	target:強化対象先
//===============================================
void CCharacter::BuildUp(CCharacter *target)
{
	this->SetMotion(MOT_SPECIAL);
	
	if( !(this->GetAttackEndFlag() ) )
	{
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() * 2)		
		{
			this->SetCurrentAnimPos(this->GetLastAnimFrame() * 2);
			
		}
		
		target->SetBuildFlag(true);
		
	}
	
	this->SetAttackEndFlag( true );
	
}






//===============================================
//アニメーションの切り替え
//===============================================
//void CCharacter::ChangeAnimation()
//{
//	switch(m_Motion)
//	{
//		/*立ちモーション*/
//		case MOT_STAND:
//		{
//			m_FirstFrame = 3;
//			
//			m_LastFrame = 62;		
//			
//			break;
//		}
//		
//		/*移動モーション*/
//		case MOT_MOVE:
//		{
//			m_FirstFrame = 63;
//			
//			m_LastFrame = 126;
//			
//			break;
//		}
//		
//		/*攻撃モーション*/
//		case MOT_ATTACK:
//		{
//			m_FirstFrame = 127;
//			
//			m_LastFrame = 188;
//			
//			break;
//		}
//		
//		/*ダメージモーション*/
//		case MOT_DAMAGE:
//		{
//			m_FirstFrame = 210;
//			
//			m_LastFrame = 272;
//			
//			break;
//		}
//		
//		/*死亡モーション*/
//		case MOT_DEAD:
//		{
//			m_FirstFrame = 273;
//			
//			m_LastFrame = 333;
//			
//			break;
//		}
//	}
//}

//===============================================
//位置座標の取得
//===============================================
//[return]
//	位置座標
//===============================================
CVector3 CCharacter::GetPosition()
{
	return m_vPos;
}

//===============================================
//ステータスの取得
//===============================================
//[return]
//	ステータス
//===============================================
int CCharacter::GetStatus()
{
	return m_Status;
}

//===============================================
//古いステータスの取得
//===============================================
//[return]
//	古いステータス
//===============================================
int CCharacter::GetOldStatus()
{
	return m_OldStatus;
}


//===============================================
//初期ステータスの取得
//===============================================
//[return]
//	初期ステータス
//===============================================
int CCharacter::GetFirstStatus()
{
	return m_FirstStatus;
}

//===============================================
//攻撃対象の取得
//===============================================
//[return]
//	攻撃対象
//===============================================
CCharacter *CCharacter::GetTarget()
{
	return m_pTarget;
}

//===============================================
//死亡フラグの取得
//===============================================
//[return]
//	死亡フラグ
//===============================================
bool CCharacter::GetDeadFlag()
{
	return m_IsDead;
}

//===============================================
//行動終了フラグの取得
//===============================================
//[return]
//	行動終了フラグ
//===============================================
bool CCharacter::GetEndFlag()
{
	return m_IsEnd;
}	

//===============================================
//クリティカルフラグの取得
//===============================================
//[return]
//	クリティカルフラグ
//===============================================
bool CCharacter::GetCriticalFlag()
{
	return m_IsCritical;
}	

//===============================================
//←溜め→フラグの取得
//===============================================
//[return]
//	←溜め→フラグ
//===============================================
bool CCharacter::GetChargeFlag()
{
	return m_IsCharge;
}	


//===============================================
//攻撃終了フラグの取得
//===============================================
//[return]
//	攻撃終了フラグ
//===============================================
bool CCharacter::GetAttackEndFlag()
{
	return m_IsAttackEnd;
}

//===============================================
//特殊能力判定フラグの取得
//===============================================
//[return]
//	特殊能力判定フラグの取得
//===============================================
bool CCharacter::GetSpecialFlag()
{
	return m_IsSpecial;
}

//===============================================
//強化判定フラグの取得
//===============================================
//[return]
//	強化判定フラグの取得
//===============================================
bool CCharacter::GetBuildFlag()
{
	return m_IsBuildUp;
}

//===============================================
//身代わり判定フラグの取得
//===============================================
//[return]
//	身代わり判定フラグの取得
//===============================================
bool CCharacter::GetProtectedFlag()
{
	return m_IsProtected;
}

//===============================================
//バーストフラグの設定
//===============================================
//[input]
//	flag:バーストフラグ
//===============================================
bool CCharacter::GetBurstFlag()
{
	return m_IsBurst;
}

//===============================================
//防御フラグの取得
//===============================================
//[return]
//	防御フラグ
//===============================================
bool CCharacter::GetGuardFlag()
{
	return m_IsGuard;
}	

//===============================================
//カウンターフラグの取得
//===============================================
//[return]
//	カウンターフラグ
//===============================================
bool CCharacter::GetCounterFlag()
{
	return m_IsCounter;
}	


//===============================================
//キャラタイプの取得
//===============================================
//[return]
//	キャラタイプ
//===============================================
eCharaType CCharacter::GetCharaType()
{
	return m_CharaType;
}

//===============================================
//攻撃タイプの取得
//===============================================
//[return]
//	攻撃タイプ
//===============================================
eAttackType CCharacter::GetAttackType()
{
	return m_AttackType;
}

//===============================================
//特殊能力の取得
//===============================================
//[return]
//	特殊能力
//===============================================
eSpecial CCharacter::GetSpecial()
{
	return m_Special;
}

//===============================================
//特殊能力タイプの取得
//===============================================
//[return]
//	特殊能力タイプ
//===============================================
eSpecialType CCharacter::GetSpecialType()
{
	return m_SpecialType;
}

//===============================================
//キャラの名前の取得
//===============================================
//[return]
//	キャラの名前
//===============================================
string CCharacter::GetName()
{
	return m_name.c_str();
}

//===============================================
//現在のアニメーション構造体の取得
//===============================================
//[return]
//	現在のアニメーション構造体
//===============================================
HIANIMATION_DESC CCharacter::GetCurrentAnim()
{
	return m_Anim[m_CurAnimID];
}


//===============================================
//モーションの取得
//===============================================
//[return]
//	モーション
//===============================================
eMotion CCharacter::GetMotion()
{
	return m_Motion;
}

//===============================================
//モーションの取得
//===============================================
//[return]
//	モーション
//===============================================
ePlayerType CCharacter::GetPlayerType()
{
	return m_plType;
}


//===============================================
//最初のフレーム数の取得
//===============================================
//[return]
//	最初のフレーム
//===============================================
float CCharacter::GetFirstFrame()
{
	return m_FirstFrame;
}

//===============================================
//最後のフレーム数の取得
//===============================================
//[return]
//	最後のフレーム
//===============================================
float CCharacter::GetLastFrame()
{
	return m_LastFrame;
}

//===============================================
//アニメーションの最後のフレーム取得
//===============================================
//[return]
//	アニメーションの最後のフレーム
//===============================================
double CCharacter::GetLastAnimFrame()
{
	return m_LastAnimFrame;
}

//===============================================
//位置の設定
//===============================================
//[input]
//	posx:X座標
//	posy:Y座標
//	posz:Z座標
//===============================================
void CCharacter::SetPosition(float posx, float posy, float posz)
{
	m_vPos.x = posx;
	m_vPos.y = posy;
	m_vPos.z = posz;
}

//===============================================
//角度の設定
//===============================================
//[input]
//	xangle:X角度
//	yagle:Y角度
//	zangle:Z角度
//===============================================
void CCharacter::SetRotate(float xangle, float yangle, float zangle)
{
	m_vRot.x = xangle;
	m_vRot.y = yangle;
	m_vRot.z = zangle;
}


//===============================================
//ステータスの設定
//===============================================
//[input]
//	status:設定するステータス
//===============================================
void CCharacter::SetStatus(int status)
{
	m_Status = status;
	m_OldStatus = status;
	m_FirstStatus = status;
}

//===============================================
//カーソルの位置セット
//===============================================
//[input]
//	player:プレイヤータイプ
//	obj:攻撃対象
//===============================================
void CCharacter::SetCursor(ePlayerType plType, CCharacter *obj)
{
	/*カーソルの位置セット*/
	//m_pCursor->SetCursor(plType, obj);
}

//===============================================
//古いステータスの設定
//===============================================
void CCharacter::SetOldStatus()
{
	m_OldStatus = m_Status;
}

//===============================================
//攻撃対象の設定
//===============================================
//[input]
//	obj:攻撃対象
//===============================================
void CCharacter::SetTarget(CCharacter *obj)
{
	m_pTarget = obj;
}

//===============================================
//攻撃タイプの設定(攻撃か特殊か)
//===============================================
//[input]
//	no:プレイヤー番号
//===============================================
void CCharacter::SetAttackType(ePlayerType no)
{
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	{
		m_AttackType = ATTACK;	
	}
	
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	{
		m_AttackType = SPECIAL;
	}
	
	//CDebug::DrawString("Type:%d", m_AttackType);
	
}

//===============================================
//攻撃タイプの設定(AI用)
//===============================================
//[input]
//	type:攻撃タイプ
//===============================================
void CCharacter::SetAttackType_AI(int type)
{
	if(type == 0)
	{
		m_AttackType = ATTACK;
	}
	
	if(type == 1)
	{
		m_AttackType = SPECIAL;
	}
}

//===============================================
//特殊能力タイプの設定(攻撃系か特殊系か)
//===============================================
//[input]
//	no:プレイヤー番号
//===============================================
void CCharacter::SetSpecialType(ePlayerType no)
{
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_LEFT) )
	{
		m_SpecialType = SP_ATTACK;
	}
	
	if(CJoyPad::GetState(no, PAD_STATE_HOLD, PAD_DIR_RIGHT) )
	{
		m_SpecialType = SP_ASSIST;
	}
}

//===============================================
//特殊能力タイプの設定(攻撃系か特殊系か)
//===============================================
//[input]
//	no:プレイヤー番号
//===============================================
void CCharacter::SetSpecialType_AI(bool type)
{
	if(type == false ) 
	{
		m_SpecialType = SP_ATTACK;
	}
	
	else
	{
		m_SpecialType = SP_ASSIST;
	}
}


//===============================================
//死亡フラグの設定
//===============================================
//[input]
//	flag:死亡したかどうか
//===============================================
void CCharacter::SetDeadFlag(bool flag)
{
	m_IsDead = flag;
}

//===============================================
//クリティカルフラグの設定
//===============================================
//[input]
//	flag:クリティカルフラグ
//===============================================
void CCharacter::SetCriticalFlag(bool flag)
{
	m_IsCritical = flag;
}


//===============================================
//強化フラグの設定
//===============================================
//[input]
//	flag:強化したかどうか
//===============================================
void CCharacter::SetBuildFlag(bool flag)
{
	m_IsBuildUp = flag;
}

//===============================================
//身代わりフラグの設定
//===============================================
//[input]
//	flag:身代わりしたかどうか
//===============================================
void CCharacter::SetProtectedFlag(bool flag)
{
	m_IsProtected = flag;
}

//===============================================
//行動終了フラグの設定
//===============================================
//[input]
//	flag:行動終了したかどうか
//===============================================
void CCharacter::SetBurstFlag(bool flag)
{
	m_IsBurst = flag;
}

//===============================================
//行動終了フラグの設定
//===============================================
//[input]
//	flag:行動終了したかどうか
//===============================================
void CCharacter::SetEndFlag(bool flag)
{
	m_IsEnd = flag;
}

//===============================================
//行動終了フラグの設定
//===============================================
//[input]
//	flag:行動終了したかどうか
//===============================================
void CCharacter::SetAttackEndFlag(bool flag)
{
	m_IsAttackEnd = flag;
}

//===============================================
//特殊能力フラグの設定
//===============================================
//[input]
//	flag:特殊能力フラグ
//===============================================
void CCharacter::SetSpecialFlag(bool flag)
{
	m_IsSpecial = flag;
}

//===============================================
//チャージフラグの設定
//===============================================
//[input]
//	flag:チャージフラグ
//===============================================
void CCharacter::SetChargeFlag(bool flag)
{
	m_IsCharge= flag;
}

//===============================================
//カウンターフラグの設定
//===============================================
//[input]
//	flag:カウンターフラグ
//===============================================
void CCharacter::SetCounterFlag(bool flag)
{
	m_IsCounter= flag;
}

//===============================================
//ガードフラグの設定
//===============================================
//[input]
//	flag:ガードフラグ
//===============================================
void CCharacter::SetGuardFlag(bool flag)
{
	m_IsGuard = flag;
}

//===============================================
//モーションの設定
//===============================================
//[input]
//	motion:設定するモーション
//===============================================
void CCharacter::SetMotion(eMotion motion)
{
	if(m_Motion != MOT_DEAD)
	{
		m_Motion = motion;
	}
}

//===============================================
//アニメーションの設定
//===============================================
//[input]
//	animID:アニメーションID
//===============================================
void CCharacter::SetAnimation(int animID)
{
	//m_pAnimController->RegisterAnimationSet
	//m_pAnimController->GetAnimationSet(animID, 
}

//===============================================
//現在のアニメーション位置の設定
//===============================================
//[input]
//	pos:位置
//===============================================
void CCharacter::SetCurrentAnimPos(double pos)
{
	m_Anim[m_CurAnimID].AnimPos = pos;
}



//===============================================
//ステータスの増減
//===============================================
//[input]
//	status:ステータス
//===============================================
void CCharacter::CalcStatus(int status)
{
	m_Status += status;
}

//===============================================
//ダメージ量の計算
//===============================================
//[input]
//	target:攻撃対象
//[return]
//	ダメージ
//===============================================
int CCharacter::CalcDamage(CCharacter *target[])
{
	int Damage = 0;//ダメージ
	
	int Attack = this->GetStatus() / 3; //攻撃力
	
	int OldAttack = Attack;
	
	int DeadCharaNum = 0;//死亡キャラ数
	
	this->m_IsSpecial = true;
	
	if(this->GetPlayerType() == PLAYER_1 )
	{
		this->numDamage->SetPosition(200.0, 200 );
		
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			target[i]->numDamage->SetPosition( F(400), F(200 + i * 50) );
			target[i]->numDamage->SetVisibleFlag( true );
		}
	}
	
	else 
	{
		this->numDamage->SetPosition(400, 200 );
		
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			target[i]->numDamage->SetPosition( F(100), F(200 + i * 50) );
			target[i]->numDamage->SetVisibleFlag( true );
		}
	}
	
	if( !(this->m_IsEnd) && !(this->m_IsAttackEnd) )
	{
		/*死亡キャラを増やす*/
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			if(target[i]->GetDeadFlag() )
			{
				DeadCharaNum ++;
			}	
		
		}
		
		int LiveCharaNum = MAX_CHARA - DeadCharaNum;//生存キャラ数
		
		/*強化されている場合*/
		if(this->GetBuildFlag() )
		{
			Attack *= 3;
		}
		
		for( int i = 0;i < MAX_CHARA;i++ )
		{
			
			/*ガーディアン*/
			if(target[i]->GetCharaType() == GUARDIAN)
			{
				/*カウンター*/
				if( target[i]->m_IsCounter )
				{
					target[i]->SetMotion(MOT_ATTACK);
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
				}
				
				else
				{
					Damage = Attack / LiveCharaNum;
					
					target[i]->m_Status -= Damage;
					
				}
			}
			
			else if( target[i]->GetCharaType() == CONTRACTOR )
			{
				if( target[i]->m_IsGuard )
				{
					Attack /= 10;
					
					Damage = Attack / LiveCharaNum;
					
					target[i]->m_Status -= Damage;
					
					char temp[MAX_PATH] = "";
				
					wsprintf(temp, "%d", Damage);
				
					string Str;
					
					Str = temp;
					
					target[i]->numDamage->SetText(Str);
					
					target[i]->SetMotion( MOT_SPECIAL );
					
					//target[i]->Aura->SetVariableFlag( true );
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
						
					
				}
				
				else
				{
					Damage = Attack / LiveCharaNum;
					
					target[i]->m_Status -= Damage;
				
				
				}
			
			}
			
			else
			{
				Damage = Attack / LiveCharaNum;
				
				target[i]->m_Status -= Damage;
				
				char temp[MAX_PATH] = "";
			
				wsprintf(temp, "%d", Damage);
			
				string Str;
				
				Str = temp;
				
				target[i]->numDamage->SetText(Str);
				
				
			}
			
		}		
		
		this->m_IsAttackEnd = true;
		
	}
	
	CDebug::DrawString("全体攻撃:%d", Damage );
	
	//----------------------------------------------
	//モーションの設定
	//----------------------------------------------
	for( int i = 0;i < MAX_CHARA;i++ )
	{
		if(target[i]->GetStatus() > 0)
		{
			if(target[i]->GetCharaType() == GUARDIAN )
			{
				/*カウンター*/
				if( target[i]->m_IsCounter )
				{
					target[i]->SetMotion(MOT_ATTACK);
					
					target[i]->PlaySe(SE_ATTACK_FENCER);
						
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						//target->StopSe(SE_ATTACK_FENCER);
						
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
						
				}
			}
			
			else if( target[i]->GetCharaType() == CONTRACTOR )
			{
				/*防御状態*/
				if( target[i]->m_IsGuard )
				{
					target[i]->SetMotion( MOT_SPECIAL );
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
					}
					
				}
			}
			
			else
			{
				target[i]->SetMotion( MOT_DAMAGE );

				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
				}
			}
		}
		
		else
		{
			/*カウンター*/
			if( target[i]->m_IsCounter )
			{
				target[i]->SetMotion(MOT_ATTACK);
				
				target[i]->PlaySe(SE_ATTACK_FENCER);
				
					
				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					//target[i]->StopSe(SE_ATTACK_FENCER);
					
					target[i]->SetMotion(MOT_DEAD);
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos(target[i]->GetLastAnimFrame() );
					}
				}
					
			}
			
			/*防御状態*/
			else if( target[i]->m_IsGuard )
			{
				target[i]->SetMotion( MOT_SPECIAL );
				
				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					target[i]->SetMotion(MOT_DEAD);
					
					if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
					{
						target[i]->SetCurrentAnimPos(target[i]->GetLastAnimFrame() );
					}
				}
				
			}
			
			else
			{
				target[i]->SetMotion( MOT_DEAD );
				
				if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
				{
					target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
				}
			}
			
		}
	}
	
	//	
	//	

	//	
	//	
	//	
	//	/*カウンターフラグ*/
	//	if( target[GUARDIAN]->GetCounterFlag() )
	//	{
	//		int CounterDamage = OldAttack / 2;
	//		
	//		this->m_Status -= CounterDamage;
	//		
	//		char temp[MAX_PATH] = "";
	//	
	//		wsprintf(temp, "%d", CounterDamage);
	//	
	//		string Str;
	//		
	//		Str = temp;
	//		
	//		this->numDamage->SetText(Str);
	//		
	//		this->numDamage->SetVisibleFlag(true);
	//		
	//		Damage = OldAttack / LiveCharaNum;
	//		
	//		target[GUARDIAN]->m_Status -= Damage;
	//		
	//		wsprintf(temp, "%d", Damage);
	//	
	//		Str = temp;
	//		
	//		target[GUARDIAN]->numDamage->SetText(Str);
	//		
	//	}
	//	
	//	else
	//	{
	//		Damage = Attack / LiveCharaNum;
	//		
	//		target[GUARDIAN]->m_Status -= Damage;
	//		
	//		char temp[MAX_PATH] = "";
	//		
	//		wsprintf(temp, "%d", Damage);
	//	
	//		string Str = temp;
	//		
	//		target[GUARDIAN]->numDamage->SetText(Str);
	//		
	//	
	//	}
	//	
	//	//int NormalDamage = OldAttack / LiveCharaNum;
	//	
	//	for( int i = 0;i < MAX_CHARA;i++ )
	//	{
	//		if( target[i]->GetCharaType() == CONTRACTOR )
	//		{
	//		
	//		}
	//		
	//		else if(target[i]->GetCharaType() == GUARDIAN )
	//		{
	//		
	//		}
	//		
	//		else
	//		{
	//			Damage = OldAttack / LiveCharaNum;
	//			
	//			target[i]->m_Status -= Damage;
	//			
	//			char temp[MAX_PATH] = " ";
	//			
	//			wsprintf(temp, "%d", Damage);
	//		
	//			string Str = temp;
	//			
	//			target[i]->numDamage->SetText(Str);
	//			
	//		}
	//	}
	//	
	//	
	//	this->m_IsAttackEnd = true;
	//
	//}
	//
	//for( int i = 0;i < MAX_CHARA;i++ )
	//{
	//	if(target[i]->GetStatus() > 0)
	//	{
	//		target[i]->SetMotion( MOT_DAMAGE );
	//		
	//		if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
	//		{
	//			target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
	//		}
	//	
	//	}
	//	
	//	else
	//	{
	//		target[i]->SetMotion( MOT_DEAD );
	//		
	//		if(target[i]->GetCurrentAnim().AnimPos >= target[i]->GetLastAnimFrame() )
	//		{
	//			target[i]->SetCurrentAnimPos( target[i]->GetLastAnimFrame() );
	//		}
	//	
	//	}
	//}
	
	
	
	return Damage;
		
}

//===============================================
//ダメージ量の計算
//===============================================
//[input]
//	target:攻撃対象
//[return]
//	ダメージ
//===============================================
int CCharacter::CalcDamage(CCharacter *target, double motoffset)
{
	int Damage = 0;//ダメージ
	
	int Attack = this->GetStatus() / 3;//攻撃力

	const int FIX_DAMAGE = 10;//固定ダメージ量
	
	if(this->GetPlayerType() == PLAYER_1 )
	{
		numDamage->SetPosition(400, 200);
	}
	
	else
	{
		numDamage->SetPosition(200, 200);
	}
	
	//if( target->GetPlayerType() == PLAYER_1 )
	//{
	//	target->numDamage->SetPosition( 400, 100 );
	//}
	//
	//else
	//{
	//	target->numDamage->SetPosition( 100, 100 );
	//}
	
	long rnd = JRand::GetInt(0, 1);
	
	if( this->GetCharaType() == FENCER ) 
	{
		/*クリティカル状態の時*/
		if(this->GetSpecialFlag() )
		{
			rnd = JRand::GetInt(0, 1);
			if(rnd == 0)
			{
				Attack *= 2;
				m_IsCritical = true;
			}
		}
	}
	
	if( this->GetCharaType() == RANGER )
	{
		if( this->GetAttackType() == SPECIAL )
		{
			if( this->GetSpecial() == FIRST_ATTACK )
			{
				Attack /= 2;
			}
			
		}
	}
	
	if( this->GetCharaType() == CONTRACTOR )
	{
		if( this->GetBurstFlag() )
		{
			Attack = this->GetOldStatus();
		}
	
	}
	
	if( target->GetCharaType() == CONTRACTOR )
	{
		/*防御状態*/
		if( target->m_IsGuard )
		{
			Attack /= 10;
		}
	}
	
	
	if( this->GetCharaType() == GUARDIAN )
	{
		if( this->m_IsCharge )
		{
			Attack *= 2;
		}

	}
	
	/*強化状態の時*/
	if(this->GetBuildFlag() )
	{
		Attack *= 3;
	}
	
	if( this->GetPlayerType() == PLAYER_1 )
	{
		this->numDamage->SetPosition( 400, 300 );
	}
	
	else
	{
		this->numDamage->SetPosition( 100, 200 );
	}
	
	this->numDamage->SetVisibleFlag(true);
	
	if( !(this->m_IsEnd) && !(this->m_IsAttackEnd) )
	{
		//------------------------------------
		//モーションの設定
		//------------------------------------		
		
		Damage = Attack + FIX_DAMAGE; 

		target->m_Status -= Damage;
		
		char temp[MAX_PATH] = "";
		
		wsprintf(temp, "%d", Damage);
		
		string Str;
		
		Str = temp;
		
		this->numDamage->SetText(Str);
		
		if( target->GetCharaType() == GUARDIAN )
		{
			/*カウンター*/
			if( target->m_IsCounter )
			{
				int CounterDamage = Attack / 2;
				
				this->m_Status -= CounterDamage;
				
				//CDebug::DrawString("%sに%dのカウンターダメージ", this->GetName().data(), CounterDamage);
			}
		
		}
		
		
		/*自爆*/
		if(this->GetBurstFlag() )
		{
			this->CalcStatus(-5000);
			
			this->SetBurstFlag( false );
		}
		
		this->m_IsAttackEnd = true;
		
	}
	
	if(this->GetCurrentAnim().AnimPos >= motoffset )
	{
		if(target->GetStatus() > 0)
		{
			/*カウンター*/
			if( target->m_IsCounter )
			{
				target->SetMotion(MOT_ATTACK);
				
				target->PlaySe(SE_ATTACK_FENCER);
					
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					//target->StopSe(SE_ATTACK_FENCER);
					
					
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
					
			}
			
			/*防御状態*/
			else if( target->m_IsGuard )
			{
				target->SetMotion( MOT_SPECIAL );
				
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
				
			}
			
			else
			{
				target->SetMotion( MOT_DAMAGE );

				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
			}
		}
		
		else
		{
			/*カウンター*/
			if( target->m_IsCounter )
			{
				target->SetMotion(MOT_ATTACK);
				
				target->PlaySe(SE_ATTACK_FENCER);
				
					
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					//target->StopSe(SE_ATTACK_FENCER);
					
					target->SetMotion(MOT_DEAD);
					
					if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
					{
						target->SetCurrentAnimPos(target->GetLastAnimFrame() );
					}
				}
					
			}
			
			/*防御状態*/
			else if( target->m_IsGuard )
			{
				target->SetMotion( MOT_SPECIAL );
				
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetMotion(MOT_DEAD);
					
					if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
					{
						target->SetCurrentAnimPos(target->GetLastAnimFrame() );
					}
				}
				
			}
			
			else
			{
				target->SetMotion( MOT_DEAD );
				
				if(target->GetCurrentAnim().AnimPos >= target->GetLastAnimFrame() )
				{
					target->SetCurrentAnimPos( target->GetLastAnimFrame() );
				}
			}
			
		}

	}

	return Damage;
		
}

//===============================================
//ダメージモーション
//===============================================
//[input]
//	target:対象
//===============================================
void CCharacter::DamageMotion(CCharacter *target[])
{
	if(this->GetMotion() == MOT_ATTACK)			
	{
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			if( this->GetPlayerType() == PLAYER_1 )
			{
				for( int i = 5;i < ALL_CHARA;i++ )
				{
					if( target[i]->GetMotion() != MOT_DEAD )
					{
						target[i]->SetMotion(MOT_DAMAGE);
					}
				}
			}
			
			else
			{
				for( int i = 0;i < MAX_CHARA;i++ )
				{
					if( target[i]->GetMotion() != MOT_DEAD )
					{
						target[i]->SetMotion(MOT_DAMAGE);
					}
				}
			}
		
		}
	}
	
}

//===============================================
//ダメージモーション
//===============================================
//[input]
//	target:対象
//===============================================
void CCharacter::DamageMotion(CCharacter *target)
{
	if(this->GetMotion() == MOT_ATTACK)			
	{
		if(this->GetCurrentAnim().AnimPos >= this->GetLastAnimFrame() )
		{
			if( this->GetPlayerType() == PLAYER_1 )
			{
				if( target->GetMotion() != MOT_DEAD )
				{
					target->SetMotion(MOT_DAMAGE);
				}
				
			}
			
			else
			{
				if( target->GetMotion() != MOT_DEAD )
				{
					target->SetMotion(MOT_DAMAGE);
				}
			}
		
		}
	}
	
}


//===============================================
//死亡モーション
//===============================================
//[input]
//	target:対象
//===============================================
void CCharacter::DeadMotion(CCharacter *target)
{
	//if(target->GetStatus() <= 0)
	//{
	//	target->SetMotion(MOT_DEAD);
	//}
}


//===============================================
//キャラクターの選択
//===============================================
//[input]
//	target:攻撃対象
//===============================================
void CCharacter::ChooseCharacter(CCharacter *target)
{
	//m_pCursor->ChooseCharacter(this, target);
}


//===============================================
//キャラの入れ替え
//===============================================
//[input]
//	target:対象とするキャラ
//===============================================
int CCharacter::Swap(CCharacter attacker, CCharacter target)
{
	int temp;
	
	temp = attacker.m_Status;
	attacker.SetStatus(target.m_Status);
	target.SetStatus(temp);
	
	return temp;
}

//void CCharacter::Swap(CCharacter *target1, CCharacter *target2)
//{
//	CCharacter temp;
//	
//	temp = *target1;
//	
//	*target1 = *target2;
//	
//	*target2 = temp;
//}





	


