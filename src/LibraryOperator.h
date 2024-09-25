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
	printf("输入标题、类别、作者、ISBN:");
	string title,category,author,isbn;
	cin>>title>>category>>author>>isbn;
	BookNode book = {title,category,author,isbn};
	if(!checkRepeatByISBNViaList(listCategory, isbn))
	{
		findCategory(listCategory,book);
		listCategory.GoTop();
		printf("成功添加书籍");
	}
	else 
	{
		printf("存在相同的ISBN号,添加书籍失败！");
	}
}

void findBook(LinkList<CategoryNode>& listCategory)
{
	printf("输入书籍的ISBN号:");
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
	printf("未能找到该书籍\n");
	return;
}

void borrowBook(LinkList<CategoryNode>& listCategory)
{
	printf("输入isbn,借书人姓名: ");
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
				printf("该书已被借走");
			}
			else 
			{
				listCategory.CurData().borrowBookByISBN(isbn, borrower);
				printf("借书成功！");
			}
			return;
		}
	}
	printf("未能找到该书籍\n");
	return;
}

void returnBook(LinkList<CategoryNode>& listCategory)
{
	printf("输入isbn,换书人姓名: ");
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
				printf("成功换书！");
			}
			else 
			{
				printf("该书并没有被接走或借书人姓名不符");
			}
			return;
		}
	}
	printf("未能找到该书籍\n");
	return;
}

void deleteBook(LinkList<CategoryNode>& listCategory)
{
	printf("输入isbn: ");
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
			printf("删除成功！\n");
			return;
		}
	}
	printf("未能找到该书籍\n");
	return;
}

void printAllBookbyCategory(LinkList<CategoryNode>& listCategory)
{
	printf("输入类别: ");
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
	printf("未能找到该类别\n");
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


//测试用代码
void creatBook(LinkList<CategoryNode>& listCategory,string title,string category,string author,string isbn)
{
	BookNode book = {title,category,author,isbn};
	findCategory(listCategory,book);
	listCategory.GoTop();
}



#endif