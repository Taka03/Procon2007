//*==============================================
//fontsprite.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "font.h"
#include "texture.h"
#include "TextureManager.h"
#include "CXModel.h"

//===============================================
//enum
//===============================================

enum eCaption
{
	GRP_PLAYER1,
	GRP_PLAYER2,
	
	GRP_TURN,
	GRP_TEAM1,
	GRP_TEAM2,
	GRP_CRYSTAL1,
	GRP_CRYSTAL2,
	
	CAP_MAX,
	
	GRP_LOADING,
	GRP_LARGETURN,
	GRP_LARGENUMBER,
	GRP_SPECIAL1,
	GRP_SPECIAL2,
	
	GRP_RESULT1,
	GRP_RESULT2,
	
	GRP_ICON,
	
	GRP_FONT,
	GRP_NUMBER,
	CAP_HP,
	GRP_HP1,
	GRP_HP2,
	
	GRP_MAX,	
	
};

enum eResult
{
	PLAYER1_WIN,
	PLAYER2_WIN,
	RESULT_MAX,
};



//===============================================
//class
//===============================================
//[Desc]
//	フォントスプライト用クラス
//===============================================
class CFontSprite :public CGameObject
{
	private:
		
		CVector3 m_vPos;//位置
		
		eCaption m_Caption;
		
		LPDIRECT3DTEXTURE9 m_pTex;
		
		C2DPol9 *m_pDraw;
		LPDIRECT3DSURFACE9 m_pSurface;
		
		RECT m_Src;//転送元矩形
		
		TextureManager *m_TexMgr;//テクスチャ管理用
		CTexture m_Tex;//テクスチャハンドル
		
		D3DCOLOR m_FontColor;
		
		string m_Text;//表示する文字
		char m_pName[17];//チーム名
		
		eCharaType m_CharaType;//キャラタイプ
		ePlayerType m_plType;//プレイヤータイプ
		
		bool m_IsVisible;//表示判定フラグ
		
	public:
	
		void Init();//初期化
		void Exec();//処理
	
		CFontSprite();//コンストラクタ
		CFontSprite(const char *pFile, eCaption cap);//コンストラクタ
		CFontSprite(LPDIRECT3DTEXTURE9 Tex, eCaption cap, RECT Src);//コンストラクタ
		CFontSprite(const char *pFile, RECT Src); 
		CFontSprite(int fontsize);
		~CFontSprite();//デストラクタ
		
		HRESULT CreateFontA(int fontsize);//フォントの生成
		HRESULT GetFontBitMap(char *pData, float x, float y);
		
		void DrawNumber(char *pText, float x, float y);//数字の描画 
		void DrawNumber(float x, float y);//数字の描画
		void DrawSpecialAttack(eSpecial spType);//特殊能力(攻撃ver)の表示
		void DrawSpecialAssist(eSpecial spType);//特殊能力(特殊ver)の表示
		void DrawLargeNumber(float x, float y);//数字の描画 
		void DrawWeaponIcon(eCharaType type);//武器アイコンの描画
		void DrawCharaIcon(ePlayerType plType, eCharaType type);//キャラアイコンの描画
		
		void Draw(float x, float y);//描画
		void DrawFont();//フォントの描画
		
		void SetCaption(eCaption cap);//キャプションの設定
		void SetRect(RECT Src);//転送元の設定
		void SetPosition(float x, float y);//位置の設定
		void SetTeamName(char *pText);//チーム名の設定
		void SetText(string Text);//テキストの設定
		void SetVisibleFlag(bool flag);
		
		void SetCharaType(eCharaType type);//キャラタイプの設定
		void SetPlayerType(ePlayerType type);//プレイヤータイプの設定
		
	public:
	
		CVector3 GetPosition();//位置の取得
		bool GetVisibleFlag();//表示フラグの取得
		
			
	
		
};