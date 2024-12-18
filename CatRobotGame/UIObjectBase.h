/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト基底用ヘッダ
	------------------------------------
	説明：UIオブジェクトの基底クラス
	------------------------------------
	UIObjectBase.h
========================================== */
#pragma once

// =============== インクルード =====================
#include "vector"
#include <string>
#include "UIComponentBase.h"	// UIコンポーネント基底クラス
#include <memory>			// std::unique_ptr用
#include "TimeManager.h"	// 経過時間をどこでも取得できるようにするため
#include <fstream>

// =============== 前方宣言 =====================
class SceneBase;	// シーン基底クラス

// =============== 定数定義 =======================
// オブジェクトID取得関数の定義を省略するためのマクロ
// 使い方：クラス定義内でDEFINE_OBJECT_TYPE(クラス名)を記述する
// 例：DEFINE_OBJECT_TYPE(ObjectPlayer);
// 関数のポインタをIDとして扱うため、コンポーネントの種類によって異なるIDを取得できる
#define DEFINE_UI_OBJECT_TYPE(name)										\
    static size_t GetStaticTypeID() {									\
		static const size_t typeID = reinterpret_cast<size_t>(&typeID); \
        return typeID;													\
    }																	\
    size_t GetTypeID() const override {									\
        return GetStaticTypeID();										\
    }																	\
	std::string GetUIClassName() const override {						\
		return #name;													\
	} 


// =============== クラス定義 =====================
class UIObjectBase
{
public:

	// オブジェクトの状態
	enum E_State
	{
		STATE_ACTIVE,	// アクティブ
		STATE_PAUSE,	// 一時停止
		STATE_DEAD,		// 死亡

		STATE_MAX,		// 状態の最大数
	};
public:
	UIObjectBase() = delete;
	UIObjectBase(SceneBase* pScene);
	virtual ~UIObjectBase() {};

	// 処理が変わらない関数
	void Init(std::string sName);
	void Uninit();
	void Update();
	void Draw();

	// 子クラスで実装する関数
	virtual void InitLocal() {};	// 個別初期化処理
	virtual void UninitLocal() {};	// 個別終了処理
	virtual void UpdateLocal() {};	// 個別更新処理
	virtual void DrawLocal() {};	// 個別描画処理

	// 親子関係
	void SetParentUI(UIObjectBase* pParentObj);		// 親オブジェクトの設定
	void AddChildUI(UIObjectBase* pChildObj);		// 子オブジェクトの追加
	void RemoveParentUI();							// 親オブジェクトの削除
	void RemoveChildUI(UIObjectBase* pChildObj);	// 子オブジェクトの削除
	void RemoveAllChildUIs();						// 全ての子オブジェクトの削除
	int GetGenerationCount();						// 子オブジェクトの数を取得


	// ファイル入出力
	virtual void OutPutLocalData(std::ofstream& file);	// オブジェクトのデータ出力
	virtual void InputLocalData(std::ifstream& file);	// オブジェクトのデータ入力

	// ゲッター
	SceneBase* GetOwnerScene() const;					// 所有シーンの取得
	E_State GetState() const;							// UIの状態の取得
	virtual size_t GetTypeID() const;					// コンポーネントの種類IDの取得
	static size_t GetStaticTypeID();					// コンポーネントの種類IDの取得
	virtual std::string GetUIClassName() const;		// オブジェクトクラス名の取得
	UIObjectBase* GetParentUI() const;				// 親オブジェクトの取得
	std::vector<UIObjectBase*> GetChildUIs() const;	// 子オブジェクトの取得
	std::string GetName() const;						// オブジェクト名の取得

	// セッター
	void SetState(E_State eState);	// UIの状態の設定
	void SetName(std::string sName);	// オブジェクト名の設定

	// コンポーネント関連
	template<typename T>
	T* AddComponent();	// コンポーネント追加

	template<typename T>
	T* GetComponent();	// コンポーネント取得

	template<typename T>
	void RemoveComponent();	// コンポーネント削除

#ifdef _DEBUG
	void Debug();					// デバッグ用の処理(オブジェクト情報ウィンドウに表示)
	virtual void DebugLocal() {};	// 個別デバッグ処理

	DebugUI::Item* InitParentList();	// 親リストの初期化

	void ChangeName();			// 名前変更
	void ChangeParentList(std::string sParentName);		// 親変更

	std::string GetListName();	// リスト表示用の名前取得
#endif

private:
	void InitDefaultComponent();	// デフォルトコンポーネント設定

protected:
	SceneBase*										m_pOwnerScene;	// 所有シーン
	std::vector<std::unique_ptr<UIComponentBase>>	m_pComponents;	// コンポーネント一覧

	std::string m_sName;	// UI名
	E_State		m_eState;	// UIの状態
	
	// 親子関係
	UIObjectBase*				m_pParentUI;	// 親UI
	std::vector<UIObjectBase*>	m_pChildUIs;	// 子UI
};

#include "UIObjectBase.inl"	// コンポーネント関連のテンプレート関数の実装