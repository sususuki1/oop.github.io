#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H
#include "LinkList.h"
#include <iomanip>
#include <string>

class CategoryNode;
class BookNode {
private:
    string title;
    string category;
    string author;
    string ISBN;
    bool isBorrowed;
    string borrowerName;

public:
    // 无参构造函数
    BookNode();

    // 有参构造函数
    BookNode(const string& title, const string& category, const string& author, const string& isbn, bool isBorrowed = false, string borrowerName = " ");

    // 获取书籍信息
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    bool getIsBorrowed() const { return isBorrowed; }
    string getBorrowerName() const { return borrowerName; }

    // 设置书籍信息
    void setTitle(const string& title) { this->title = title; }
    void setAuthor(const string& author) { this->author = author; }
    void setISBN(const string& isbn) { this->ISBN = isbn; }
    void setIsBorrowed(bool borrowed) { isBorrowed = borrowed; }
    void setBorrowerName(const string& name) { borrowerName = name; }

    // 重载输出运算符
    friend ostream& operator<<(ostream& out, const BookNode& book);

    // 声明友元类
    friend class CategoryNode;
};

// 重载输出运算符的实现
ostream& operator<<(ostream& out, const BookNode& book);

class CategoryNode {
private:
    string categoryName;
    LinkList<BookNode> listBooks;

public:
    // 无参构造函数
    CategoryNode();

    // 有参构造函数
    CategoryNode(const string& name, LinkList<BookNode>& listBooks);

    //添加类别
    CategoryNode addCategory(string category);

    // 向类别中添加书籍
    void addBook(BookNode* book);

    // 查找书籍
    BookNode* findBookByISBN(const string& isbn);

    // 借书操作
    bool borrowBookByISBN(const string& isbn, const string& borrower);

    // 还书操作
    bool returnBookByISBN(const string& isbn);

    // 插入新书
    //void insertBook(const string& title, const string& author, const string& isbn);

    // 删除书籍
    void deleteBookByISBN(const string& isbn);

    // 查询书籍状态
    bool queryBookStatus(const string& isbn);

    // 输出类别中的所有书籍信息
    void printBooks(const string &category) const;

    // 获取类别名称
    // string getCategoryName() const { return categoryName; }

    // 输出所有书籍信息
    static void printAllBooks( LinkList<CategoryNode>& categories);
};

#endif
#pragma once
