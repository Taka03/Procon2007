//*==============================================
//cursor.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "character.h"
#include "texture.h"

//===============================================
//class
//===============================================
//[Desc]
//	�Q�[���J�[�\���p�N���X
//===============================================
class CCursor :public CXModel
{
	private:
	
		CVector3 m_vPos;//�ʒu
		
		bool m_IsEnd;//�L�����N�^�[�I���I������t���O
		
		int Cursor;//�J�[�\��
		
		int CursorMax;//�J�[�\���̍ő�
		
		int next;//���̃L�����N�^�[
		
		//CTexture m_CurTex;//�e�N�X�`��
		
	
	public:
	
		CCursor();//�R���X�g���N�^
		CCursor(const char *name);//�R���X�g���N�^
		~CCursor();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		void SetCursor(ePlayerType player, CCharacter *obj);//�J�[�\���Z�b�g
		void SetEndFlag(bool flag);//�I���I���t���O�Z�b�g
		
		int GetCursor();//�J�[�\���̎擾
		
		void MoveCursor(int no, int num);//�J�[�\���̈ړ�
		void ChooseCharacter(CCharacter *attacker, CCharacter *target);//�U���Ώۂ̑I��
		void ChooseCharacter(ePlayerType plType, CCharacter *attacker[], CCharacter *target[]);//�U���Ώۂ̑I��
	
	public:
	
		bool GetEndFlag();//�I���I���t���O�̎擾
};

