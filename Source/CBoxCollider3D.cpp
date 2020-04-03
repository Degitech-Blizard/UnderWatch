#include "DXUT.h"
#include "CBoxCollider3D.h"


CBoxCollider3D::CBoxCollider3D()
{
}


CBoxCollider3D::~CBoxCollider3D()
{
}

void CBoxCollider3D::Awake()
{
	this->m_Type = Collider3D_Type::OBB;
	this->m_Offset = Vector3(0, 0, 0);
}

void CBoxCollider3D::Start()
{
}

void CBoxCollider3D::Update()
{
	m_Box.Center = this->Transform->GetPosition() + m_Offset;
}

void CBoxCollider3D::LateUpdate()
{
}

void CBoxCollider3D::OnDestroy()
{
}

void CBoxCollider3D::OnRender()
{
}

void CBoxCollider3D::OnEnable()
{
}

void CBoxCollider3D::OnDisable()
{
}

void CBoxCollider3D::OnCollisionEnter(CObject * _pObject)
{
}

void CBoxCollider3D::OnCollisionStay(CObject * _pObject)
{
}

void CBoxCollider3D::OnCollisionExit(CObject * _pObject)
{
}
