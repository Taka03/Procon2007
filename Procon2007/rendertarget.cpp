//*==============================================
//rendertarget.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "rendertarget.h"
#include "joypad.h"

/*CRenderTargetHead�N���X*/
//===============================================
//������
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CRenderTargetHead::Init()
{
	HRESULT hr = NULL;
	
	m_pDrawTex = new C2DPolVB9;
	m_pDrawTex->Init( Joker::GetDevice() );
	m_pDrawTex->SetPosition(&D3DXVECTOR3(450, 400, 0.0f), 256, 256, 0xffffff);

	/*�e�N�X�`���̍쐬*/
	hr = Joker::GetDevice()->CreateTexture(512, 512, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
								  D3DPOOL_DEFAULT, &m_pRenderTex, NULL);
							  
	/*�T�[�t�F�C�X���x���̎擾*/
	m_pRenderTex->GetSurfaceLevel(0, &m_pSurf);
	
	/*�o�b�N�o�b�t�@�̎擾*/
	Joker::GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	
	
}

//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CRenderTargetHead::Exec()
{
	Joker::GetDevice()->SetRenderTarget(0, m_pSurf);
	
	Joker::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR_BLACK, 1.0f, 0);

}

/*RenderTargetEnd�N���X*/
//===============================================
//����
//===============================================
//[input]
//	�Ȃ�
//[return]
//	�Ȃ�
//===============================================
void CRenderTargetEnd::Exec()
{
	Joker::GetDevice()->SetRenderTarget(0, m_pBackBuffer);
	
	if(CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_01) )
	{
		MESSAGE("ScreenShot���B�e���܂����B");
		
		::D3DXSaveTextureToFile("aa.bmp", D3DXIFF_BMP, m_pRenderTex, NULL);
	}
		
	Joker::GetDevice()->SetTexture(0, m_pRenderTex);
	
	m_pDrawTex->Draw(Joker::GetDevice());
	
	Joker::GetDevice()->SetTexture(0, NULL);
}



