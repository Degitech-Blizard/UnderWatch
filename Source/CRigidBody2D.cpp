#include "DXUT.h"
#include "CRigidBody2D.h"

#define GRAVITY 9.8f

void CRigidBody2D::Awake()
{
	this->m_vVelocity = Vector2(0.f, 0.f);
	this->m_bIsKinematic = false;
	this->m_fGravityScale = 1.f;
	this->m_fMass = 1.f;
}

void CRigidBody2D::Start()
{
}

void CRigidBody2D::Update()
{
	if (m_bMove == true)
	{
		if (m_bIsKinematic == FALSE)
		{
			m_vVelocity.y += 4800 * m_fMass * m_fGravityScale * DeltaTime;
			
			m_vVelocity.y *= 0.98f;
			m_vVelocity.x *= 0.95f;
		}
		this->Transform->Translation(m_vVelocity * DeltaTime);
	}
}

void CRigidBody2D::LateUpdate()
{
}

void CRigidBody2D::OnDestroy()
{
}

void CRigidBody2D::OnRender()
{
}

void CRigidBody2D::OnEnable()
{
}

void CRigidBody2D::OnDisable()
{
}

void CRigidBody2D::OnCollisionEnter(CObject * _pObject)
{
	/*this->m_pObject->Transform->Translation(-m_vVelocity * DeltaTime);
	m_bMove = false;*/
}

void CRigidBody2D::OnCollisionStay(CObject * _pObject)
{
	//m_bMove = false;
}

void CRigidBody2D::OnCollisionExit(CObject * _pObject)
{
	//m_bMove = true;
}

CRigidBody2D::CRigidBody2D()

{
}


CRigidBody2D::~CRigidBody2D()
{
}
