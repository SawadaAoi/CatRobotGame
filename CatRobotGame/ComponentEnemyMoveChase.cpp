/* ========================================
	CatRobotGame/
	------------------------------------
	�G�L�����ړ��R���|�[�l���g(�ǐ�)�pcpp
	------------------------------------
	ComponentEnemyMoveChase.cpp
========================================== */

// =============== �C���N���[�h =====================
#include "ComponentEnemyMoveChase.h"
#include "ComponentTransform.h"
#include "ComponentRigidbody.h"
#include "ObjectBase.h"
#include "SceneBase.h"
#include "ShapeLine.h"
#include "ColorVec3.h"

// =============== �萔��` =======================
const float DEFAULT_CHASE_START_DIST	= 10.0f;		// �ǐՊJ�n����
const float DEFAULT_LIMIT_DIST_SQ		= 1.0f * 1.0f;	// �ړ���ɓ��B���鋗����2��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�҃I�u�W�F�N�g
========================================= */
ComponentEnemyMoveChase::ComponentEnemyMoveChase(ObjectBase* pOwner)
	:ComponentEnemyMoveBase(pOwner)
	, m_pTargetObj(nullptr)
	, m_fDistSq(0.0f)
	, m_fLimitDistSq(DEFAULT_LIMIT_DIST_SQ)
	, m_fChaseStartDist(DEFAULT_CHASE_START_DIST)
#ifdef _DEBUG
	, m_bDispDistLine(true)
#else
	, m_bDispDistLine(false)
#endif // _DEBUG
	, m_pDistLine(nullptr)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================= */
void ComponentEnemyMoveChase::Init()
{
	ComponentEnemyMoveBase::Init();

	m_pTargetObj = m_pOwnerObj->GetOwnerScene()->FindSceneObject("Player");
	m_pDistLine = std::make_unique<ShapeLine>(1);
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================= */
void ComponentEnemyMoveChase::Update()
{
#ifdef _DEBUG
	if (CHECK_DISP_COMP("EnemyMoveChase"))
	{
		WIN_OBJ_INFO["EnemyMoveChase"]["TargetObj"].SetText(m_pTargetObj ? m_pTargetObj->GetName() : "None");
		WIN_OBJ_INFO["EnemyMoveChase"]["ChaseStartDistSqr"].SetText(std::to_string(m_fChaseStartDist * m_fChaseStartDist));
	}
#endif // _DEBUG

	// �v���C���[�����Ȃ��ꍇ�͉������Ȃ�
	if (!m_pTargetObj)
	{
		m_pTargetObj = m_pOwnerObj->GetOwnerScene()->FindSceneObject("Player");
		return;
	}

	// �ړ�����
	Move();

	// �������C���`��
	if (m_bDispDistLine)
		DrawPlayerDistLine();
	
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
========================================= */
void ComponentEnemyMoveChase::Draw()
{
	if (m_bDispDistLine)
	{
		m_pDistLine->Draw();
	}
}


/* ========================================
	�ړ��֐�
	-------------------------------------
	���e�F�ړ�����
========================================= */
void ComponentEnemyMoveChase::Move()
{
	// �v���C���[�̍��W���擾
	Vector3<float> vTargetPos = m_pTargetObj->GetComponent<ComponentTransform>()->GetWorldPosition();

	// �v���C���[�Ƃ̋������v�Z
	m_fDistSq = m_pCompTransform->GetWorldPosition().DistanceSq(vTargetPos);

	// �ǐՊJ�n�������߂Â�����ǐՊJ�n�@���@�ǐՌ��E������艓���ꍇ
	if (m_fDistSq < m_fChaseStartDist * m_fChaseStartDist
		&& m_fDistSq >= m_fLimitDistSq)
	{
		// �v���C���[�̍��W�Ɍ������Ĉړ�
		Vector3 vDir = vTargetPos - m_pCompTransform->GetWorldPosition();
		vDir.Normalize();	// ���K��
		vDir.y = 0.0f;		// �����͍l�����Ȃ�
		m_pCompRigidbody->SetVelocity(vDir * m_fMoveSpeed);

		// �ړ���̍��W������(�����͍l�����Ȃ�)
		Vector3<float> vLook = vTargetPos;
		vLook.y = m_pCompTransform->GetWorldPosition().y;
		m_pCompTransform->LookAt(vLook);
	}
	else
	{
		// �ړ���~
		m_pCompRigidbody->SetVelocity(Vector3<float>::Zero());
	}

}

/* ========================================
	�������C���X�V�֐�
	-------------------------------------
	���e�F�v���C���[�Ƃ̋������C����`��
========================================= */
void ComponentEnemyMoveChase::DrawPlayerDistLine()
{
	// �v���C���[�̍��W���擾
	Vector3<float> vTargetPos = m_pTargetObj->GetComponent<ComponentTransform>()->GetWorldPosition();

	// �������C���`��(�^�[�Q�b�g�̕����ցA�ǐՊJ�n�������̋���)
	Vector3<float> vStart = m_pCompTransform->GetWorldPosition();				// �����̈ʒu
	Vector3<float> vDir = vTargetPos - m_pCompTransform->GetWorldPosition();	// �v���C���[�̕���
	vDir.Normalize();															// ���K��
	Vector3<float> vEnd = vStart + (vDir * m_fChaseStartDist);					// �ǐՊJ�n�������̈ʒu

	// ������0.5f�ɌŒ�
	vStart.y = 0.5f;
	vEnd.y	 = 0.5f;

	m_pDistLine->UpdateLine(1, vStart, vEnd, ColorVec3::BLUE);
}

/* ========================================
	�Q�b�^�[(�ǐՊJ�n����)�֐�
	-------------------------------------
	�߂�l�Ffloat	�ǐՊJ�n����
=========================================== */
float ComponentEnemyMoveChase::GetChaseStartDist() const
{
	return m_fChaseStartDist;
}

/* ========================================
	�Q�b�^�[(�������C���\���t���O)�֐�
	-------------------------------------
	�߂�l�Fbool	�������C���\���t���O
=========================================== */
bool ComponentEnemyMoveChase::GetDispDistLine() const
{
	return m_bDispDistLine;
}

/* ========================================
	�Q�b�^�[(�ǐՌ��E����)�֐�
	-------------------------------------
	�߂�l�Ffloat	�ǐՌ��E����
=========================================== */
float ComponentEnemyMoveChase::GetLimitDistSq() const
{
	return m_fLimitDistSq;
}


/* ========================================
	�Z�b�^�[(�ǐՊJ�n����)�֐�
	-------------------------------------
	�����Ffloat	�ǐՊJ�n����
=========================================== */
void ComponentEnemyMoveChase::SetChaseStartDist(float fDist)
{
	m_fChaseStartDist = fDist;
}

/* ========================================
	�Z�b�^�[(�������C���\���t���O)�֐�
	-------------------------------------
	�����Fbool	�������C���\���t���O
=========================================== */
void ComponentEnemyMoveChase::SetDispDistLine(bool bDisp)
{
	m_bDispDistLine = bDisp;
}

/* ========================================
	�Z�b�^�[(�ǐՌ��E����)�֐�
	-------------------------------------
	�����Ffloat	�ǐՌ��E����
=========================================== */
void ComponentEnemyMoveChase::SetLimitDistSq(float fDist)
{
	m_fLimitDistSq = fDist;
}


#ifdef _DEBUG
/* ========================================
	�f�o�b�O�֐�
	-------------------------------------
	���e�F�f�o�b�O�p�̏���
	-------------------------------------
	����1�F�E�B���h�E	DebugUI::Window&
=========================================== */
void ComponentEnemyMoveChase::Debug(DebugUI::Window& window)
{
	using namespace DebugUI;

	Item* pEnemyMoveChaser = Item::CreateGroup("EnemyMoveChase");

	pEnemyMoveChaser->AddGroupItem(Item::CreateBind("MoveSpeed",			Item::Kind::Float, &m_fMoveSpeed));
	pEnemyMoveChaser->AddGroupItem(Item::CreateValue("TargetObj",			Item::Kind::Text));
	pEnemyMoveChaser->AddGroupItem(Item::CreateBind("DistanceSq",			Item::Kind::Float, &m_fDistSq));
	pEnemyMoveChaser->AddGroupItem(Item::CreateBind("ChaseStartDist",		Item::Kind::Float, &m_fChaseStartDist));
	pEnemyMoveChaser->AddGroupItem(Item::CreateValue("ChaseStartDistSqr",	Item::Kind::Text));

	window.AddItem(pEnemyMoveChaser);
}

#endif // _DEBUG