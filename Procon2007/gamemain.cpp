//*==============================================
//gamemain.h
//*==============================================

//===============================================
//include 
//===============================================
#include "gamemain.h"

/*CTaskHead�N���X*/
//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CTaskHead::CTaskHead()
{
	lasttime = 0;
	Rect.Set(0, 0, 0, 0);
}

//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CTaskHead::~CTaskHead()
{

}

//===============================================
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CTaskHead::Init()
{
	lasttime = 0;
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CTaskHead::Exec()
{
	//const DWORD WAIT_TIME = 16;//��60FPS
	//
	////�Ō�ɍs������������̎��Ԃ𒲂ׂ�
	//DWORD ntime = timeGetTime();
	//DWORD rtime = ntime - lasttime;
	//
	//lasttime = ntime;
	//
	//if(rtime < WAIT_TIME)
	//{
	//	/*�E�F�C�g�������s��*/
	//	Sleep(WAIT_TIME - rtime);
	//}
	//
	//if(Joker::GetDevice() == NULL)
	//{
	//	MessageBox(NULL, "pD3DDevice��������Ȃ�", "Base", MB_OK | MB_ICONSTOP);
	//}
	
	/*�����_�����O��Ԃ̃Z�b�g*/
	Joker3D::SetRenderState();
	
	/*�J�n�錾*/
	Joker::GetDevice()->BeginScene();
	
	/*��ʂ̃N���A*/
	//Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, COLOR_BLACK, 1.0f, 0);
	Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , COLOR_BLACK, 1.0f, 0);
	
}

/*TaskKill�N���X*/
//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CTaskKill::Exec()
{
	//Joker::GetDevice()->SetViewport(&m_Client);
	
	/*�\��*/
	Joker::GetDevice()->EndScene();
	Joker::GetDevice()->Present(NULL, NULL, NULL, NULL);
	
}
