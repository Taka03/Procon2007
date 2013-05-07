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
//�R���X�g���N�^
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
//�R���X�g���N�^
//===============================================
CCursor::CCursor(const char *name)
{
	m_vPos.Set(100.0f, 0.0f, 0.0f);
	
	m_IsEnd = false;
	
	//m_CurTex.LoadTexture(name);
}

//===============================================
//�f�X�g���N�^
//===============================================
CCursor::~CCursor()
{
	Release();
}

//===============================================
//������
//===============================================
void CCursor::Init()
{
	//m_CurTex.LoadTexture("data/mouse.bmp");
	
	Load(Joker::GetDevice(), "data/act_soldier_basic.x", Joker::GetMaxBlend() );
}

//===============================================
//����
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
//�J�[�\���̈ʒu�Z�b�g
//===============================================
//[input]
//	player:�v���C���[�^�C�v
//	obj:�U���Ώ�
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
//�I���I���t���O�̃Z�b�g
//===============================================
//[input]
//	flag:����t���O
//===============================================
void CCursor::SetEndFlag(bool flag)
{
	m_IsEnd = flag;
}

//===============================================
//�J�[�\���̈ʒu�擾
//===============================================
int CCursor::GetCursor()
{
	return CursorMax;
}

//===============================================
//�J�[�\���̈ړ�
//===============================================
//[input]
//	no:�v���C���[�ԍ�
//	num:���ڐ�
//===============================================
void CCursor::MoveCursor(int no, int num)
{
	CJoyPad::CursorWrapUpDown(no, &Cursor, num);
	
	CursorMax = Cursor % MAX_CHARA;
	
}

//===============================================
//�U���Ώۂ̑I��
//===============================================
//[input]
//	plType:�v���C���[�^�C�v
//	attacker:�U����
//�@target:�U���Ώ�
//===============================================
void CCursor::ChooseCharacter(ePlayerType plType, CCharacter *attacker[], CCharacter *target[])
{
	MoveCursor(plType, MAX_CHARA);
	
	/*�U���^�C�v�̐ݒ�*/
	attacker[next]->SetAttackType(plType);
	
	if(attacker[next]->GetAttackType() == SPECIAL)
	{
		switch(attacker[next]->GetSpecial() )
		{
			/*�g����*/
			case ALTER:
			{
				/*�J�[�\���̃Z�b�g*/
				SetCursor(plType, attacker[CursorMax] );
				
				/*�^�[�Q�b�g�̃Z�b�g*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(attacker[CursorMax]);
					attacker[next]->GetTarget()->SetProtectedFlag( true );
					next++;
				}
				
				break;
				
			}
			
			/*�񕜖��@*/
			case RECOVER:
			{
				/*�J�[�\���̃Z�b�g*/
				SetCursor(plType, attacker[CursorMax] );
				
				/*�^�[�Q�b�g�̃Z�b�g*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(attacker[CursorMax]);
					next++;
				}
				
				break;
			}
			
			/*����*/
			case BUILDUP:
			{
				/*�J�[�\���̃Z�b�g*/
				SetCursor(plType, attacker[CursorMax] );
				
				/*�^�[�Q�b�g�̃Z�b�g*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(attacker[CursorMax]);
					attacker[next]->GetTarget()->SetBuildFlag( true );
					next++;
				}
				
				break;
			}
			
			/*����*/
			case BURST:
			{
				
				/*�J�[�\���̃Z�b�g*/
				SetCursor(plType, target[CursorMax] );
				
				/*�^�[�Q�b�g�̃Z�b�g*/
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					attacker[next]->SetTarget(target[CursorMax]);
					attacker[next]->SetBurstFlag( true );
					next++;
				}
				
				break;
				
			}
			
			/*�K�[�h*/
			case GUARD:
			{
				
			}
			
			/*�J�E���^�[*/
			case COUNTER:
			{
				attacker[next]->SetTarget(attacker[next]);
				
				if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
				{
					next++;
				}
					
				break;
			}
			
			/*���̑�*/
			default:
			{
				/*�J�[�\���̃Z�b�g*/
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
		/*�J�[�\���̃Z�b�g*/
		SetCursor(plType, target[CursorMax] );
		
		
		if(CJoyPad::GetState( (int)plType, PAD_STATE_PUSH, PAD_BUTTON_01) )
		{
			attacker[next]->SetTarget(target[CursorMax]);
			next++;
		}
	
	}
	
	/*���S���Ă����ꍇ�J�E���^�[��i�߂�*/
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
	
	
	CDebug::DrawString("player%d:%s�̃^�[��:Type:%d", plType, attacker[next]->GetName().data(), attacker[next]->GetAttackType() );
	
	
		
}

//===============================================
//�U���Ώۂ̑I��
//===============================================
//[input]
//	attacker:�U����
//�@target:�U���Ώ�
//===============================================
void CCursor::ChooseCharacter(CCharacter *attacker, CCharacter *target)
{
	if(m_vPos.z == target->GetPosition().z)
	{
		/*�퓬�V�[���Ɉړ�*/
		attacker->SetTarget(target);
	}
		
}


//===============================================
//�I���I���t���O�̎擾
//===============================================
//[return]
//	�I���I���t���O�̎擾
//===============================================
bool CCursor::GetEndFlag()
{
	return m_IsEnd;
}
