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
#define PI						(3.141592653589793238462643383279f)											///< π
#define PI2						(6.283185307179586476925286766559f)											///< 2π

#define toF(V)					((Float)(V))																//Float型へのキャストマクロ
#define toI(V)					((Sint32)(V))																//Sint32型へのキャストマクロ
#define F(V)					toF(V)
#define L(V)					toI(V)


#define COLOR_BLUE D3DCOLOR_XRGB(0, 0, 255)
#define COLOR_BLACK D3DCOLOR_XRGB(0, 0, 0)
#define COLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define MESSAGE(text)			MessageBox(NULL, text, "Error", MB_OK | MB_ICONSTOP)

#define MemoryAlloc(size)		::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define MemoryFree(pointer)		if( (pointer) !=NULL	){::HeapFree(::GetProcessHeap(), 0, pointer); (pointer) = NULL; }
#define MemoryClear(PD,S)		::FillMemory((PD),(S),0x00)													//メモリクリア
#define MemoryFill(PD,PS,S)		::FillMemory((PD),(S),(PS))													//メモリ塗りつぶし
#define MemoryMove(PD,PS,S)		::MoveMemory((PD),(PS),(S))													//メモリ移動
#define MemoryCopy(PD,PS,S)		::CopyMemory((PD),(PS),(S))													//メモリコピー


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

#define MIN(N1,N2)				((N1 < N2) ? (N1) : (N2))													//最小値取得マクロ
#define MAX(N1,N2)				((N1 > N2) ? (N1) : (N2))													//最大値取得マクロ
#define SWAP(N1,N2)				{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										//値交換マクロ

#define SIN_TABLE_BIT			(16)																		//サインテーブルのビット数
#define SIN_TABLE_SIZE			(1 << SIN_TABLE_BIT)														//サインテーブルのサイズ
#define SIN_TABLE_MASK			(SIN_TABLE_SIZE - 1)														//サインテーブルのアクセス用マスク
#define ARCTAN_TABLE_SIZE		(SIN_TABLE_SIZE >> 3)														//アークタンジェントテーブルのサイズ
#define ARCTAN_POS_1			(ARCTAN_TABLE_SIZE << 1)													//アークタンジェントの第１象限
#define ARCTAN_POS_2			(ARCTAN_POS_1 + ARCTAN_POS_1)												//アークタンジェントの第２象限
#define ARCTAN_POS_3			(ARCTAN_POS_1 + ARCTAN_POS_2)												//アークタンジェントの第３象限
#define ARCTAN_POS_4			(ARCTAN_POS_1 + ARCTAN_POS_3)												//アークタンジェントの第４象限
#define ARCTAN_POS_SHIFT		(SIN_TABLE_BIT - 3)															//アークタンジェントの位置シフト量
#define ARCTAN_SCALE(V)			(toF(V) * toF(1 << ARCTAN_POS_SHIFT))										//アークタンジェントの拡大率

#define NORMALIZE_ANGLE(A)		((A) & SIN_TABLE_MASK)														//角度の正規化（0～65535へ）
#define GET_ANGLE(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(360))								//専用角度の算出
#define GET_ANGLE_PI(A)			toI(toF(A) * toF(SIN_TABLE_SIZE) / toF(PI2))								//ラジアンから専用角度の算出

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
	FORMAT_FROM_FILE,					//ファイルから

	FORMAT_DEPTH16,						//16Bit深度バッファ
	FORMAT_DEPTH32,						//32Bit深度バッファ
	FORMAT_DEPTHSTENCIL,				//ステンシル深度バッファ

	FORMAT_DXT1,						//DXT1圧縮フォーマットテクスチャ
	FORMAT_DXT3,						//DXT3圧縮フォーマットテクスチャ
	FORMAT_DXT5,						//DXT5圧縮フォーマットテクスチャ

	FORMAT_BACKBUFFER,					//バックバッファーに準拠
	FORMAT_TARGET16,					//16Bitレンダリングターゲット
	FORMAT_TARGET32,					//32Bitレンダリングターゲット
	FORMAT_TARGETFloat,					//浮動小数点レンダリングターゲット

	FORMAT_ALPHAONLY,					//アルファ用テクスチャ

	FORMAT_TEXTURE32,					//32Bitテクスチャフォーマットに準拠
	FORMAT_TEXTURE16,					//16Bitテクスチャフォーマットに準拠

	FORMAT_TEXTURE_2D,					//2D用汎用テクスチャフォーマット
	FORMAT_TEXTURE_3D,					//3D用汎用テクスチャフォーマット
};

//===============================================
//typedef
//===============================================
typedef char					Sint8;								//signed char 型の別定義
typedef short					Sint16;								//signed short 型の別定義
typedef long					Sint32;								//signed long 型の別定義
typedef __int64					Sint64;								//signed __int64 型の別定義
typedef unsigned char			Uint8;								//unsigned char 型の別定義
typedef unsigned short			Uint16;								//unsigned short 型の別定義
typedef unsigned long			Uint32;								//unsigned long 型の別定義
typedef unsigned __int64		Uint64;								//unsigned __int64 型の別定義
typedef float					Float;								//Float 型の別定義
typedef float					Float32;							//Float 型の別定義
typedef double					Float64;							//double 型の別定義
typedef long double				Float80;							//long double 型の別定義
typedef bool					Bool;								//Bool 型の別定義

//===============================================
//class
//===============================================
class Joker
{
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	
	private:
	
		static HWND m_hWnd;//ウィンドウハンドル
		static HINSTANCE m_hInst;//インスタンスハンドル
		static LPCSTR m_WndClass;//ウィンドウクラス名
		static char m_AppName[MAX_PATH];//アプリケーション名
		
		static bool m_IsWinMode;//ウィンドウモード判定フラグ
		static bool m_IsSetWindowInfo;//画面情報の表示判定フラグ
		
		static HDROP m_hDrop;
		
		static bool Initialize();//初期化
		
		static HRESULT ReleaseD3DDevice();//D3Dオブジェクトの解放 
		
		static void ResetDevice(bool IsChange);//3Dデバイスのリセット
		
		static void Finalize();//終了処理
		
	private:
	
		static RECT m_rectWindow;//ウィンドウ用矩形
		static D3DPRESENT_PARAMETERS m_d3dpp;//D3DDeviceの設定	
		static D3DPRESENT_PARAMETERS m_d3dppWindow;//D3DDeviceの設定(Window)
		static D3DPRESENT_PARAMETERS m_d3dppFull;//D3DDeviceの設定(Full)
		
		static D3DFORMAT m_fmtRenderTexWindow;//レンダリング・テクスチャのフォーマット(Window)
		static D3DFORMAT m_fmtRenderTexFull;//レンダリング・テクスチャのフォーマット(Full)
		
	
	private:
	
		static Uint64 m_NowTime; //現在フレームの時間
		static Uint64 m_OldTime; //前フレームの時間
		static Uint64 m_BeforeTime;//フレームの差分時間
		
		
		
		/*フレーム情報*/	
		static long m_SyncCount; //総フレーム数
		static long m_FrameRate; //フレームレート
		static long m_FPS; //秒間フレーム数
		static long m_OldFPS; //上のバックアップ
		static long m_PPS; //秒間ポリゴン数
		static long m_OldPPS;//上のバックアップ
		static long m_PPS3D;//秒間3Dポリゴン数
		static long m_OldPPS3D; //上のバックアップ
		static long m_PPF; //フレームポリゴン数
		static long m_OldPPF;//上のバックアップ
		static long m_PPF3D;//フレーム3Dポリゴン数
		static long m_OldPPF3D;//上のバックアップ
		static Float m_fFrameTime;//フレーム時間
		
	protected:
	
		static UINT m_WinWidth;//ウィンドウの幅
		static UINT m_WinHeight;//ウィンドウの高さ
		
		static char m_DragFileName[256];
		
		static string m_DragFile;//ドラッグファイル名
		
		static DWORD m_MaxVertexBlend;
		
		static LPDIRECT3D9 pD3D;//Direct3Dオブジェクトハンドル
		static LPDIRECT3DDEVICE9 pD3DDevice;//デバイスのレンダリング
		static LPD3DXSPRITE pSprite;//スプライトハンドル
	
	public:
	
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//ウィンドウプロシージャー
		
		static bool RegisterWindowClass(HINSTANCE hInst);//ウィンドウクラスの登録
		static bool InitWindow();//ウィンドウの初期化
		
		static void SetWindowSize(int width, int height);//ウィンドウサイズの設定
		static bool SetWindowInfo(bool IsWindow);
				
		static void ChangeWindowMode();//ウィンドウモードの切替
		
		static void SyncFrame();//フレームの同期
		
		static Uint64 GetSystemTime(); //現在のカウンターの取得
		static Uint64 GetSystemTimeSecond(); //秒間のカウンターの取得
		
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
