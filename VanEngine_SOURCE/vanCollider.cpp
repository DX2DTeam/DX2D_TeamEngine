#include "vanCollider.h"

namespace van
{
	Collider::Collider()
		: Component(COMPONENTTYPE::COLLIDER)
		, mSize(math::Vector2::Zero)			// �浹ü �⺻ũ�� 0
		, mOffset(math::Vector2::Zero)			// ��ü�� �������κ��� �浹ü�� ��ġ������
		, mPos(math::Vector2::Zero)				// �浹ü�� �߽���ǥ : (0,0)
		, mCollisionNum(-1)						// �̸� �⺻�� : -1
		, mbIsCollision(false)					// �浹���� �⺻�� : ���浹����
		, lineColor(RGB(50, 255, 50))			// ���� �ʷϻ�
		, collisionLineColor(RGB(255, 50, 50))	// ������
		, inActiveLineColor(RGB(128, 128, 128))	// ȸ��
		, mbActive(true)
		, mbAffectedCamera(true)
	{
		SetName(L"Collider class");
		// �浹ü Numbering : 0 ~ ...
		mCollisionNum = mCollisionCount;	// �浹ü�� �����Ǹ� ���° �浹ü���� �̸��� �ް�
		++mCollisionCount;					// ��ü �浹ü�� ������ �ϳ� �÷��ش�.
	}

	Collider::~Collider()
	{
		// nothing
	}

	void Collider::Initialize()
	{
		// nothing
	}

	void Collider::Update()
	{
	}

	void Collider::Render()
	{
	}

	void Collider::OnCollisionEnter(Collider* _other)
	{
	}

	void Collider::OnCollisionStay(Collider* _other)
	{
	}

	void Collider::OnCollisionExit(Collider* _other)
	{
	}
}