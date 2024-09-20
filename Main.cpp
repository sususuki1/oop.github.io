#include <iostream>
#include <conio.h>
#include <cstring>
#include "LinkList.h"
#include "Library.h"


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


CategoryNode getCategory()
{
	printf("����Ŀ¼���ƣ�");
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
	// �����鼮ʵ��
	BookNode book1("The Great Gatsby", "Classic", "F. Scott Fitzgerald", "123456789", false, "");
	BookNode book2("To Kill a Mockingbird", "Classic", "Harper Lee", "987654321", false, "");
	BookNode book3("1984", "Dystopian", "George Orwell", "456789123", false, "");

	// �������ʵ��������鼮
	CategoryNode classics;
	classics.addCategory("Classic");
	classics.addBook(&book1);
	classics.addBook(&book2);
	listClassics.Append(classics);
	CategoryNode dystopian;
	dystopian.addBook(&book3);
	listClassics.Append(dystopian);
	// �����鼮
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
		cout << "\n\n\tͼ��ݹ���" << endl;
		cout << "1 --- ������" << endl;
		cout << "2 --- �����������鼮" << endl;
		cout << "3 --- �����鼮" << endl;
		cout << "4 --- ����" << endl;
		cout << "5 --- ����" << endl;
		cout << "6 --- ɾ���鼮" << endl;
		cout << "7 --- ��ѯ�鼮״̬" << endl;
		cout << "8 --- �������е������鼮��Ϣ" << endl;
		cout << "9 --- ��������鼮��Ϣ" << endl;
		key = Choice("\n��ѡ��", "123456789\x1b");
		cout << "\n\n";
		if(key==27)		// '\x1b'����27��ָESC��
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
