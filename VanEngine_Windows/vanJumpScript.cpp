#include "vanJumpScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
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

#define VELOCITY_X	3.f
#define ERRPRVALUE  0.05f
#define FORCE_X     1.5f
#define FORCE_Y     3.5f	

namespace van
{
	JumpScript::JumpScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.0f, 0.0f, 1.0f, 0.0f))
	{
	}

	JumpScript::~JumpScript()
	{
	}

	void JumpScript::Initialize()
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mFloorTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"TriangleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");



	}

	void JumpScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		


		if (owner->GetCollisionEnter())
		{
			// Floor ��ü�� �浹�� ��ü�� Playe �� ���
			if (player != nullptr)
			{

				player->SetCollisionCheck(true);
				Rigidbody* rb = player->GetComponent<Rigidbody>();

				
				
				Vector3 playerSize = mPlayerCollider->GetSize();              // Player�� �ݶ��̴��� ������
				Vector3 playerPos = mPlayerCollider->GetPosition();           // Player�� �ݶ��̴��� ��ġ

				
				Vector3 floorSize = mFloorCollider->GetSize();                // Floor �� �ݶ��̴��� ������
				Vector3 floorPos = mFloorCollider->GetPosition();             // Floor �� �ݶ��̴��� ��ġ

				// Player�� Floor �� ��ġ�� �� - ���� �浹
				bool collisionFlagX = (playerPos.y - playerSize.y / 2) >= (floorPos.y + floorSize.y / 2) - ERRPRVALUE;
				// Player�� Floor �� ��ġ�� �� - ���� �浹
				bool collisionFlagY = false;

				// Y�� �浹(������ = 0.05)
				if (collisionFlagX)
				{
					Vector3 temp = Vector3(rb->GetVelocity().x, 0.0f, rb->GetVelocity().z);
					rb->SetVelocity(temp + Vector3(0.0f, FORCE_Y, 0.0f));
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
							Vector3 temp = Vector3(0.0f, rb->GetVelocity().y, rb->GetVelocity().z);
							rb->SetVelocity(temp + Vector3(FORCE_X, 0.0f, 0.0f));
						}
					}
					// Player �� Floor ���� ���ʿ� ���� �� (Left)
					else
					{
						collisionFlagY = (floorPos.x - floorSize.x / 2) < (playerPos.x + playerSize.x / 2);
						if (collisionFlagY)
						{
							Vector3 temp = Vector3(0.0f, rb->GetVelocity().y, rb->GetVelocity().z);
							rb->SetVelocity(temp + Vector3(-FORCE_X, 0.0f, 0.0f));
						}
					}
				}
			}

		}
	}

	void JumpScript::LateUpdate()
	{
	}

	void JumpScript::Render()
	{

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mFloorTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);



		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}
}