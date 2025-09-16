#include <iostream.h>
#include <string>
#include <fstream>
#define head "printflush message1\nread adr cell1 0\nop mul adr adr 2\nop add @counter @counter adr"

using namespace std;
int main(int argc, char *argv[])
{
	ifstream fcnt("code.txt");
	int size=0;
	string text;
	if (fcnt.is_open())
	{
		while(getline(fcnt,text))
		{size++;}
		fcnt.close();
	}
	if(size>495)
	{
		cout<<"\033[31mtoo many lines\033[0m"<<endl;
	}
	ifstream fcode("code.txt");
	if (fcode.is_open())
	{
		string code = "";
		
		for (int i = 0; i < size; i++)
		{
			code += "print ";
			code += '"';
			getline(fcode, text);
			code += text;
			code += '"';
			code += '\n';
			code += "set @counter 0\n";
		}
		
		fcode.close();
		ofstream fout("output.txt", ios_base::out);
		
		if (fout.is_open())
		{
			fout << head << '\n' << code;
			fout.close();
		}
		cout<<head<<'\n'<<code<<'\n';
	}
	else
	{
		ofstream fout("code.txt", ios_base::out);
		// это чтоб создать файл
		if (fout.is_open())
		{
			fout << ' ';
			fout.close();
		}
	}
	return 0;
}
/*
printflush message1
read adr cell1 0
op mul adr adr 2
op add @counter @counter adr
print "frog"
set @counter 0
print "cat"
set @counter 0
print "dog"
set @counter 0
*/
