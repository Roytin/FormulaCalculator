#include <iostream>
#include <string>
using namespace std;
#include "Script.h"

int main()
{

	cout<<"-------��ӭʹ��CR����ʽ������-------"<<endl;
	cout<<"��������֧�ִ���������Ƕ�׵���������"<<endl;
	while(true){
		cout<<"*****************************"<<endl;
		cout<<"������һ����ʽ:"<<endl;
		string buffer;
		cin>>buffer;
		FormulaTree tree;

		tree.BuildTree(buffer.c_str());

		cout<<tree.Root->GetValue()<<endl;
	}
	return 0;
}