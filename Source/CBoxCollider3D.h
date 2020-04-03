#pragma once
#include "CCollider3D.h"
class CBoxCollider3D :
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
	CBoxCollider3D();
	~CBoxCollider3D();

private:
	Box m_Box;
	Vector3 m_LocalMin;
	Vector3 m_LocalMax;
			
	Vector3 m_Center;
	Vector3 m_Offset;

public:
	Vector3 GetOffset() { return m_Offset; }
	void SetOffset(Vector3 _vOffset) { m_Offset = _vOffset; }

	void SetBox(CRBox _Box) { m_Box = _Box; }
	Box GetBox() { return m_Box; }
	Vector3 GetLoaclMin() { return m_LocalMin; }
	Vector3 GetLoaclMax() { return m_LocalMax; }
	Vector3 GetMin() { return m_Center + m_LocalMin; }
	Vector3 GetMax() { return m_Center + m_LocalMax; }

};

