#pragma once
class CRay
{
	friend class CCameraManager;
	friend class CPhysic;
public:
	CRay();
	~CRay();
	Vector3 m_vPos;
	Vector3 m_vDir;
	float m_fMaxDistance = -1.f;

private:

	void TransformRay();
};





