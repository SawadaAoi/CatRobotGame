/* ========================================
	CatRobotGame/
	------------------------------------
	オブジェクト(プレイヤー)用cpp
	------------------------------------
	ObjectPlayer.cpp
========================================== */

// =============== インクルード =====================
#include "ObjectPlayer.h"
// コンポーネント
#include "ComponentTransform.h"
#include "ComponentRigidbody.h"
#include "ComponentCollisionSphere.h"
#include "ComponentPlayerController.h"
#include "ComponentGroundRaycast.h"
#include "ComponentModelAnime.h"
#include "ComponentSmokeEffect.h"
#include "ComponentShadow.h"

#include "ModelAnimeManager.h"
#include "SoundManager.h"

// =============== 定数定義 =======================
const int	MAX_HP				= 5;	// プレイヤーの最大HP
const float INVINCIBLE_TIME		= 2.0f;	// 無敵時間
const float INV_FLASH_INTERVAL	= 0.1f;	// 無敵点滅間隔
// レイ
const float				RAY_LENGTH	= 0.2f;									// レイの長さ
const Vector3<float>	RAY_OFFSET	= Vector3<float>(0.0f, -0.4f, 0.0f);	// レイの開始位置
// リジッドボディ
const float				GROUND_DRAG = 0.9f;	// 地面摩擦

const float CLEAR_ANGLE = 180.0f;	// クリア時の回転角度

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーンポインタ
=========================================== */
ObjectPlayer::ObjectPlayer(SceneBase* pScene)
	: ObjectBase(pScene)
	, m_pCompGroundRaycast(nullptr)
	, m_pCompRigidbody(nullptr)
	, m_pCompModelAnime(nullptr)
	, m_pCompModelStatic(nullptr)
	, m_pCompPlayerController(nullptr)
	, m_nMaxHp(MAX_HP)
	, m_nHp(MAX_HP)
	, m_bInvincible(false)
	, m_fInvCnt(0.0f)
	, m_fInvFlashCnt(0.0f)
	, m_ePlayerState(E_PlayerState::PS_Normal)
	, m_nCoinNum(0)

{
	SetTag(E_ObjectTag::Player);	// タグの設定
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================= */
void ObjectPlayer::InitLocal()
{
	m_pCompGroundRaycast = AddComponent<ComponentGroundRaycast>();
	m_pCompGroundRaycast->SetStartPosOffset(RAY_OFFSET);
	m_pCompGroundRaycast->SetRayLength(RAY_LENGTH);

	AddComponent<ComponentCollisionSphere>();
	
	m_pCompRigidbody = AddComponent<ComponentRigidbody>();
	m_pCompRigidbody->SetUseGravity(true);
	m_pCompRigidbody->SetGroundDrag(GROUND_DRAG);


	m_pCompModelAnime = AddComponent<ComponentModelAnime>();

	m_pCompModelAnime->SetModel(GET_MODEL_ANIME(ANIME_BASE_KEY::AB_PLAYER));
	m_pCompModelAnime->SetPosOffset(Vector3<float>{0.0f, -0.5f, 0.0f});
	m_pCompModelAnime->PlayAnime(ANIME_KEY_PLAYER::PLYR_IDLE, true, 1.0f);

	m_pCompPlayerController = AddComponent<ComponentPlayerController>();

	SetLightMaterial(1.0f, 1.5f, 0.3f);

	AddComponent<ComponentSmokeEffect>();

	AddComponent<ComponentShadow>();
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================= */
void ObjectPlayer::UpdateLocal()
{
	// 接地判定
	CheckGround();

	// ダメージ後の無敵時間処理
	if (m_bInvincible)	InvincibleUpdate();


	// 演出アニメが他アニメ上書きされるのを防止
	if (m_ePlayerState == E_PlayerState::PS_GameClear
		&& !m_pCompModelAnime->GetIsPlayAnime(ANIME_KEY_PLAYER::PLYR_GAMECLEAR))
	{
		// ゲームクリアアニメーション再生
		m_pCompModelAnime->PlayAnime(ANIME_KEY_PLAYER::PLYR_GAMECLEAR, false, 1.0f);
	}
	if (m_ePlayerState == E_PlayerState::PS_Dead
		&& !m_pCompModelAnime->GetIsPlayAnime(ANIME_KEY_PLAYER::PLYR_DIE))
	{
		// 死亡アニメーション
		m_pCompModelAnime->PlayAnime(ANIME_KEY_PLAYER::PLYR_DIE, false, 1.0f);
	}

}

/* ========================================
	ゲームクリア関数
	-------------------------------------
	内容：ゲームクリア時の処理
========================================= */
void ObjectPlayer::GameClear()
{
	m_pCompPlayerController->SetInputEnable(false);			// 操作を無効に
	m_pCompRigidbody->SetVelocity(Vector3<float>::Zero());	// 移動速度を0に

	// プレイヤーの向きを-Z軸方向に
	float fRad = MathUtils::ToRadian(CLEAR_ANGLE);
	m_pCompTransform->SetRotationEuler(Vector3<float>(0.0f, fRad, 0.0f));

	// ゲームクリアアニメーション再生
	m_pCompModelAnime->PlayAnime(ANIME_KEY_PLAYER::PLYR_GAMECLEAR, false, 1.0f);

	m_ePlayerState = E_PlayerState::PS_GameClear;
	PLAY_SE(SE_KEY::SE_GAME_CLEAR);

	STOP_BGM();
}

/* ========================================
	死亡関数
	-------------------------------------
	内容：死亡時の処理
========================================= */
void ObjectPlayer::Dead()
{
	m_pCompPlayerController->SetInputEnable(false);			// 操作を無効に
	m_pCompRigidbody->SetVelocity(Vector3<float>::Zero());	// 移動速度を0に

	// 死亡アニメーション
	m_pCompModelAnime->PlayAnime(ANIME_KEY_PLAYER::PLYR_DIE, false, 1.0f);

	m_ePlayerState = E_PlayerState::PS_Dead;
	PLAY_SE(SE_KEY::SE_GAME_OVER);
}

/* ========================================
	衝突判定(開始時)関数
	-------------------------------------
	内容：他オブジェクトとの衝突判定(開始時)
	-------------------------------------
	引数：衝突相手オブジェクト
=========================================== */
void ObjectPlayer::OnCollisionEnter(ObjectBase* pHit)
{
	// コインと接触したら
	if (pHit->GetTag() == E_ObjectTag::Coin)
	{
		m_nCoinNum++;	// コイン取得数加算
	}
}

/* ========================================
	衝突判定(継続時)関数
	-------------------------------------
	内容：他オブジェクトとの衝突判定(継続時)
	-------------------------------------
	引数：衝突相手オブジェクト
=========================================== */
void ObjectPlayer::OnCollisionStay(ObjectBase* pHit)
{
	// 敵キャラと接触したら
	if (pHit->GetTag() == E_ObjectTag::Enemy)
	{
		Damage();
	}
}

/* ========================================
	接地判定関数
	-------------------------------------
	内容：地面に設置しているか判定
========================================= */
void ObjectPlayer::CheckGround()
{
	// 地面に設置している場合　かつ　ジャンプ中でない場合
	if (m_pCompGroundRaycast->GetHitFlg() 
		&& m_pCompRigidbody->GetVelocity().y <= 0.0f)
	{
		// 地面に設置している位置にプレイヤーを設定
		Vector3<float> vPos = m_pCompTransform->GetPosition();
		vPos.y = m_pCompGroundRaycast->GetHitPos().y + 0.5f;
		m_pCompTransform->SetPosition(vPos);

		m_pCompPlayerController->SetUseJump(true);
	}
	else
	{
		m_pCompPlayerController->SetUseJump(false);
	}
}

/* ========================================
	ダメージ関数
	-------------------------------------
	内容：ダメージ処理
========================================= */
void ObjectPlayer::Damage()
{
	if (m_bInvincible)	return;	// 無敵時間中はダメージを受けない
	if (m_nHp <= 0)		return;	// HPが0以下の場合はダメージを受けない


	m_bInvincible = true;	// 無敵時間開始
	m_nHp--;				// HP減少

	// ダメージ音再生
	PLAY_SE(SE_KEY::SE_PLAYER_DAMAGE);

	if (m_nHp <= 0)
	{
		Dead();
	}
}

/* ========================================
	無敵時間更新関数
	-------------------------------------
	内容：無敵時間処理
========================================= */
void ObjectPlayer::InvincibleUpdate()
{
	// カウント加算
	m_fInvFlashCnt	+= DELTA_TIME;
	m_fInvCnt		+= DELTA_TIME;

	// 一定時間ごとに点滅
	if (m_fInvFlashCnt >= INV_FLASH_INTERVAL)
	{
		m_fInvFlashCnt	= 0.0f;
		bool bVisible	= m_pCompModelAnime->GetIsVisible();
		m_pCompModelAnime->SetIsVisible(!bVisible);			// モデルの表示切り替え

	}
	// 無敵時間終了
	if (m_fInvCnt >= INVINCIBLE_TIME)
	{
		m_bInvincible	= false;
		m_fInvCnt		= 0.0f;
		m_fInvFlashCnt	= 0.0f;
		m_pCompModelAnime->SetIsVisible(true);	// モデルの表示ON
	}
}

/* ========================================
	ゲッター(HP)関数
	-------------------------------------
	戻値：int	HP
=========================================== */
int ObjectPlayer::GetHp()
{
	return m_nHp;
}

/* ========================================
	ゲッター(最大HP)関数
	-------------------------------------
	戻値：int	最大HP
=========================================== */
int ObjectPlayer::GetMaxHp()
{
	return m_nMaxHp;
}

/* ========================================
	ゲッター(無敵時間)関数
	-------------------------------------
	戻値：bool	無敵時間フラグ
=========================================== */
bool ObjectPlayer::GetInvincible()
{
	return m_bInvincible;
}

/* ========================================
	ゲッター(コイン数)関数
	-------------------------------------
	戻値：int	コイン数
=========================================== */
int ObjectPlayer::GetCoinNum()
{
	return m_nCoinNum;
}

/* ========================================
	セッター(HP)関数
	-------------------------------------
	引数：int	HP
=========================================== */
void ObjectPlayer::SetHp(int hp)
{
	m_nHp = hp;
}

/* ========================================
	セッター(最大HP)関数
	-------------------------------------
	引数：int	最大HP
=========================================== */
void ObjectPlayer::SetMaxHp(int maxHp)
{
	m_nMaxHp = maxHp;
}

/* ========================================
	セッター(無敵時間)関数
	-------------------------------------
	引数：bool	無敵時間フラグ
=========================================== */
void ObjectPlayer::SetInvincible(bool bInvincible)
{
	m_bInvincible = bInvincible;
}

/* ========================================
	セッター(コイン数)関数
	-------------------------------------
	引数：int	コイン数
=========================================== */
void ObjectPlayer::SetCoinNum(int coinNum)
{
	m_nCoinNum = coinNum;
}

