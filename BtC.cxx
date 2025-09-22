#include <iostream.h>
#include <string>
#include <fstream>

#define list (text[i]=='0'|text[i]=='1'|text[i]=='2'|text[i]=='3'|text[i]=='4'|text[i]=='5'|text[i]=='6'|text[i]=='7'|text[i]=='8'|text[i]=='9'|text[i]=='A'|text[i]=='B'|text[i]=='C'|text[i]=='D'|text[i]=='E'|text[i]=='F'|text[i]=='a'|text[i]=='b'|text[i]=='c'|text[i]=='d'|text[i]=='e'|text[i]=='f')

using namespace std;
int main(int argc, char *argv[])
{//400 495
	bool err=0;
	uint16_t *data;
	ifstream fbn("hex.txt");
	if (fbn.is_open())
	{
		int cnt=0;
		int line_cnt=0;
		string text;	
		while(getline(fbn,text))//проверка файла
		{
			bool flag=1;
			int word_cnt=0;
			int word_len=0;
			for(int i=0;i<text.length();i++)
			{
				if(!(list|text[i]==' '))//проверка разрешенных символов
				{
					cout<<"err: unknown symbol at: "<<line_cnt<<' '<<word_cnt<<' '<<text[i]<<' '<<int(text[i])<<'\n';
					err=1;
				}
				
				if(flag&list)//механизм
				{
					word_cnt++;
					cnt++;
					flag=0;
				}
				if(!flag&(text[i]==' '|i==text.length()-1))
				{
					flag=1;
				}
				
				if(list)//проверка длины слова
				{
					word_len++;
				}
				else
				{
					word_len=0;
				}
				if(word_len>4)
				{
					cout<<"err: incorrect word length at: "<<line_cnt<<' '<<word_cnt<<' '<<word_len<<'\n';
					err=1;
				}
				
			}
			line_cnt++;
		}
	//	cout<<cnt;
		data=new uint16_t[cnt];
		fbn.close();
		ifstream fwd("hex.txt");
		if (fwd.is_open()&!err)
		{
			int adr=0;
			while(getline(fwd,text))//проверка файла
			{
				bool flag=1;
				string word="";
			//	cout<<text<<'\n';
				for(int i=0;i<text.length();i++)
				{
					if(flag&list)
					{
						flag=0;
					}
					if(list)//запис слова
					{
						word+=text[i];
					}
					if(!flag&(text[i]==' '|i==text.length()-1))//обработка и сохранение числа из слова
					{
						flag=1;
						//cout<<word<<'\n';
						uint16_t num=0;
						for(int j=0;j<word.length();j++)//конвертирование слова в число
						{
							int char_num=0;
							if(word[j]<58)
							{
								char_num=int(word[j])-48;
							}
							else if(word[j]<71)
							{
								char_num=int(word[j])-55;
							}
							else
							{
								char_num=int(word[j])-87;
							}
							num<<=4;
							num|=char_num;
						}
						//cout<<num<<'\n';//сохранение
						data[adr]=num;
						adr++;
						word="";
						if(cnt<adr)
						{
							cout<<"err: unknown error, adr>cnt"<<'\n';
							err=1;
							break;//если что-то пошло не так
						}
					}
				}
				if(err){break;}
			}
			ofstream fout("code.txt", ios::binary);
			if (!fout.is_open())
			{
    		    cout<<"err: file is missing, creating new file"<<'\n';
				err=1;
				ofstream fout("code.txt", ios::binary);
				// это чтоб создать файл если его не существует
				if (fout.is_open())
				{
					fout << ' ';
				}else{
					cout<<"err: error of creating new file"<<'\n';
					err=1;
				}
    		}
    	/*	uint16_t bom = 0xFEFF;
		    fout.write(reinterpret_cast<const char*>(&bom), sizeof(bom));
    		for(int i=0;i<cnt;i++)
			{
				fout.write(reinterpret_cast<const char*>(&data[i]),sizeof(data[i]));
				cout<<data[i]<<' ';
			}*/
			uint16_t bom = 0xFFFF;
			uint16_t val = 0x03E8;
			fout.write(reinterpret_cast<const char*>(&bom), sizeof(bom));
			fout.write(reinterpret_cast<const char*>(&val), sizeof(val));
    		fout.close();
		}
		else if(err&fwd.is_open())
		{
			cout<<"code is stopped"<<'\n';
		}
		else
		{
			cout<<"err: file is dissappeared while code running"<<'\n';
			err=1;
		}
		
		fwd.close();
	}else{
		cout<<"err: file is missing, creating new file"<<'\n';
		err=1;
		ofstream fbn("hex.txt", ios_base::out);
		// это чтоб создать файл если его не существует
		if (fbn.is_open())
		{
			fbn << ' ';
		}else{
			cout<<"err: error of creating new file"<<'\n';
			err=1;
		}
		fbn.close();
	}	
return 0;}
//0123456789ABCDEF
//пробел-разделитель
//ff ffff 00 29 29c9 AcB1
/*
aa aa aaaa aa aaaa i
aaaa aa aa aaaa aai
aa aa aa ... aai


*/