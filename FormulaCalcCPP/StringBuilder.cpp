#include "StringBuilder.h"

void StringBuilder::Append(char c)
{
	m_buffer[m_Cursor] = c;
	m_Cursor++;
}

void StringBuilder::Clear()
{
	for(size_t i = 0; i!= m_Cursor; i++){
		m_buffer[i] = '\0';
	}
	m_Cursor = 0;
}

double StringBuilder::ConvertToDouble()
{
	double res = atof(m_buffer);
	this->Clear();
	return res;
}