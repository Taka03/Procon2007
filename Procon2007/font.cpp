//*==============================================
//font.cpp
//*==============================================

//===============================================
//include
//===============================================
#include "font.h"

//===============================================
//define
//===============================================

//===============================================
//コンストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CFont::CFont()
{
	m_pFont = NULL;
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	m_Text.clear();
	m_FontColor = COLOR_WHITE;
	Create(16);
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	fontsize:フォントサイズ
//===============================================
CFont::CFont(int fontsize)
{
	m_pFont = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Text.clear();
	
	m_IsVariable = true;
	
	m_FontColor = COLOR_WHITE;
	
	Create(fontsize);
}

//===============================================
//コンストラクタ
//===============================================
//[input]
//	fontsize:フォントサイズ
//	name:フォント名
//===============================================
CFont::CFont(int fontsize, LPCSTR name)
{
	m_pFont = NULL;
	
	m_vPos.Set(0.0f, 0.0f, 0.0f);
	
	m_Text.clear();
	
	m_FontColor = COLOR_WHITE;
	
	m_IsVariable = true;
	
	Create( fontsize, name );
}


//===============================================
//デストラクタ
//===============================================
//[input]
//	なし
//[return]
//	なし
//===============================================
CFont::~CFont()
{
	RELEASE(m_pFont);
}

//===============================================
//フォント生成
//===============================================
//[input]	
//	fontsize:フォントサイズ
//[return]
//	なし
//===============================================
bool CFont::Create(int fontsize)
{
	RELEASE(m_pFont);
	
	int result = D3DXCreateFont(pD3DDevice, fontsize, NULL, FW_NORMAL, 1, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("MS UI Gothic"), &m_pFont);
	
	return (result == 0) ? false : true;
}

//===============================================
//フォント生成
//===============================================
//[input]	
//	fontsize:フォントサイズ
//	name:フォント名
//[return]
//	なし
//===============================================
bool CFont::Create(int fontsize, LPCSTR name)
{
	RELEASE(m_pFont);
	
	int result = D3DXCreateFontA(pD3DDevice, fontsize, fontsize, FW_REGULAR, 1, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, _T(name), &m_pFont);
	
	if(name != NULL)
	{
		name = "MS UI Gothic";
	}
	
	return (result == 0) ? false : true;
}


//===============================================
//フォント描画
//===============================================
//[input]
//	text:文字列
//	count:表示文字数
//	pRect:文字描画範囲
//	Fotmat:文字列描画設定
//	color:フォントカラー
//[return]
//	なし
//===============================================
void CFont::Draw(string text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color)
{
	/*描画開始*/
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	/*テキスト描画*/
	m_pFont->DrawText(pSprite, text.c_str(), count, pRect, format, color);
	
	/*描画終了*/
	pSprite->End();
}


//===============================================
//フォント描画
//===============================================
//[input]
//	text:文字列
//	x:X座標
//	y:Y座標
//	color:フォントカラー
//[return]
//	なし
//===============================================
void CFont::Draw(string text, int x, int y, D3DXCOLOR color)
{
	RECT rect = {x, y, x, y};
	
	Draw(text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
	
}

//===============================================
//フォント描画
//===============================================
//[input]
//	text:文字列
//	x:X座標
//	y:Y座標
//	color:フォントカラー
//[return]
//	なし
//===============================================
void CFont::Draw(int x, int y, D3DXCOLOR color)
{
	RECT rect = {x, y, x, y};
	
	Draw(m_Text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
	
}


//===============================================
//処理
//===============================================
//[input]
//	なし
//[return]	
//	なし
//===============================================
void CFont::Exec()
{
	if(m_IsVariable)
	{
		if(!m_Text.empty() )
		{
			Draw( (int)(m_vPos.x), (int)(m_vPos.y), m_FontColor);
		}
	}
}

//===============================================
//フォント位置の設定
//===============================================
//[input]
//	x:X座標
//	y:Y座標
//===============================================
void CFont::SetPosition(float x, float y)
{
	m_vPos.Set(x, y, 0.0f);
}

//===============================================
//テキストの設定
//===============================================
//[input]
//	Text:設定するテキスト
//===============================================
void CFont::SetText(string text)
{
	m_Text = text;
}

//===============================================
//フォントカラーの設定
//===============================================
//[input]
//	color:フォントカラー
//===============================================
void CFont::SetFontColor(D3DXCOLOR color)
{
	m_FontColor = color;
}

//===============================================
//存在フラグの設定
//===============================================
//[input]
//	flag:存在フラグ
//===============================================
void CFont::SetVariableFlag(bool flag)
{
	m_IsVariable = flag;
}

//===============================================
//存在フラグの取得
//===============================================
//[return]
//	存在フラグ
//===============================================
bool CFont::GetVariableFlag()
{
	return m_IsVariable;
}





