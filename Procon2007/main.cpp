//*==============================================
//main.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joker.h"
#include "joypad.h"
#include "light.h"
#include "sound.h"
#include "debug.h"
#include "scenemanager.h"
#include "network.h"
#include "multithread.h"
#include "rand.h"

//#include "scene2.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//===============================================
//���C���֐�
//===============================================
//[input]
//	hInst:�A�v���P�[�V�����C���X�^���g�n���h��
//[return]
//	�Ȃ�
//===============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	/*�V�[���}�l�[�W���̐���*/
	CSceneManager *scene = new CSceneManager();
	CJoyPad *JoyPad = new CJoyPad();
	
	/*�f�o�b�O�E�B���h�E���J��*/
	//CDebug::OpenWindow();
	
	/*�E�B���h�E�̐���*/
	Joker::RegisterWindowClass(hInstance);

	/*������*/
	Joker::Initialize();
	
	/*��������*/
	JRand::Seed( (Uint32)::time_t( NULL ) * ::timeGetTime() );
	
	
	
	/*Input�f�o�C�X�̐���*/
	CInput::CreateDevice();
	
	/*�T�E���h�f�o�C�X�̐���*/
	CSound::CreateDevice();
	
	/*Ayame�̏�����*/
	CSound::InitAyame();
	
	JoyPad->Init();
	
	if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
	{
		return false;
	}
	
	/*�E�B���h�E��������܂Ń��[�v*/
	MSG msg;
	
	//while(TRUE)
	//{
	//	if( !(CNetWork::CServer::GetConnectFlag() ) )
	//	{
	//			/*�E�B���h�E�ɒʒB����悤�Ƃ��Ă���C�x���g���擾*/
	//		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
	//		{
	//			/*�I���C�x���g��������I��*/
	//			if(msg.message == WM_QUIT)
	//			{
	//				break;
	//			}

	//			/*���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�*/
	//			TranslateMessage(&msg);
	//			
	//			/*�E�B���h�E�ɃC�x���g��ʒB*/
	//			DispatchMessage(&msg);
	//		}
	//			
	//		else
	//		{
	//			
	//			/*�t���[���̓���*/
	//			Joker::SyncFrame();
	//			
	//			/*�f�o�b�O��ʂ̏���*/
	//			CDebug::Clear();
	//			
	//			/*�V�[���̕`��*/
	//			scene->DrawScene(SCENE_INIT);
	//			
	//			/*���͋@��̍X�V*/
	//			CInput::Update();
	//	
	//		}
	//		
	//	}
	//	
	//	else
	//	{
	//		break;
	//	}
	//	
	//}
	
	while(TRUE)
	{
		/*�E�B���h�E�ɒʒB����悤�Ƃ��Ă���C�x���g���擾*/
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			/*�I���C�x���g��������I��*/
			if(msg.message == WM_QUIT)
			{
				break;
			}

			/*���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�*/
			TranslateMessage(&msg);
			
			/*�E�B���h�E�ɃC�x���g��ʒB*/
			DispatchMessage(&msg);
			
		}
			
		else
		{
			/*�t���[���̓���*/
			Joker::SyncFrame();
			
			JoyPad->Exec();
			
			/*�f�o�b�O��ʂ̏���*/
			CDebug::Clear();
			
			/*�V�[���̕`��*/
			scene->DrawScene();
			
			/*���͋@��̍X�V*/
			CInput::Update();
	
		}
		
	}
	
	/*COM�̊J��*/
	CoUninitialize();

	/*�T�[�o�[�̏I������*/
	if( !( scene->GetAnalogFlag() ) )
	{
		CNetWork::CServer::Finalize();
	}
	
	/*�f�o�C�X�̉��*/
	CInput::ReleaseDevice();
	
	/*�f�o�b�O�E�B���h�E�̏I��*/
	CDebug::Finalize();
	
	/*�f�o�C�X�̉��*/
	Joker3D::ReleaseDevice();

	/*�I������*/
	Joker::Finalize();
	
	return 0;
	
}
