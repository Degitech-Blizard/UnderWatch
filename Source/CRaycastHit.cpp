#include "DXUT.h"
#include "CRaycastHit.h"


CRaycastHit::CRaycastHit()
{
	this->m_fDistance = 0.f;
	this->m_pCollider = nullptr;
	this->m_pHitObject = nullptr;
	this->m_vHitPoint = Vector3(0.f,0.f,0.f);
}


CRaycastHit::~CRaycastHit()
{
}
