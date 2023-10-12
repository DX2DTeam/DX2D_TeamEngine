#include "vanStraightScript.h"
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

#include "..\\VanEngine_SOURCE\\vanPlayer.h"
#include "..\\VanEngine_SOURCE\\vanFloor.h"

#define VELOCITY_X	3.f

namespace van
{
	StraightScript::StraightScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f)),
		mDir(StraightDir::None),
		isSetDir(false),
		mbStraight(false)
	{
	}

	StraightScript::~StraightScript()
	{
	}

	void StraightScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();

		mSize = mTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mColor = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

		
	}

	void StraightScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());
	
		if (player->IsCollisionCheck() && mbStraight)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			mbStraight = false;
			rb->SetStraight(false);
		}


		if (owner->GetCollisionEnter())
		{
			Transform* tr = player->GetComponent<Transform>();
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			switch (mDir)
			{
			case van::enums::StraightDir::Left:
				tr->SetPosition(Vector3(mTransform->GetPosition().x - 0.07f, mTransform->GetPosition().y, 0.0f));
				rb->SetVelocity(Vector3(0.f));
				rb->SetStraight(true);
				mbStraight = true;
				break;
			case van::enums::StraightDir::Right:
				tr->SetPosition(Vector3(mTransform->GetPosition().x + 0.07f, mTransform->GetPosition().y, 0.0f));
				rb->SetVelocity(Vector3(0.f));
				rb->SetStraight(true);
				mbStraight = true;
				break;
			case van::enums::StraightDir::None:
				break;
			default:
				break;
			}
		}
	

		if (mbStraight)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			switch (mDir)
			{
			case van::enums::StraightDir::Left:
				rb->AddVelocity(Vector3(-3.0f, 0.f, 0.f));
				break;
			case van::enums::StraightDir::Right:
				rb->AddVelocity(Vector3(3.0f, 0.f, 0.f));
				break;
			case van::enums::StraightDir::None:
				break;
			default:
				break;
			}
		}


		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::LEFT) == KEY_STATE::DOWN)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			rb->SetStraight(false); 
			mbStraight = false;
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::RIGHT) == KEY_STATE::DOWN)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			rb->SetStraight(false);
			mbStraight = false;
		}

		// 231010 
		// straight ��ũ��Ʈ 
		// ������ �ʹ������� �ȵ��.
		// 
		// ���� ¥�� ������ ���ǹ� ���� RigidBody�� ���� ���� ���� �������ִ°��ε�
		// �̷��� ¥���ִ� ������ straight��ũ��Ʈ�� ��������� ���������� update���� RigidBody�� ������ָ�
		// �浹�������� straight floor�� rigid body���� �����Ͽ� �̻��ϰ� �̵���Ű�⶧���̴�.
		// 
		// �̷� ������ ������ ���������� 
		// 1. Ŭ������ ��� �浹�̺�Ʈ�� ���ÿ� �浹�̺�Ʈ�� �ϸ� �޾ƿ� �浹ü�� ������ �־����� 
		// ��ũ��Ʈ�� �浹�̺�Ʈ�� �ƴ� update���� �� �� �ۿ� ������ �̷���
		// 
		// 2. Movement�� control�� �и��������� -> �̵��� �Է��� �������־� �̵�& �Է� ���� �۾��� �Ҷ� �����ϴ�.
		// 
		// 
		// 
			

		if (isSetDir == false)
		{
			if (mDir == StraightDir::Left)
			{
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
			}
			else if (mDir == StraightDir::Right)
			{
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshR");
			}

			isSetDir = true;
		}

	}

	void StraightScript::LateUpdate()
	{
	}

	void StraightScript::Render()
	{

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);



		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}
	void StraightScript::Straight()
	{
		
	}
}