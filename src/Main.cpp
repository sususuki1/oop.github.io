#include <cstdio>
#include <iostream>
#include <conio.h>
#include "LinkList.h"
#include "Library.h"
#include "LibraryOperator.h"

using namespace std;

LinkList<CategoryNode> listClassics;

int Pos(char ch, const char *str)			// 返回指定字符ch在字符串str中的下标。不存在时返回-1
{
	int i;
	for(i=0; str[i]!='\0'; i++)
		if(ch==str[i])
			return i;
	return -1;
}

int Choice(const char *prompt, const char *options="");	// 函数声明
int Choice(const char *prompt, const char *options)		// 函数定义。输出提示信息prompt，输入选择的字符并返回。
{
	int key;
	cout << prompt << "{";
	for(int i=0; options[i]!='\0'; i++)
	{
		if(' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// 选项options中的可打印字符
			cout << options[i] << ' ';
		else														// 选项options中的部分控制字符
		{
			switch(options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// 选项中的Tab字符'\t'（即ASCII编码9）
			case '\x1b': cout << "[Esc] ";   break;					// 选项中的Esc字符'\x1b'（即ASCII编码27）
			case ' ':    cout << "[Space] "; break;					// 选项中的空格字符' '（即ASCII编码32）
			}
		}
	}
	cout << "\b}: ";					// '\b'退格。先退一格，在输出右花括号
	do
	{
		key = getch();
	}while(options[0]!='\0' && Pos(key, options)<0); // 若options为空长度为0的字符串，则输入无限制；否则输入项应该在optins中。
	cout << endl;
	return key;
}

void initLibraryTest()
{
	// 创建书籍实例
	BookNode book1("The Great Gatsby", "Classic", "F. Scott Fitzgerald", "123456789", false, "");
	BookNode book2("To Kill a Mockingbird", "Classic", "Harper Lee", "987654321", false, "");
	BookNode book3("1984", "Dystopian", "George Orwell", "456789123", false, "");
	// 创建类别实例并添加书籍
	CategoryNode classics;
	classics.changeCategory("Classic");
	classics.addBook(&book1);
	classics.addBook(&book2);
	listClassics.Append(classics);
	CategoryNode dystopian;
	dystopian.changeCategory("Dystopian");
	dystopian.addBook(&book3);
	listClassics.Append(dystopian);
	
	//更快的创建书籍
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
		cout << "\n\n\t图书馆管理" << endl;
		cout << "1 --- 添加书籍" << endl;
		cout << "2 --- 查找书籍" << endl;
		cout << "3 --- 借书" << endl;
		cout << "4 --- 还书" << endl;
		cout << "5 --- 删除书籍" << endl;
		cout << "6 --- 输出类别中的所有书籍信息" << endl;
		cout << "7 --- 输出所有书籍信息" << endl;
		key = Choice("\n请选择", "1234567\x1b");
		cout << "\n\n";
		if(key==27)		// '\x1b'等于27，指ESC键
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