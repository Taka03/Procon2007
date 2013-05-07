//*==============================================
//joypad.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joypad.h"

//===============================================
//variable
//===============================================
static const int PadSortBitTbl[] =
{
	1 << 0,	 //PAD_DIR_UP
	1 << 1,  //PAD_DIR_DOWN
	1 << 2,  //PAD_DIR_LEFT
	1 << 3,  //PAD_DIR_RIGHT
	
	1 << 4,  //PAD_BUTTON_01
	1 << 5,  //PAD_BUTTON_02
	1 << 6,  //PAD_BUTTON_03
	1 << 7,  //PAD_BUTTON_04
	1 << 8,  //PAD_BUTTON_05
	1 << 9,  //PAD_BUTTON_06
	1 << 10, //PAD_BUTTON_07
	1 << 11, //PAD_BUTTON_08
	1 << 12, //PAD_BUTTON_09
	1 << 13, //PAD_BUTTON_10
	1 << 14, //PAD_BUTTON_11
	1 << 15, //PAD_BUTTON_12
	1 << 16, //PAD_BUTTON_13
	1 << 17, //PAD_BUTTON_14
	1 << 18, //PAD_BUTTON_15
	1 << 19, //PAD_BUTTON_16
	
	0xFFFFFFFF,
};

int CJoyPad::m_UseMapPadMax;
int CJoyPad::m_KeyRepeatInterval;
int CJoyPad::m_KeyRepeatTime;
bool CJoyPad::m_IsUseAlias;

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CJoyPad::Init()
{
	CJoyPad::Initialize(2, true, 30, 3);
	
	CJoyPad::SetButton(0, PAD_BUTTON_01, 0);
	CJoyPad::SetButton(0, PAD_BUTTON_02, 1);
	CJoyPad::SetButton(0, PAD_BUTTON_03, 2);
	CJoyPad::SetButton(0, PAD_BUTTON_04, 3);
	
	CJoyPad::SetButton(1, PAD_BUTTON_01, 0);
	CJoyPad::SetButton(1, PAD_BUTTON_02, 1);
	CJoyPad::SetButton(1, PAD_BUTTON_03, 2);
	CJoyPad::SetButton(1, PAD_BUTTON_04, 3);
	
	
	CJoyPad::SetAlias(0, PAD_BUTTON_01, DIK_Z);
	CJoyPad::SetAlias(0, PAD_BUTTON_02, DIK_X);
	CJoyPad::SetAlias(0, PAD_BUTTON_03, DIK_C);
	CJoyPad::SetAlias(0, PAD_BUTTON_04, DIK_V);
	
	CJoyPad::SetAlias(0, PAD_DIR_UP, DIK_W);
	CJoyPad::SetAlias(0, PAD_DIR_DOWN, DIK_S);
	CJoyPad::SetAlias(0, PAD_DIR_LEFT, DIK_A);
	CJoyPad::SetAlias(0, PAD_DIR_RIGHT, DIK_D);
	
	CJoyPad::SetAlias(1, PAD_BUTTON_01, DIK_B);
	CJoyPad::SetAlias(1, PAD_BUTTON_02, DIK_N);
	CJoyPad::SetAlias(1, PAD_BUTTON_03, DIK_M);
	CJoyPad::SetAlias(1, PAD_BUTTON_04, DIK_COMMA);
	
	CJoyPad::SetAlias(1, PAD_DIR_UP, DIK_UP);
	CJoyPad::SetAlias(1, PAD_DIR_DOWN, DIK_DOWN);
	CJoyPad::SetAlias(1, PAD_DIR_LEFT, DIK_LEFT);
	CJoyPad::SetAlias(1, PAD_DIR_RIGHT, DIK_RIGHT);
	
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CJoyPad::Exec()
{
	/*パッドデータの更新*/
	CJoyPad::Update();
}



//===============================================
//初期化
//===============================================
//[input]
//	PadMax:パッドの最大数
//	IsUseAlias:キーボードの代用判定
//	KeyRepeatTime:キーの連続時間
//	KeyRepearInter:	
//[return]
//	なし
//===============================================
void CJoyPad::Initialize(int PadMax, bool IsUseAlias, int KeyRepeatTime, int KeyRepeatInter)
{
	m_UseMapPadMax = PadMax;
	m_KeyRepeatTime = KeyRepeatTime;
	m_KeyRepeatInterval	= KeyRepeatInter;
	m_IsUseAlias = IsUseAlias;
}

//===============================================
//パッドの更新
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CJoyPad::Update()
{
	int x;
	int y;
	
	//------------------------------------
	//各パッドの更新
	//------------------------------------
	for(int i = 0;i < m_UseMapPadMax;i++)
	{
				
		//-----------------------------------
		//ワーク初期化
		//-----------------------------------
		m_pJoystickData[i].KeyStateWork[1] = m_pJoystickData[i].KeyStateWork[0];
		m_pJoystickData[i].KeyStateWork[0] = 0x00000000;
		
		DIJOYSTATE2 Joy;
		
		//-----------------------------------
		//ジョイスティックの状態を取得
		//-----------------------------------
		if(CInput::GetJoystickData(i, &Joy) )
		{
			x = Joy.lX;
			y = Joy.lY;
			
			/*左側*/
			if(x < 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_LEFT];
			}
			
			/*右側*/
			if(x > 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_RIGHT];
			}
			
			/*上側*/
			if(y < 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP];
			}
			
			/*下側*/
			if(y > 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_DOWN];
			}
			
			/*ボタン*/
			for(int j = 0; j <= PAD_BUTTON_MAX;j++)
			{
				if(Joy.rgbButtons[j])
				{
					m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[j+4];
				}
			}
			
			/*POVを方向キーに変換*/
			if(m_pJoystickData[i].IsUsePOVDirection)
			{
				switch(Joy.rgdwPOV[0])
				{
					case POV_N:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP];
						break;
					}
					
					case POV_NE:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP] | PadSortBitTbl[PAD_DIR_RIGHT];
						break;
					}
					
					case POV_E:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_RIGHT];
						break;
					}
					
					case POV_SE:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_DOWN] | PadSortBitTbl[PAD_DIR_RIGHT];
						break;
					}
					
					case POV_S:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_DOWN];
						break;
					}
					
					case POV_SW:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_DOWN] | PadSortBitTbl[PAD_DIR_LEFT];
						break;
					}
					
					case POV_W:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_LEFT];
						break;
					}
					
					case POV_NW:
					{
						m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP] | PadSortBitTbl[PAD_DIR_LEFT];
						break;
					}
					
					default:
					{
						break;
					}
				}	
			}
		}
			
		//--------------------------------------------
		//キーボードの状態の取得
		//--------------------------------------------
		if(m_IsUseAlias)
		{
			///*左側*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_LEFT] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_LEFT];
			}	
			
			//*右側*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_RIGHT] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_RIGHT];
			}
			
			///*上側*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_UP] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP];
			}
			
			///*下側*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_DOWN] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_DOWN];
			}
			
			for(int j = (int)PAD_BUTTON_01; j < (int)PAD_BUTTON_16;j++)
			{
				if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[j]) )
				{
					m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[j];
				}
			}
		}
		
		//----------------------------------
		//状態更新
		//----------------------------------
		m_pJoystickData[i].KeyState[PAD_STATE_PUSH] = (~m_pJoystickData[i].KeyStateWork[1]) & (m_pJoystickData[i].KeyStateWork[0]);
		m_pJoystickData[i].KeyState[PAD_STATE_PULL] = (m_pJoystickData[i].KeyStateWork[1]) & (~m_pJoystickData[i].KeyStateWork[0]); 
		m_pJoystickData[i].KeyState[PAD_STATE_HOLD] = (m_pJoystickData[i].KeyStateWork[1]) & (m_pJoystickData[i].KeyStateWork[1]);
		m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] = 0x00000000;
		
		//----------------------------------
		//キーリピート
		//----------------------------------
		for(int j = 0;j < (int)PAD_SORT_MAX;j++)
		{
			/*押している状態*/
			if(CJoyPad::GetState(i, PAD_STATE_HOLD, (ePadSort)j ) )
			{
				/*一回目は検出しておく(押した瞬間を拾うため*/
				if(m_pJoystickData[i].KeyRepeatCounter[j] == 0)
				{
					m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] |= PadSortBitTbl[j];
				}
				
				/*一定時間押し続けてるときに一定間隔でON・OFF繰り返し*/
				else if(m_pJoystickData[i].KeyRepeatCounter[j] > m_KeyRepeatTime)
				{
					if(!(m_pJoystickData[i].KeyRepeatCounter[j] % m_KeyRepeatInterval) )
					{
						m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] |= PadSortBitTbl[j];
					}
				}
				
				/*カウンター++*/
				m_pJoystickData[i].KeyRepeatCounter[j]++;
			}
			
			/*押していない状態*/
			else
			{
				/*カウンタリセット*/	
				m_pJoystickData[i].KeyRepeatCounter[j] = 0;
			}
		}
		
		//----------------------------------
		//キーロック
		//----------------------------------
		//m_pJoystickData[i].KeyState[PAD_STATE_PUSH]   &= ~m_pJoystickData[i].LockKey;
		//m_pJoystickData[i].KeyState[PAD_STATE_PULL]   &= ~m_pJoystickData[i].LockKey;
		//m_pJoystickData[i].KeyState[PAD_STATE_HOLD]   &= ~m_pJoystickData[i].LockKey;
		//m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] &= ~m_pJoystickData[i].LockKey;
	}
}


//===============================================
//ボタンセット
//===============================================
//[input]
//	no:パッド番号
//	sort:パッドボタン
//	button:ボタン番号
//[return]
//	なし
//===============================================
void CJoyPad::SetButton(int no, ePadSort sort, int button)
{
	m_pJoystickData[no].PadMap[sort-4] = button;//m_pJoystickData[no].PadMap[sort] = button;
}

//===============================================
//代用キーのセット
//===============================================
//[input]
//	no:パッド番号
//	sort:パッドボタン
//	Keyno:キーの番号
//[return]
//	なし
//===============================================
void CJoyPad::SetAlias(int no, ePadSort sort, int Keyno)
{
	m_pJoystickData[no].KeyAlias[sort] = Keyno;
}

//===============================================
//POVの使用
//===============================================
//[input]
//	no:パッド番号
//	IsUse:POVの使用判定フラグ
//[return]
//	なし
//===============================================
void CJoyPad::UsePOVDirection(int no, bool IsUse)
{
	CInput::m_pJoystickData[no].IsUsePOVDirection = IsUse;
}

//===============================================
//POV使用判定
//===============================================
//[input]
//	no:パッド番号
//[return]
//	POVの使用判定
//===============================================
BOOL CJoyPad::IsUsePOVDirection(int no)
{
	return CInput::m_pJoystickData[no].IsUsePOVDirection;
}

//===============================================
//パッド状態の取得
//===============================================
//[input]
//	no:パッド番号
//	state:パッド状態
//	sort:
//[return]
//	取得したパッド状態
//===============================================
bool CJoyPad::GetState(int no, ePadState state, ePadSort sort)
{
	return ( (CInput::m_pJoystickData[no].KeyState[state] & PadSortBitTbl[sort]) != 0);
}

//===============================================
//パッドの状態セット
//===============================================
//[input]
//	no:パッド番号
//	state:パッドの状態
//	sort:パッドボタン
//[return]
//	なし
//===============================================
void CJoyPad::SetState(int no, ePadState state, ePadSort sort)
{
	CInput::m_pJoystickData[no].KeyState[state] |= PadSortBitTbl[sort];
}

//===============================================
//ラップ式上下カーソル処理
//===============================================
//[input]
//	no:パッド番号
//	pCursor:カーソル位置
//	max:項目最大値
//[return]
//	パッドの上下
//===============================================
ePadSort CJoyPad::CursorWrapUpDown(int no, int *pCursor, int max)
{
	if(GetState(no, PAD_STATE_REPEAT, PAD_DIR_UP) )
	{
		if( (*pCursor) == 0)
		{
			(*pCursor) = max - 1;
		}
		
		else
		{
			(*pCursor)--;
		}
		
		return PAD_DIR_UP;
	}
	
	else if(GetState(no, PAD_STATE_REPEAT, PAD_DIR_DOWN) )
	{
		if( (*pCursor) == max - 1)
		{
			(*pCursor) = 0;
		}
		
		else
		{
			(*pCursor)++;
		}
		
		return PAD_DIR_DOWN;
	}
	
	return PAD_SORT_NONE;
	
}

//===============================================
//ラップ式左右カーソル処理
//===============================================
//[input]
//	no:パッド番号
//	pCursor:カーソル位置
//	max:最大項目数
//[return]
//	押されたパッドのボタン
//===============================================
ePadSort CJoyPad::CursorWrapLeftRight(int no, int *pCursor, int max)
{
	if(GetState(no, PAD_STATE_REPEAT, PAD_DIR_LEFT) )
	{
		if( (*pCursor) > 0)
		{
			(*pCursor)--;
		}
		
		else
		{
			(*pCursor) = max - 1;
		}
		
		return PAD_DIR_LEFT;
		
	}
	
	else if(GetState(no, PAD_STATE_REPEAT, PAD_DIR_RIGHT) )
	{
		if( (*pCursor) < max - 1)
		{
			(*pCursor)++;
		}
		
		else 
		{
			(*pCursor) = 0;
		}
		
		return PAD_DIR_RIGHT;
	}
	
	return PAD_SORT_NONE;
}



