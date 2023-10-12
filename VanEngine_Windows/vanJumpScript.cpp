#include "vanJumpScript.h"
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

#define VELOCITY_X	3.f

namespace van
{
	JumpScript::JumpScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f))
	{
	}

	JumpScript::~JumpScript()
	{
	}

	void JumpScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();

		mSize = mTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"TriangleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

	}

	void JumpScript::Update()
	{
	}

	void JumpScript::LateUpdate()
	{
	}

	void JumpScript::Render()
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
}