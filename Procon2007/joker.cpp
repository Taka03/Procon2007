//*==============================================
//joker.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "joker.h"

//===============================================
//variable
//===============================================
HWND	Joker::m_hWnd = NULL;
HINSTANCE	Joker::m_hInst = NULL;
LPCSTR Joker::m_WndClass = NULL;
char Joker::m_AppName[MAX_PATH];
bool Joker::m_IsWinMode = true;
bool Joker::m_IsSetWindowInfo = true;

UINT Joker::m_WinWidth = 800;
UINT Joker::m_WinHeight = 600;

DWORD Joker::m_MaxVertexBlend = 0;

HDROP Joker::m_hDrop;
string Joker::m_DragFile;
char Joker::m_DragFileName[256];
	
LPDIRECT3D9	Joker::pD3D = NULL;
LPDIRECT3DDEVICE9 Joker::pD3DDevice = NULL;
LPD3DXSPRITE Joker::pSprite = NULL;

Uint64 Joker::m_NowTime = 0;
Uint64 Joker::m_OldTime = 0; 
Uint64 Joker::m_BeforeTime = 0;
		
long Joker::m_SyncCount = 0; //���t���[����
long Joker::m_FrameRate = 60; //�t���[�����[�g
long Joker::m_FPS = 0; //�b�ԃt���[����
long Joker::m_OldFPS = 0; //��̃o�b�N�A�b�v
long Joker::m_PPS = 0; //�b�ԃ|���S����
long Joker::m_OldPPS = 0;//��̃o�b�N�A�b�v
long Joker::m_PPS3D = 0;//�b��3D�|���S����
long Joker::m_OldPPS3D = 0; //��̃o�b�N�A�b�v
long Joker::m_PPF = 0; //�t���[���|���S����
long Joker::m_OldPPF = 0;//��̃o�b�N�A�b�v
long Joker::m_PPF3D = 0;//�t���[��3D�|���S����
long Joker::m_OldPPF3D = 0;//��̃o�b�N�A�b�v
float Joker::m_fFrameTime = 0.0f;//�t���[������


//===============================================
//�E�B���h�E�C�x���g�����֐�
//===============================================
//[input]
//	hWnd:�E�B���h�E�n���h��
//	msg:���b�Z�[�W�n���h��(�C�x���g�̓��e)
//	wParam:�C�x���g����ʒm���ꂽ�f�[�^
//	lParam:�C�x���g����ʒm���ꂽ�f�[�^
//[return]
//	DefWindowProc:�V�X�e���ɃC�x���g�ۓ���
//===============================================
LRESULT CALLBACK Joker::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UINT FileNo = 0;
	
	if(msg == WM_CREATE)
	{
		//::DragAcceptFiles(hWnd, TRUE);
	}
	
	/*�E�B���h�E�j����*/
	if(msg == WM_DESTROY)
	{
		/*�v���O�����̏I�����V�X�e���ɒʒm����*/
		PostQuitMessage(NULL);

		return TRUE;
	}
	
	/*�L�[���������Ƃ�*/
	if(msg == WM_KEYDOWN)
	{
		if(wParam == VK_ESCAPE)
		{
			PostQuitMessage(NULL);
		}
		
		if(wParam == VK_F1)
		{
			ChangeWindowMode();
		}
	}
	
	if(msg == WM_DROPFILES)
	{
/*		m_DragFile.clear();
		
		m_hDrop = (HDROP)wParam;
		
		FileNo = DragQueryFile( (HDROP)wParam, 0xFFFFFFFF, NULL, 0);
		
		for( int i = 0;i < (int)FileNo;i++ )
		{
			::DragQueryFile(m_hDrop, i, m_DragFileName, sizeof(m_DragFileName) );
			
		}
		
		::DragFinish(m_hDrop); 
		
	*/	
	}
	
	else
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
	return 0;
		
}


//===============================================
//�E�B���h�E�N���X�̐���
//===============================================
//[input]
//	hInst:�C���X�^���X�n���h��
//[return]
//
//===============================================
bool Joker::RegisterWindowClass(HINSTANCE hInst)
{
	m_hInst = hInst;
	
	m_WndClass = _T("Game");
	
	//strcpy( m_WndClass, "Game" );
	
	strcpy( m_AppName, "Sample" );
	
	WNDCLASSEX wc;//�E�B���h�E�N���X
	
	ZeroMemory(&wc, sizeof(wc) );//������
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;//�\���̂̃T�C�Y���g������o�C�g��
	wc.cbWndExtra = 0;//�E�B���h�E�̃T�C�Y���g������o�C�g��
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//�w�i�F
	wc.hCursor = LoadCursor(m_hInst, IDC_ARROW);//�J�[�\��
	wc.hIcon = NULL;//�A�C�R��
	wc.hInstance = m_hInst;//�C���X�^���X�n���h��
	wc.lpfnWndProc = WndProc;//�E�B���h�E�̃C�x���g����
	wc.lpszClassName = m_WndClass;//�o�^����E�B���h�E�N���X��
	wc.lpszMenuName = NULL;//���j���[��
	wc.style = NULL;//�E�B���h�E�N���X�̃X�^�C��
	
	/*�E�B���h�E�N���X�̓o�^*/
	if(RegisterClassEx(&wc) == NULL)
	{
		MESSAGE("�E�B���h�E�N���X�̓o�^�Ɏ��s");
		return false;
	}
	
	m_hWnd = CreateWindow(wc.lpszClassName, m_AppName, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, m_WinWidth, m_WinHeight, NULL, NULL, m_hInst, NULL);
	
	/*�E�B���h�E��������*/
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);
	
	return true;	
	

}	

//===============================================
//�E�B���h�E�̃T�C�Y�ݒ�
//===============================================
//[input]
//	width:�E�B���h�E�̕�
//	height:�E�B���h�E�̍���
//[return]
//	
//===============================================
void Joker::SetWindowSize(int width, int height)
{
	m_WinWidth = width;
	m_WinHeight = height;
}

//===============================================
//������
//===============================================
//[input]
//	hWnd:�E�B���h�E�n���h��
//	hInst:�C���X�^���X�n���h��
//[return]
//
//===============================================
bool Joker::Initialize()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(pD3D == NULL)
	{
		MessageBox(NULL, "DirectXDevice�̏������Ɏ��s���܂����B", "Base", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	SetWindowInfo(m_IsWinMode);
	
	//----------------------------------------------
	//�u�����h���[�h�̐ݒ�
	//----------------------------------------------
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Joker::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 8);
	
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	
	D3DXMATRIX mat;
	
	D3DXMatrixIdentity(&mat);
	
	/*�ړ��s����쐬*/
	D3DXMatrixTranslation(&mat, 0.0f, 0.0f, 10.0f);
	
	/*�����_�����O�p�C�v���C���Ƀ_�~�[�̃r���[�ϊ���ݒ�*/
	pD3DDevice->SetTransform(D3DTS_VIEW, &mat);
	
	
	if(FAILED(D3DXCreateSprite(pD3DDevice, &pSprite) ) )
	{
		MessageBox(NULL, "SpriteObject�̍쐬�Ɏ��s���܂����B", "Base", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	return true;
	
}

//===============================================
//�E�B���h�E���[�h�̐ؑ�
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void Joker::ChangeWindowMode()
{
	m_IsWinMode = !m_IsWinMode;
}

//===============================================
//3D�f�o�C�X�̃��Z�b�g
//===============================================
//[input]
//	IsChange:��ʃ��[�h��؂�ւ��邩�ǂ���
//===============================================
void Joker::ResetDevice(bool IsChange)
{
	HRESULT hr = NULL;
	
	/*�f�o�C�X����������Ă��Ȃ��ꍇ*/
	if(pD3DDevice == NULL)
	{
		return;
	}
	
	/*�X�N���[�����[�h�̕ύX�łȂ���*/
	if( !IsChange && (pD3DDevice->TestCooperativeLevel() == D3D_OK) )
	{
		return;
	}
	
	
}

//===============================================
//��ʏ��̐ݒ�
//===============================================
//[input]
//	IsFull:�E�B���h�E���ǂ���
//[return]
//	�Ȃ�
//===============================================
bool Joker::SetWindowInfo(bool IsWindow)
{
	D3DDISPLAYMODE d3ddm;
	
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) ) )
	{
		MessageBox(NULL, "DirectX3DDevice�̏������Ɏ��s���܂����B", "Base", MB_OK | MB_ICONSTOP);
		
		return false;
	}
	
	D3DPRESENT_PARAMETERS d3dpp;
	
	ZeroMemory(&d3dpp, sizeof(d3dpp) );
	
	if(IsWindow)
	{
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		
	}
	
	else
	{
		d3dpp.BackBufferWidth = m_WinWidth;
		d3dpp.BackBufferHeight = m_WinHeight;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.Windowed = FALSE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.FullScreen_RefreshRateInHz = 75;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
	}
	
	//hr = Joker::GetDevice()->Reset(&d3dpp);
	//
	//if(hr == D3DERR_DEVICELOST)
	//{
	//	return true;
	//}
	//
	//if(FAILED(hr) )
	//{
	//	return false;
	//}
	
	D3DCAPS9 caps;
	DWORD behavior = D3DCREATE_MIXED_VERTEXPROCESSING;
	pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	
	m_MaxVertexBlend = caps.MaxVertexBlendMatrices;
	
	//�n�[�h�E�F�A
	if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice) ) )
	{
		//MESSAGE("�n�[�h�E�F�A�ł̍쐬�Ɏ��s�B");
		
		//�\�t�g�E�F�A
		if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice) ) ) 
		{
			MESSAGE("�\�t�g�E�F�A�ł̍쐬�Ɏ��s");
			
			if(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice) ) )
			{
				MessageBox(NULL, "3DDeviceObject�̏������Ɏ��s���܂����B", "Base", MB_OK | MB_ICONSTOP);
				
				return false;
			}
		}
	}
	
	return true;

}

//===============================================
//�t���[���̓���
//===============================================
void Joker::SyncFrame()
{
	/*���݂̎��Ԃ��擾*/
	m_NowTime = GetSystemTime();
	
	/*����*/
	Uint64 DiffTime = m_NowTime - m_OldTime;
	
	//------------------------------------
	//�t���[�����[�g��0�łȂ��ꍇ
	//------------------------------------	
	if( m_FrameRate > 0 )
	{
		Uint64 WaitTime = GetSystemTimeSecond() / m_FrameRate;
		
		//------------------------------------
		//���Ԍo�߂�҂�
		//------------------------------------
		if( DiffTime < WaitTime )
		{
			Uint32 SleepTime = (Uint32)( (WaitTime - DiffTime) >> TIMER_SCALE_SHIFT );
			
			if(SleepTime > 3)
			{
				::SleepEx( SleepTime - 2, TRUE );
			}
			
			/*�󃋁[�v�Ō����ɏ���������*/
			do
			{
				m_NowTime = GetSystemTime();
				
			} while( m_NowTime - m_OldTime < WaitTime );
			
			DiffTime = m_NowTime - m_OldTime;
  		}
	}
	
	else
	{
		::SleepEx( 0, TRUE);
	}
	
	/*�I��*/
	m_OldTime = m_NowTime;
	
	/*�t���[�������Z*/
	m_SyncCount++;
	m_FPS++;
	
	//------------------------------------
	//FPS�Z�o
	//------------------------------------
	if( (m_NowTime - m_BeforeTime) >= GetSystemTimeSecond() )
	{
		m_BeforeTime = m_NowTime;
		
		//FPS�ۑ�
		m_OldFPS = m_FPS;
		m_OldPPS = m_PPS;
		m_OldPPF = m_PPS / m_FPS;
		m_OldPPF3D = m_PPS3D / m_FPS;
		m_FPS = 0;
		m_PPS = 0;
		m_PPF = 0;
		m_PPS3D = 0;
		m_PPF3D = 0;
		
		/*�`��ON�Ȃ�^�C�g�����ɕ\��*/
		if( m_IsSetWindowInfo )
		{
			char Temp[MAX_PATH]	= "";
			
			sprintf( Temp, "%s FPS[%d] PPF[%d] PPF3D[%d]", 
					 m_AppName,
					 m_OldFPS, m_OldPPF, m_OldPPF3D );
					 
			::SetWindowText(m_hWnd, Temp);
		}
	}
}

//===============================================
//���݂̃J�E���^�[���擾
//===============================================
//[return]
//	�J�E���g��
//===============================================
Uint64 Joker::GetSystemTime()
{
	Uint64 Time = (Uint64)::timeGetTime();
	return Time << TIMER_SCALE_SHIFT;
}

//===============================================
//���݂̃J�E���^�[���擾(�b��)
//===============================================
//[return]
//	�J�E���g��
//===============================================
Uint64 Joker::GetSystemTimeSecond()
{
	Uint64 Time = (Uint64)1000;
	return Time << TIMER_SCALE_SHIFT;
}

//===============================================
//D3D�I�u�W�F�N�g�̉��
//===============================================
//[return]
//	HRESULT�l
//===============================================
HRESULT Joker::ReleaseD3DDevice()
{
	if(pSprite)
	{
		pSprite->OnLostDevice();
	}
	
	return S_OK;
}

//===============================================
//�I������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void Joker::Finalize()
{
	RELEASE(pD3DDevice);
	RELEASE(pD3D);
	RELEASE(pSprite);
	
	/*�E�B���h�E�N���X�o�^����*/
	UnregisterClass(m_WndClass, m_hInst);
}




