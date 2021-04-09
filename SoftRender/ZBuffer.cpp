#include "ZBuffer.h"
#include <float.h>
#include <string.h>

ZBuffer::ZBuffer()
	:m_w(1000), m_h(1000)
{
	m_z = new float[m_w * m_h];
	m_default = new float[m_w * m_h];

	for (int i = 0; i < m_w * m_h; i++) {
		m_default[i] = FLT_MAX;
	}
}


ZBuffer::~ZBuffer()
{
	delete []m_z;
	delete []m_default;
}

void ZBuffer::Clean()
{
	memcpy(m_z, m_default, sizeof(float) * m_w * m_h);
}
