//*==============================================
//character.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "CXModel.h"
#include "font.h"
#include "SoundFactory.h"
#include "Effect.h"
#include "TextureFactory.h"
 
//===============================================
//class
//===============================================
//[Desc]
//	�L�����N�^�[�p�N���X
//===============================================
class CCharacter :public CXModel
{
	private:
	
	/*���p*/
	protected:
	
		CVector3 m_vPos;//���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
		
		//float m_Anim;//�A�j���[�V����
		float m_OldAnim;//
		float m_AnimSpeed;//�A�j���[�V�������x
		
		double m_LastAnimFrame;//�A�j���[�V�����̍Ō�̃t���[��
		
		double m_AnimTime;//�A�j���[�V��������
		
	/*�Q�[�������p*/
	protected:
	
		string m_name;//���O
		int m_Status;//�X�e�[�^�X
		int m_OldStatus;//�X�e�[�^�X�ێ��p
		int m_FirstStatus;//�ŏ��̃X�e�[�^�X
		
		float m_FirstFrame;//�ŏ��̃t���[����
		float m_LastFrame;//�Ō�̃t���[����
		
		eSpecial m_Special;//����\��
		eSpecialType m_SpecialType;//����\�̓^�C�v
		ePlayerType m_plType;//�v���C���[�^�C�v
		eCharaType m_CharaType;//�L�����̃^�C�v�ݒ�
		CCharacter *m_pTarget;//�U���Ώ�
		eMotion m_Motion;//���[�V����
		//CCursor *m_pCursor;//�J�[�\��
		
		eAttackType m_AttackType;//����\�͂��g�����ǂ���
		
		bool m_IsSpecial;//����\�͔�������t���O
		bool m_IsCritical;//�N���e�B�J������
		bool m_IsBuildUp;//��������t���O
		bool m_IsProtected;//�g���蔻��t���O
		bool m_IsBurst;//��������t���O
		bool m_IsCharge;//���ߔ���t���O
		bool m_IsCounter;//�J�E���^�[����t���O
		bool m_IsDead;//���S�������ǂ���
		bool m_IsGuard;//�K�[�h���Ă��邩�ǂ���
		
		bool m_IsAttackEnd;//�U���������ǂ���(�_���[�W����p)
		bool m_IsEnd;//�s���I���������ǂ���
		
		CSound *se[SE_MAX];
		
	protected:
	
	public:
	
		CFontSprite *numDamage;//�_���[�W
		CEffect *Burst;//����(�S�̍U���p)
		CEffect *Fire;//���@�U��
		CEffect *Aura;		
		
	
		CCharacter(); //�R���X�g���N�^
		CCharacter(int type); //�R���X�g���N�^
		CCharacter(const char *name);//�R���X�g���N�^
		CCharacter(eCharaType type, ePlayerType plType);//�R���X�g���N�^
		
		~CCharacter(); //�f�X�g���N�^
	
		void Init();//������
		void Exec();//����
		
		void Move(CCharacter *target);//�ړ�
		void Attack(CCharacter *target, int moveoffset, double motoffset);//�U��
		void MagicAttack(CCharacter *target);//���@�U��
		void MagicAllAttack(CCharacter *target[]);//���@�U��
		void Alternate(CCharacter *target[]);//�g����
		void Recover(CCharacter *target);//�񕜖��@
		void BurstS(CCharacter *target, int moveoffset, double motoffset);//����
		void BuildUp(CCharacter *target);//����
//		void ChangeAnimation();//�A�j���[�V�����̐؂�ւ�

		void DamageMotion(CCharacter *target[]);//�_���[�W���[�V����
		void DamageMotion(CCharacter *target);//�_���[�W���[�V����
		void DeadMotion(CCharacter *target);//���S���[�V����

		void LoadSe();//���ʉ��̓ǂݍ���
		void PlaySe(int index);//���ʉ��̍Đ�
		void StopSe(int index);//���ʉ��̒�~

		virtual void Rendering(){};//�����_�����O
		
	public:
		
		CVector3 GetPosition();//�ʒu���W�̎擾
		int GetStatus();//�X�e�[�^�X�̎擾
		int GetOldStatus();//�Â��X�e�[�^�X�̎擾
		int GetFirstStatus();//�����X�e�[�^�X�̎擾
		//float GetAnimation();//�A�j���[�V�����̐��l�̎擾
		
		CCharacter *GetTarget();//�U���Ώۂ̏��擾
		
		eMotion GetMotion();//���[�V�����̎擾
		float GetFirstFrame();//�ŏ��̃t���[�����̎擾
		float GetLastFrame();//�Ō�̃t���[�����̎擾
		
		double GetLastAnimFrame();//�A�j���t���[���̍Ō�̎擾
		
		bool GetDeadFlag();//���S�t���O�̎擾
		bool GetEndFlag();//�s���I���t���O�̎擾
		bool GetAttackEndFlag();//�U���I���t���O�̎擾
		bool GetSpecialFlag();//����\�͔���t���O�̎擾
		bool GetCriticalFlag();//�N���e�B�J������t���O�̎擾
		bool GetProtectedFlag();//�g���蔻��t���O
		bool GetBuildFlag();//��������t���O�̎擾
		bool GetBurstFlag();//��������t���O�̎擾
		bool GetGuardFlag();//�K�[�h����t���O�̎擾
		bool GetChargeFlag();//���ߔ���t���O�̎擾
		bool GetCounterFlag();//�J�E���^�[����t���O�̎擾
		
		
		eSpecial GetSpecial();//����\�͂̎擾
		eSpecialType GetSpecialType();//����\�̓^�C�v�̎擾
		eCharaType GetCharaType();//�L�����^�C�v�̎擾
		eAttackType GetAttackType();//�U���^�C�v�̎擾
		ePlayerType GetPlayerType();//�v���C���[�^�C�v�̎擾
		string GetName();//���O�̎擾
		
		HIANIMATION_DESC GetCurrentAnim();//���݂̃A�j���[�V�����\���̂̎擾
		
		
	public:
	
		void SetPosition(float posx, float posy, float posz);//�ʒu�̐ݒ�
		void SetRotate(float xangle, float yangle, float zangle);//�p�x�̐ݒ�
		
		void SetTarget(CCharacter *obj);//�U���Ώۂ̐ݒ�
		void SetStatus(int status);//�X�e�[�^�X�̐ݒ�
		void SetCursor(ePlayerType plType, CCharacter *obj);//�J�[�\���̐ݒ�
		void SetOldStatus();//�X�e�[�^�X�̃o�b�N�A�b�v
		void SetAttackType(ePlayerType no);//�U���^�C�v�̐ݒ�(�U�������ꂩ)
		void SetAttackType_AI(int type);
		void SetSpecialType(ePlayerType no);//����\�̓^�C�v�̐ݒ�(����͗p)
		void SetSpecialType_AI(bool type);//����\�̓^�C�v�̐ݒ�(AI�p)
		virtual void SetAbility(){};//����\�͂̐ݒ�
		void SetDeadFlag(bool flag);//���S�t���O�̐ݒ�
		void SetBuildFlag(bool flag);//�����t���O�̐ݒ�
		void SetProtectedFlag(bool flag);//�g����t���O�̐ݒ�
		void SetEndFlag(bool flag);//�I���t���O�̐ݒ�
		void SetAttackEndFlag(bool flag);//�U���I���t���O�̐ݒ�
		void SetCriticalFlag(bool flag);//�N���e�B�J���t���O�̐ݒ�
		void SetBurstFlag(bool flag);//��������t���O�̐ݒ�
		void SetSpecialFlag(bool flag);//����\�͔���t���O�̐ݒ�
		void SetChargeFlag(bool flag);//�p���[�`���[�W�t���O�̐ݒ�
		void SetCounterFlag(bool flag);//�J�E���^�[����t���O�̐ݒ�
		void SetGuardFlag(bool flag);//�K�[�h����t���O�̐ݒ�
		void SetMotion(eMotion motion);//���[�V�����̐ݒ�
		
		void SetAnimation(int animID);//�A�j���[�V�����̐ݒ�
		void SetCurrentAnimPos(double pos);//���݂̃A�j���[�V�����ʒu�̐ݒ�
		
	public:
		
		void CalcStatus(int status);//�X�e�[�^�X�̑���
		int CalcDamage(CCharacter *target[]);//�_���[�W�v�Z(�S�̍U���p)
		int CalcDamage(CCharacter *target, double motoffset);//�_���[�W�v�Z
		void ChooseCharacter(CCharacter *target);//�L�����N�^�[�I��
		int Swap(CCharacter attacker, CCharacter target);//����ւ�
		//void Swap(CCharacter *target1, CCharacter *target2);//����ւ�
		
		virtual void SpecialAttack(){};//����\��(�U��ver)
		virtual void SpecialAssist(CCharacter *attacker, CCharacter *target){};//����\��(�x��ver)
	
	public:
	
		
		
};