//*==============================================
//CXModel.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "CXMesh.h"

#include <vector>

//===============================================
//enum
//===============================================
//�v���C���[�^�C�v
enum ePlayerType
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_MAX,
};

//�L�����^�C�v
enum eCharaType
{
	FENCER,
	MAGICIAN,
	RANGER,
	CONTRACTOR,
	GUARDIAN,
	MAX_CHARA,
};

const int ALL_CHARA = 10;
const int MAX_STATUS = 5000;
//const int MAX_CHARA = 2;

//�U���^�C�v
enum eAttackType
{
	ATTACK, //�U��
	SPECIAL, //����\��
	ATTYPE_MAX,
};

//����\�̓^�C�v
enum eSpecialType
{
	SP_ATTACK, //�U���n
	SP_ASSIST,	//�x���n
	SPTYPE_MAX,
};

//����\��
enum eSpecial
{
	CRITICAL,//�N���e�B�J��
	ALTER, //�g����
	ALLMAGIC, //�S�̍U��
	RECOVER, //��
	FIRST_ATTACK, //�搧�U��
	BUILDUP, //����
	BURST,   //����
	GUARD, //�h��
	COUNTER, //�J�E���^�[
	CHARGE_ATTACK, //���ߍU��
};

//���[�V����
enum eMotion
{
	MOT_STAND,//�������[�V����
	MOT_MOVE,//�ړ����[�V����
	MOT_ATTACK,//�U�����[�V����
	MOT_DAMAGE,//�_���[�W���[�V����
	MOT_DEAD,//���S���[�V����
	MOT_SPECIAL,//���ꃂ�[�V����
	MOT_MAX,//���[�V�����̍ő�l
};


//===============================================
//struct
//===============================================
struct HIANIMATION_DESC
{
	int AnimID; //�A�j���[�V����ID
	LPD3DXANIMATIONSET pAnimSet;//�A�j���[�V�����Z�b�g
	float fLoopTime; //1���[�v�̎���
	float fTrackSpeed; //�g���b�N�X�s�[�h
	float fShiftTime; //�V�t�g����̂ɂ����鎞��
	float fCurWeight; //���݂̃E�F�C�g����
	
	double AnimPos;//�A�j���[�V�����̈ʒu
	bool IsLoop;//���[�v�����邩�ǂ���
};

const int MAX_ANIM = 20;

//===============================================
//class
//===============================================
//[Desc]
//	���f���p�N���X
//===============================================
class CXModel :public CGameObject
{
	private:
		
	
	protected:
		
		LPD3DXFRAME					m_pFrameRoot;// ���[�g�t���[��

		LPD3DXANIMATIONCONTROLLER	m_pAnimController;	// �A�j���[�V�����R���g���[���[
		//LPD3DXANIMATIONSET			m_pAnimSet[MAX_ANIM];	//�A�j���[�V�����Z�b�g

		UINT						m_NumBoneMatricesMax;
		D3DXMATRIXA16*				m_pBoneMatrices;

		D3DXMATRIX					m_matWorld;	//���[���h�s��
		D3DXMATRIX					m_matTrans; //���f���s��
		D3DXMATRIX					m_matRotate;//��]�s��
		D3DXMATRIX					m_matScale; //�X�P�[���s��
		int							m_MaxBlend;
		
		D3DXQUATERNION				m_quatModel;//���f���̃N�H�[�^�j�I��
		
		HIANIMATION_DESC			m_Anim[MAX_ANIM]; //�A�j���[�V����
		int							m_CurAnimID;//���݂̃A�j���[�V����
		int							m_PreAnimID;//�O�̃A�j���[�V����
		
		bool m_IsChangeAnim;//�A�j���[�V�����؂�ւ��t���O
		
		
		//CVector3 vAxisX; //X���x�N�g��
		//CVector3 vAxisZ; //Z���x�N�g��
				
	private:

		CVector3 m_vPos;//���W
		CVector3 m_vRot;//�p�x
		CVector3 m_vScale;//�g�k
		
		float m_AnimSpeed;//�A�j���[�V�������x
				
	private:
		
		void DrawFrame( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXFRAME pD3DXFrame );// �t���[����`��

		// �{�[���֘A�̃Z�b�g�A�b�v
		bool SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pD3DXMeshContainer );
		bool SetupBoneMatrixPointers( LPD3DXFRAME pD3DXFrame );

		void UpdateFrameMatrices( LPD3DXFRAME pD3DXFrame, LPD3DXMATRIX pParentMatrix );// �t���[���̍X�V
		
	protected:

		
		void SetWorldMatrix();//���[���h�s��̐ݒ�
		void DrawMeshContainer( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXMESHCONTAINER pD3DXMeshContainer, LPD3DXFRAME pD3DXFrame );		// ���b�V����`��

		
	public:
	
		virtual void Init();
		virtual void Exec();
		
		CXModel();// �R���X�g���N�^
		
		CXModel(const char *name); //�R���X�g���N�^
		
		~CXModel();	// �f�X�g���N�^

		void Render( LPDIRECT3DDEVICE9 pD3DX9 );//�����_�����O

		bool Load( LPDIRECT3DDEVICE9 pD3DX9, const char *pFileName, D3DCOLOR Color );// .X�t�@�C����ǂݍ���
		
		bool ChangeAnimation( UINT animID );//�A�j���[�V�����̐؂�ւ�
		
		bool SetLoopTime( UINT animID, float Time );//���[�v���Ԃ̐ݒ�
		
		bool SetShiftTime( UINT animID, float Time );//�V�t�g���Ԃ̐ݒ�
		
		bool Update( float Time );// ���f���̃A�b�v�f�[�g
		
  		void Release();	// �J��

		HRESULT GenerateSkinnedMesh( LPDIRECT3DDEVICE9 pD3DX9, CXMesh *pCXMeshBase, int MaxBlend );

		
	public:

		void TranslationX(float x);//X�����ւ̈ړ�
		void TranslationY(float y);//Y�����ւ̈ړ�
		void TranslationZ(float z);//Z�����ւ̈ړ�
		void Translation(float x, float y, float z);//�ړ�
		
		void RotationX(float angle);//X�����ւ̉�]
		void RotationY(float angle);//Y�����ւ̉�]
		void RotationZ(float angle);//Z�����ւ̉�]
		void Rotation(float xangle, float yangle, float zangle);//��]
		
		void Scaling(float Sx, float Sy, float Sz);//�g��k��
		
		void Heading(float angle);//�w�b�f�B���O
		void Pitching(float angle);//�s�b�`���O
		void Rolling(float angle);//���[�����O
		
		
	public:
	
		// �擾�֐�
		UINT						GetNumBoneMatrixesMax() const {		return m_NumBoneMatricesMax;	}

		LPD3DXFRAME					GetFrameRoot();			//�t���[�����[�g
		LPD3DXANIMATIONCONTROLLER	GetAniController();		//�A�j���[�V�����R���g���[���[
		

		D3DXMATRIX& GetWorldMatrix();	//���[���h�s��̎擾
		D3DXMATRIX& GetLocalMatrix();	//���f���s��̎擾
		
		virtual CVector3 GetPosition();
		
		virtual float GetPosX();
		virtual float GetPosY();
		virtual float GetPosZ();

		// �ݒ�֐�
		bool SetTrackEnable( DWORD Track, BOOL Enable );
		bool SetTrackSpeed( DWORD Track, FLOAT Speed );
		bool SetTrackWeight( DWORD Track, FLOAT Weight );
	
	
};