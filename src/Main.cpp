#include <cstdio>
#include <iostream>
#include <conio.h>
#include "LinkList.h"
#include "Library.h"
#include "LibraryOperator.h"

using namespace std;

LinkList<CategoryNode> listClassics;

int Pos(char ch, const char *str)			// ����ָ���ַ�ch���ַ���str�е��±ꡣ������ʱ����-1
{
	int i;
	for(i=0; str[i]!='\0'; i++)
		if(ch==str[i])
			return i;
	return -1;
}

int Choice(const char *prompt, const char *options="");	// ��������
int Choice(const char *prompt, const char *options)		// �������塣�����ʾ��Ϣprompt������ѡ����ַ������ء�
{
	int key;
	cout << prompt << "{";
	for(int i=0; options[i]!='\0'; i++)
	{
		if(' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// ѡ��options�еĿɴ�ӡ�ַ�
			cout << options[i] << ' ';
		else														// ѡ��options�еĲ��ֿ����ַ�
		{
			switch(options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// ѡ���е�Tab�ַ�'\t'����ASCII����9��
			case '\x1b': cout << "[Esc] ";   break;					// ѡ���е�Esc�ַ�'\x1b'����ASCII����27��
			case ' ':    cout << "[Space] "; break;					// ѡ���еĿո��ַ�' '����ASCII����32��
			}
		}
	}
	cout << "\b}: ";					// '\b'�˸�����һ��������һ�����
	do
	{
		key = getch();
	}while(options[0]!='\0' && Pos(key, options)<0); // ��optionsΪ�ճ���Ϊ0���ַ����������������ƣ�����������Ӧ����optins�С�
	cout << endl;
	return key;
}

void initLibraryTest()
{
	// �����鼮ʵ��
	BookNode book1("The Great Gatsby", "Classic", "F. Scott Fitzgerald", "123456789", false, "");
	BookNode book2("To Kill a Mockingbird", "Classic", "Harper Lee", "987654321", false, "");
	BookNode book3("1984", "Dystopian", "George Orwell", "456789123", false, "");
	// �������ʵ��������鼮
	CategoryNode classics;
	classics.changeCategory("Classic");
	classics.addBook(&book1);
	classics.addBook(&book2);
	listClassics.Append(classics);
	CategoryNode dystopian;
	dystopian.changeCategory("Dystopian");
	dystopian.addBook(&book3);
	listClassics.Append(dystopian);
	
	//����Ĵ����鼮
	creatBook(listClassics, "unity_course","program","ly", "123321123");
	creatBook(listClassics,"Lost Time", "Science Fiction", "Li Ming", "9783161484100");
	creatBook(listClassics, "Shadow City", "Mystery", "Wang Xiao", "9781617290084");
	creatBook(listClassics, "The Disappearing Code", "Mystery", "Zhao Min", "9780137081890");
}

int main()
{
	initLibraryTest();
	int key;
	while(true)
	{
		cout << "\n\n\tͼ��ݹ���" << endl;
		cout << "1 --- ����鼮" << endl;
		cout << "2 --- �����鼮" << endl;
		cout << "3 --- ����" << endl;
		cout << "4 --- ����" << endl;
		cout << "5 --- ɾ���鼮" << endl;
		cout << "6 --- �������е������鼮��Ϣ" << endl;
		cout << "7 --- ��������鼮��Ϣ" << endl;
		key = Choice("\n��ѡ��", "123456789\x1b");
		cout << "\n\n";
		if(key==27)		// '\x1b'����27��ָESC��
			break;
		switch(key)
		{
		case '1':
			getBook(listClassics);
			break;
		case '2':
			findBook(listClassics);
			break;
		case '3':
			borrowBook(listClassics);
			break;
		case '4':
			returnBook(listClassics);
			break;
		case '5':
			deleteBook(listClassics);
			break;
		case '6':
			printAllBookbyCategory(listClassics);
			break;
		case '7':
			printAllBook(listClassics);
			break;
		}
	}
	return 0;
}