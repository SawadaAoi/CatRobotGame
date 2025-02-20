/* ========================================
	DX22Base/
	------------------------------------
	シーン管理用cpp
	------------------------------------
	SceneManager.cpp
========================================== */

// =============== インクルード =====================
#include "SceneManager.h"
#include "SceneBase.h"
#include "RegisterAllScene.h"

#include "UIObjectFade.h"
#include "UIObjectFadeIrisOut.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
=========================================== */
void SceneManager::Init()
{
#ifndef _DEBUG
	ChangeScene("SceneTitile", 0.0f);
#endif
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：削除時
=========================================== */
void SceneManager::Uninit()
{
	m_pScene->Uninit();	// 終了処理
}


/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void SceneManager::Update()
{
	m_pScene->Update();	// 更新処理
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
=========================================== */
void SceneManager::Draw()
{
	m_pScene->Draw();	// 描画処理

	// フェード処理が行われている場合はシーン変更処理を行わない
	if (m_pFade && m_pFade->GetFadeType() != UIObjectFade::FADE_NONE) return;

	// シーン変更処理が指示されていたら
	if (m_isSceneChange)	CommitSceneChange();
}
/* ========================================
	シーン変更予約関数
	-------------------------------------
	内容：シーンを変更を予約する
	-------------------------------------
	引数1：シーン名
	引数2：フェード時間
=========================================== */
void SceneManager::ChangeScene(const std::string& sSceneName, float fFadeTime)
{
	if (m_isSceneChange) return;	// シーン変更中は処理しない

	m_sNextSceneName	= sSceneName;	// 次のシーン名を設定
	m_isSceneChange		= true;			// シーン再読み込みフラグを立てる
	m_fFadeTime			= fFadeTime;	// フェード時間を設定

	// シーンが存在していない場合は即座に変更
	if (!m_pScene)
	{
		InitScene();
		return;
	}

	InitFadeOut();	// フェードアウト初期化
}

/* ========================================
	シーン再読み込み予約関数
	-------------------------------------
	内容：シーン再読み込みを予約する
	-------------------------------------
	引数1：フェード時間
=========================================== */
void SceneManager::ReloadScene(float fFadeTime)
{
	if (m_isSceneChange) return;	// シーン変更中は処理しない

	m_sNextSceneName	= m_pScene->GetSceneName();	// 現在のシーン名を再設定
	m_isSceneChange		= true;						// シーン再読み込みフラグを立てる
	m_fFadeTime			= fFadeTime;				// フェード時間を設定

	InitFadeOut();	// フェードアウト初期化
}


/* ========================================
	シーン変更実行関数
	-------------------------------------
	内容：シーン変更を実行する
=========================================== */
void SceneManager::CommitSceneChange()
{
	// シーンが存在していたら終了処理を行う
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();  // 終了処理
	}

	// 新しいシーンを生成
	m_pScene = m_SceneMap[m_sNextSceneName]();

	m_pScene->Init();  // 初期化処理

	m_isSceneChange = false;	// シーン再読み込みフラグを下げる

	InitFadeIn();	// フェードイン初期化
}

/* ========================================
	フェードアウト初期化関数
	-------------------------------------
	内容：フェードアウト初期化
=========================================== */
void SceneManager::InitFadeOut()
{
	if (!m_pFade) return;

	m_pFade->SetState(UIObjectBase::STATE_DEAD);	// 現在のフェードを削除

	// フェードアウト種類によって生成するフェードを変更
	switch (m_eFadeOutKind)
	{
	case SceneManager::FADE_NORMAL:
		m_pFade = m_pScene->AddSceneUI<UIObjectFade>("Fade");
		break;
	case SceneManager::FADE_IRIS_OUT_CIRCLE:
		m_pFade = m_pScene->AddSceneUI<UIObjectFadeIrisOut>("Fade");
		static_cast<UIObjectFadeIrisOut*>(m_pFade)->SetIrisOutType(UIObjectFadeIrisOut::IRIS_OUT_CIRCLE);
		break;
	case SceneManager::FADE_IRIS_OUT_TEXTURE:
		m_pFade = m_pScene->AddSceneUI<UIObjectFadeIrisOut>("Fade");
		static_cast<UIObjectFadeIrisOut*>(m_pFade)->SetIrisOutType(UIObjectFadeIrisOut::IRIS_OUT_TEXTURE);
		break;
	}
	m_pFade->StartFade(FADE_MODE_OUT, m_fFadeTime);
}

/* ========================================
	フェードイン初期化関数
	-------------------------------------
	内容：フェードイン初期化
=========================================== */
void SceneManager::InitFadeIn()
{
	if (!m_pFade) return;
	// フェードイン種類によって生成するフェードを変更
	switch (m_eFadeInKind)
	{
	case SceneManager::FADE_NORMAL:
		m_pFade = m_pScene->AddSceneUI<UIObjectFade>("Fade");
		break;
	case SceneManager::FADE_IRIS_OUT_CIRCLE:
		m_pFade = m_pScene->AddSceneUI<UIObjectFadeIrisOut>("Fade");
		static_cast<UIObjectFadeIrisOut*>(m_pFade)->SetIrisOutType(UIObjectFadeIrisOut::IRIS_OUT_CIRCLE);
		break;
	case SceneManager::FADE_IRIS_OUT_TEXTURE:
		m_pFade = m_pScene->AddSceneUI<UIObjectFadeIrisOut>("Fade");
		static_cast<UIObjectFadeIrisOut*>(m_pFade)->SetIrisOutType(UIObjectFadeIrisOut::IRIS_OUT_TEXTURE);
		break;
	}
	m_pFade->StartFade(FADE_MODE_IN, m_fFadeTime);
}

/* ========================================
	シーン初期化関数
	-------------------------------------
	内容：シーン初期化
=========================================== */
void SceneManager::InitScene()
{
	// シーンが存在していない場合は即座に変更
	CommitSceneChange();
	m_pFade = m_pScene->AddSceneUI<UIObjectFade>("Fade");

}



/* ========================================
	シーン登録関数
	-------------------------------------
	内容：シーンを登録する
=========================================== */
void SceneManager::RegisterScene(const std::string& sSceneName, CreateSceneFunc func)
{
	m_SceneMap[sSceneName] = func;
}

/* ========================================
	ゲッター(シーン)関数
	-------------------------------------
	戻値：SceneBase*		シーン
=========================================== */
SceneBase* SceneManager::GetScene()
{
	return m_pScene.get();
}

/* ========================================
	ゲッター(シーン名リスト)関数
	-------------------------------------
	戻値：std::vector<std::string>		シーン名リスト
=========================================== */
std::vector<std::string> SceneManager::GetSceneNameList()
{
	std::vector<std::string> sSceneNameList;
	for (auto& scene : m_SceneMap)
	{
		sSceneNameList.push_back(scene.first);
	}
	return sSceneNameList;
}

/* ========================================
	セッター(フェードイン種類)関数
	-------------------------------------
	引数：E_FadeKind		フェードイン種類
=========================================== */
void SceneManager::SetFadeInKind(E_FadeKind eFadeInKind)
{
	m_eFadeInKind = eFadeInKind;
}


/* ========================================
	セッター(フェードアウト種類)関数
	-------------------------------------
	引数：E_FadeKind		フェードアウト種類
=========================================== */
void SceneManager::SetFadeOutKind(E_FadeKind eFadeOutKind)
{
	m_eFadeOutKind = eFadeOutKind;
}


/* ========================================
	セッター(フェード種類)関数
	-------------------------------------
	内容：フェード種類を設定する
	-------------------------------------
	引数1：E_FadeKind		フェードイン種類
	引数2：E_FadeKind		フェードアウト種類
=========================================== */
void SceneManager::SetFadeKind(E_FadeKind eFadeInKind, E_FadeKind eFadeOutKind)
{
	SetFadeInKind(eFadeInKind);
	SetFadeOutKind(eFadeOutKind);
}


/* ========================================
	セッター(フェード時間)関数
	-------------------------------------
	引数：float		フェード時間
=========================================== */
void SceneManager::SetFadeTime(float fFadeTime)
{
	m_fFadeTime = fFadeTime;
}
