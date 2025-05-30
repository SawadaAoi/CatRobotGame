/* ========================================
	CatRobotGame/
	------------------------------------
	敵キャラ移動コンポーネント(ランダム)用ヘッダ
	------------------------------------
	説明：敵キャラのランダム移動処理クラス
		　一定間隔でランダムな座標を生成し、移動する
	------------------------------------
	ComponentEnemyMoveRandom.h
========================================== */
#pragma once

// =============== インクルード =====================
#include "ComponentEnemyMoveBase.h"
#include <vector>
#include <memory>

// =============== 前方宣言 =======================
class ShapeLine;
class ShapeSphere;

// =============== クラス定義 =====================
class ComponentEnemyMoveRandom :
    public ComponentEnemyMoveBase
{
public:
	ComponentEnemyMoveRandom(ObjectBase* pOwner);
	void Init() override;
	void Update() override;
	void Draw() override;

	void InitTargetPos();	// 目的座標初期化

	// ゲッター
	Vector3<float> GetTargetPos() const;
	float GetTargetSwitchTime() const;
	std::vector<Vector3<float>>& GetMoveLimitRect();
	Vector3<float> GetMoveLimitRectCenter();

	// セッター
	void SetTargetSwitchTime(float fTime);
	void SetMoveLimitRect(const std::vector<Vector3<float>>& vtRect);	// 移動範囲を設定する
	void SetMoveLimitRectSquare(float fSize);				// 移動範囲を正方形に設定する場合の一辺の長さ
	void SetMoveLimitRectXZ(const Vector2<float>& vSize);	// 移動範囲をXZ平面で設定する場合のサイズ
	void SetDispMoveLimitRect(bool bDisp);					// 移動範囲表示フラグを設定する
	void SetMoveLimitRectCenter(const Vector3<float>& vCenter);	// 移動範囲中心座標を設定する

	DEFINE_COMPONENT_TYPE

#ifdef _DEBUG
	void Debug(DebugUI::Window& window) override;
#endif // _DEBUG
private:
	void Move();
	void SwitchTargetPos();

	Vector3<float> GetRandomPoint(
		const Vector3<float>& v1, const Vector3<float>& v2, const Vector3<float>& v3, const Vector3<float>& v4);
	Vector3<float> GetRandomPointInTriangle(
		const Vector3<float>& v1, const Vector3<float>& v2, const Vector3<float>& v3);

	float GetTriangleArea(const Vector3<float>& P1, const Vector3<float>& P2, const Vector3<float>& P3);

	void UpdateMoveLimitRectWorldPos();
private:
	Vector3<float>	m_vTargetPos;			// 目的座標
	float			m_fTargetSwitchTime;	// 目的座標切り替え時間
	float			m_fTargetSwitchCnt;		// 目的座標切り替えカウント

	Vector3<float>				m_vRectCenter;			// 移動範囲中心座標
	std::vector<Vector3<float>> m_vtMoveLimitRectLocal;	// 移動範囲座標(四角形)
	std::vector<Vector3<float>> m_vtMoveLimitRectWorld;	// 移動範囲座標(四角形)(ワールド座標)

	bool m_bDispMoveLimitRect;						// 移動範囲表示フラグ
	std::unique_ptr<ShapeLine>	m_pRectLine;		// 移動範囲描画用
	std::unique_ptr<ShapeSphere> m_pTargetSphere;	// 目的座標描画用

#ifdef _DEBUG
	bool m_bMoveStop;	// 移動停止フラグ
#endif // _DEBUG

};

