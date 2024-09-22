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
    // �޲ι��캯��
    BookNode();

    // �вι��캯��
    BookNode(const string& title, const string& category, const string& author, const string& isbn, bool isBorrowed = false, string borrowerName = " ");

    // ��ȡ�鼮��Ϣ
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    string getCategory() const { return category; }
    bool getIsBorrowed() const { return isBorrowed; }
    string getBorrowerName() const { return borrowerName; }

    // �����鼮��Ϣ
    void setTitle(const string& title) { this->title = title; }
    void setAuthor(const string& author) { this->author = author; }
    void setISBN(const string& isbn) { this->ISBN = isbn; }
    void setIsBorrowed(bool borrowed) { isBorrowed = borrowed; }
    void setBorrowerName(const string& name) { borrowerName = name; }

    // ������������
    friend ostream& operator<<(ostream& out, const BookNode& book);

    // ������Ԫ��
    friend class CategoryNode;
};

// ��������������ʵ��
ostream& operator<<(ostream& out, const BookNode& book);

class CategoryNode {
private:
    string categoryName;
    LinkList<BookNode> listBooks;

public:
    // �޲ι��캯��
    CategoryNode();

    // �вι��캯��
    CategoryNode(const string& name, LinkList<BookNode>& listBooks);

    //������
    //CategoryNode addCategory(string category);

    //�޸����
    void changeCategory(string category){categoryName = category;};

    // �����������鼮
    void addBook(BookNode* book);

    // �����鼮
    BookNode* findBookByISBN(const string& isbn);

    // �������
    bool borrowBookByISBN(const string& isbn, const string& borrower);

    // �������
    bool returnBookByISBN(const string& isbn);

    // ��������
    //void insertBook(const string& title, const string& author, const string& isbn);

    // ɾ���鼮
    void deleteBookByISBN(const string& isbn);

    // ��ѯ�鼮״̬
    bool queryBookStatus(const string& isbn);

    // �������е������鼮��Ϣ
    void printBooks(const string &category) const;

    //��ȡ�������
    string getCategoryName() const { return categoryName; }

    // ��������鼮��Ϣ
    void printAllBooks();

};

#endif
#pragma once
