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

Uint32 CSound::m_SoundMax;//�T�E���h���ő�
AYAME_INITIALIZE_PROC CSound::m_pAyameInit;
AYAME_UNINITIALIZE_PROC CSound::m_pAyameUnInit;
AYAME_CREATE_FROM_FILE_EX_PROC CSound::m_pAyameCreateFromFile;
AYAME_CREATE_FROM_MEMORY_PROC CSound::m_pAyameCreateFromMemory;
AYAME_GETERROR_PROC CSound::m_pAyameGetError;

const int SAMPLING_RATE = 44100;
const int NUM_BIT = 16;

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CSound::CSound()
{

}

//===============================================
//�R���X�g���N�^
//===============================================
//[input]
//	name:�t�@�C����
//[return]
//	�Ȃ�
//===============================================	
CSound::CSound(char *name, int index)
{
//	ZeroMemory(&m_pSound->pFile, sizeof(FILEDATA) );
	
	CreateFromFile(name, true, index);
	
	SetVolume(100, index);
}

//===============================================
//�f�X�g���N�^
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
CSound::~CSound()
{
	Release();
}

//===============================================
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CSound::Init()
{
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CSound::Exec()
{
	//Play(-1, 0);
}

//===============================================
//�f�o�C�X�̐���
//===============================================
//[input]
//	�Ȃ�
//[return]
//
//===============================================
bool CSound::CreateDevice()
{
	HRESULT hr;
	
	/*DirectSound�̍쐬*/
	hr = DirectSoundCreate8(NULL, &m_pDirectSound, NULL);
	
	if(FAILED(hr) )
	{
		MESSAGE("DirectSound�̃C���^�[�t�F�[�X�̎擾�Ɏ��s");
		
		return false;
	}
	
	/*�������x���̐ݒ�*/
	hr = m_pDirectSound->SetCooperativeLevel(Joker::GetHWnd(), DSSCL_PRIORITY);
	
	if(FAILED(hr) )
	{
		MESSAGE("�������x���̐ݒ�Ɏ��s");
		
		return false;
	}
	
	DSCAPS caps;
	
	ZeroMemory(&caps, sizeof(DSCAPS) );
	caps.dwSize = sizeof(DSCAPS);
	
	/*�f�o�C�X�\�͂̎擾*/
	hr = m_pDirectSound->GetCaps(&caps);
	
	if(FAILED(hr) )
	{
		MESSAGE("�f�o�C�X�\�͂̎擾�Ɏ��s");
		
		return false;
	}
	
	/*�X�s�[�J�[�̐ݒ�*/
	SetSpeakerConfig();
	
	/*�v���C�}���E�o�b�t�@�̐���*/
	CreatePrimaryBuffer();
	
	return true;

}

//===============================================
//�X�s�[�J�[�̐ݒ�
//===============================================
//[input]
//	�Ȃ�
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
			/*�T�u�E�[�t�@�[�t��5�T���E���h�X�s�[�J�[*/
			#if (DIRECTSOUND_VERSION >= 0x1000)
				case DSSPEAKER_5POINT1_BACK:
			#else
				case DSSPEAKER_5POINT1:
			#endif
				break;
				
			/*�z�[���V�A�^�[�����T�u�E�[�t�@�[�t��5�T���E���h�X�s�[�J�[*/
			#if (DIRECTSOUND_VERSION >= 0x1000)
				case DSSPEAKER_5POINT1_SURROUND:
				{
					break;
				}
			#endif
			
			/*�X�s�[�J�[�p�̍\���͍s���Ȃ�*/
			case DSSPEAKER_DIRECTOUT:
			{
				break;
			}
			
			/*�w�b�h�z��*/
			case DSSPEAKER_HEADPHONE:
			{
				break;
			}
			
			/*���m�����E�X�s�[�J�[*/
			case DSSPEAKER_MONO:
			{
				break;
			}
			
			/*4�`�����l���E�X�s�[�J�[*/
			case DSSPEAKER_QUAD:
			{
				break;
			}
			
			/*�X�e���I�E�X�s�[�J�[*/
			case DSSPEAKER_STEREO:
			{
				/*�W�I���g���\��*/
				switch(DSSPEAKER_GEOMETRY(SpeakerConfig) )
				{
					/*���X�i�[�𒆐S�Ƃ���20�x�̊p�x*/
					case DSSPEAKER_GEOMETRY_WIDE:
					{
						break;
					}
					
					/*���X�i�[�𒆐S�Ƃ���10�x�̊p�x*/
					case DSSPEAKER_GEOMETRY_NARROW:
					{
						break;
					}
					
					/*���X�i�[�𒆐S�Ƃ���5�x�̊p�x*/
					case DSSPEAKER_GEOMETRY_MIN:
					{
						break;
					}
					
					/*���X�i�[�𒆐S�Ƃ���180�x�̊p�x*/
					case DSSPEAKER_GEOMETRY_MAX:
					{
						break;
					}
				}
				
				break;
			}
			
			/*�T���E���h�E�X�s�[�J�[*/
			case DSSPEAKER_SURROUND:
			{
				break;
			}
			
			/*�T�u�E�[�t�@�t����7�T���E���h�E�X�s�[�J�[*/
			case DSSPEAKER_7POINT1_WIDE:
			{
				break;
			}
			
			/*�z�[���V�A�^�[�����̃T�u�E�[�t�@�t��7�T���E���h�X�s�[�J�[*/
			case DSSPEAKER_7POINT1_SURROUND:
			{
				break;
			}
		}
	}
	
	return true;
}

//===============================================
//�v���C�}���E�o�b�t�@�̐���
//===============================================
//[input]
//	�Ȃ�
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
	//�v���C�}���E�o�b�t�@���w��
	//------------------------------------
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;
	
	/*�o�b�t�@�̐���*/
	hr = m_pDirectSound->CreateSoundBuffer(&dsbdesc, &m_pDSPrimary, NULL);
	
	if(FAILED(hr) )
	{
		MESSAGE("�o�b�t�@�̍쐬�Ɏ��s");
		
		return false;
	}	
	
	//----------------------------------------------
	//�v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g�̐ݒ�
	//----------------------------------------------
	WAVEFORMATEX pcmwf;
	
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX) );
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2; //2�`�����l��(�X�e���I)
	pcmwf.nSamplesPerSec = SAMPLING_RATE;//�T���v�����O���[�g
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = NUM_BIT;//16�r�b�g
	
	/*�t�H�[�}�b�g�̐ݒ�*/
	m_pDSPrimary->SetFormat(&pcmwf);
	
	return true;
}

//===============================================
//�Z�J���_���E�o�b�t�@�̐���
//===============================================
//[input]
//	�Ȃ�
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
	//�o�b�t�@��WAVE�t�H�[�}�b�g��ݒ�
	//----------------------------------------------
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;//�X�e���I
	pcmwf.nSamplesPerSec = SAMPLING_RATE;//�T���v�����O���[�g
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = NUM_BIT;//16�r�b�g
	
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC) );
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;//�T�E���h�o�b�t�@�̐���
	dsbdesc.dwBufferBytes = 3 * pcmwf.nAvgBytesPerSec;//3�b�̃o�b�t�@�����
	dsbdesc.lpwfxFormat = &pcmwf;
	
	LPDIRECTSOUNDBUFFER pDSB;
	
	/*�o�b�t�@�̐���*/
	hr = m_pDirectSound->CreateSoundBuffer(&dsbdesc, &pDSB, NULL);
	
	if(FAILED(hr) )
	{
		MESSAGE("�o�b�t�@�̍쐬�Ɏ��s");
		
		return false;
	}
	
	/*DirectSoundBuffer8�C���^�[�t�F�[�X�����o��*/
	hr = pDSB->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)m_pDirectSoundBuffer);
	
	/*���*/
	pDSB->Release();
	
	if(FAILED(hr) )
	{
		MESSAGE("�C���^�[�t�F�[�X�̎擾�Ɏ��s");
		
		return false;
	}
	
	return true;
}

//===============================================
//Ayame�̏�����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
bool CSound::InitAyame()
{
	if(m_hAyame != NULL)
	{
		return true;
	}
	
	/*DLL�̃��[�h*/
	m_hAyame = ::LoadLibrary("Ayame.dll");
	
	/*�֐��̃��[�h*/
	m_pAyameInit = (AYAME_INITIALIZE_PROC)::GetProcAddress(m_hAyame, "Ayame_Initialize");
	m_pAyameUnInit = (AYAME_UNINITIALIZE_PROC)::GetProcAddress(m_hAyame, "Ayame_Uninitialize");
	m_pAyameCreateFromFile = (AYAME_CREATE_FROM_FILE_EX_PROC)::GetProcAddress(m_hAyame, "Ayame_CreateInstanceFromFileEx");
	m_pAyameCreateFromMemory = (AYAME_CREATE_FROM_MEMORY_PROC)::GetProcAddress(m_hAyame, "Ayame_CreateInstanceFromMemory");
	m_pAyameGetError = (AYAME_GETERROR_PROC)::GetProcAddress(m_hAyame, "Ayame_GetLastError");
	
	//----------------------------------------------
	//���[�h����
	//----------------------------------------------
	if(m_pAyameInit == NULL)
	{
		MESSAGE("Ayame�������Ɏ��s");
		return false;
	}
	
	if(m_pAyameUnInit == NULL)
	{
		MESSAGE("Ayame�I������");
		return false;
	}
	
	if(m_pAyameCreateFromFile == NULL)
	{
		MESSAGE("Ayame�t�@�C�������Ɏ��s");
		return false;
	}
	
	if(m_pAyameCreateFromMemory == NULL)
	{
		MESSAGE("Ayame�����������Ɏ��s");
		return false;
	}
	
	if(m_pAyameGetError == NULL)
	{
		return false;
	}
	
	/*�h���C�o�[�̏�����*/
	m_IsInitAyame = m_pAyameInit(NULL, (void**)&m_pDirectSound, NULL, NULL);
	
	return m_IsInitAyame;
	
}

//===============================================
//�����̓ǂݍ���
//===============================================
//[input]
//	name:�t�@�C����
//	IsNoStop:�E�B���h�E���t�H�[�J�X�������Ă�
//[return]
//	�Ȃ�
//===============================================
bool CSound::CreateFromFile(char *name, bool IsNoStop, int index)
{
	m_pSound[index].pFile.FileName = name;
	
	/*�f�[�^�̓ǂݍ���*/
	m_pSound[index].pFile.hFile = FILE_OPEN_READ( (LPSTR)m_pSound[index].pFile.FileName);
	
	if(m_pSound[index].pFile.hFile == NULL)
	{
		MESSAGE("�t�@�C���ǂݍ��݂Ɏ��s���܂���");
		
		return false;
	}
	
	/*�t�@�C�������ۑ�*/
	FILE_GET_TIME(m_pSound[index].pFile.hFile, &m_pSound[index].pFile.CreationTime, &m_pSound[index].pFile.LastAccessTime, &m_pSound[index].pFile.LastWriteTime);
	
	/*�t�@�C���T�C�Y�擾*/
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
//�T�E���h���Đ������ǂ���
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�T�E���h���Đ�����Ă��邩�ǂ���
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
//�T�E���h�̍Đ�
//===============================================
//[input]
//	LoopCount:���[�v��
//	LoopInSample:���[�v�ɓ���|�C���g
//[return]
//	�Ȃ�
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
//�T�E���h�̒�~
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CSound::Stop(int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->Stop();
	}
}

//===============================================
//�T�E���h�̈ꎞ��~
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================	
void CSound::Pause(int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->Pause();
	}
}

//===============================================
//�Đ����̃{�����[���̐ݒ�
//===============================================
//[input]
//	fParam:�{�����[���l
//[return]
//	�Ȃ�
//===============================================
void CSound::SetVolume(float fParam, int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->SetVolume(fParam);
	}
}

//===============================================
//�Đ����̃p����ݒ�
//===============================================
//[input]
//	fParam:�p���l
//[return]
//	�Ȃ�
//===============================================
void CSound::SetPan(float fParam, int index)
{
	if(m_pSound[index].pAyame != NULL)
	{
		m_pSound[index].pAyame->SetPan(fParam);
	}
}

//===============================================
//�������̉��
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CSound::Release()
{
	/*�h���C�o�[�̉��*/
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