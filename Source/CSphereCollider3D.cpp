#include "DXUT.h"
#include "CSphereCollider3D.h"


CSphereCollider3D::CSphereCollider3D()
{
}


CSphereCollider3D::~CSphereCollider3D()
{
}


void CSphereCollider3D::Awake()
{
	m_Type = Collider3D_Type::SPHERE;
}

void CSphereCollider3D::Start()
{
}

void CSphereCollider3D::Update()
{
	m_Sphere.Center = this->Transform->GetPosition();
}

void CSphereCollider3D::LateUpdate()
{
}

void CSphereCollider3D::OnDestroy()
{
}

void CSphereCollider3D::OnRender()
{
}

void CSphereCollider3D::OnEnable()
{
}

void CSphereCollider3D::OnDisable()
{
}


void CSphereCollider3D::OnCollisionEnter(CObject * _pObject)
{
}

void CSphereCollider3D::OnCollisionStay(CObject * _pObject)
{
}

void CSphereCollider3D::OnCollisionExit(CObject * _pObject)
{
}
