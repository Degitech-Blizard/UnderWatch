#pragma once
class CFrustum
{
public:
	CFrustum();
	~CFrustum();

	Vector3 m_vtx[8]; /// ���������� ������ ���� 8��
	Vector3 m_vPos; /// ���� ī�޶��� ������ǥ
	D3DXPLANE m_plane[6]; /// ���������� �����ϴ� 6���� ���

public:


	/// ī�޶�(view) * ��������(projection)����� �Է¹޾� 6���� ����� �����.
	BOOL Make(Matrix* _matProj, Matrix * _matView);



	/// ���� v�� �������Ҿȿ� ������ TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
	BOOL IsIn(D3DXVECTOR3* pv);
	/** �߽�(v)�� ������(radius)�� ���� ��豸(bounding sphere)�� �������Ҿȿ� ������
	* TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.*/
	BOOL IsInSphere(D3DXVECTOR3* pv, float radius);



	/// ���� ī�޶��� ������ǥ�� ����ش�.
	D3DXVECTOR3* GetPos() { return &m_vPos; }



};

