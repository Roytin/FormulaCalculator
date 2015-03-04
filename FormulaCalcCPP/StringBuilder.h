#pragma once
#include "common.h"

class StringBuilder
{
private:
	char m_buffer[1024];
	int m_Cursor;
public:
	StringBuilder()
	{
		m_Cursor = 0;
		for(size_t i = 0; i != 1024; i++){
			m_buffer[i] = '\0';
		}
	}

	void Append(char c);
	void Clear();
	double ConvertToDouble();

public:
	int GetLength()
	{
		return m_Cursor;
	}

};
