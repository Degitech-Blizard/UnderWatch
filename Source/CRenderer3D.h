#pragma once
#include "CComponent.h"
class CRenderer3D abstract :
	public CComponent 
{
public:
	CRenderer3D();
	virtual ~CRenderer3D();

	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Awake()								PURE;
	virtual void Start()								PURE;
	virtual void Update()								PURE;
	virtual void LateUpdate()							PURE;
	virtual void Render()								PURE;
	virtual void OnRender()								PURE;
	virtual void OnDestroy()							PURE;
	virtual void OnEnable()								PURE;
	virtual void OnDisable()							PURE;
	virtual void OnCollisionEnter(CObject * _pObject)	PURE;
	virtual void OnCollisionStay(CObject * _pObject)	PURE;
	virtual void OnCollisionExit(CObject * _pObject)	PURE;
protected:
	std::function<void()> OnRenderFunc;
public:
	void SetOnRenderFunction(function<void()> _Func) { OnRenderFunc = _Func; }

};

