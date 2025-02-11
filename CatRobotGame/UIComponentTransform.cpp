/* ========================================
	DX22Base/
	------------------------------------
	UI用座標変換コンポーネント用cpp
	------------------------------------
	UIComponentTransform.cpp
========================================== */

// =============== インクルード =====================
#include "UIComponentTransform.h"
#include "UIObjectBase.h"
#include "Vector3.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所持オブジェクト
=========================================== */
UIComponentTransform::UIComponentTransform(UIObjectBase* pOwner)
	: UIComponentBase(pOwner, UIOrderTransform)
	, m_vLocalPosition(0.0f, 0.0f)
	, m_fLocalRotation(0.0f)
	, m_vLocalScale(100.0f, 100.0f)
	, m_vWorldPosition(0.0f, 0.0f)
	, m_fWorldRotation(0.0f)
	, m_vWorldScale(1.0f, 1.0f)
{

}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void UIComponentTransform::Init()
{
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void UIComponentTransform::Update()
{
	UpdateWorldTransform();
}

/* ========================================
	ワールド座標更新関数
	-------------------------------------
	内容：ワールド座標を更新する
=========================================== */
void UIComponentTransform::UpdateWorldTransform()
{
	// 親オブジェクトがある場合
	if (m_pOwnerObj->GetParentUI())
	{
		UIComponentTransform* pParentTran = m_pOwnerObj->GetParentUI()->GetComponent<UIComponentTransform>();

		// ローカル行列(回転、座標)を生成
		DirectX::XMMATRIX localMat =
			DirectX::XMMatrixRotationZ(m_fLocalRotation) *
			DirectX::XMMatrixTranslation(m_vLocalPosition.x, m_vLocalPosition.y, 0.0f);

		// 親オブジェクトのワールド行列(回転、座標)を生成
		DirectX::XMMATRIX parentMat =
			DirectX::XMMatrixRotationZ(pParentTran->GetRotation()) *
			DirectX::XMMatrixTranslation(
				pParentTran->GetPosition().x,
				pParentTran->GetPosition().y,
				0.0f);

		// 自身のローカル行列(回転、座標)と親オブジェクトのワールド行列(回転、座標)を合成
		DirectX::XMMATRIX matrix = localMat * parentMat;

		// 合成行列から座標、回転を取得
		Vector3<float> vPos = Vector3<float>::FromMatrix_Translation(matrix);	// 座標取得
		Vector3<float> vRot = Vector3<float>::FromMatrix_RotationEuler(matrix);	// 回転取得
		m_vWorldPosition.x = vPos.x;
		m_vWorldPosition.y = vPos.y;
		m_fWorldRotation = vRot.z;

		// ワールドスケールを計算(回転、座標と一緒に計算すると大きさが不正確になるため別で計算)
		m_vWorldScale = m_vLocalScale * pParentTran->GetScale();
	}
	else
	{
		// 親オブジェクトがない場合はローカル座標をワールド座標に設定
		m_vWorldPosition = m_vLocalPosition;
		m_fWorldRotation = m_fLocalRotation;
		m_vWorldScale = m_vLocalScale;
	}
}

/* ========================================
	親オブジェクト解除関数
	-------------------------------------
	内容：親オブジェクトが解除された際の処理
=========================================== */
void UIComponentTransform::ClearParent()
{
	// ワールド座標をローカル座標に設定(現在の状態を保持するため)
	m_vLocalPosition = m_vWorldPosition;
	m_fLocalRotation = m_fWorldRotation;
	m_vLocalScale = m_vWorldScale;
}

/* ========================================
	ローカル座標再計算関数
	-------------------------------------
	内容：親オブジェクトがセットされた時に、
		　現在のローカル座標の座標、回転、大きさを保持したまま
		  親オブジェクトのワールド座標を考慮したローカル座標を再計算する
=========================================== */
void UIComponentTransform::RecalculateLocalTransform()
{
	if (!m_pOwnerObj->GetParentUI()) return;	// 親オブジェクトがない場合は処理しない

	// 回転、座標の再計算
	// 親オブジェクトのTransformコンポーネントを取得
	UIComponentTransform* pParentTran = m_pOwnerObj->GetParentUI()->GetComponent<UIComponentTransform>();
	// 親オブジェクトのワールド行列(回転、座標)を生成
	DirectX::XMMATRIX parentMat =
		DirectX::XMMatrixRotationZ(pParentTran->GetRotation()) *		// 回転
		DirectX::XMMatrixTranslation(							// 座標		
			pParentTran->GetPosition().x,
			pParentTran->GetPosition().y,
			0.0f);

	// ローカル行列(回転、座標)を生成
	DirectX::XMMATRIX localMat =
		DirectX::XMMatrixRotationZ(m_fWorldRotation) *
		DirectX::XMMatrixTranslation(m_vWorldPosition.x, m_vWorldPosition.y, 0.0f);

	// 親のワールド行列の逆行列を取得
	DirectX::XMMATRIX parentMatInv = DirectX::XMMatrixInverse(nullptr, parentMat);

	// ローカル行列と親の逆行列を掛け合わせてローカル行列を取得
	DirectX::XMMATRIX computedLocalMatrix = localMat * parentMatInv;

	// 作成した行列から座標、回転を取得
	Vector3<float> vPos = Vector3<float>::FromMatrix_Translation(computedLocalMatrix);		// 座標取得
	Vector3<float> vRot = Vector3<float>::FromMatrix_RotationEuler(computedLocalMatrix);	// 回転取得
	m_vLocalPosition.x = vPos.x;
	m_vLocalPosition.y = vPos.y;
	m_fLocalRotation = vRot.z;

	// 大きさの再計算(回転、座標と一緒に計算すると大きさが不正確になるため別で計算)
	m_vLocalScale = m_vWorldScale / pParentTran->GetScale();
}

/* ========================================
	座標移動関数
	-------------------------------------
	内容：座標を移動する
	-------------------------------------
	引数1：移動量	Vector2<float>
=========================================== */
void UIComponentTransform::Translate(const Vector2<float>& vPos)
{
	m_vLocalPosition += vPos;
	UpdateWorldTransform();
}

/* ========================================
	座標移動関数
	-------------------------------------
	内容：座標を移動する
	-------------------------------------
	引数1：移動量	X座標
	引数2：移動量	Y座標
=========================================== */
void UIComponentTransform::Translate(float x, float y)
{
	Translate(Vector2<float>(x, y));
}

/* ========================================
	X座標移動関数
	-------------------------------------
	内容：X座標を移動する
	-------------------------------------
	引数1：移動量	X座標
=========================================== */
void UIComponentTransform::TranslateX(float x)
{
	Translate(Vector2<float>(x, 0.0f));
}

/* ========================================
	Y座標移動関数
	-------------------------------------
	内容：Y座標を移動する
	-------------------------------------
	引数1：移動量	Y座標
=========================================== */
void UIComponentTransform::TranslateY(float y)
{
	Translate(Vector2<float>(0.0f, y));
}

/* ========================================
	回転加算関数
	-------------------------------------
	内容：引数の回転を加える
	-------------------------------------
	引数1：回転量(デグリー) float
=========================================== */
void UIComponentTransform::Rotate(float fRot)
{
	m_fLocalRotation += MathUtils::ToRadian(fRot);
	UpdateWorldTransform();
}

/* ========================================
	スケール変更関数
	-------------------------------------
	内容：スケールを変更する
	-------------------------------------
	引数1：スケール	Vector2<float>
=========================================== */
void UIComponentTransform::Scale(const Vector2<float>& vScale)
{
	m_vLocalScale *= vScale;
	UpdateWorldTransform();
}

/* ========================================
	スケール変更関数
	-------------------------------------
	内容：スケールを変更する
	-------------------------------------
	引数1：スケール	X座標
	引数2：スケール	Y座標
=========================================== */
void UIComponentTransform::Scale(float x, float y)
{
	Scale(Vector2<float>(x, y));
	UpdateWorldTransform();
}

/* ========================================
	X座標スケール変更関数
	-------------------------------------
	内容：X座標スケールを変更する
	-------------------------------------
	引数1：スケール	X座標
=========================================== */
void UIComponentTransform::ScaleX(float x)
{
	Scale(Vector2<float>(x, 1.0f));
	UpdateWorldTransform();
}

/* ========================================
	Y座標スケール変更関数
	-------------------------------------
	内容：Y座標スケールを変更する
	-------------------------------------
	引数1：スケール	Y座標
=========================================== */
void UIComponentTransform::ScaleY(float y)
{
	Scale(Vector2<float>(1.0f, y));
	UpdateWorldTransform();
}

/* ========================================
	ゲッター(ワールド座標)関数
	-------------------------------------
	戻値：座標	Vector3<float>
=========================================== */
Vector2<float> UIComponentTransform::GetPosition()
{
	return m_vWorldPosition;
}

/* ========================================
	ゲッター(ワールド回転)関数
	-------------------------------------
	戻値：回転	float
=========================================== */
float UIComponentTransform::GetRotation()
{
	return m_fWorldRotation;
}

/* ========================================
	ゲッター(ワールドスケール)関数
	-------------------------------------
	戻値：スケール	Vector3<float>
=========================================== */
Vector2<float> UIComponentTransform::GetScale()
{
	return m_vWorldScale;
}

/* ========================================
	ゲッター(ローカル座標)関数
	-------------------------------------
	戻値：座標	Vector3<float>
=========================================== */
Vector2<float> UIComponentTransform::GetLocalPosition()
{
	return m_vLocalPosition;
}

/* ========================================
	ゲッター(ローカル回転)関数
	-------------------------------------
	戻値：回転	float
=========================================== */
float UIComponentTransform::GetLocalRotation()
{
	return m_fLocalRotation;
}


/* ========================================
	ゲッター(ローカルスケール)関数
	-------------------------------------
	戻値：スケール	Vector3<float>
=========================================== */
Vector2<float> UIComponentTransform::GetLocalScale()
{
	return m_vLocalScale;
}


/* ========================================
	セッター(ワールド座標)関数
	-------------------------------------
	引数：座標	Vector3<float>
=========================================== */
void UIComponentTransform::SetPosition(Vector2<float> vPos)
{
	m_vWorldPosition = vPos;

	if (m_pOwnerObj->GetParentUI())
	{
		// 親オブジェクトのTransformコンポーネントを取得
		UIComponentTransform* pParentTran = m_pOwnerObj->GetParentUI()->GetTransform();
		// 親オブジェクトのワールド行列(座標)を生成
		DirectX::XMMATRIX parentMat = DirectX::XMMatrixTranslation(
			pParentTran->GetPosition().x, pParentTran->GetPosition().y, 0.0f);

		// ローカル行列(座標)を生成
		DirectX::XMMATRIX localMat = DirectX::XMMatrixTranslation(vPos.x, vPos.y, 0.0f);

		// 親のワールド行列の逆行列を取得
		DirectX::XMMATRIX parentMatInv = DirectX::XMMatrixInverse(nullptr, parentMat);

		// ローカル行列と親の逆行列を掛け合わせてローカル行列を取得
		DirectX::XMMATRIX localMatInv = localMat * parentMatInv;

		// 作成した行列から座標を取得
		Vector3<float> vPos = Vector3<float>::FromMatrix_Translation(localMatInv);	// 座標取得

		m_vLocalPosition.x = vPos.x;
		m_vLocalPosition.y = vPos.y;

		// ワールド座標の更新
		UpdateWorldTransform();
	}
	else
	{
		m_vLocalPosition = vPos;
	}
}


/* ========================================
	セッター(ワールド回転)関数
	-------------------------------------
	引数：回転	float
=========================================== */
void UIComponentTransform::SetRotation(float fRot)
{
	if (m_pOwnerObj->GetParentUI())
	{
		// 親オブジェクトのTransformコンポーネントを取得
		UIComponentTransform* pParentTran = m_pOwnerObj->GetParentUI()->GetTransform();
		// 親オブジェクトのワールド行列(回転)を生成
		DirectX::XMMATRIX parentMat = DirectX::XMMatrixRotationZ(pParentTran->GetRotation());

		// ローカル行列(回転)を生成
		DirectX::XMMATRIX localMat = DirectX::XMMatrixRotationZ(fRot);

		// 親のワールド行列の逆行列を取得
		DirectX::XMMATRIX parentMatInv = DirectX::XMMatrixInverse(nullptr, parentMat);

		// ローカル行列と親の逆行列を掛け合わせてローカル行列を取得
		DirectX::XMMATRIX localMatInv = localMat * parentMatInv;

		// 作成した行列から回転を取得
		Vector3<float> vRot = Vector3<float>::FromMatrix_RotationEuler(localMatInv);	// 回転取得

		m_fLocalRotation = vRot.z;

		// ワールド座標の更新
		UpdateWorldTransform();
	}
	else
	{
		m_fLocalRotation = fRot;
	}
}

/* ========================================
	セッター(ワールドスケール)関数
	-------------------------------------
	引数：スケール	Vector3<float>
=========================================== */
void UIComponentTransform::SetScale(Vector2<float> vScale)
{
	if (m_pOwnerObj->GetParentUI())
	{
		// 親オブジェクトのTransformコンポーネントを取得
		UIComponentTransform* pParentTran = m_pOwnerObj->GetParentUI()->GetTransform();

		m_vLocalScale = vScale / pParentTran->GetScale();

		// ワールド座標の更新
		UpdateWorldTransform();
	}
	else
	{
		m_vLocalScale = vScale;
	}
}

/* ========================================
	セッター(ローカル座標)関数
	-------------------------------------
	引数：座標	Vector3<float>
=========================================== */
void UIComponentTransform::SetLocalPosition(Vector2<float> vPos)
{
	m_vLocalPosition = vPos;
	UpdateWorldTransform();
}

/* ========================================
	セッター(ローカル回転)関数
	-------------------------------------
	引数：回転	float
=========================================== */
void UIComponentTransform::SetLocalRotation(float fRot)
{
	m_fLocalRotation = fRot;
	UpdateWorldTransform();
}

/* ========================================
	セッター(ローカルスケール)関数
	-------------------------------------
	引数：スケール	Vector3<float>
=========================================== */
void UIComponentTransform::SetLocalScale(Vector2<float> vScale)
{
	m_vLocalScale = vScale;
	UpdateWorldTransform();
}

#ifdef _DEBUG
/* ========================================
	デバッグ関数
	-------------------------------------
	内容：デバッグ用の処理
	-------------------------------------
	引数1：ウィンドウ	DebugUI::Window&
=========================================== */
void UIComponentTransform::Debug(DebugUI::Window& window)
{
	using namespace DebugUI;

	Item* pGroupUITran = Item::CreateGroup("UI_Transform");

	// 親オブジェクトがある場合
	if (m_pOwnerObj->GetParentUI())
	{
		// ワールド変数
		pGroupUITran->AddGroupItem(Item::CreateValue("World", Item::Kind::Label));
		// 座標
		pGroupUITran->AddGroupItem(Item::CreateBind("Position", Item::Kind::Vector2, &m_vWorldPosition));
		// 回転
		// 表示だけオイラー角に変換(クォータニオンは直接入力できないため)
		pGroupUITran->AddGroupItem(Item::CreateCallBack("Rotation", Item::Kind::Float,
			[this](bool isWrite, void* arg)	// isWrite:入力があるかどうか arg:入力値
		{
			float* fRotDeg = static_cast<float*>(arg);
			// 値変更時
			if (isWrite)
				m_fWorldRotation = MathUtils::ToRadian(*fRotDeg);
			else
				*fRotDeg = MathUtils::ToDegree(m_fWorldRotation);
		}));
		// 大きさ
		pGroupUITran->AddGroupItem(Item::CreateBind("Scale", Item::Kind::Vector2, &m_vWorldScale));

		// 親クラスがある場合は、ローカルとワールドの2️種類を表示する為、見出しを追加
		pGroupUITran->AddGroupItem(Item::CreateValue("Local", Item::Kind::Label));
	}

	// ローカル変数
	// 座標
	pGroupUITran->AddGroupItem(Item::CreateBind("Position ", Item::Kind::Vector2, &m_vLocalPosition, true));
	// 回転
	pGroupUITran->AddGroupItem(Item::CreateCallBack("Rotation ", Item::Kind::Float,
		[this](bool isWrite, void* arg)
	{
		float* fRotDeg = static_cast<float*>(arg);
		// 値変更時
		if (isWrite)
			m_fLocalRotation = MathUtils::ToRadian(*fRotDeg);
		else
			*fRotDeg = MathUtils::ToDegree(m_fLocalRotation);
	}));
	// 大きさ
	pGroupUITran->AddGroupItem(Item::CreateBind("Scale ", Item::Kind::Vector2, &m_vLocalScale));

	window.AddItem(pGroupUITran);
}
#endif // _DEBUG
