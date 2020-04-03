#pragma once
class CCircle
{
public:
	CCircle();
	CCircle(Vector2 _Center, float _Radius);
	~CCircle();

public:
	Vector2 Center;
	float Radius;

	bool IntersectPoint(Vector2 _Point);
	bool IntersectRect(CRect _Rect);
	bool IntersectCircle(CCircle _Circle);
};

