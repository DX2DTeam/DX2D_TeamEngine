#include "vanPortalInScript.h"
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
#include "vanPortalOutScript.h"

#define VELOCITY_X	3.f

namespace van
{
	PortalInScript::PortalInScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mOutPortalPos(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f)),
		mbCreateOutPortal(true)
	{
	}

	PortalInScript::~PortalInScript()
	{
	}

	void PortalInScript::Initialize()
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mFloorTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

		mFloorCollider->SetVisible(false);
	}

	void PortalInScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		if (mbCreateOutPortal)
		{
			mbCreateOutPortal = false;
			Floor* Outfloor = new Floor();										// �ƿ���Ż ��ũ��Ʈ ��뿡 �ʿ��� �⺻�ٴڻ���
			mPotalOutTransform = Outfloor->GetComponent<Transform>();
			Outfloor->GetComponent<Collider>()->SetVisible(false);
			mPotalOutTransform->SetPosition(owner->GetComponent<Transform>()->GetPosition());	// Out/In floor ��ġ��ġ

			if (mOutPortalPos == Vector3::Zero)					// OutPortal ��ġ ������
			{
				mOutPortalPos = mPotalOutTransform->GetPosition();
				mOutPortalPos += Vector3(-0.25f, 0.f, 0.0f);	// OutPortal �⺻��ġ
				mPotalOutTransform->SetPosition(mOutPortalPos);					// ���ο� out��ġ�� floor/script ��ġ ����
			}
			else // OutPortal ��ġ ����
			{
				mPotalOutTransform->SetPosition(mOutPortalPos);
			}
			PortalOutScript* outPortalScript = Outfloor->AddComponent<PortalOutScript>();
			SceneManager::GetActiveScene()->AddGameObject(Outfloor, LAYER::NONECOLLISION);
		}

		if (owner->GetCollisionEnter())
		{
			owner->SetCollisionEnter(false);
			player->GetComponent<Transform>()->SetPosition(mOutPortalPos);
			player->SetCollisionCheck(false);
		}
	}

	void PortalInScript::LateUpdate()
	{
	}

	void PortalInScript::Render()
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