//*==============================================
//joypad.h
//*==============================================
//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include "input.h"

//===============================================
//class
//===============================================

class CJoyPad :public CInput
{

	
	protected:
	
			static bool m_IsUseAlias;//�L�[�̑�p����t���O
			static int m_UseMapPadMax;
			static int m_KeyRepeatTime;//�L�[���s�[�g����
			static int m_KeyRepeatInterval;
	
	protected:
	
	public:
	
		CJoyPad(){};//�R���X�g���N�^
		virtual ~CJoyPad(){};//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		static void Initialize(int PadMax, bool IsUseAlias, int KeyRepeatTime, int KeyRepeatInter);	//������
		static void SetButton(int no, ePadSort sort, int button);//�{�^���ݒ�
		static void SetAlias(int no, ePadSort sort, int Keyno);//����̃{�^���ݒ�
		
		static void UsePOVDirection(int no, bool IsUse);//POV�L�[���g�p
		static BOOL IsUsePOVDirection(int no);
		
		static bool GetState(int no, ePadState state, ePadSort sort);
		static void SetState(int no, ePadState state, ePadSort sort);
		
		static ePadSort CursorWrapUpDown(int no, int *pCursor, int max);
		static ePadSort CursorWrapLeftRight(int no, int *pCursor, int max);
		
		static void Update();//�X�V
		
		
};