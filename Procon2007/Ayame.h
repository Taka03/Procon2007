
/**
*/

#ifndef ___AYAME_H___
#define ___AYAME_H___


//====================================================================
// INCLUDE
//====================================================================
#include <windows.h>


//====================================================================
// DEFINE
//====================================================================
#define LOOP_INFINITY	(0xFFFFFFFF)


//====================================================================
// TYPEDEF
//====================================================================
typedef void *(*AYAME_MEMORY_ALLOC_PROC)( unsigned long Size, const char *pFileName, unsigned long Line );										//メモリ確保用コールバック関数
typedef void (*AYAME_MEMORY_FREE_PROC)( void *pData );																							//メモリ解放用コールバック関数

typedef Bool (*AYAME_INITIALIZE_PROC)( HWND hWnd, void **ppDirectSound, AYAME_MEMORY_ALLOC_PROC pAllocProc, AYAME_MEMORY_FREE_PROC pFreeProc );	//ドライバー初期化
typedef void (*AYAME_UNINITIALIZE_PROC)( void );																								//ドライバー解放
typedef Bool (*AYAME_GETERROR_PROC)( char *pErrStr );																							//ドライバーからのエラーを取得
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_PROC)( const char *pFileName, Bool IsGlobal );													//ドライバーからオブジェクト取得
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_EX_PROC)( const char *pFileName, unsigned long Start, unsigned long Size, Bool IsGlobal );		//ドライバーからオブジェクト取得
typedef class CAyame *(*AYAME_CREATE_FROM_MEMORY_PROC)( void *pData, unsigned long Size, Bool IsGlobal );										//ドライバーからオブジェクト取得


//====================================================================
/**
	@brief	OggVorbis再生用クラス

	DLL用に純粋仮想関数だけの中身のないクラスです
*/
//====================================================================
typedef class CAyame
{
public:
	virtual Bool __stdcall IsPlay( void )																		= 0;	//再生チェック
	virtual Bool __stdcall Play( unsigned long nLoopCount= 0, unsigned long nLoopInSample = 0 )					= 0;	//再生
	virtual Bool __stdcall Loop( unsigned long nLoopCount = LOOP_INFINITY, unsigned long nLoopInSample = 0 )	= 0;	//ループ再生
	virtual Bool __stdcall Stop( void )																			= 0;	//停止
	virtual Bool __stdcall Pause( void )																		= 0;	//一時停止
	virtual Bool __stdcall SetVolume( Float fParam )															= 0;	//ボリューム設定
	virtual Bool __stdcall SetPan( Float fParam )																= 0;	//パン設定
	virtual Bool __stdcall Release( void )																		= 0;	//解放
	virtual Bool __stdcall AddRef( void )																		= 0;	//参照カウントインクリメント
	virtual void __stdcall WaitEvent( void )																	= 0;	//イベント終了待ち
}
COggVorbis, *PCOggVorbis;


#endif // ___AYAME_H___


