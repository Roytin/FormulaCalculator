#include <iostream>
#include <string>
using namespace std;
#include "Script.h"

int main()
{

	cout<<"-------欢迎使用CR的算式计算器-------"<<endl;
	cout<<"本计算器支持带各种括号嵌套的四则运算"<<endl;
	while(true){
		cout<<"*****************************"<<endl;
		cout<<"请输入一行算式:"<<endl;
		string buffer;
		cin>>buffer;
		FormulaTree tree;

		tree.BuildTree(buffer.c_str());

		cout<<tree.Root->GetValue()<<endl;
	}
	return 0;
}