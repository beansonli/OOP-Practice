/******************************************************************************
# Question 1 — Digital Library System

Create a class `Book`.

## Private Data Members
- `int bookID`
- `string title`
- `string author`
- `bool issued`
- `static int bookCounter`

## Requirements
- Implement a constructor that assigns `bookID` automatically using `bookCounter`.
- Implement a parameterized constructor to initialize title and author.
- Implement a copy constructor.
- Implement a `const` member function `displayBook()` that prints all details.
- Implement functions:
  - `issueBook()`
  - `returnBook()`
- Implement a static member function `getTotalBooks()`.

## In main()
- Create an **array of Book objects**.
- Issue some books and display their status.

*******************************************************************************/

#include <iostream>
using namespace std;

class Book{
    private:
    static int bookCounter;
    int bookID;
    string title, author;
    bool issued;
    
    public:
    
    Book(string Title, string Author){
        title=Title;
        author=Author;
        ++bookCounter;
        bookID=bookCounter;
    }
    
    Book(Book &book){
        title=book.title;
        author= book.author;
        bookID= book.bookID;
    }
    
    void displayBook() const{
        cout<<"\nBook ID: "<<bookID<<endl;
        cout<<"Title: "<<title<<endl;
        cout<<"Author :"<<author<<endl;
        cout<<"Issued: "<<issued<<endl;
    }
    
    static int getTotalBooks(){
        return bookCounter;
    }
    
    void issueBook(){
        issued=true;
    }
    
    void returnBook(){
        issued=false;
    }
};

int Book::bookCounter=0;

int main(){
    Book *books[5];
    string title, author;
    
    for(int i=0; i<5; i++){
        cout<<"\nEnter title: ";
        cin>>title;
        cout<<"Enter author: ";
        cin>>author;
        
        books[i]= new Book(title, author);
    }
    
    books[2]->issueBook();
    books[4]->issueBook();
    
    for(int i=0; i<5; i++)
        books[i]->displayBook();
    
    books[2]->returnBook();
    
    Book b(*books[3]);
    
    for(int i=0; i<5; i++)
        books[i]->displayBook();
    
    b.displayBook();
    
    cout<<"\nTotal books: "<<Book::getTotalBooks()<<endl;
    
    return 0;
}
