#include "DXUT.h"
#include "CRigidBody3D.h"

#define GRAVITY 9.8f

CRigidBody3D::CRigidBody3D()
{
}


CRigidBody3D::~CRigidBody3D()
{
}


void CRigidBody3D::Awake()
{
		this->m_vVelocity = Vector3(0.f, 0.f,0.f);
		this->m_bIsKinematic = false;
		this->m_fGravityScale = 1.f;
		this->m_fMass = 1.f;
}

void CRigidBody3D::Start()
{
}

void CRigidBody3D::Update()
{

	if (m_bMove == true)
	{
		if (m_bIsKinematic == FALSE)
		{
			m_vVelocity.y -= 7000 * m_fMass * m_fGravityScale * DeltaTime;

			m_vVelocity.y *= 0.99f;
			m_vVelocity.x *= 0.96f;
			m_vVelocity.z *= 0.96f;
		}
		this->Transform->Translation(m_vVelocity * DeltaTime);
	}
	if (this->Transform->GetPosition().y < 32)
	{
		m_bIsKinematic = true;
		m_vVelocity = Vector3(0, 0, 0);
	}
}

void CRigidBody3D::LateUpdate()
{
}

void CRigidBody3D::OnDestroy()
{
}

void CRigidBody3D::OnRender()
{
}

void CRigidBody3D::OnEnable()
{
}

void CRigidBody3D::OnDisable()
{
}


void CRigidBody3D::OnCollisionEnter(CObject * _pObject)
{

}

void CRigidBody3D::OnCollisionStay(CObject * _pObject)
{

}

void CRigidBody3D::OnCollisionExit(CObject * _pObject)
{
	m_bIsKinematic = false;

}
