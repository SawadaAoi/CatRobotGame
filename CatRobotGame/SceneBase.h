/* ========================================
	DX22Base/
	------------------------------------
	シーン用ヘッダ
	------------------------------------
	説明：各シーンの基底クラス
	------------------------------------
	SceneBase.h
========================================== */
#pragma once

// =============== インクルード =====================
#include <vector>
#include "ObjectBase.h"
#include <memory>
#include "DebugMenu.h"
#include "UIObjectBase.h"

// =============== 前方宣言 =======================
class ComponentCollisionBase;

// =============== 定数定義 =======================
// E_Stateの呼び出しを省略
#define OBJ_ACTIVE	ObjectBase::E_State::STATE_ACTIVE
#define OBJ_DEAD	ObjectBase::E_State::STATE_DEAD
#define OBJ_PAUSE	ObjectBase::E_State::STATE_PAUSE

// E_Stateの呼び出しを省略(UIオブジェクト用)
#define UI_ACTIVE	UIObjectBase::E_State::STATE_ACTIVE
#define UI_DEAD		UIObjectBase::E_State::STATE_DEAD
#define UI_PAUSE	UIObjectBase::E_State::STATE_PAUSE

// シーン名取得関数の定義を省略するためのマクロ
#define DEFINE_SCENE_TYPE(name)				\
	std::string GetSceneName() override {	\
		return #name;						\
	} 

// =============== クラス定義 =====================
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {};

	void Init();	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	virtual void InitLocal() {};	// 個別初期化処理
	virtual void UninitLocal() {};	// 個別終了処理
	virtual void UpdateLocal() {};	// 個別更新処理
	virtual void DrawLocal() {};	// 個別描画処理

	void UpdateObject();
	void UpdateUI();

	// UI描画順並び替え
	void SortUIObjects();

	void RemoveDeadObjects();
	void RemoveDeadUIObjects();

	// オブジェクト関連
	template<typename T>
	T* AddSceneObject(std::string sName);	// オブジェクト追加
	template<typename T>
	T* GetSceneObject(std::string sName);	// オブジェクト取得(名前指定)
	template<typename T>
	T* GetSceneObject();					// オブジェクト取得(型検索(最初に見つかったもの))
	template<typename T>
	std::vector<T*> GetSceneObjects();		// オブジェクト取得(型検索(全て))

	void AddSceneObjectBase(ObjectBase* pObject);	// オブジェクト追加
	ObjectBase* FindSceneObject(std::string sName);	// オブジェクト検索

	// UIオブジェクト関連
	template<typename T>
	T* AddSceneUI(std::string sName);	// UIオブジェクト追加
	template<typename T>
	T* GetSceneUI(std::string sName);	// UIオブジェクト取得(名前指定)
	template<typename T>
	T* GetSceneUI();					// UIオブジェクト取得(型検索(最初に見つかったもの))
	template<typename T>
	std::vector<T*> GetSceneUIs();		// UIオブジェクト取得(型検索(全て))

	void AddSceneUI(UIObjectBase* pUIObject);		// UIオブジェクト追加
	UIObjectBase* FindSceneUI(std::string sName);	// UIオブジェクト検索


	// 衝突判定関連
	void AddObjectCollision(ComponentCollisionBase* pCollision);	// 衝突判定コンポーネント追加
	void RemoveObjectCollision(ComponentCollisionBase* pCollision);	// 衝突判定コンポーネント削除

	// 名前連番付与関数(重複チェック)
	std::string CreateUniqueName(std::string sName);
	std::string CreateUniqueUIName(std::string sName);

	// ゲッター
	virtual std::string GetSceneName();								// シーン名取得
	std::vector<ObjectBase*> GetAllSceneObjects();					// シーン上に存在する全てのオブジェクトを取得
	std::vector<UIObjectBase*> GetAllSceneUIObjects();				// シーン上に存在する全てのUIオブジェクトを取得
	std::vector<ObjectBase*> GetSceneObjectsTag(E_ObjectTag tag);	// タグに対応するオブジェクトを取得
	ObjectBase* GetSceneObjectTag(E_ObjectTag tag);					// タグに対応するオブジェクトを取得(一番最初に見つかったもの)

private:
	void UpdateCollision();	// 衝突判定更新関数
	bool CheckUniqueName(std::string sName, std::vector<ObjectBase*> pObjects);	// 名前重複チェック
	bool CheckUniqueUIName(std::string sName, std::vector<UIObjectBase*> pUIs);	// 名前重複チェック

#ifdef _DEBUG
	void InitObjectList();
	void InitObjectInfo(std::string sName);
	void InitUIList();
	void InitUIInfo(std::string sName);

	void ReloadDebugObjectList();	// オブジェクトリスト再読み込み
	void AddObjectListChild(ObjectBase* pObject);
	void ReloadDebugUIList();		// UIオブジェクトリスト再読み込み
	void AddUIListChild(UIObjectBase* pUIObject);

#endif // _DEBUG
protected:
	std::vector<std::unique_ptr<ObjectBase>>	m_pObjects;				// シーンに所属するオブジェクト一覧
	std::vector<std::unique_ptr<ObjectBase>>	m_pStandbyObjects;		// オブジェクトを一時的に保存しておく配列
	std::vector<ComponentCollisionBase*>		m_pObjectCollision;		// 各オブジェクトが持つ衝突判定コンポーネント

	std::vector<std::unique_ptr<UIObjectBase>>	m_pUIObjects;			// シーンに所属するUIオブジェクト一覧
	std::vector<std::unique_ptr<UIObjectBase>>	m_pStandbyUIObjects;	// UIオブジェクトを一時的に保存しておく配列

	bool m_bIsUpdating;	// 更新中かどうか
	bool m_bIsUpdatingUI;	// UI更新中かどうか

#ifdef _DEBUG
	ObjectBase*		m_pSelectObj;			// 一覧で選択中のオブジェクト
	int				m_nObjectListSelectNo;	// オブジェクトリストの番号
	UIObjectBase*	m_pSelectUI;			// 一覧で選択中のUIオブジェクト
	int				m_nUISelectNo;			// UIオブジェクトリストの番号
#endif // _DEBUG
};

#include "SceneBase.inl"