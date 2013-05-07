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
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
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
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::Exec()
{
	/*�p�b�h�f�[�^�̍X�V*/
	CJoyPad::Update();
}



//===============================================
//������
//===============================================
//[input]
//	PadMax:�p�b�h�̍ő吔
//	IsUseAlias:�L�[�{�[�h�̑�p����
//	KeyRepeatTime:�L�[�̘A������
//	KeyRepearInter:	
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::Initialize(int PadMax, bool IsUseAlias, int KeyRepeatTime, int KeyRepeatInter)
{
	m_UseMapPadMax = PadMax;
	m_KeyRepeatTime = KeyRepeatTime;
	m_KeyRepeatInterval	= KeyRepeatInter;
	m_IsUseAlias = IsUseAlias;
}

//===============================================
//�p�b�h�̍X�V
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::Update()
{
	int x;
	int y;
	
	//------------------------------------
	//�e�p�b�h�̍X�V
	//------------------------------------
	for(int i = 0;i < m_UseMapPadMax;i++)
	{
				
		//-----------------------------------
		//���[�N������
		//-----------------------------------
		m_pJoystickData[i].KeyStateWork[1] = m_pJoystickData[i].KeyStateWork[0];
		m_pJoystickData[i].KeyStateWork[0] = 0x00000000;
		
		DIJOYSTATE2 Joy;
		
		//-----------------------------------
		//�W���C�X�e�B�b�N�̏�Ԃ��擾
		//-----------------------------------
		if(CInput::GetJoystickData(i, &Joy) )
		{
			x = Joy.lX;
			y = Joy.lY;
			
			/*����*/
			if(x < 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_LEFT];
			}
			
			/*�E��*/
			if(x > 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_RIGHT];
			}
			
			/*�㑤*/
			if(y < 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP];
			}
			
			/*����*/
			if(y > 0)
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_DOWN];
			}
			
			/*�{�^��*/
			for(int j = 0; j <= PAD_BUTTON_MAX;j++)
			{
				if(Joy.rgbButtons[j])
				{
					m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[j+4];
				}
			}
			
			/*POV������L�[�ɕϊ�*/
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
		//�L�[�{�[�h�̏�Ԃ̎擾
		//--------------------------------------------
		if(m_IsUseAlias)
		{
			///*����*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_LEFT] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_LEFT];
			}	
			
			//*�E��*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_RIGHT] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_RIGHT];
			}
			
			///*�㑤*/
			if(CInput::GetKeyData(m_pJoystickData[i].KeyAlias[PAD_DIR_UP] ) )
			{
				m_pJoystickData[i].KeyStateWork[0] |= PadSortBitTbl[PAD_DIR_UP];
			}
			
			///*����*/
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
		//��ԍX�V
		//----------------------------------
		m_pJoystickData[i].KeyState[PAD_STATE_PUSH] = (~m_pJoystickData[i].KeyStateWork[1]) & (m_pJoystickData[i].KeyStateWork[0]);
		m_pJoystickData[i].KeyState[PAD_STATE_PULL] = (m_pJoystickData[i].KeyStateWork[1]) & (~m_pJoystickData[i].KeyStateWork[0]); 
		m_pJoystickData[i].KeyState[PAD_STATE_HOLD] = (m_pJoystickData[i].KeyStateWork[1]) & (m_pJoystickData[i].KeyStateWork[1]);
		m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] = 0x00000000;
		
		//----------------------------------
		//�L�[���s�[�g
		//----------------------------------
		for(int j = 0;j < (int)PAD_SORT_MAX;j++)
		{
			/*�����Ă�����*/
			if(CJoyPad::GetState(i, PAD_STATE_HOLD, (ePadSort)j ) )
			{
				/*���ڂ͌��o���Ă���(�������u�Ԃ��E������*/
				if(m_pJoystickData[i].KeyRepeatCounter[j] == 0)
				{
					m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] |= PadSortBitTbl[j];
				}
				
				/*��莞�ԉ��������Ă�Ƃ��Ɉ��Ԋu��ON�EOFF�J��Ԃ�*/
				else if(m_pJoystickData[i].KeyRepeatCounter[j] > m_KeyRepeatTime)
				{
					if(!(m_pJoystickData[i].KeyRepeatCounter[j] % m_KeyRepeatInterval) )
					{
						m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] |= PadSortBitTbl[j];
					}
				}
				
				/*�J�E���^�[++*/
				m_pJoystickData[i].KeyRepeatCounter[j]++;
			}
			
			/*�����Ă��Ȃ����*/
			else
			{
				/*�J�E���^���Z�b�g*/	
				m_pJoystickData[i].KeyRepeatCounter[j] = 0;
			}
		}
		
		//----------------------------------
		//�L�[���b�N
		//----------------------------------
		//m_pJoystickData[i].KeyState[PAD_STATE_PUSH]   &= ~m_pJoystickData[i].LockKey;
		//m_pJoystickData[i].KeyState[PAD_STATE_PULL]   &= ~m_pJoystickData[i].LockKey;
		//m_pJoystickData[i].KeyState[PAD_STATE_HOLD]   &= ~m_pJoystickData[i].LockKey;
		//m_pJoystickData[i].KeyState[PAD_STATE_REPEAT] &= ~m_pJoystickData[i].LockKey;
	}
}


//===============================================
//�{�^���Z�b�g
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	sort:�p�b�h�{�^��
//	button:�{�^���ԍ�
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::SetButton(int no, ePadSort sort, int button)
{
	m_pJoystickData[no].PadMap[sort-4] = button;//m_pJoystickData[no].PadMap[sort] = button;
}

//===============================================
//��p�L�[�̃Z�b�g
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	sort:�p�b�h�{�^��
//	Keyno:�L�[�̔ԍ�
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::SetAlias(int no, ePadSort sort, int Keyno)
{
	m_pJoystickData[no].KeyAlias[sort] = Keyno;
}

//===============================================
//POV�̎g�p
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	IsUse:POV�̎g�p����t���O
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::UsePOVDirection(int no, bool IsUse)
{
	CInput::m_pJoystickData[no].IsUsePOVDirection = IsUse;
}

//===============================================
//POV�g�p����
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//[return]
//	POV�̎g�p����
//===============================================
BOOL CJoyPad::IsUsePOVDirection(int no)
{
	return CInput::m_pJoystickData[no].IsUsePOVDirection;
}

//===============================================
//�p�b�h��Ԃ̎擾
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	state:�p�b�h���
//	sort:
//[return]
//	�擾�����p�b�h���
//===============================================
bool CJoyPad::GetState(int no, ePadState state, ePadSort sort)
{
	return ( (CInput::m_pJoystickData[no].KeyState[state] & PadSortBitTbl[sort]) != 0);
}

//===============================================
//�p�b�h�̏�ԃZ�b�g
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	state:�p�b�h�̏��
//	sort:�p�b�h�{�^��
//[return]
//	�Ȃ�
//===============================================
void CJoyPad::SetState(int no, ePadState state, ePadSort sort)
{
	CInput::m_pJoystickData[no].KeyState[state] |= PadSortBitTbl[sort];
}

//===============================================
//���b�v���㉺�J�[�\������
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	pCursor:�J�[�\���ʒu
//	max:���ڍő�l
//[return]
//	�p�b�h�̏㉺
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
//���b�v�����E�J�[�\������
//===============================================
//[input]
//	no:�p�b�h�ԍ�
//	pCursor:�J�[�\���ʒu
//	max:�ő區�ڐ�
//[return]
//	�����ꂽ�p�b�h�̃{�^��
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



