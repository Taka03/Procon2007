
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
typedef void *(*AYAME_MEMORY_ALLOC_PROC)( unsigned long Size, const char *pFileName, unsigned long Line );										//�������m�ۗp�R�[���o�b�N�֐�
typedef void (*AYAME_MEMORY_FREE_PROC)( void *pData );																							//����������p�R�[���o�b�N�֐�

typedef Bool (*AYAME_INITIALIZE_PROC)( HWND hWnd, void **ppDirectSound, AYAME_MEMORY_ALLOC_PROC pAllocProc, AYAME_MEMORY_FREE_PROC pFreeProc );	//�h���C�o�[������
typedef void (*AYAME_UNINITIALIZE_PROC)( void );																								//�h���C�o�[���
typedef Bool (*AYAME_GETERROR_PROC)( char *pErrStr );																							//�h���C�o�[����̃G���[���擾
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_PROC)( const char *pFileName, Bool IsGlobal );													//�h���C�o�[����I�u�W�F�N�g�擾
typedef class CAyame *(*AYAME_CREATE_FROM_FILE_EX_PROC)( const char *pFileName, unsigned long Start, unsigned long Size, Bool IsGlobal );		//�h���C�o�[����I�u�W�F�N�g�擾
typedef class CAyame *(*AYAME_CREATE_FROM_MEMORY_PROC)( void *pData, unsigned long Size, Bool IsGlobal );										//�h���C�o�[����I�u�W�F�N�g�擾


//====================================================================
/**
	@brief	OggVorbis�Đ��p�N���X

	DLL�p�ɏ������z�֐������̒��g�̂Ȃ��N���X�ł�
*/
//====================================================================
typedef class CAyame
{
public:
	virtual Bool __stdcall IsPlay( void )																		= 0;	//�Đ��`�F�b�N
	virtual Bool __stdcall Play( unsigned long nLoopCount= 0, unsigned long nLoopInSample = 0 )					= 0;	//�Đ�
	virtual Bool __stdcall Loop( unsigned long nLoopCount = LOOP_INFINITY, unsigned long nLoopInSample = 0 )	= 0;	//���[�v�Đ�
	virtual Bool __stdcall Stop( void )																			= 0;	//��~
	virtual Bool __stdcall Pause( void )																		= 0;	//�ꎞ��~
	virtual Bool __stdcall SetVolume( Float fParam )															= 0;	//�{�����[���ݒ�
	virtual Bool __stdcall SetPan( Float fParam )																= 0;	//�p���ݒ�
	virtual Bool __stdcall Release( void )																		= 0;	//���
	virtual Bool __stdcall AddRef( void )																		= 0;	//�Q�ƃJ�E���g�C���N�������g
	virtual void __stdcall WaitEvent( void )																	= 0;	//�C�x���g�I���҂�
}
COggVorbis, *PCOggVorbis;


#endif // ___AYAME_H___


