using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace FormulaCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("-------欢迎使用CR的算式计算器-------");
            Console.WriteLine("本计算器支持带各种括号嵌套的四则运算");
            while (true)
            {
                Console.WriteLine("*****************************");
                Console.WriteLine("请输入一行算式: ");
                string formula = Console.ReadLine();
                FormulaTree tree = new FormulaTree();
                if (tree.BuildTree(formula))
                {
                    Console.WriteLine(tree.Root.Value);
                }

                #region 已弃用的旧方法

                //{
                //    OperationElement element = Script.Parse(formula);
                //    if (element != null)
                //        Console.WriteLine(element.Result);
                //    else
                //    {
                //        Console.WriteLine("请输入正确的算式格式");
                //    }
                //}
                //catch (Exception)
                //{
                //    Console.WriteLine("请输入正确的算式格式");
                //}
                //finally
                //{
                //    Console.WriteLine();
                //}

                #endregion
            }
        }
    }

    class Node
    {
        public Node Father;
        public Node LeftChild;
        public Node RightChild;

        public BaseOperator Operator;
        private double _value;

        public Node(BaseOperator op)
        {
            Operator = op;
        }

        public Node(double value)
        {
            _value = value;
        }

        public double Value
        {
            get
            {
                if (Operator == null)
                {
                    return _value;
                }
                else
                {
                    return Operator.Compute(LeftChild.Value, RightChild.Value);
                }
            }
        }
    }

    class FormulaTree
    {
        public Node Root;

        public FormulaTree()
        {
            Root = new Node(0);
        }

        public bool BuildTree(string formula)
        {
            int index = 0;
            Root = Parse(formula, ref index);
            if(Root != null)
                return true;
            else
                return false;
        }
        
        //遇到括号开启新栈的,遇到后括号退出堆栈, 遇到优先级上升进堆栈
        private Node Parse(string source, ref int index, Node left = null, BaseOperator op = null)
        {
            int initPriority = -1;
            Node rootNode = null;
            if (left != null && op != null)
            {
                rootNode = new Node(op);
                rootNode.LeftChild = left;
                initPriority = 1;
                index++;
            }

            StringBuilder buffer = new StringBuilder();
            for (; index < source.Length; index++)
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
                            if (buffer.Length != 0 && rootNode != null)
                            {
                                Node valueNode = new Node(double.Parse(buffer.ToString()));
                                buffer.Clear();
                                rootNode.RightChild = valueNode;
                            }
                            index--;
                            return rootNode;
                        }

                        if (buffer.Length != 0)
                        {
                            Node valueNode = new Node(double.Parse(buffer.ToString()));
                            buffer.Clear();
                            Node opNode = new Node(new Plus());
                            if (rootNode == null)
                            {
                                initPriority = 0;//初始化优先级为0
                                rootNode = opNode;
                                rootNode.LeftChild = valueNode;
                            }
                            else
                            {
                                opNode.LeftChild = rootNode;
                                rootNode.RightChild = valueNode;
                                rootNode.Father = opNode;
                                rootNode = opNode;
                            }
                        }
                        else
                        {
                            if (rootNode == null)//以+号开头的行
                            {
                                initPriority = 0;//初始化优先级为0
                                rootNode = new Node(new Plus());
                                rootNode.LeftChild = new Node(0);
                            }
                            else
                            {
                                Node opNode = new Node(new Plus());
                                rootNode.Father = opNode;
                                opNode.LeftChild = rootNode;
                                rootNode = opNode;
                            }
                        }
                        break;
                    case '－':
                    case '-':
                        //判断是否有出栈的必要
                        if (initPriority != -1 && initPriority > 0)
                        {
                            if (buffer.Length != 0 && rootNode != null)
                            {
                                Node valueNode = new Node(double.Parse(buffer.ToString()));
                                buffer.Clear();
                                rootNode.RightChild = valueNode;
                            }
                            index--;
                            return rootNode;
                        }

                        if (buffer.Length != 0)
                        {
                            Node valueNode = new Node(double.Parse(buffer.ToString()));
                            buffer.Clear();
                            Node opNode = new Node(new Minus());
                            if (rootNode == null)
                            {
                                initPriority = 0;//初始化优先级为0
                                rootNode = opNode;
                                rootNode.LeftChild = valueNode;
                            }
                            else
                            {
                                opNode.LeftChild = rootNode;
                                rootNode.RightChild = valueNode;
                                rootNode.Father = opNode;
                                rootNode = opNode;
                            }
                        }
                        else
                        {
                            if (rootNode == null)//以-号开头的行
                            {
                                initPriority = 0;//初始化优先级为0
                                rootNode = new Node(new Minus());
                                rootNode.LeftChild = new Node(0);
                            }
                            else
                            {
                                Node opNode = new Node(new Minus());
                                rootNode.Father = opNode;
                                opNode.LeftChild = rootNode;
                                rootNode = opNode;
                            }
                        }
                        break;
                    case '×':
                    case 'X':
                    case 'x':
                    case '*':
                        if (buffer.Length != 0)
                        {
                            Node valueNode = new Node(double.Parse(buffer.ToString()));
                            buffer.Clear();
                            Node opNode = new Node(new Multiply());
                            if (rootNode == null)
                            {
                                //initPriority = 1;//初始化优先级为1
                                rootNode = new Node(new Plus());
                                rootNode.LeftChild = new Node(0);
                                rootNode.RightChild = Parse(source, ref index, valueNode, new Multiply());
                            }
                            else
                            {
                                if (initPriority < 1)
                                {
                                    rootNode.RightChild = Parse(source, ref index, valueNode, new Multiply());
                                }
                                else
                                {
                                    rootNode.Father = opNode;
                                    rootNode.RightChild = valueNode;
                                    opNode.LeftChild = rootNode;
                                    rootNode = opNode;
                                }
                            }
                        }
                        else
                        {
                            if (rootNode == null) return null;
                            if (initPriority < 1)
                            {
                                rootNode.RightChild = Parse(source, ref index, rootNode.RightChild, new Multiply());
                            }
                            else
                            {
                                rootNode.Father = new Node(new Multiply());
                                rootNode.Father.LeftChild = rootNode;
                                rootNode = rootNode.Father;
                            }
                        }
                        break;
                    case '÷':
                    case '/':
                        if (buffer.Length != 0)
                        {
                            Node valueNode = new Node(double.Parse(buffer.ToString()));
                            buffer.Clear();
                            Node opNode = new Node(new Divide());
                            if (rootNode == null)
                            {
                                //initPriority = 1;//初始化优先级为1
                                rootNode = new Node(new Plus());
                                rootNode.LeftChild = new Node(0);
                                rootNode.RightChild = Parse(source, ref index, valueNode, new Divide());
                            }
                            else
                            {
                                if (initPriority < 1)
                                {
                                    index++;
                                    rootNode.RightChild = Parse(source, ref index, valueNode, new Divide());
                                }
                                else
                                {
                                    rootNode.Father = opNode;
                                    rootNode.RightChild = valueNode;
                                    opNode.LeftChild = rootNode;
                                    rootNode = opNode;
                                }
                            }
                        }
                        else
                        {
                            if (rootNode == null) return null;
                            if (initPriority < 1)
                            {
                                rootNode.RightChild = Parse(source, ref index, rootNode.RightChild, new Divide());
                            }
                            else
                            {
                                rootNode.Father = new Node(new Divide());
                                rootNode.Father.LeftChild = rootNode;
                                rootNode = rootNode.Father;
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
                        if (buffer.Length != 0) return null;
                        if (rootNode == null)
                        {
                            rootNode = new Node(new Plus());
                            rootNode.LeftChild = new Node(0);
                            //rootNode.RightChild = Parse(source, ref index);
                        }
                        //else
                        //{
                            rootNode.RightChild = Parse(source, ref index);
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
                        if (buffer.Length != 0 && rootNode != null)
                        {
                            Node valueNode = new Node(double.Parse(buffer.ToString()));
                            buffer.Clear();
                            rootNode.RightChild = valueNode;
                        }
                        return rootNode;
                }
            }

            if (buffer.Length != 0 && rootNode != null)
            {
                Node valueNode = new Node(double.Parse(buffer.ToString()));
                buffer.Clear();
                rootNode.RightChild = valueNode;
            }
            return rootNode;
        }
    }
}
