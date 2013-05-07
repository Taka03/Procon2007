//*==============================================
//debug.h
//*==============================================

//===============================================
//include
//===============================================
#include <windows.h>
#include <stdio.h>

//===============================================
//class
//===============================================
//[Desc]
//�f�o�b�O�p�N���X
//===============================================
class CDebug
{
	private:
	
		static HWND m_hWnd;//�E�B���h�E�n���h��
	
	public:
	
		static bool Initialize();
		static void Finalize();
		
		static bool OpenWindow();//�f�o�b�O�E�B���h�E���J��
		static void CloseWindow();//�f�o�b�O�E�B���h�E�����
		
		static void DrawString(const char *pStr,...);//�����̕`��
		static void Clear();//�����̏���
		
};