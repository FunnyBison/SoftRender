#pragma once

class ZBuffer
{
public:
	ZBuffer();
	~ZBuffer();

	void Clean();

	bool Set(int i, int j, float z) {
		float *p = GetPointer(i, j);
		if (z < *p) {
			*p = z;
			return true;
		}
		else {
			return false;
		}
	}

private:
	float *GetPointer(int i, int j) { return m_z + (i * m_h + j); }

private:
	float  *m_z;
	float  *m_default;

	const int m_w;
	const int m_h;
};

