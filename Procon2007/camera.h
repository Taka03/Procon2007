//*==============================================
//camera.h
//*==============================================
//二重インクルード防止
#pragma once

//===============================================
//include
//===============================================
#include "gameobject.h"
#include "vector3.h"

//===============================================
//class
//===============================================
class CCamera :public CGameObject
{
	private:
	
		D3DXMATRIX m_matWorld;//ワールド変換行列
		D3DXMATRIX m_matView;//ビュー変換行列
		D3DXMATRIX m_matProj;//射影変換行列
	
		D3DXMATRIX m_matRotate;//回転用行列
		D3DXMATRIX m_matTrans;//移動用行列
		D3DXMATRIX m_matScale;//拡縮用行列
		
	private:
		
		CVector3 m_vUp;
		CVector3 m_vEye;
		CVector3 m_vAt;
		
		
		CVector3 m_vPos;//座標
		CVector3 m_vRot;//回転
		CVector3 m_vScale;//拡縮
		
		float m_fDistance;//距離
		
	public:
	
		bool m_IsMove;//カメラが移動できるか
	
	
	
		CVector3 m_vBase;//基準位置の位置座標
		CVector3 m_vNormalizeObj;//正規化された対称点
		CVector3 m_vObj;//対称点の位置
	
	
		CCamera();//コンストラクタ
		~CCamera();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
	
		void SetWorldMatrix();//ワールド変換行列の設定
		void SetProjMatrix(float fov, float Aspect, float znear, float zfar);//ビュー変換行列の設定
		void SetViewMatrix(CVector3 *pEye, CVector3 *pAt, CVector3 *pUp);//射影変換行列
		
		void SetWholeMatrix();//全体の変換行列の設定
		void RegistBuffer();//バッファの登録
		void RegistProShader();//プログラマブル・シェーダーの登録
		
		void Translation(float x, float y, float z);//移動
		void TranslationX(float x);//X方向移動
		void TranslationY(float y);//Y方向移動
		void TranslationZ(float z);//Z方向移動
		
		void Rotation(float xangle, float yangle, float zangle);//回転
		void RotationX(float angle);//X方向回転
		void RotationY(float angle);//Y方向回転
		void RotationZ(float angle);//Z方向回転
		
		void Scaling(float Sx, float Sy, float Sz);//拡縮
		void SetBillBoard();
		
		//void Heading(float angle);//ヘッディング
		//void Rolling(float angle);//ローリング
		//void Pitching(float angle);//ピッチング
		
		void Update();//カメラの更新
		
	public:
	
		float GetPosition(CVector3 &Pos);//座標の取得
		
	public:
	
		HRESULT SetDistance(float fDist);//距離の設定
		HRESULT SetView(CVector3 &vEye, CVector3 &vAt, CVector3 &vUp);//ビュー行列の設定
		HRESULT SetPosition(float x, float y, float z);//位置の設定
		HRESULT Pitching(float angle);//ピッチング
		HRESULT Heading(float angle);//ヘッディング
		HRESULT UpdateView();//ビュー行列の更新
		
	public:
	
		float GetDistance()
		{
			return m_fDistance;
		}
		
};