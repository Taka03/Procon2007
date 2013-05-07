//*==============================================
//sound.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "Ayame.h"

//�t�@�C���f�[�^
struct FILEDATA
{
	HANDLE hFile;						//�t�@�C���n���h��
	BOOL IsPack;						//�p�b�N�t�@�C�����ۂ�
	Uint32 Start;						//�t�@�C���J�n�ʒu
	Uint32 Size;						//�t�@�C���I���ʒu
	FILETIME CreationTime;				//�쐬����
	FILETIME LastAccessTime;			//�ŏI�A�N�Z�X����
	FILETIME LastWriteTime;				//�ŏI�X�V����
	char *FileName;					//�t�@�C����
};



struct SOUNDDATA
{
	IDirectSoundBuffer *pBuffer;
	Uint32 PausePos;
	Bool IsLoop;
	Bool IsPause;

	FILEDATA pFile;						//�t�@�C���n���h��
	CAyame *pAyame;							//�h���C�o�[

	// ����p
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
		static Uint32 m_SoundMax;//�T�E���h���ő�
		static AYAME_INITIALIZE_PROC m_pAyameInit;
		static AYAME_UNINITIALIZE_PROC m_pAyameUnInit;
		static AYAME_CREATE_FROM_FILE_EX_PROC m_pAyameCreateFromFile;
		static AYAME_CREATE_FROM_MEMORY_PROC m_pAyameCreateFromMemory;
		static AYAME_GETERROR_PROC m_pAyameGetError;
	
	public:
	
		static bool InitAyame();
	
	public:	
	
		CSound();//�R���X�g���N�^
		CSound(char *name, int index);//�R���X�g���N�^
		~CSound();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		static bool CreateDevice();//�f�o�C�X�̐���
		static bool CreatePrimaryBuffer();//�v���C�}���E�o�b�t�@�̐���
		static bool CreateSecondaryBuffer();//�Z�J���_���E�o�b�t�@�̐���
		static bool SetSpeakerConfig();//�X�s�[�J�[�̐ݒ�
		
		static bool CreateFromFile(char *name, bool IsNoStop, int index);//�t�@�C���ǂݍ���
		static bool IsPlay(int index);
		static void Play(int index, Uint32 LoopCount = 0, Uint32 LoopInSample = 0);//�Đ�
		static void Stop(int index);//��~
		static void Pause(int index);//�ꎞ��~
		static void SetVolume(float fParam, int index);//�{�����[���̃Z�b�g
		static void SetPan(float fParam, int index);//�p���̐ݒ�
		
		static void Release();//�������̉��
		
		
		
};