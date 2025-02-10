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

// =============== クラス定義 ===================
class SceneStageSelect :
    public SceneBase
{
public:
	void InitLocal() override;
	void UpdateLocal() override;
private:
	UIObjectText* m_pStageName;
	UIObjectText* m_pScreenName;

	UIObjectBase* m_pStageImage;
	UIComponentSprite* m_pCompSpriteStgImg;

	int m_nSelectStageNum;
};

