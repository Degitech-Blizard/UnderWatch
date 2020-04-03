#pragma once
class CObject;
class CCollider3D;
class CRaycastHit
{
	friend class CPhysic;

public:
	CRaycastHit();
	~CRaycastHit();

private:
	Vector3 m_vHitPoint;
	float m_fDistance;
	CObject * m_pHitObject ;
	CCollider3D * m_pCollider;
 
public:
	Vector3 GetHitPoint() { return m_vHitPoint; }
	float GetDistance() { return m_fDistance; }
	CObject * GetHitObject() { return m_pHitObject; }
	CCollider3D * GetCollider() { return m_pCollider; }
};

