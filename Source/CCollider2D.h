#pragma once
#include "CComponent.h"
enum class Collider2D_Type { OBB, CIRCLE };

class CCollider2D :
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
	CCollider2D();
	virtual  ~CCollider2D();


public:
	Collider2D_Type m_Type;
	set< CObject *> m_listCollision;
};

