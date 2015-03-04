using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FormulaCalculator
{
    public static class OperatorFactory
    {
        public static BaseOperator CreateOperator(byte operatorIndex)
        {
            BaseOperator op = null;
            switch (operatorIndex)
            {
                case 0:
                    op = new Plus();
                    break;
                case 1:
                    op = new Minus();
                    break;
                case 2:
                    op = new Multiply();
                    break;
                case 3:
                    op = new Divide();
                    break;
            }
            return op;
        }
    }
}
