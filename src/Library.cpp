#include<iostream>
#include"LinkList.h"
#include"Library.h"
#include<string>


BookNode::BookNode()
    : title(""), category(""), author(""), ISBN(""), isBorrowed(false), borrowerName("") {}

BookNode::BookNode(const string& title, const string& category, const string& author, const string& isbn, bool isBorrowed, string borrowerName)
    : title(title), category(category), author(author), ISBN(isbn), isBorrowed(isBorrowed), borrowerName(borrowerName) {}

CategoryNode::CategoryNode()
    : categoryName(" "), listBooks() {}

CategoryNode::CategoryNode(const std::string& name, LinkList<BookNode>& listBooks)
    : categoryName(name), listBooks(listBooks) {}

// CategoryNode CategoryNode::addCategory(string category)
// {
//     CategoryNode newcategory;
//     newcategory.categoryName = category;
//     return newcategory;
// }

void CategoryNode::addBook(BookNode* book)
{
    listBooks.Append(*book);
}

BookNode* CategoryNode::findBookByISBN(const std::string& isbn)
{
    int num = listBooks.NumNodes();
    for (int i = 0; i < num; ++i) 
    {
        listBooks.Go(i);
        if (listBooks.CurData().getISBN() == isbn) 
        {
            return &listBooks.CurData();
        }
    }
    return nullptr;
}
bool CategoryNode::borrowBookByISBN(const std::string& isbn, const std::string& borrower)
{
    BookNode* book = findBookByISBN(isbn);
    if (book != nullptr && !book->getIsBorrowed()) 
    {
        book->setIsBorrowed(true);
        book->setBorrowerName(borrower);
        return true;
    }
    return false;
}
bool CategoryNode::returnBookByISBN(const std::string & isbn) {
     BookNode* book = findBookByISBN(isbn);
     if (book != nullptr && book->getIsBorrowed()) 
     {
         book->setIsBorrowed(false);
         book->setBorrowerName("");
         return true;
     }
     return false;
    }


void CategoryNode::deleteBookByISBN(const std::string& isbn)
{
    BookNode* book = findBookByISBN(isbn);
    if (book != nullptr)
    {
        int pos = listBooks.CurPos();
        listBooks.GoTop();
        while (listBooks.CurPos() != pos)
        {
            listBooks.Skip(1);
        }
        listBooks.DeleteCurNode();
    }
}

bool CategoryNode::queryBookStatus(const std::string& isbn)
{
    BookNode* book = findBookByISBN(isbn);
    if (book != nullptr)
    {
        cout << *book << endl;
        return book->getIsBorrowed();
    }
    return false;
}

void CategoryNode::printBooks(const std::string& category)
{
    if (categoryName == category)
    {
        // listBooks.ShowList();
        printf("---%s---\n",category.c_str());
        int n = listBooks.NumNodes();
        for(int i=0;i<n;i++)
        {
            listBooks.Go(i);
            if(listBooks.CurNode() != nullptr)
            {
                const BookNode book = listBooks.CurData();
                printf("%d:\n书名:%s\t类别:%s\t作者:%s\nISBN:%s\t是否被借阅:%s\t%s%s\n",i+1,book.getTitle().c_str(),book.getCategory().c_str()
                ,book.getAuthor().c_str(),book.getISBN().c_str(),book.getIsBorrowed()?"是":"否",book.getIsBorrowed()?"借阅人姓名:":"",book.getIsBorrowed()?book.getBorrowerName().c_str():"");
            }
        }
    }
}

void CategoryNode::printAllBooks()
{
    printf("---%s---\n",categoryName.c_str());
    int n = listBooks.NumNodes();
    for(int i=0;i<n;i++)
    {
        listBooks.Go(i);
        if(listBooks.CurNode() != nullptr)
        {
            const BookNode book = listBooks.CurData();
            printf("%d:\n书名:%s\t类别:%s\t作者:%s\nISBN:%s\t是否被借阅:%s\t%s%s\n",i+1,book.getTitle().c_str(),book.getCategory().c_str()
            ,book.getAuthor().c_str(),book.getISBN().c_str(),book.getIsBorrowed()?"是":"否",book.getIsBorrowed()?"借阅人姓名:":"",book.getIsBorrowed()?book.getBorrowerName().c_str():"");
        }
    }
}


bool CategoryNode::checkRepaetByISBN(string checkISBN)
{
    int n = listBooks.NumNodes();
    for(int i=0;i<n;i++)
    {
        listBooks.Go(i);
        if(listBooks.CurData().getISBN() == checkISBN)
            return true;
    }
    return false;
}


ostream& operator<<(ostream& out, const BookNode& book) {
    out << "Title: " << book.title << "Category: " << book.category << ", Author: " << book.author << ", ISBN: " << book.ISBN
        << ", Borrowed: " << (book.isBorrowed ? "Yes" : "No") << ", Borrower: " << book.borrowerName;
    return out;
}