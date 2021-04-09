#pragma once
inline int Round(float x)
{
	return int(x + 0.5);
}
const float PI = 3.14159265f;
inline float RToD(float r)
{
	return r * 180 / PI;
}

inline float DToR(float d)
{
	return d * PI / 180;
}

#define NUMMID(x, l, h) (x < l ? l : (x > h ? h : x))