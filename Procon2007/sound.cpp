//*==============================================
//sound.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "sound.h"

LPDIRECTSOUND8 CSound::m_pDirectSound;
LPDIRECTSOUNDBUFFER  CSound::m_pDSPrimary;
LPDIRECTSOUNDBUFFER8 CSound::m_pDirectSoundBuffer;

bool CSound::m_IsInitAyame;
HINSTANCE CSound::m_hAyame;

SOUNDDATA CSound::m_pSound[20];

Uint32 CSound::m_SoundMax;//サウンド数最大
AYAME_INITIALIZE_PROC CSound::m_pAyameInit;
AYAME_UNINITIALIZE_PROC CSound::m_pAyameUnInit;
AYAME_CREATE_FROM_FILE_EX_PROC CSound::m_pAyameCreateFromFile;
AYAME_CREATE_FROM_MEMORY_PROC CSound::m_pAyameCreateFromMemory;
AYAME_GETERROR_PROC CSound::m_pAyameGetError;

const int SAMPLING_RATE = 44100;
const int NUM_BIT = 16;

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CSound::CSound()
{

}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	name:ファイル名
//[return]
//	なし
//===============================================	
CSound::CSound(char *name, int index)
{
//	ZeroMemory(&m_pSound->pFile, sizeof(FILEDATA) );
	
	CreateFromFile(name, true, index);
	
	SetVolume(100, index);
}

//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CSound::~CSound()
{
	Release();
}

//===============================================
//初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CSound::Init()
{
}

//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CSound::Exec()
{
	//Play(-1, 0);
}

//===============================================
//デバイスの生成
//===============================================
//[input]
//	なし
//[return]
//
//===============================================
bool CSound::CreateDevice()
{
	HRESULT hr;
	
	/*DirectSoundの作成*/
	hr = DirectSoundCreate8(NULL, &m_pDirectSound, NULL);
	
	if(FAILED(hr) )
	{
		MESSAGE("DirectSoundのインターフェースの取得に失敗");
		
		return false;
	}
	
	/*協調レベルの設定*/
	hr = m_pDirectSound->SetCooperativeLevel(Joker::GetHWnd(), DSSCL_PRIORITY);
	
	if(FAILED(hr) )
	{
		MESSAGE("協調レベルの設定に失敗");
		
		return false;
	}
	
	DSCAPS caps;
	
	ZeroMemory(&caps, sizeof(DSCAPS) );
	caps.dwSize = sizeof(DSCAPS);
	
	/*デバイス能力の取得*/
	hr = m_pDirectSound->GetCaps(&caps);
	
	if(FAILED(hr) )
	{
		MESSAGE("デバイス能力の取得に失敗");
		
		return false;
	}
	
	/*スピーカーの設定*/
	SetSpeakerConfig();
	
	/*プライマリ・バッファの生成*/
	CreatePrimaryBuffer();
	
	return true;

}

//===============================================
//スピーカーの設定
//===============================================
//[input]
//	なし
//[return]
//
//===============================================
bool CSound::SetSpeakerConfig()
{
	HRESULT hr;
	DWORD SpeakerConfig;
	
	hr = m_pDirectSound->GetSpeakerConfig(&SpeakerConfig);
	
	if(SUCCEEDED(hr) )
	{
		switch(DSSPEAKER_CONFIG(SpeakerConfig) )
		{
			/*サブウーファー付き5サラウンドスピーカー*/
			#if (DIRECTSOUND_VERSION >= 0x1000)
				case DSSPEAKER_5POINT1_BACK:
			#else
				case DSSPEAKER_5POINT1:
			#endif
				break;
				
			/*ホームシアター向けサブウーファー付き5サラウンドスピーカー*/
			#if (DIRECTSOUND_VERSION >= 0x1000)
				case DSSPEAKER_5POINT1_SURROUND:
				{
					break;
				}
			#endif
			
			/*スピーカー用の構成は行われない*/
			case DSSPEAKER_DIRECTOUT:
			{
				break;
			}
			
			/*ヘッドホン*/
			case DSSPEAKER_HEADPHONE:
			{
				break;
			}
			
			/*モノラル・スピーカー*/
			case DSSPEAKER_MONO:
			{
				break;
			}
			
			/*4チャンネル・スピーカー*/
			case DSSPEAKER_QUAD:
			{
				break;
			}
			
			/*ステレオ・スピーカー*/
			case DSSPEAKER_STEREO:
			{
				/*ジオメトリ構成*/
				switch(DSSPEAKER_GEOMETRY(SpeakerConfig) )
				{
					/*リスナーを中心として20度の角度*/
					case DSSPEAKER_GEOMETRY_WIDE:
					{
						break;
					}
					
					/*リスナーを中心として10度の角度*/
					case DSSPEAKER_GEOMETRY_NARROW:
					{
						break;
					}
					
					/*リスナーを中心として5度の角度*/
					case DSSPEAKER_GEOMETRY_MIN:
					{
						break;
					}
					
					/*リスナーを中心として180度の角度*/
					case DSSPEAKER_GEOMETRY_MAX:
					{
						break;
					}
				}
				
				break;
			}
			
			/*サラウンド・スピーカー*/
			case DSSPEAKER_SURROUND:
			{
				break;
			}
			
			/*サブウーファ付きの7サラウンド・スピーカー*/
			case DSSPEAKER_7POINT1_WIDE:
			{
				break;
			}
			
			/*ホームシアター向けのサブウーファ付き7サラウンドスピーカー*/
			case DSSPEAKER_7POINT1_SURROUND:
			{
				break;
			}
		}
	}
	
	return true;
}

//===============================================
//プライマリ・バッファの生成
//===============================================
//[input]
//	なし
//[return]
//	
//===============================================
bool CSound::CreatePrimaryBuffer()
{
	DSBUFFERDESC dsbdesc;
	HRESULT hr;
	
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC) );
	
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	
	//------------------------------------
	//プライマリ・バッファを指定
	//------------------------------------
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;
	
	/*バッファの生成*/
	hr = m_pDirectSound->CreateSoundBuffer(&dsbdesc, &m_pDSPrimary, NULL);
	
	if(FAILED(hr) )
	{
		MESSAGE("バッファの作成に失敗");
		
		return false;
	}	
	
	//----------------------------------------------
	//プライマリ・バッファのWaveフォーマットの設定
	//----------------------------------------------
	WAVEFORMATEX pcmwf;
	
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX) );
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2; //2チャンネル(ステレオ)
	pcmwf.nSamplesPerSec = SAMPLING_RATE;//サンプリングレート
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = NUM_BIT;//16ビット
	
	/*フォーマットの設定*/
	m_pDSPrimary->SetFormat(&pcmwf);
	
	return true;
}

//===============================================
//セカンダリ・バッファの生成
//===============================================
//[input]
//	なし
//[return]
//
//===============================================
bool CSound::CreateSecondaryBuffer()
{
	HRESULT hr;
	
	WAVEFORMATEX pcmwf;
	DSBUFFERDESC dsbdesc;
	
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX) );
	
	//----------------------------------------------
	//バッファのWAVEフォーマットを設定
	//----------------------------------------------
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;//ステレオ
	pcmwf.nSamplesPerSec = SAMPLING_RATE;//サンプリングレート
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = NUM_BIT;//16ビット
	
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC) );
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;//サウンドバッファの生成
	dsbdesc.dwBufferBytes = 3 * pcmwf.nAvgBytesPerSec;//3秒のバッファを作る
	dsbdesc.lpwfxFormat = &pcmwf;
	
	LPDIRECTSOUNDBUFFER pDSB;
	
	/*バッファの生成*/
	hr = m_pDirectSound->CreateSoundBuffer(&dsbdesc, &pDSB, NULL);
	
	if(FAILED(hr) )
	{
		MESSAGE("バッファの作成に失敗");
		
		return false;
	}
	
	/*DirectSoundBuffer8インターフェースを取り出す*/
	hr = pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)m_pDirectSoundBuffer);
	
	/*解放*/
	pDSB->Release();
	
	if(FAILED(hr) )
	{
		MESSAGE("インターフェースの取得に失敗");
		
		return false;
	}
	
	return true;
}

//===============================================
//Ayameの初期化
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
bool CSound::InitAyame()
{
	if(m_hAyame != NULL)
	{
		return true;
	}
	
	/*DLLのロード*/
	m_hAyame = ::LoadLibrary("Ayame.dll");
	
	/*関数のロード*/
	m_pAyameInit = (AYAME_INITIALIZE_PROC)::GetProcAddress(m_hAyame, "Ayame_Initialize");
	m_pAyameUnInit = (AYAME_UNINITIALIZE_PROC)::GetProcAddress(m_hAyame, "Ayame_Uninitialize");
	m_pAyameCreateFromFile = (AYAME_CREATE_FROM_FILE_EX_PROC)::GetProcAddress(m_hAyame, "Ayame_CreateInstanceFromFileEx");
	m_pAyameCreateFromMemory = (AYAME_CREATE_FROM_MEMORY_PROC)::GetProcAddress(m_hAyame, "Ayame_CreateInstanceFromMemory");
	m_pAyameGetError = (AYAME_GETERROR_PROC)::GetProcAddress(m_hAyame, "Ayame_GetLastError");
	
	//----------------------------------------------
	//ロード判定
	//----------------------------------------------
	if(m_pAyameInit == NULL)
	{
		MESSAGE("Ayame初期化に失敗");
		return false;
	}
	
	if(m_pAyameUnInit == NULL)
	{
		MESSAGE("Ayame終了処理");
		return false;
	}
	
	if(m_pAyameCreateFromFile == NULL)
	{
		MESSAGE("Ayameファイル生成に失敗");
		return false;
	}
	
	if(m_pAyameCreateFromMemory == NULL)
	{
		MESSAGE("Ayameメモリ生成に失敗");
		return false;
	}
	
	if(m_pAyameGetError == NULL)
	{
		return false;
	}
	
	/*ドライバーの初期化*/
	m_IsInitAyame = m_pAyameInit(NULL, (void**)&m_pDirectSound, NULL, NULL);
	
	return m_IsInitAyame;
	
}

//===============================================
//音声の読み込み
//===============================================
//[input]
//	name:ファイル名
//	IsNoStop:ウィンドウがフォーカスを失っても
//[return]
//	なし
//===============================================
bool CSound::CreateFromFile(char *name, bool IsNoStop, int index)
{
	m_pSound[index].pFile.FileName = name;
	
	/*データの読み込み*/
	m_pSound[index].pFile.hFile = FILE_OPEN_READ( (LPSTR)m_pSound[index].pFile.FileName);
	
	if(m_pSound[index].pFile.hFile == NULL)
	{
		MESSAGE("ファイル読み込みに失敗しました");
		
		return false;
	}
	
	/*ファイル時刻保存*/
	FILE_GET_TIME(m_pSound[index].pFile.hFile, &m_pSound[index].pFile.CreationTime, &m_pSound[index].pFile.LastAccessTime, &m_pSound[index].pFile.LastWriteTime);
	
	/*ファイルサイズ取得*/
	m_pSound[index].pFile.Size = FILE_GET_SIZE(m_pSound[index].pFile.hFile);
	
	m_pSound[index].pAyame = m_pAyameCreateFromFile(m_pSound[index].pFile.FileName, m_pSound[index].pFile.Start, m_pSound[index].pFile.Size, IsNoStop);
	
	if(m_pSound[index].pAyame	== NULL)
	{
		char Buff[512] = "";	
		m_pAyameGetError(Buff);
		
		FILE_CLOSE(m_pSound[index].pFile.hFile);
		
		return false;
	}
	
	FILE_CLOSE(m_pSound[index].pFile.hFile);

//	strcpy(m_pSound[index].pFile.FileName, name);
	
	return true;
		
}

//===============================================
//サウンドが再生中かどうか
//===============================================
//[input]
//	なし
//[return]
//	サウンドが再生されているかどうか
//===============================================
bool CSound::IsPlay(int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		return m_pSound[index].pAyame->IsPlay();
	}
	
	return false;
}

//===============================================
//サウンドの再生
//===============================================
//[input]
//	LoopCount:ループ回数
//	LoopInSample:ループに入るポイント
//[return]
//	なし
//===============================================
void CSound::Play(int index, Uint32 LoopCount, Uint32 LoopInSample)
{
	if(m_pSound[index].pAyame != NULL)
	{
		if(!IsPlay(index) )
		{
			m_pSound[index].pAyame->Play(LoopCount, LoopInSample);
		}
	}
}

//===============================================
//サウンドの停止
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CSound::Stop(int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->Stop();
	}
}

//===============================================
//サウンドの一時停止
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================	
void CSound::Pause(int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->Pause();
	}
}

//===============================================
//再生時のボリュームの設定
//===============================================
//[input]
//	fParam:ボリューム値
//[return]
//	なし
//===============================================
void CSound::SetVolume(float fParam, int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->SetVolume(fParam);
	}
}

//===============================================
//再生時のパンを設定
//===============================================
//[input]
//	fParam:パン値
//[return]
//	なし
//===============================================
void CSound::SetPan(float fParam, int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->SetPan(fParam);
	}
}

//===============================================
//メモリの解放
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
void CSound::Release()
{
	/*ドライバーの解放*/
	if(m_hAyame != NULL)
	{
		if(m_pAyameUnInit != NULL)
		{
			m_pAyameUnInit();
		}
		
		::FreeLibrary(m_hAyame);
	}
	
	F_RELEASE(m_pDSPrimary);
	F_RELEASE(m_pDirectSound);
	
}