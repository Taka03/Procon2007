//*==============================================
//character.h
//*==============================================
#pragma once

//===============================================
//include
//===============================================
#include "CXModel.h"
#include "font.h"
#include "SoundFactory.h"
#include "Effect.h"
#include "TextureFactory.h"
 
//===============================================
//class
//===============================================
//[Desc]
//	キャラクター用クラス
//===============================================
class CCharacter :public CXModel
{
	private:
	
	/*共用*/
	protected:
	
		CVector3 m_vPos;//座標
		CVector3 m_vRot;//角度
		CVector3 m_vScale;//拡縮
		
		//float m_Anim;//アニメーション
		float m_OldAnim;//
		float m_AnimSpeed;//アニメーション速度
		
		double m_LastAnimFrame;//アニメーションの最後のフレーム
		
		double m_AnimTime;//アニメーション時間
		
	/*ゲーム特化用*/
	protected:
	
		string m_name;//名前
		int m_Status;//ステータス
		int m_OldStatus;//ステータス保持用
		int m_FirstStatus;//最初のステータス
		
		float m_FirstFrame;//最初のフレーム数
		float m_LastFrame;//最後のフレーム数
		
		eSpecial m_Special;//特殊能力
		eSpecialType m_SpecialType;//特殊能力タイプ
		ePlayerType m_plType;//プレイヤータイプ
		eCharaType m_CharaType;//キャラのタイプ設定
		CCharacter *m_pTarget;//攻撃対象
		eMotion m_Motion;//モーション
		//CCursor *m_pCursor;//カーソル
		
		eAttackType m_AttackType;//特殊能力を使うかどうか
		
		bool m_IsSpecial;//特殊能力発動判定フラグ
		bool m_IsCritical;//クリティカル判定
		bool m_IsBuildUp;//強化判定フラグ
		bool m_IsProtected;//身代わり判定フラグ
		bool m_IsBurst;//自爆判定フラグ
		bool m_IsCharge;//溜め判定フラグ
		bool m_IsCounter;//カウンター判定フラグ
		bool m_IsDead;//死亡したかどうか
		bool m_IsGuard;//ガードしているかどうか
		
		bool m_IsAttackEnd;//攻撃したかどうか(ダメージ判定用)
		bool m_IsEnd;//行動終了したかどうか
		
		CSound *se[SE_MAX];
		
	protected:
	
	public:
	
		CFontSprite *numDamage;//ダメージ
		CEffect *Burst;//爆発(全体攻撃用)
		CEffect *Fire;//魔法攻撃
		CEffect *Aura;		
		
	
		CCharacter(); //コンストラクタ
		CCharacter(int type); //コンストラクタ
		CCharacter(const char *name);//コンストラクタ
		CCharacter(eCharaType type, ePlayerType plType);//コンストラクタ
		
		~CCharacter(); //デストラクタ
	
		void Init();//初期化
		void Exec();//処理
		
		void Move(CCharacter *target);//移動
		void Attack(CCharacter *target, int moveoffset, double motoffset);//攻撃
		void MagicAttack(CCharacter *target);//魔法攻撃
		void MagicAllAttack(CCharacter *target[]);//魔法攻撃
		void Alternate(CCharacter *target[]);//身代わり
		void Recover(CCharacter *target);//回復魔法
		void BurstS(CCharacter *target, int moveoffset, double motoffset);//自爆
		void BuildUp(CCharacter *target);//強化
//		void ChangeAnimation();//アニメーションの切り替え

		void DamageMotion(CCharacter *target[]);//ダメージモーション
		void DamageMotion(CCharacter *target);//ダメージモーション
		void DeadMotion(CCharacter *target);//死亡モーション

		void LoadSe();//効果音の読み込み
		void PlaySe(int index);//効果音の再生
		void StopSe(int index);//効果音の停止

		virtual void Rendering(){};//レンダリング
		
	public:
		
		CVector3 GetPosition();//位置座標の取得
		int GetStatus();//ステータスの取得
		int GetOldStatus();//古いステータスの取得
		int GetFirstStatus();//初期ステータスの取得
		//float GetAnimation();//アニメーションの数値の取得
		
		CCharacter *GetTarget();//攻撃対象の情報取得
		
		eMotion GetMotion();//モーションの取得
		float GetFirstFrame();//最初のフレーム数の取得
		float GetLastFrame();//最後のフレーム数の取得
		
		double GetLastAnimFrame();//アニメフレームの最後の取得
		
		bool GetDeadFlag();//死亡フラグの取得
		bool GetEndFlag();//行動終了フラグの取得
		bool GetAttackEndFlag();//攻撃終了フラグの取得
		bool GetSpecialFlag();//特殊能力判定フラグの取得
		bool GetCriticalFlag();//クリティカル判定フラグの取得
		bool GetProtectedFlag();//身代わり判定フラグ
		bool GetBuildFlag();//強化判定フラグの取得
		bool GetBurstFlag();//自爆判定フラグの取得
		bool GetGuardFlag();//ガード判定フラグの取得
		bool GetChargeFlag();//溜め判定フラグの取得
		bool GetCounterFlag();//カウンター判定フラグの取得
		
		
		eSpecial GetSpecial();//特殊能力の取得
		eSpecialType GetSpecialType();//特殊能力タイプの取得
		eCharaType GetCharaType();//キャラタイプの取得
		eAttackType GetAttackType();//攻撃タイプの取得
		ePlayerType GetPlayerType();//プレイヤータイプの取得
		string GetName();//名前の取得
		
		HIANIMATION_DESC GetCurrentAnim();//現在のアニメーション構造体の取得
		
		
	public:
	
		void SetPosition(float posx, float posy, float posz);//位置の設定
		void SetRotate(float xangle, float yangle, float zangle);//角度の設定
		
		void SetTarget(CCharacter *obj);//攻撃対象の設定
		void SetStatus(int status);//ステータスの設定
		void SetCursor(ePlayerType plType, CCharacter *obj);//カーソルの設定
		void SetOldStatus();//ステータスのバックアップ
		void SetAttackType(ePlayerType no);//攻撃タイプの設定(攻撃か特殊か)
		void SetAttackType_AI(int type);
		void SetSpecialType(ePlayerType no);//特殊能力タイプの設定(手入力用)
		void SetSpecialType_AI(bool type);//特殊能力タイプの設定(AI用)
		virtual void SetAbility(){};//特殊能力の設定
		void SetDeadFlag(bool flag);//死亡フラグの設定
		void SetBuildFlag(bool flag);//強化フラグの設定
		void SetProtectedFlag(bool flag);//身代わりフラグの設定
		void SetEndFlag(bool flag);//終了フラグの設定
		void SetAttackEndFlag(bool flag);//攻撃終了フラグの設定
		void SetCriticalFlag(bool flag);//クリティカルフラグの設定
		void SetBurstFlag(bool flag);//自爆判定フラグの設定
		void SetSpecialFlag(bool flag);//特殊能力判定フラグの設定
		void SetChargeFlag(bool flag);//パワーチャージフラグの設定
		void SetCounterFlag(bool flag);//カウンター判定フラグの設定
		void SetGuardFlag(bool flag);//ガード判定フラグの設定
		void SetMotion(eMotion motion);//モーションの設定
		
		void SetAnimation(int animID);//アニメーションの設定
		void SetCurrentAnimPos(double pos);//現在のアニメーション位置の設定
		
	public:
		
		void CalcStatus(int status);//ステータスの増減
		int CalcDamage(CCharacter *target[]);//ダメージ計算(全体攻撃用)
		int CalcDamage(CCharacter *target, double motoffset);//ダメージ計算
		void ChooseCharacter(CCharacter *target);//キャラクター選択
		int Swap(CCharacter attacker, CCharacter target);//入れ替え
		//void Swap(CCharacter *target1, CCharacter *target2);//入れ替え
		
		virtual void SpecialAttack(){};//特殊能力(攻撃ver)
		virtual void SpecialAssist(CCharacter *attacker, CCharacter *target){};//特殊能力(支援ver)
	
	public:
	
		
		
};