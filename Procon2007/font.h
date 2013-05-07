//*==============================================
//font.h
//*==============================================
//二重インクルード防止
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"

//===============================================
//class
//===============================================
class CFont :public CGameObject
{
	private:
	
		CVector3 m_vPos;//位置
		D3DXCOLOR m_FontColor;//フォントカラー
		
		LPD3DXFONT m_pFont;//フォントハンドル
		string m_Text;
		//LPCTSTR m_pText;//テキスト
		
		bool m_IsVariable;//表示判定フラグ
		
	protected:
	
		
	public:
	
		CFont();//コンストラクタ
		CFont(int fontsize);//コンストラクタ
		CFont(int fontsize, LPCSTR name);//コンストラクタ
		~CFont();//デストラクタ
		
		void Init(){};//初期化
		void Exec();//処理
		
		bool Create(int fontsize);//フォント生成
		bool Create(int fontsize, LPCSTR name);//フォント生成
		
		void Draw(string text, int x, int y, D3DXCOLOR color);//描画
		void Draw(string text, int count, LPRECT pRect, DWORD format, D3DXCOLOR color);//描画
		void Draw(int x, int y, D3DXCOLOR color);
		
		const LPD3DXFONT GetD3DXFont()
		{
			return m_pFont;
		}
		
		void SetPosition(float x, float y);//位置の設定
		void SetText(string text);//表示する文字のセット
		void SetFontColor(D3DXCOLOR color);//フォントカラーのセット
		
		void SetVariableFlag(bool flag);//表示判定フラグの設定
		
	public:
	
		bool GetVariableFlag();//表示判定フラグの取得
};

