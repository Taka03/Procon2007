//*==============================================
//CXModel.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "CXMesh.h"

#include <vector>

//===============================================
//enum
//===============================================
//プレイヤータイプ
enum ePlayerType
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_MAX,
};

//キャラタイプ
enum eCharaType
{
	FENCER,
	MAGICIAN,
	RANGER,
	CONTRACTOR,
	GUARDIAN,
	MAX_CHARA,
};

const int ALL_CHARA = 10;
const int MAX_STATUS = 5000;
//const int MAX_CHARA = 2;

//攻撃タイプ
enum eAttackType
{
	ATTACK, //攻撃
	SPECIAL, //特殊能力
	ATTYPE_MAX,
};

//特殊能力タイプ
enum eSpecialType
{
	SP_ATTACK, //攻撃系
	SP_ASSIST,	//支援系
	SPTYPE_MAX,
};

//特殊能力
enum eSpecial
{
	CRITICAL,//クリティカル
	ALTER, //身代わり
	ALLMAGIC, //全体攻撃
	RECOVER, //回復
	FIRST_ATTACK, //先制攻撃
	BUILDUP, //強化
	BURST,   //自爆
	GUARD, //防御
	COUNTER, //カウンター
	CHARGE_ATTACK, //溜め攻撃
};

//モーション
enum eMotion
{
	MOT_STAND,//立ちモーション
	MOT_MOVE,//移動モーション
	MOT_ATTACK,//攻撃モーション
	MOT_DAMAGE,//ダメージモーション
	MOT_DEAD,//死亡モーション
	MOT_SPECIAL,//特殊モーション
	MOT_MAX,//モーションの最大値
};


//===============================================
//struct
//===============================================
struct HIANIMATION_DESC
{
	int AnimID; //アニメーションID
	LPD3DXANIMATIONSET pAnimSet;//アニメーションセット
	float fLoopTime; //1ループの時間
	float fTrackSpeed; //トラックスピード
	float fShiftTime; //シフトするのにかかる時間
	float fCurWeight; //現在のウェイト時間
	
	double AnimPos;//アニメーションの位置
	bool IsLoop;//ループさせるかどうか
};

const int MAX_ANIM = 20;

//===============================================
//class
//===============================================
//[Desc]
//	モデル用クラス
//===============================================
class CXModel :public CGameObject
{
	private:
		
	
	protected:
		
		LPD3DXFRAME					m_pFrameRoot;// ルートフレーム

		LPD3DXANIMATIONCONTROLLER	m_pAnimController;	// アニメーションコントローラー
		//LPD3DXANIMATIONSET			m_pAnimSet[MAX_ANIM];	//アニメーションセット

		UINT						m_NumBoneMatricesMax;
		D3DXMATRIXA16*				m_pBoneMatrices;

		D3DXMATRIX					m_matWorld;	//ワールド行列
		D3DXMATRIX					m_matTrans; //モデル行列
		D3DXMATRIX					m_matRotate;//回転行列
		D3DXMATRIX					m_matScale; //スケール行列
		int							m_MaxBlend;
		
		D3DXQUATERNION				m_quatModel;//モデルのクォータニオン
		
		HIANIMATION_DESC			m_Anim[MAX_ANIM]; //アニメーション
		int							m_CurAnimID;//現在のアニメーション
		int							m_PreAnimID;//前のアニメーション
		
		bool m_IsChangeAnim;//アニメーション切り替えフラグ
		
		
		//CVector3 vAxisX; //X軸ベクトル
		//CVector3 vAxisZ; //Z軸ベクトル
				
	private:

		CVector3 m_vPos;//座標
		CVector3 m_vRot;//角度
		CVector3 m_vScale;//拡縮
		
		float m_AnimSpeed;//アニメーション速度
				
	private:
		
		void DrawFrame( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXFRAME pD3DXFrame );// フレームを描画

		// ボーン関連のセットアップ
		bool SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pD3DXMeshContainer );
		bool SetupBoneMatrixPointers( LPD3DXFRAME pD3DXFrame );

		void UpdateFrameMatrices( LPD3DXFRAME pD3DXFrame, LPD3DXMATRIX pParentMatrix );// フレームの更新
		
	protected:

		
		void SetWorldMatrix();//ワールド行列の設定
		void DrawMeshContainer( LPDIRECT3DDEVICE9 pD3DX9, LPD3DXMESHCONTAINER pD3DXMeshContainer, LPD3DXFRAME pD3DXFrame );		// メッシュを描画

		
	public:
	
		virtual void Init();
		virtual void Exec();
		
		CXModel();// コンストラクタ
		
		CXModel(const char *name); //コンストラクタ
		
		~CXModel();	// デストラクタ

		void Render( LPDIRECT3DDEVICE9 pD3DX9 );//レンダリング

		bool Load( LPDIRECT3DDEVICE9 pD3DX9, const char *pFileName, D3DCOLOR Color );// .Xファイルを読み込む
		
		bool ChangeAnimation( UINT animID );//アニメーションの切り替え
		
		bool SetLoopTime( UINT animID, float Time );//ループ時間の設定
		
		bool SetShiftTime( UINT animID, float Time );//シフト時間の設定
		
		bool Update( float Time );// モデルのアップデート
		
  		void Release();	// 開放

		HRESULT GenerateSkinnedMesh( LPDIRECT3DDEVICE9 pD3DX9, CXMesh *pCXMeshBase, int MaxBlend );

		
	public:

		void TranslationX(float x);//X方向への移動
		void TranslationY(float y);//Y方向への移動
		void TranslationZ(float z);//Z方向への移動
		void Translation(float x, float y, float z);//移動
		
		void RotationX(float angle);//X方向への回転
		void RotationY(float angle);//Y方向への回転
		void RotationZ(float angle);//Z方向への回転
		void Rotation(float xangle, float yangle, float zangle);//回転
		
		void Scaling(float Sx, float Sy, float Sz);//拡大縮小
		
		void Heading(float angle);//ヘッディング
		void Pitching(float angle);//ピッチング
		void Rolling(float angle);//ローリング
		
		
	public:
	
		// 取得関数
		UINT						GetNumBoneMatrixesMax() const {		return m_NumBoneMatricesMax;	}

		LPD3DXFRAME					GetFrameRoot();			//フレームルート
		LPD3DXANIMATIONCONTROLLER	GetAniController();		//アニメーションコントローラー
		

		D3DXMATRIX& GetWorldMatrix();	//ワールド行列の取得
		D3DXMATRIX& GetLocalMatrix();	//モデル行列の取得
		
		virtual CVector3 GetPosition();
		
		virtual float GetPosX();
		virtual float GetPosY();
		virtual float GetPosZ();

		// 設定関数
		bool SetTrackEnable( DWORD Track, BOOL Enable );
		bool SetTrackSpeed( DWORD Track, FLOAT Speed );
		bool SetTrackWeight( DWORD Track, FLOAT Weight );
	
	
};