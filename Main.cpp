#include <iostream>
#include <conio.h>
#include <cstring>
#include "LinkList.h"
#include "Library.h"


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


CategoryNode getCategory()
{
	printf("输入目录名称：");
	string str;
	cin>>str;
	LinkList<BookNode> listbooks;
	CategoryNode newcategory = {str,listbooks};
	return newcategory;
}

BookNode *getBook()
{
	string title,category,author,isbn;
	cin>>title>>category>>author>>isbn;
	BookNode *book = new BookNode(title,category,author,isbn);
	return book;
}

int main()
{
	// 创建书籍实例
	BookNode book1("The Great Gatsby", "Classic", "F. Scott Fitzgerald", "123456789", false, "");
	BookNode book2("To Kill a Mockingbird", "Classic", "Harper Lee", "987654321", false, "");
	BookNode book3("1984", "Dystopian", "George Orwell", "456789123", false, "");

	// 创建类别实例并添加书籍
	CategoryNode classics;
	classics.addCategory("Classic");
	classics.addBook(&book1);
	classics.addBook(&book2);
	listClassics.Append(classics);
	CategoryNode dystopian;
	dystopian.addBook(&book3);
	listClassics.Append(dystopian);
	// 查找书籍
	BookNode* foundBook = classics.findBookByISBN("123456789");
	if (foundBook != nullptr) {
		cout << "Found book: " << *foundBook << endl;
	}
	else {
		cout << "Book not found." << endl;
	}

	int key;
	while(true)
	{
		cout << "\n\n\t图书馆管理" << endl;
		cout << "1 --- 添加类别" << endl;
		cout << "2 --- 向类别中添加书籍" << endl;
		cout << "3 --- 查找书籍" << endl;
		cout << "4 --- 借书" << endl;
		cout << "5 --- 还书" << endl;
		cout << "6 --- 删除书籍" << endl;
		cout << "7 --- 查询书籍状态" << endl;
		cout << "8 --- 输出类别中的所有书籍信息" << endl;
		cout << "9 --- 输出所有书籍信息" << endl;
		key = Choice("\n请选择", "123456789\x1b");
		cout << "\n\n";
		if(key==27)		// '\x1b'等于27，指ESC键
			break;
			
		switch(key)
		{
		case '1':
			//classics.addCategory(listClassics,);
			listClassics.Append(getCategory());
			break;
		case '2':
			//classics.addBook(getBook());
			break;
		case '3':	break;
		case '4':	break;
		case '5':	break;
		}
	}
	return 0;


	return 0;
}
