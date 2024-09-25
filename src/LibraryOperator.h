#ifndef LIBRARYOPERATOR_H
#define LIBRARYOPERATOR_H
#include <cstdio>
#include <iostream>
#include "LinkList.h"
#include "Library.h"

void findCategory(LinkList<CategoryNode>& listCategory,BookNode& book)
{
	int n = listCategory.NumNodes();
	string target_category = book.getCategory();
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		if(listCategory.CurData().getCategoryName() == target_category)
		{
			listCategory.CurData().addBook(&book);
			return;
		}
	}
	LinkList<BookNode> listBooks;
	listBooks.Append(book);
	CategoryNode newCategoryNode = {target_category,listBooks};
	listCategory.Append(newCategoryNode);
}

bool checkRepeatByISBNViaList(LinkList<CategoryNode>& listCategory,string checkISBN)
{
	int n = listCategory.NumNodes();
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		if(listCategory.CurData().checkRepaetByISBN(checkISBN))
			return true;
	}
	return false;
}

void getBook(LinkList<CategoryNode>& listCategory)
{
	printf("������⡢������ߡ�ISBN:");
	string title,category,author,isbn;
	cin>>title>>category>>author>>isbn;
	BookNode book = {title,category,author,isbn};
	if(!checkRepeatByISBNViaList(listCategory, isbn))
	{
		findCategory(listCategory,book);
		listCategory.GoTop();
		printf("�ɹ�����鼮");
	}
	else 
	{
		printf("������ͬ��ISBN��,����鼮ʧ�ܣ�");
	}
}

void findBook(LinkList<CategoryNode>& listCategory)
{
	printf("�����鼮��ISBN��:");
	string isbn;
	int n = listCategory.NumNodes();
	cin>>isbn;
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		BookNode* book = listCategory.CurData().findBookByISBN(isbn);
		if(book != nullptr)
		{
			cout<<*book<<endl;
			return;
		}
	}
	printf("δ���ҵ����鼮\n");
	return;
}

void borrowBook(LinkList<CategoryNode>& listCategory)
{
	printf("����isbn,����������: ");
	string isbn,borrower;
	int n = listCategory.NumNodes();
	cin>>isbn>>borrower;
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		BookNode* book = listCategory.CurData().findBookByISBN(isbn);
		if(book != nullptr)
		{
			if(book->getIsBorrowed())
			{
				printf("�����ѱ�����");
			}
			else 
			{
				listCategory.CurData().borrowBookByISBN(isbn, borrower);
				printf("����ɹ���");
			}
			return;
		}
	}
	printf("δ���ҵ����鼮\n");
	return;
}

void returnBook(LinkList<CategoryNode>& listCategory)
{
	printf("����isbn,����������: ");
	string isbn,returner;
	int n = listCategory.NumNodes();
	cin>>isbn>>returner;
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		BookNode* book = listCategory.CurData().findBookByISBN(isbn);
		if(book != nullptr)
		{
			if(book->getIsBorrowed() && book->getBorrowerName() == returner)
			{
				listCategory.CurData().returnBookByISBN(isbn);
				printf("�ɹ����飡");
			}
			else 
			{
				printf("���鲢û�б����߻��������������");
			}
			return;
		}
	}
	printf("δ���ҵ����鼮\n");
	return;
}

void deleteBook(LinkList<CategoryNode>& listCategory)
{
	printf("����isbn: ");
	string isbn;
	int n = listCategory.NumNodes();
	cin>>isbn;
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		BookNode* book = listCategory.CurData().findBookByISBN(isbn);
		if(book != nullptr)
		{
			listCategory.CurData().deleteBookByISBN(isbn);
			printf("ɾ���ɹ���\n");
			return;
		}
	}
	printf("δ���ҵ����鼮\n");
	return;
}

void printAllBookbyCategory(LinkList<CategoryNode>& listCategory)
{
	printf("�������: ");
	string category;
	int n = listCategory.NumNodes();
	cin>>category;
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		if(listCategory.CurData().getCategoryName() == category)
		{
			listCategory.CurData().printBooks(category);
			return;
		}
	}
	printf("δ���ҵ������\n");
	return;
}

void printAllBook(LinkList<CategoryNode>& listCategory)
{
	int n = listCategory.NumNodes();
	for(int i=0;i<n;i++)
	{
		listCategory.Go(i);
		if(listCategory.CurNode() != nullptr)
			listCategory.CurData().printAllBooks();
	}
	return;
}


//�����ô���
void creatBook(LinkList<CategoryNode>& listCategory,string title,string category,string author,string isbn)
{
	BookNode book = {title,category,author,isbn};
	findCategory(listCategory,book);
	listCategory.GoTop();
}



#endif