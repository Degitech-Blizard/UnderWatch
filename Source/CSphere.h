#pragma once
class CSphere 
{
public:
	CSphere();
	CSphere(Vector3 _Center, float _Radius);
	~CSphere();

public:
	Vector3 Center;
	float	Radius; 
};

