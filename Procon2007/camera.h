//*==============================================
//camera.h
//*==============================================
//��d�C���N���[�h�h�~
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "vector3.h"

//===============================================
//class
//===============================================
class CCamera :public CGameObject
{
	private:
	
		D3DXMATRIX m_matWorld;//���[���h�ϊ��s��
		D3DXMATRIX m_matView;//�r���[�ϊ��s��
		D3DXMATRIX m_matProj;//�ˉe�ϊ��s��
	
		D3DXMATRIX m_matRotate;//��]�p�s��
		D3DXMATRIX m_matTrans;//�ړ��p�s��
		D3DXMATRIX m_matScale;//�g�k�p�s��
		
	private:
		
		CVector3 m_vUp;
		CVector3 m_vEye;
		CVector3 m_vAt;
		
		
		CVector3 m_vPos;//���W
		CVector3 m_vRot;//��]
		CVector3 m_vScale;//�g�k
		
		float m_fDistance;//����
		
	public:
	
		bool m_IsMove;//�J�������ړ��ł��邩
	
	
	
		CVector3 m_vBase;//��ʒu�̈ʒu���W
		CVector3 m_vNormalizeObj;//���K�����ꂽ�Ώ̓_
		CVector3 m_vObj;//�Ώ̓_�̈ʒu
	
	
		CCamera();//�R���X�g���N�^
		~CCamera();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
	
		void SetWorldMatrix();//���[���h�ϊ��s��̐ݒ�
		void SetProjMatrix(float fov, float Aspect, float znear, float zfar);//�r���[�ϊ��s��̐ݒ�
		void SetViewMatrix(CVector3 *pEye, CVector3 *pAt, CVector3 *pUp);//�ˉe�ϊ��s��
		
		void SetWholeMatrix();//�S�̂̕ϊ��s��̐ݒ�
		void RegistBuffer();//�o�b�t�@�̓o�^
		void RegistProShader();//�v���O���}�u���E�V�F�[�_�[�̓o�^
		
		void Translation(float x, float y, float z);//�ړ�
		void TranslationX(float x);//X�����ړ�
		void TranslationY(float y);//Y�����ړ�
		void TranslationZ(float z);//Z�����ړ�
		
		void Rotation(float xangle, float yangle, float zangle);//��]
		void RotationX(float angle);//X������]
		void RotationY(float angle);//Y������]
		void RotationZ(float angle);//Z������]
		
		void Scaling(float Sx, float Sy, float Sz);//�g�k
		void SetBillBoard();
		
		//void Heading(float angle);//�w�b�f�B���O
		//void Rolling(float angle);//���[�����O
		//void Pitching(float angle);//�s�b�`���O
		
		void Update();//�J�����̍X�V
		
	public:
	
		float GetPosition(CVector3 &Pos);//���W�̎擾
		
	public:
	
		HRESULT SetDistance(float fDist);//�����̐ݒ�
		HRESULT SetView(CVector3 &vEye, CVector3 &vAt, CVector3 &vUp);//�r���[�s��̐ݒ�
		HRESULT SetPosition(float x, float y, float z);//�ʒu�̐ݒ�
		HRESULT Pitching(float angle);//�s�b�`���O
		HRESULT Heading(float angle);//�w�b�f�B���O
		HRESULT UpdateView();//�r���[�s��̍X�V
		
	public:
	
		float GetDistance()
		{
			return m_fDistance;
		}
		
};