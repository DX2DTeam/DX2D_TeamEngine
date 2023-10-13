#include "vanDisappearScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanTime.h"
#include "vanInput.h"

#include "vanCollider.h"
#include "vanRigidbody.h"
#include "vanMeshRenderer.h"
#include "vanResourceManager.h"
#include "vanConstantBuffer.h"
#include "vanRenderer.h"
#include "vanSceneManager.h"
#include "vanPlayer.h"
#include "vanFloor.h"

#define ERRPRVALUE  0.05f
#define FORCE_X     1.5f
#define FORCE_Y     2.5f

van::DisappearScript::DisappearScript()
{

}

van::DisappearScript::~DisappearScript()
{

}

void van::DisappearScript::Initialize()
{
	mFloorTransform = GetOwner()->GetComponent<Transform>();
	mFloorCollider = GetOwner()->GetComponent<Collider>();
	mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

	mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
	mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
	mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

	//mSize = mFloorTransform->GetScale();
	//mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
	//mMesh = ResourceManager::Find<Mesh>(L"RectangleMesh");
	//mShader = ResourceManager::Find<Shader>(L"FloorShader");
}

void van::DisappearScript::Update()
{
	Floor* owner = dynamic_cast<Floor*>(GetOwner());

	if (owner->GetCollisionEnter())
	{
		SceneManager::GetPlayer()->SetCollisionCheck(true);

		Vector3 playerSize = mPlayerCollider->GetSize();		// Player�� �ݶ��̴��� ������
		Vector3 playerPos = mPlayerCollider->GetPosition();		// Player�� �ݶ��̴��� ��ġ

		Collider* colFloor = owner->GetComponent<Collider>();	// Floor �� �ݶ��̴�
		Vector3 floorSize = colFloor->GetSize();				// Floor �� �ݶ��̴��� ������
		Vector3 floorPos = colFloor->GetPosition();				// Floor �� �ݶ��̴��� ��ġ

		// Player�� Floor �� ��ġ�� �� - ���� �浹
		bool collisionFlagX = (playerPos.y - playerSize.y / 2) >= (floorPos.y + floorSize.y / 2) - ERRPRVALUE;
		// Player�� Floor �� ��ġ�� �� - ���� �浹
		bool collisionFlagY = false;

		// Y�� �浹(������ = 0.05)
		if (collisionFlagX)
		{
			Vector3 temp = Vector3(mPlayerRigidbody->GetVelocity().x, 0.0f, mPlayerRigidbody->GetVelocity().z);
			mPlayerRigidbody->SetVelocity(temp + Vector3(0.0f, FORCE_Y, 0.0f));

			// ������ ��ġ�� ��ġ�� �ű����ν� ȭ�鿡�� �������ó�� ���̵��� ��
			mFloorTransform->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		}
		// X�� �浹
		else
		{
			// Player �� Floor ���� �����ʿ� ���� �� (Right)
			if (playerPos.x > floorPos.x)
			{
				collisionFlagY = (floorPos.x + floorSize.x / 2) > (playerPos.x - playerSize.x / 2);
				if (collisionFlagY)
				{
					Vector3 temp = Vector3(0.0f, mPlayerRigidbody->GetVelocity().y, mPlayerRigidbody->GetVelocity().z);
					mPlayerRigidbody->SetVelocity(temp + Vector3(FORCE_X, 0.0f, 0.0f));
				}
			}
			// Player �� Floor ���� ���ʿ� ���� �� (Left)
			else
			{
				collisionFlagY = (floorPos.x - floorSize.x / 2) < (playerPos.x + playerSize.x / 2);
				if (collisionFlagY)
				{
					Vector3 temp = Vector3(0.0f, mPlayerRigidbody->GetVelocity().y, mPlayerRigidbody->GetVelocity().z);
					mPlayerRigidbody->SetVelocity(temp + Vector3(-FORCE_X, 0.0f, 0.0f));
				}
			}
		}
	}
}

void van::DisappearScript::LateUpdate()
{

}

void van::DisappearScript::Render()
{

}
