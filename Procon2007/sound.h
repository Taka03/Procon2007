//*==============================================
//sound.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "Ayame.h"

//ファイルデータ
struct FILEDATA
{
	HANDLE hFile;						//ファイルハンドル
	BOOL IsPack;						//パックファイルか否か
	Uint32 Start;						//ファイル開始位置
	Uint32 Size;						//ファイル終了位置
	FILETIME CreationTime;				//作成日時
	FILETIME LastAccessTime;			//最終アクセス日時
	FILETIME LastWriteTime;				//最終更新日時
	char *FileName;					//ファイル名
};



struct SOUNDDATA
{
	IDirectSoundBuffer *pBuffer;
	Uint32 PausePos;
	Bool IsLoop;
	Bool IsPause;

	FILEDATA pFile;						//ファイルハンドル
	CAyame *pAyame;							//ドライバー

	// 制御用
	struct 
	{
		Float fStart;
		Float fEnd;
		Sint32 Time;
		Sint32 TimeAll;
		Bool IsCtrl;
	} Volume, Pan;
};


//===============================================
//class
//===============================================
class CSound :public CGameObject
{
	private:
			
		static LPDIRECTSOUND8 m_pDirectSound;
		static LPDIRECTSOUNDBUFFER m_pDSPrimary;
		static LPDIRECTSOUNDBUFFER8 m_pDirectSoundBuffer;
		
		static SOUNDDATA m_pSound[20];
		
		static bool m_IsInitAyame;
		static HINSTANCE m_hAyame;
		static Uint32 m_SoundMax;//サウンド数最大
		static AYAME_INITIALIZE_PROC m_pAyameInit;
		static AYAME_UNINITIALIZE_PROC m_pAyameUnInit;
		static AYAME_CREATE_FROM_FILE_EX_PROC m_pAyameCreateFromFile;
		static AYAME_CREATE_FROM_MEMORY_PROC m_pAyameCreateFromMemory;
		static AYAME_GETERROR_PROC m_pAyameGetError;
	
	public:
	
		static bool InitAyame();
	
	public:	
	
		CSound();//コンストラクタ
		CSound(char *name, int index);//コンストラクタ
		~CSound();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		static bool CreateDevice();//デバイスの生成
		static bool CreatePrimaryBuffer();//プライマリ・バッファの生成
		static bool CreateSecondaryBuffer();//セカンダリ・バッファの生成
		static bool SetSpeakerConfig();//スピーカーの設定
		
		static bool CreateFromFile(char *name, bool IsNoStop, int index);//ファイル読み込み
		static bool IsPlay(int index);
		static void Play(int index, Uint32 LoopCount = 0, Uint32 LoopInSample = 0);//再生
		static void Stop(int index);//停止
		static void Pause(int index);//一時停止
		static void SetVolume(float fParam, int index);//ボリュームのセット
		static void SetPan(float fParam, int index);//パンの設定
		
		static void Release();//メモリの解放
		
		
		
};