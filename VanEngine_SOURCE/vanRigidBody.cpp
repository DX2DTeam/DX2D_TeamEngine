#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanTime.h"

namespace van
{
	RigidBody::RigidBody()
		: Component(COMPONENTTYPE::RIGIDBODY)
		, mMass(1.0f)
		, mFriction(15.0f)
		, mForce(math::Vector2::Zero)
		, mAccelation(math::Vector2::Zero)
		, mVelocity(math::Vector2::Zero)
		, mGravity(math::Vector2(0.0f, 0.0f))	// �� ��������� �Ѵ�.
		, mLimitedVelocity(math::Vector2(0.0f, 0.0f))	// �� ���� ����� �Ѵ�.
		, mbGround(false)
	{
		SetName(L"RigidBody class");
	}

	RigidBody::~RigidBody()
	{
		// nothing
	}

	void RigidBody::Initialize()
	{
		// nothing
	}

	void RigidBody::Update()
	{
		mAccelation = mForce / mMass;	// F = m * a -> a = F / m
		mVelocity += mAccelation * Time::DeltaTime();	// v1 = v0 + at

		if (mbGround)					// y�� �� �ۿ� x
		{
			math::Vector2 gravity = mGravity;			// �߷� �ʱⰪ -> x = 0, y = 980
			gravity.Normalize();						// �߷� -> x = 0, y = 1
			float dot = mVelocity.Dot(gravity);			
			math::Vector2 vel = gravity * dot;
			mVelocity -= vel;							
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �ִ� �ӵ� ����
		math::Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;
		math::Vector2 sideVelocity = mVelocity - gravity;

		if (mLimitedVelocity.y < gravity.Length())			// y���� �ӵ��� y���� ���Ѽӵ����� Ŭ��
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())		// x���� �ӵ��� x���� ���Ѽӵ����� Ŭ��
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// ������
		bool noSpeed = (mVelocity == math::Vector2::Zero);
		if (!noSpeed)	// �ӵ� 0�� �ƴ� ���
		{
			math::Vector2 friction = -mVelocity;	// �ӵ��� �ݴ� �������� ������ �ۿ�
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();	// ������ = ������ ��� * ����

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.Length() < friction.Length())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = math::Vector2(0.0f, 0.0f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				// �������� �ӵ��� �ݴ�����̱⿡ '+' �Ѵ�.
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();	// �ش� �κ� ������ GameObject �� �����ڿ��� Transform �߰�����
		math::Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();	// Vector3 + Vector2 * float �ε� �������� ���� ��ȯ���� �𸣰ڴ�.
		tr->SetPosition(pos);
		//mForce.Clear();	// �̰� �� ���ִ°���? �������� ���� �� ����?
	}

	void RigidBody::Render()
	{
		// nothing
	}
}