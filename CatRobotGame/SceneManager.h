/* ========================================
	DX22Base/
	------------------------------------
	シーン管理用ヘッダ
	------------------------------------
	説明：各シーンの管理を行うクラス
	------------------------------------
	SceneManager.h
========================================== */
#pragma once

// =============== インクルード =====================
#include "SceneBase.h"
#include "UIObjectFade.h"
#include <unordered_map>
#include <functional>

// =============== 定数定義 =======================
#define REGISTER_SCENE(className) SceneManager::RegisterScene(#className, []() { return std::make_unique<className>(); })

#define FADE_KIND_NORMAL			SceneManager::FADE_NORMAL
#define FADE_KIND_IRIS_OUT_CIRCLE	SceneManager::FADE_IRIS_OUT_CIRCLE
#define FADE_KIND_IRIS_OUT_TEXTURE	SceneManager::FADE_IRIS_OUT_TEXTURE

// =============== 前方宣言 =======================
class UIObjectFade;

// =============== クラス定義 =====================
class SceneManager
{
public:
	using CreateSceneFunc = std::function<std::unique_ptr<SceneBase>()>;

	enum E_FadeKind
	{
		FADE_NORMAL,
		FADE_IRIS_OUT_CIRCLE,
		FADE_IRIS_OUT_TEXTURE,
	};
public:

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// すべてのシーン登録
	static void RegisterAllScene();
	// シーン登録
	static void RegisterScene(const std::string& sSceneName, CreateSceneFunc func);
	
	// シーン切り替え
	static void ChangeScene(const std::string& sSceneName, float fFadeTime = 1.0f);	// シーン切り替え

	// シーン再読み込み
	static void ReloadScene(float fFadeTime = 1.0f);	// シーン再読み込みを呼び出す

	// ゲッター
	static SceneBase* GetScene();	// シーン取得
	static std::vector<std::string> GetSceneNameList();	// シーン名リスト取得

	// セッター
	static void SetFadeInKind(E_FadeKind eFadeInKind);							// フェードイン種類設定
	static void SetFadeOutKind(E_FadeKind eFadeOutKind);						// フェードアウト種類設定
	static void SetFadeKind(E_FadeKind eFadeInKind, E_FadeKind eFadeOutKind);	// フェード種類設定
	static void SetFadeTime(float fFadeTime);									// フェード時間設定

private:
	static void CommitSceneChange();	// シーン変更を確定する
	static void InitFadeOut();			// フェードアウト初期化
	static void InitFadeIn();			// フェードイン初期化
	static void InitScene();			// シーン初期化
private:
	static inline std::unique_ptr<SceneBase> m_pScene = nullptr;	// std::unique_ptrに変更

	static inline std::unordered_map<std::string, CreateSceneFunc> m_SceneMap;	// シーン生成関数マップ
	static inline std::string	m_sNextSceneName	= "";		// 次のシーン名
	static inline bool			m_isSceneChange		= false;	// シーン切り替えフラグ

	static inline UIObjectFade* m_pFade = nullptr;
	static inline E_FadeKind	m_eFadeInKind	= FADE_NORMAL;
	static inline E_FadeKind	m_eFadeOutKind = FADE_NORMAL;
	static inline float			m_fFadeTime = 1.0f;
};

