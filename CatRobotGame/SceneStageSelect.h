/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージセレクト)用ヘッダ
	------------------------------------
	説明：各ステージを選択するシーンクラス
	------------------------------------
	SceneStageSelect.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneBase.h"

// =============== 前方宣言 ===================
class UIObjectText;
class UIComponentSprite;
class ObjectCamera;

// =============== クラス定義 ===================
class SceneStageSelect :
    public SceneBase
{
public:
	SceneStageSelect();
	void InitLocal() override;
	void UpdateLocal() override;
private:
	void StageChangeInput();
private:
	ObjectCamera* m_pCamera;

	UIObjectText* m_pStageName;
	UIObjectText* m_pScreenName;

	int m_nSelectStageNum;
	int m_nSelectStageNumOld;

	bool m_bChangeStageModel;
};

