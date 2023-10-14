#pragma once
#include "vanScript.h"

namespace van
{
	class Transform;
	class Collider;
	class Rigidbody;
	class Floor;

	using namespace math;

	class MoveFloorScript : public Script
	{
	public:
		MoveFloorScript();
		virtual ~MoveFloorScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetmMovingTime(float time) { mMovingTime = time; }		// �ִ� �̵� �ð�
		void SetDir(bool value) { mbGoLeft = value; }				// ���� ���⼼�� (�⺻ ������)

	private:
		Transform* mFloorTransform;
		Collider* mFloorCollider;
		Rigidbody* mFloorRigidbody;

		Transform* mPlayerTransform;
		Collider* mPlayerCollider;
		Rigidbody* mPlayerRigidbody;

		Floor* mLeftfloor;
		Floor* mRightfloor;

		Vector3 mOwnerPos;
		Vector3 mLeftFloorPos;
		Vector3 mRightFloorPos;
		
		float mTime;
		float mMovingTime;
		bool mbGoLeft;
		
	};
}