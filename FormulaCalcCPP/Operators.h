#pragma  once

class BaseOperator
{
private:	
	short Index;
public:

	virtual double Compute(double number1, double number2) = 0;

	BaseOperator(short index)
	{
		Index = index;
	}
};

class Plus :public BaseOperator
{
public:
	Plus():BaseOperator(0)
	{
	}

	virtual double Compute(double number1, double number2)
	{
		return number1 + number2;
	}
};

class Minus :public BaseOperator
{
public:
	Minus(): BaseOperator(1)
	{
	}

	virtual double Compute(double number1, double number2)
	{
		return number1 - number2;
	}
};

class Multiply :public BaseOperator
{
public:
	Multiply(): BaseOperator(2)
	{
	}

	virtual double Compute(double number1, double number2)
	{
		return number1 * number2;
	}
};

class Divide :public BaseOperator
{
public:
	Divide(): BaseOperator(3)
	{
	}

	virtual double Compute(double number1, double number2)
	{
		return number1 / number2;
	}
};
