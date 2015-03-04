#pragma once
#include "common.h"
#include "Operators.h"

class Node
{
private:
	double m_value;
public:
	Node* m_pFather;
	Node* m_pLeftChild;
	Node* m_pRightChild;

	BaseOperator* m_pOperator;

	Node(BaseOperator* op)
	{
		m_value = 0;
		m_pOperator = op;
		m_pFather = NULL;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
	}

	Node(double value)
	{
		m_value = value;
		m_pFather = NULL;
		m_pLeftChild = NULL;
		m_pRightChild = NULL;
		m_pOperator = NULL;
	}

	~Node()
	{
		//if(m_pOperator != NULL)
		//	delete m_pOperator;
		//if(m_pLeftChild != NULL)
		//	delete m_pLeftChild;
		//if(m_pRightChild != NULL)
		//	delete m_pRightChild;
		//if(m_pFather != NULL)
		//	delete m_pFather;
	}

	double GetValue()
	{
		if (m_pOperator == NULL)
		{
			return m_value;
		}
		else
		{
			return m_pOperator->Compute(m_pLeftChild->GetValue(), m_pRightChild->GetValue());
		}
	}
};
