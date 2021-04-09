#pragma once
inline int Round(float x)
{
	return int(x + 0.5);
}

#define NUMMID(x, l, h) (x < l ? l : (x > h ? h : x))