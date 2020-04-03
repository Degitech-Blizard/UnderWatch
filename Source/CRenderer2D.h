#pragma once
class   CRenderer2D abstract :
	public CComponent 
{
public:
	CRenderer2D();
	virtual ~CRenderer2D();

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
	SortingLayer m_SortingLayer = SortingLayer::Default;
	int m_iOrderInLayer = 0;
	RenderMode m_Type;

public:
	RenderMode GetRenderMode() { return m_Type; }
	void SetRenderMode(RenderMode _Type) { m_Type = _Type; }
	int GetOrderInLayer() { return m_iOrderInLayer; }
	void SetOrderInLayer(int _OrderInLayer) { m_iOrderInLayer = _OrderInLayer; }
};

