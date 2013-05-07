//*==============================================
//input.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#define _CRT_SECURE_NO_DEPRECATE
#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif

#include <wbemidl.h>
#include <objbase.h>

//===============================================
//enum
//===============================================
//�L�[�̏��
enum eKeyState
{
	KEY_STATE_FREE,//�������͂���Ă��Ȃ����
	KEY_STATE_PUSH,//�L�[�������ꂽ�u��
	KEY_STATE_PULL,//�L�[�������ꂽ�u��
	KEY_STATE_HOLD,//�L�[�������ꑱ���Ă���u��	
};

//�}�E�X�̏��
enum eMouseState
{
	MOUSE_FREE,//�������͂���Ă��Ȃ����
	MOUSE_PUSH,//�}�E�X�{�^���������ꂽ�u��
	MOUSE_PULL,//�}�E�X�{�^���������ꂽ�u��
	MOUSE_HOLD,//�}�E�X�{�^���������ꑱ���Ă�����
};

//POV�L�[
enum ePov
{
	POV_0   = 0,
	POV_45  = 45,
	POV_90  = 90,
	POV_135 = 135,
	POV_180 = 180,
	POV_225 = 225,
	POV_270 = 270,
	POV_315 = 315,
	POV_N   = POV_0,
	POV_NE  = POV_45,
	POV_E   = POV_90,
	POV_SE  = POV_135,
	POV_S   = POV_180,
	POV_SW  = POV_225,
	POV_W   = POV_270,
	POV_NW  = POV_315,
	
};

//�p�b�h�̏��
enum ePadState
{
	PAD_STATE_PUSH,
	PAD_STATE_PULL,
	PAD_STATE_HOLD,
	PAD_STATE_REPEAT,
	
	PAD_STATE_MAX,
};

//�p�b�h�̃{�^��
enum ePadSort
{
	PAD_DIR_UP,
	PAD_DIR_DOWN,
	PAD_DIR_LEFT,
	PAD_DIR_RIGHT,
	
	PAD_BUTTON_01,
	PAD_BUTTON_02,
	PAD_BUTTON_03,
	PAD_BUTTON_04,
	PAD_BUTTON_05,
	PAD_BUTTON_06,
	PAD_BUTTON_07,
	PAD_BUTTON_08,
	PAD_BUTTON_09,
	PAD_BUTTON_10,
	PAD_BUTTON_11,
	PAD_BUTTON_12,
	PAD_BUTTON_13,
	PAD_BUTTON_14,
	PAD_BUTTON_15,
	PAD_BUTTON_16,
	
	PAD_SORT_MAX,
	
	PAD_SORT_NONE,
};

const int PAD_BUTTON_MAX = 16;
const int JOYSTICK_MAX = 16;

//===============================================
//struct
//===============================================
struct XINPUT_DEVICE_NODE
{
	DWORD dwVidPid;
	XINPUT_DEVICE_NODE *pNext;
};

struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG *pPrefrredJoyCfg;
	bool IsPreferredJoyCfg;
};

//�L�[�{�[�h�f�[�^
struct KEYBOARDDATA
{
	char Key[256];//�L�[�f�[�^
};

//�}�E�X�f�[�^
struct MOUSEDATA
{
	int PosX;//X���W
	int PosY;//Y���W
	int PosW;//Z���W
	
	int Mx;//X�ړ���
	int My;//Y�ړ���
	
	bool IsClickL;//���{�^���N���b�N����
	bool IsClickR;//�E�{�^���N���b�N����
	bool IsClickW;//�z�C�[���N���b�N����
	
	bool IsDClickL;//���{�^���_�u���N���b�N����
	bool IsDClickR;//�E�{�^���_�u���N���b�N����
	bool IsDClickW;//�z�C�[���_�u���N���b�N����
	
	eMouseState StateL;//���{�^�����
	eMouseState StateR;//�E�{�^�����
	eMouseState StateW;//�z�C�[���{�^�����
};

//���f�[�^
struct AXISDATA
{
	Sint32 Ax;
	Sint32 Ay;
	Sint32 Az;
};

//�p�b�h�̏��
struct PADSTATUS
{
	Sint32 KeyState[PAD_STATE_MAX];
};

//�p�b�h�ۑ��p�f�[�^
struct PADSAVEHEADER
{
	char Guid[4]; //�t�@�C�����ʗp
	Sint32 LayerMax;	//���C���[��
	Sint32 FrameMax;	//�t���[����
};

//�W���C�X�e�B�b�N�f�[�^
struct JOYSTICKDATA
{
	CVector3 Pos;//��
	CVector3 Rot;//��]��
	CVector3 Sp;//���x
	CVector3 SpRot;//�p���x
	CVector3 Acc;//�����x
	CVector3 AccRot;//�p�����x
	CVector3 Force;//�t�H�[�X
	CVector3 ForRot;//�g���N
	
	int Slider[2];//�X���C�_�[
	int Pov[4];//POV
	
	char Button[PAD_BUTTON_MAX];//�{�^��
	
};



struct JOYSTICKWORK
{
	DIJOYSTATE2 Data;
	LPDIRECTINPUTDEVICE8 pDevice;//�W���C�X�e�B�b�N�f�o�C�X
	
	bool IsPolling;//�|�[�����O����t���O
	bool IsForceFeedback;//�t�H�[�X�t�B�[�h�o�b�N�ɑΉ�����t���O
	
	int LockKey;//���b�N����L�[
	int KeyState[PAD_STATE_MAX];//�L�[�̏��
	int KeyStateWork[2];//�L�[���擾�p���[�N
	int KeyRepeatCounter[PAD_SORT_MAX];//�L�[���s�[�g�J�E���^�[
	int PadMap[PAD_SORT_MAX];//�p�b�h�}�b�s���O���
	int KeyAlias[PAD_SORT_MAX];//�L�[�{�[�h�}�b�s���O�p
	
	bool IsUsePOVDirection;//POV������L�[����
};




//===============================================
//class
//===============================================
class CInput :public CGameObject
{
	protected:
	
		static bool m_IsFilterXInputDevice;
		static XINPUT_DEVICE_NODE *m_pXInputDeviceList;
		
		static KEYBOARDDATA m_KeyboardData;//�L�[�{�[�h�f�[�^
		static JOYSTICKWORK m_pJoystickData[JOYSTICK_MAX];//�W���C�X�e�B�b�N�f�[�^
		
		static Uint32 m_JoystickMax;//�W���C�X�e�B�b�N�ő吔
		static Uint32 m_JoystickCount;//�W���C�X�e�B�b�N�̃J�E���^
		
		static LPDIRECTINPUT8 m_pDirectInput;//�f�o�C�X
		static LPDIRECTINPUTDEVICE8 m_pKeyboard;//�L�[�{�[�h�f�o�C�X
		static MOUSEDATA m_MouseData;//�}�E�X�f�[�^
		
		static bool m_DoubleClickL;//���{�^���_�u���N���b�N����
		static bool m_DoubleClickR;//�E�{�^���_�u���N���b�N����
		static bool m_DoubleClickW;//�z�C�[���_�u���N���b�N����
		
		
		
	public:
	
		CInput(){};//�R���X�g���N�^
		~CInput(){};//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		static void Update();//�X�V
		
		static HRESULT CreateDevice();//�f�o�C�X�̐���
		static HRESULT SetupXInputDevice();//X�C���v�b�g�̃Z�b�g�A�b�v
		static bool IsXInputDevice(const GUID *pGuidDirectInput);
		static void ReleaseXInputDevice();
		static bool GetJoystickData(int no, DIJOYSTATE2 *pJoy);//�W���C�X�e�B�b�N�f�[�^�̎擾
		//static JOYSTICKDATA GetJoystickData(int no);
		static bool GetKeyData(int key);//�L�[�f�[�^�擾
		static void GetMouseData(MOUSEDATA *pMouse);//�}�E�X�f�[�^�̎擾
		
		
		static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);//�W���C�X�e�B�b�N�̗�
		static BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);//�I�u�W�F�N�g�̗�
		static HRESULT InitJoystick();//�W���C�X�e�B�b�N�̏�����
		static HRESULT InitKeyboard();//�L�[�{�[�h�̏�����
		
		static void UpdateKeyboard();//�L�[�{�[�h�f�[�^�̍X�V
		static void UpdateMouse();//�}�E�X�f�[�^�̍X�V
		static void UpdateInputState();//��Ԃ̍X�V
	
		static VOID ReleaseDevice();//�f�o�C�X�̉��
		
		
};
