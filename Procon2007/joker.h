//*==============================================
//joker.h
//*==============================================
#pragma once

//===============================================
//library
//===============================================
#pragma comment(lib, "d3d9.lib")

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")

//===============================================
//include 
//===============================================
#include <iostream>
#include <list>
#include <tchar.h>
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <dinputd.h>

#define DIRECTSOUND_VERSION 0x1000

#include <dsound.h>

#define NAME_SIZE 32
#define PI						(3.141592653589793238462643383279f)											///< ��
#define PI2						(6.283185307179586476925286766559f)											///< 2��

#define toF(V)					((Float)(V))																//Float�^�ւ̃L���X�g�}�N��
#define toI(V)					((Sint32)(V))																//Sint32�^�ւ̃L���X�g�}�N��
#define F(V)					toF(V)
#define L(V)					toI(V)


#define COLOR_BLUE D3DCOLOR_XRGB(0, 0, 255)
#define COLOR_BLACK D3DCOLOR_XRGB(0, 0, 0)
#define COLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define MESSAGE(text)			MessageBox(NULL, text, "Error", MB_OK | MB_ICONSTOP)

#define MemoryAlloc(size)		::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define MemoryFree(pointer)		if( (pointer) !=NULL	){::HeapFree(::GetProcessHeap(), 0, pointer); (pointer) = NULL; }
#define MemoryClear(PD,S)		::FillMemory((PD),(S),0x00)													//�������N���A
#define MemoryFill(PD,PS,S)		::FillMemory((PD),(S),(PS))													//�������h��Ԃ�
#define MemoryMove(PD,PS,S)		::MoveMemory((PD),(PS),(S))													//�������ړ�
#define MemoryCopy(PD,PS,S)		::CopyMemory((PD),(PS),(S))													//�������R�s�[


#define RELEASE(x)	{if(x){ x->Release();x = NULL;} }
#define F_RELEASE(x) {if(x != NULL){x->Release();x = NULL;} }

#define SAFE_DELETE(x)  {if(x) { delete (x); (x) = NULL;} }
#define SAFE_DELETE_ARRAY(x) {if(x) {delete[] (x);(x) = NULL;} }

#define FILE_OPEN_READ(name)				::CreateFile( name, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_WRITE(name)				::CreateFile( name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_OPEN_READ_WRITE(name)			::CreateFile( name, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )
#define FILE_CLOSE(handle)					::CloseHandle( handle )
#define FILE_GET_SIZE(handle)				::GetFileSize( handle, NULL )
#define FILE_READ(handle,ptr,size)			{Uint32 ReadBytes; ::ReadFile( handle, ptr, size, &ReadBytes, NULL);}
#define FILE_WRITE(handle,ptr,size)			{Uint32 WriteBytes; ::WriteFile( handle, ptr, size, &WriteBytes, NULL);}
#define FILE_SEEK_BEGIN(handle,pos)			::SetFilePointer( handle, pos, NULL, FILE_BEGIN )
#define FILE_SEEK_CURRENT(handle,pos)		::SetFilePointer( handle, pos, NULL, FILE_CURRENT )
#define FILE_SEEK_END(handle,pos)			::SetFilePointer( handle, pos, NULL, FILE_END )
#define FILE_SET_TIME(handle,ft0,ft1,ft2)	::SetFileTime( handle, ft0, ft1, ft2 )
#define FILE_GET_TIME(handle,ft0,ft1,ft2)	::GetFileTime( handle, ft0, ft1, ft2 )

#define MIN(N1,N2)				((N1 < N2) ? (N1) : (N2))													//�ŏ��l�擾�}�N��
#define MAX(N1,N2)				((N1 > N2) ? (N1) : (N2))													//�ő�l�擾�}�N��
#define SWAP(N1,N2)				{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										//�l�����}�N��

#define SIN_TABLE_BIT			(16)																		//�T�C���e�[�u���̃r�b�g��
#define SIN_TABLE_SIZE			(1 << SIN_TABLE_BIT)														//�T�C���e�[�u���̃T�C�Y
#define SIN_TABLE_MASK			(SIN_TABLE_SIZE - 1)														//�T�C���e�[�u���̃A�N�Z�X�p�}�X�N
#define ARCTAN_TABLE_SIZE		(SIN_TABLE_SIZE >> 3)														//�A�[�N�^���W�F���g�e�[�u���̃T�C�Y
#define ARCTAN_POS_1			(ARCTAN_TABLE_SIZE << 1)													//�A�[�N�^���W�F���g�̑�P�ی�
#define ARCTAN_POS_2			(ARCTAN_POS_1 + ARCTAN_POS_1)												//�A�[�N�^���W�F���g�̑�Q�ی�
#define ARCTAN_POS_3			(ARCTAN_POS_1 + ARCTAN_POS_2)												//�A�[�N�^���W�F���g�̑�R�ی�
#define ARCTAN_POS_4			(ARCTAN_POS_1 + ARCTAN_POS_3)												//�A�[�N�^���W�F���g�̑�S�ی�
#define ARCTAN_POS_SHIFT		(SIN_TABLE_BIT - 3)															//�A�[�N�^���W�F���g�̈ʒu�V�t�g��
#define ARCTAN_SCALE(V)			(toF(V) * toF(1 << ARCTAN_POS_SHIFT))										//�A�[�N�^���W�F���g�̊g�嗦

#define NORMALIZE_ANGLE(A)		((A) & SIN_TABLE_MASK)														//�p�x�̐��K���i0�`65535�ցj
#define GET_ANGLE(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(360))								//��p�p�x�̎Z�o
#define GET_ANGLE_PI(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(PI2))								//���W�A�������p�p�x�̎Z�o

#define TIMER_SCALE_SHIFT		(32)


//===============================================
//using
//===============================================
using namespace std;

//===============================================
//enum
//===============================================
enum eSurfaceFormat
{
	FORMAT_FROM_FILE,					//�t�@�C������

	FORMAT_DEPTH16,						//16Bit�[�x�o�b�t�@
	FORMAT_DEPTH32,						//32Bit�[�x�o�b�t�@
	FORMAT_DEPTHSTENCIL,				//�X�e���V���[�x�o�b�t�@

	FORMAT_DXT1,						//DXT1���k�t�H�[�}�b�g�e�N�X�`��
	FORMAT_DXT3,						//DXT3���k�t�H�[�}�b�g�e�N�X�`��
	FORMAT_DXT5,						//DXT5���k�t�H�[�}�b�g�e�N�X�`��

	FORMAT_BACKBUFFER,					//�o�b�N�o�b�t�@�[�ɏ���
	FORMAT_TARGET16,					//16Bit�����_�����O�^�[�Q�b�g
	FORMAT_TARGET32,					//32Bit�����_�����O�^�[�Q�b�g
	FORMAT_TARGETFloat,					//���������_�����_�����O�^�[�Q�b�g

	FORMAT_ALPHAONLY,					//�A���t�@�p�e�N�X�`��

	FORMAT_TEXTURE32,					//32Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
	FORMAT_TEXTURE16,					//16Bit�e�N�X�`���t�H�[�}�b�g�ɏ���

	FORMAT_TEXTURE_2D,					//2D�p�ėp�e�N�X�`���t�H�[�}�b�g
	FORMAT_TEXTURE_3D,					//3D�p�ėp�e�N�X�`���t�H�[�}�b�g
};

//===============================================
//typedef
//===============================================
typedef char					Sint8;								//signed char �^�̕ʒ�`
typedef short					Sint16;								//signed short �^�̕ʒ�`
typedef long					Sint32;								//signed long �^�̕ʒ�`
typedef __int64					Sint64;								//signed __int64 �^�̕ʒ�`
typedef unsigned char			Uint8;								//unsigned char �^�̕ʒ�`
typedef unsigned short			Uint16;								//unsigned short �^�̕ʒ�`
typedef unsigned long			Uint32;								//unsigned long �^�̕ʒ�`
typedef unsigned __int64		Uint64;								//unsigned __int64 �^�̕ʒ�`
typedef float					Float;								//Float �^�̕ʒ�`
typedef float					Float32;							//Float �^�̕ʒ�`
typedef double					Float64;							//double �^�̕ʒ�`
typedef long double				Float80;							//long double �^�̕ʒ�`
typedef bool					Bool;								//Bool �^�̕ʒ�`

//===============================================
//class
//===============================================
class Joker
{
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	
	private:
	
		static HWND m_hWnd;//�E�B���h�E�n���h��
		static HINSTANCE m_hInst;//�C���X�^���X�n���h��
		static LPCSTR m_WndClass;//�E�B���h�E�N���X��
		static char m_AppName[MAX_PATH];//�A�v���P�[�V������
		
		static bool m_IsWinMode;//�E�B���h�E���[�h����t���O
		static bool m_IsSetWindowInfo;//��ʏ��̕\������t���O
		
		static HDROP m_hDrop;
		
		static bool Initialize();//������
		
		static HRESULT ReleaseD3DDevice();//D3D�I�u�W�F�N�g�̉�� 
		
		static void ResetDevice(bool IsChange);//3D�f�o�C�X�̃��Z�b�g
		
		static void Finalize();//�I������
		
	private:
	
		static RECT m_rectWindow;//�E�B���h�E�p��`
		static D3DPRESENT_PARAMETERS m_d3dpp;//D3DDevice�̐ݒ�	
		static D3DPRESENT_PARAMETERS m_d3dppWindow;//D3DDevice�̐ݒ�(Window)
		static D3DPRESENT_PARAMETERS m_d3dppFull;//D3DDevice�̐ݒ�(Full)
		
		static D3DFORMAT m_fmtRenderTexWindow;//�����_�����O�E�e�N�X�`���̃t�H�[�}�b�g(Window)
		static D3DFORMAT m_fmtRenderTexFull;//�����_�����O�E�e�N�X�`���̃t�H�[�}�b�g(Full)
		
	
	private:
	
		static Uint64 m_NowTime; //���݃t���[���̎���
		static Uint64 m_OldTime; //�O�t���[���̎���
		static Uint64 m_BeforeTime;//�t���[���̍�������
		
		
		
		/*�t���[�����*/	
		static long m_SyncCount; //���t���[����
		static long m_FrameRate; //�t���[�����[�g
		static long m_FPS; //�b�ԃt���[����
		static long m_OldFPS; //��̃o�b�N�A�b�v
		static long m_PPS; //�b�ԃ|���S����
		static long m_OldPPS;//��̃o�b�N�A�b�v
		static long m_PPS3D;//�b��3D�|���S����
		static long m_OldPPS3D; //��̃o�b�N�A�b�v
		static long m_PPF; //�t���[���|���S����
		static long m_OldPPF;//��̃o�b�N�A�b�v
		static long m_PPF3D;//�t���[��3D�|���S����
		static long m_OldPPF3D;//��̃o�b�N�A�b�v
		static Float m_fFrameTime;//�t���[������
		
	protected:
	
		static UINT m_WinWidth;//�E�B���h�E�̕�
		static UINT m_WinHeight;//�E�B���h�E�̍���
		
		static char m_DragFileName[256];
		
		static string m_DragFile;//�h���b�O�t�@�C����
		
		static DWORD m_MaxVertexBlend;
		
		static LPDIRECT3D9 pD3D;//Direct3D�I�u�W�F�N�g�n���h��
		static LPDIRECT3DDEVICE9 pD3DDevice;//�f�o�C�X�̃����_�����O
		static LPD3DXSPRITE pSprite;//�X�v���C�g�n���h��
	
	public:
	
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//�E�B���h�E�v���V�[�W���[
		
		static bool RegisterWindowClass(HINSTANCE hInst);//�E�B���h�E�N���X�̓o�^
		static bool InitWindow();//�E�B���h�E�̏�����
		
		static void SetWindowSize(int width, int height);//�E�B���h�E�T�C�Y�̐ݒ�
		static bool SetWindowInfo(bool IsWindow);
				
		static void ChangeWindowMode();//�E�B���h�E���[�h�̐ؑ�
		
		static void SyncFrame();//�t���[���̓���
		
		static Uint64 GetSystemTime(); //���݂̃J�E���^�[�̎擾
		static Uint64 GetSystemTimeSecond(); //�b�Ԃ̃J�E���^�[�̎擾
		
		static LPDIRECT3DDEVICE9 GetDevice()
		{
			return pD3DDevice;
		}
		
		static DWORD GetMaxBlend() 
		{
			return m_MaxVertexBlend;
		}
		
		static HWND GetHWnd() 
		{ 
			return m_hWnd;	
		}
		
		static HINSTANCE GetHInst() 
		{
			return m_hInst;
		}
		
		static bool GetWinMode()
		{
			return m_IsWinMode;
		}
	
};
