/* ========================================
	CatRobotGame/
	------------------------------------
	リスポーン用ヘッダ
	------------------------------------
	説明：衝突したらリスポーンするオブジェクト
	------------------------------------
	ObjectRespawn.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "ObjectBase.h"

// =============== 前方宣言 =======================
class ComponentCollisionAABB;

// =============== クラス =======================
class ObjectRespawn :
    public ObjectBase
{
public:
	// リスポーン種類
	enum E_RespawnType
	{
		RT_RELOAD_SCENE,	// シーンを再読み込み
		RT_POSITION,		// 決まった位置からリスポーン
	};

public:
	ObjectRespawn(SceneBase* pScene);

	void InitLocal() override;
	void UpdateLocal() override;

	void OnCollisionEnter(ObjectBase* pHit) override;

	// ゲッター
	E_RespawnType GetRespawnType() const;
	Vector3<float> GetRespawnPosition() const;

	// セッター
	void SetRespawnType(E_RespawnType type);
	void SetRespawnPosition(const Vector3<float>& pos);

	DEFINE_OBJECT_TYPE(ObjectRespawn)
private:
	E_RespawnType	m_RespawnType;			// リスポーン種類
	Vector3<float>	m_RespawnPosition;		// リスポーン位置

	bool			m_IsReloadScene;		// シーン再読み込みフラグ

	ComponentCollisionAABB* m_pCompColAABB;	// 当たり判定
};

