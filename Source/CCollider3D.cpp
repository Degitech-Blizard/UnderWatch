#include "DXUT.h"
#include "CCollider3D.h"


CCollider3D::CCollider3D()
{
	OBJECT.RegisterCollider3D(this);
}


CCollider3D::~CCollider3D()
{
	OBJECT.UnRegisterCollider3D(this);
}
