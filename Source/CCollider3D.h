#pragma once
#include "CComponent.h"

enum class Collider3D_Type {OBB, SPHERE};
class CCollider3D :
	public CComponent
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Awake()								PURE;
	virtual void Start()								PURE;
	virtual void Update()								PURE;
	virtual void LateUpdate()							PURE;
	virtual void OnDestroy()							PURE;
	virtual void OnRender()								PURE;
	virtual void OnEnable()								PURE;
	virtual void OnDisable()							PURE;
	virtual void OnCollisionEnter(CObject * _pObject)	PURE;
	virtual void OnCollisionStay(CObject * _pObject)	PURE;
	virtual void OnCollisionExit(CObject * _pObject)	PURE;
public:
	CCollider3D();
	virtual ~CCollider3D();
	Collider3D_Type GetColliderType() { return m_Type; }
protected: 
	Collider3D_Type m_Type;
	set < CCollider3D *> m_listCollision;
};

