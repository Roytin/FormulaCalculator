#pragma once
#include "Node.h"
#include "Operators.h"
#include "StringBuilder.h"

class FormulaTree
{
public:
	Node* Root;

	FormulaTree()
	{
		Root = new Node(0.0);
	}

	bool BuildTree(const char* formula)
	{
		int index = 0;
		Root = Parse(formula, index);
		if(Root != NULL)
			return true;
		else
			return false;
	}

	//遇到括号开启新栈的,遇到后括号退出堆栈, 遇到优先级上升进堆栈
private:
	Node* Parse(const char* source, int& index, Node* left = NULL, BaseOperator* op = NULL)
	{
		int initPriority = -1;
		Node* rootNode = NULL;
		if (left != NULL && op != NULL)
		{
			rootNode = new Node(op);
			rootNode->m_pLeftChild = left;
			initPriority = 1;
			index++;
		}

		StringBuilder buffer;
		for (; *(source+index) != '\0'; index++)
		{
			char c = source[index];
			switch (c)
			{
			case ' ':
			case '　':
			case '\t':
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				buffer.Append(c);
				break;
			case '＋':
			case '+':
				//判断是否有出栈的必要
				if (initPriority != -1 && initPriority > 0)
				{
					if (buffer.GetLength() != 0 && rootNode != NULL)
					{
						Node* valueNode = new Node(buffer.ConvertToDouble());
						buffer.Clear();
						rootNode->m_pRightChild = valueNode;
					}
					index--;
					return rootNode;
				}

				if (buffer.GetLength() != 0)
				{
					Node* valueNode = new Node(buffer.ConvertToDouble());
					buffer.Clear();
					Node* opNode = new Node(new Plus());
					if (rootNode == NULL)
					{
						initPriority = 0;//初始化优先级为0
						rootNode = opNode;
						rootNode->m_pLeftChild = valueNode;
					}
					else
					{
						opNode->m_pLeftChild = rootNode;
						rootNode->m_pRightChild = valueNode;
						rootNode->m_pFather = opNode;
						rootNode = opNode;
					}
				}
				else
				{
					if (rootNode == NULL)//以+号开头的行
					{
						initPriority = 0;//初始化优先级为0
						rootNode = new Node(new Plus());
						rootNode->m_pLeftChild = new Node(0.0);
					}
					else
					{
						Node* opNode = new Node(new Plus());
						rootNode->m_pFather = opNode;
						opNode->m_pLeftChild = rootNode;
						rootNode = opNode;
					}
				}
				break;
			case '－':
			case '-':
				//判断是否有出栈的必要
				if (initPriority != -1 && initPriority > 0)
				{
					if (buffer.GetLength() != 0 && rootNode != NULL)
					{
						Node* valueNode = new Node(buffer.ConvertToDouble());
						buffer.Clear();
						rootNode->m_pRightChild = valueNode;
					}
					index--;
					return rootNode;
				}

				if (buffer.GetLength() != 0)
				{
					Node* valueNode = new Node(buffer.ConvertToDouble());
					buffer.Clear();
					Node* opNode = new Node(new Minus());
					if (rootNode == NULL)
					{
						initPriority = 0;//初始化优先级为0
						rootNode = opNode;
						rootNode->m_pLeftChild = valueNode;
					}
					else
					{
						opNode->m_pLeftChild = rootNode;
						rootNode->m_pRightChild = valueNode;
						rootNode->m_pFather = opNode;
						rootNode = opNode;
					}
				}
				else
				{
					if (rootNode == NULL)//以-号开头的行
					{
						initPriority = 0;//初始化优先级为0
						rootNode = new Node(new Minus());
						rootNode->m_pLeftChild = new Node(0.0);
					}
					else
					{
						Node* opNode = new Node(new Minus());
						rootNode->m_pFather = opNode;
						opNode->m_pLeftChild = rootNode;
						rootNode = opNode;
					}
				}
				break;
			case '×':
			case 'X':
			case 'x':
			case '*':
				if (buffer.GetLength() != 0)
				{
					Node* valueNode = new Node(buffer.ConvertToDouble());
					buffer.Clear();
					Node* opNode = new Node(new Multiply());
					if (rootNode == NULL)
					{
						//initPriority = 1;//初始化优先级为1
						rootNode = new Node(new Plus());
						rootNode->m_pLeftChild = new Node(0.0);
						rootNode->m_pRightChild = Parse(source, index, valueNode, new Multiply());
					}
					else
					{
						if (initPriority < 1)
						{
							rootNode->m_pRightChild = Parse(source, index, valueNode, new Multiply());
						}
						else
						{
							rootNode->m_pFather = opNode;
							rootNode->m_pRightChild = valueNode;
							opNode->m_pLeftChild = rootNode;
							rootNode = opNode;
						}
					}
				}
				else
				{
					if (rootNode == NULL) return NULL;
					if (initPriority < 1)
					{
						rootNode->m_pRightChild = Parse(source, index, rootNode->m_pRightChild, new Multiply());
					}
					else
					{
						rootNode->m_pFather = new Node(new Multiply());
						rootNode->m_pFather->m_pLeftChild = rootNode;
						rootNode = rootNode->m_pFather;
					}
				}
				break;
			case '÷':
			case '/':
				if (buffer.GetLength() != 0)
				{
					Node* valueNode = new Node(buffer.ConvertToDouble());
					buffer.Clear();
					Node* opNode = new Node(new Divide());
					if (rootNode == NULL)
					{
						//initPriority = 1;//初始化优先级为1
						rootNode = new Node(new Plus());
						rootNode->m_pLeftChild = new Node(0.0);
						rootNode->m_pRightChild = Parse(source, index, valueNode, new Divide());
					}
					else
					{
						if (initPriority < 1)
						{
							index++;
							rootNode->m_pRightChild = Parse(source, index, valueNode, new Divide());
						}
						else
						{
							rootNode->m_pFather = opNode;
							rootNode->m_pRightChild = valueNode;
							opNode->m_pLeftChild = rootNode;
							rootNode = opNode;
						}
					}
				}
				else
				{
					if (rootNode == NULL) return NULL;
					if (initPriority < 1)
					{
						rootNode->m_pRightChild = Parse(source, index, rootNode->m_pRightChild, new Divide());
					}
					else
					{
						rootNode->m_pFather = new Node(new Divide());
						rootNode->m_pFather->m_pLeftChild = rootNode;
						rootNode = rootNode->m_pFather;
					}
				}
				break;

			case '(':
			case '[':
			case '{':
			case '（':
			case '［':
			case '｛':
			case '〖':
			case '【':
				index++;
				if (buffer.GetLength() != 0) return NULL;
				if (rootNode == NULL)
				{
					rootNode = new Node(new Plus());
					rootNode->m_pLeftChild = new Node(0.0);
					//rootNode.RightChild = Parse(source, ref index);
				}
				//else
				//{
				rootNode->m_pRightChild = Parse(source, index);
				//}
				break;
			case ')':
			case ']':
			case '}':
			case '）':
			case '］':
			case '｝':
			case '〗':
			case '】':
				if (buffer.GetLength() != 0 && rootNode != NULL)
				{
					Node* valueNode = new Node(buffer.ConvertToDouble());
					rootNode->m_pRightChild = valueNode;
				}
				return rootNode;
			}
		}

		if (buffer.GetLength() != 0 && rootNode != NULL)
		{
			Node* valueNode = new Node(buffer.ConvertToDouble());
			rootNode->m_pRightChild = valueNode;
		}
		return rootNode;
	}
};