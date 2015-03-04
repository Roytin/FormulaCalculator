using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FormulaCalculator
{
    public abstract class BaseOperator
    {
        public readonly byte Index;

        public abstract double Compute(double number1, double number2);

        protected BaseOperator(byte index)
        {
            Index = index;
        }
    }

    public class Plus : BaseOperator
    {
        public Plus()
            : base(0)
        {
        }

        public override double Compute(double number1, double number2)
        {
            return number1 + number2;
        }
    }

    public class Minus : BaseOperator
    {
        public Minus()
            : base(1)
        {
        }

        public override double Compute(double number1, double number2)
        {
            return number1 - number2;
        }
    }

    public class Multiply : BaseOperator
    {
        public Multiply()
            : base(2)
        {
        }

        public override double Compute(double number1, double number2)
        {
            return number1 * number2;
        }
    }

    public class Divide : BaseOperator
    {
        public Divide()
            : base(3)
        {
        }

        public override double Compute(double number1, double number2)
        {
            return number1 / number2;
        }
    }
}
