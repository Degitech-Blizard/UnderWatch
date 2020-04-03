#pragma once
class CBox 
{
public:
	CBox();

	CBox(Vector3 _vCenter, Vector3 _vRadius);
	~CBox();

public:
	Vector3 Center;
	Vector3 Rotation;
	Vector3 Radius;


public:
	Vector3 GetMin()
	{
		Vector3 Min = Vector3(
			Center.x - Radius.x/2.f,
			Center.y - Radius.y/2.f,
			Center.y - Radius.z/2.f
		);

		//Matrix matRot, matRotX, matRotY, matRotZ;
		//D3DXMatrixRotationX(&matRotX, D3DXToRadian(Rotation.x));
		//D3DXMatrixRotationY(&matRotY, D3DXToRadian(Rotation.y));
		//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(Rotation.z));

		//matRot = matRotX * matRotY * matRotZ;

		//D3DXVec3TransformCoord(&Min, &Min, &matRot);
		return Min;

	}

	Vector3 GetMax()
	{
		Vector3 Max = Vector3(
			Center.x + Radius.x /2.f,
			Center.y + Radius.y /2.f,
			Center.y + Radius.z /2.f
		);

		//Matrix matRot, matRotX, matRotY, matRotZ;
		//D3DXMatrixRotationX(&matRotX, D3DXToRadian(Rotation.x));
		//D3DXMatrixRotationY(&matRotY, D3DXToRadian(Rotation.y));
		//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(Rotation.z));

		//matRot = matRotX * matRotY * matRotZ;
		//D3DXVec3TransformCoord(&Max, &Max, &matRot);

		return Max;
	}
	Vector3 GetAxisX()
	{
		Vector3 Right = Vector3(1, 0, 0);
		Matrix matRot, matRotX,matRotY,matRotZ;
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(Rotation.x));
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(Rotation.y));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(Rotation.z));

		matRot = matRotX * matRotY * matRotZ;
		D3DXVec3TransformNormal(&Right, &Right, &matRot);

		return Right;
	}
	Vector3 GetAxisY() 
	{
		Vector3 UP =  Vector3(0, 1, 0);
		Matrix matRot, matRotX, matRotY, matRotZ;
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(Rotation.x));
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(Rotation.y));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(Rotation.z));

		matRot = matRotX * matRotY * matRotZ;
		D3DXVec3TransformNormal(&UP, &UP, &matRot);

		return UP;
	}
	Vector3 GetAxisZ() 
	{
		Vector3 Forward = Vector3(0, 0, 1);
		Matrix matRot, matRotX, matRotY, matRotZ;
		D3DXMatrixRotationX(&matRotX, D3DXToRadian(Rotation.x));
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(Rotation.y));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(Rotation.z));

		matRot = matRotX * matRotY * matRotZ;
		D3DXVec3TransformNormal(&Forward, &Forward, &matRot);

		return Forward;
	}

	//Vector3 GetMin() { return Center + LocalMin; }
	//Vector3 GetMax() { return Center + LocalMax; }
};

