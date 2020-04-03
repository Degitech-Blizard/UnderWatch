#pragma once
#include "CCollider3D.h"


class CSphereCollider3D :
	public CCollider3D
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Awake()								override;
	virtual void Start()								override;
	virtual void Update()								override;
	virtual void LateUpdate()							override;
	virtual void OnDestroy()							override;
	virtual void OnRender()								override;
	virtual void OnEnable()								override;
	virtual void OnDisable()							override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;

public:
	CSphereCollider3D();
	~CSphereCollider3D();

private:
	Sphere m_Sphere;
public:
	void SetSphere(CRSphere _Sphere) { m_Sphere = _Sphere; }
	Sphere GetSphere() { return m_Sphere; }
};

