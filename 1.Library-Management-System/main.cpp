#include<bits/stdc++.h>
using namespace std;
class Book{

    public:
    string title;
    string author;

    //constuctors
    
    Book(string title_inp,string author_inp,string isbn_inp,
          int copies_available_inp,int tc_inp)  //normal constrctor
    {
        title=title_inp;
        author=author_inp;
        isbn=isbn_inp;
        copies_available=copies_available_inp;
        total_copies=tc_inp;
    }
    Book(){                         //defaultconstructor
        title="UnknownTitle";
        author="UnknownAuthor";
        isbn="ISBN";
        copies_available=0;
        total_copies=5;
    }
    Book(Book b,string isbn_inp){   //copyconstructor
        title=b.title;
        author=b.author;
        isbn=isbn_inp;
        copies_available=b.copies_available;
        total_copies=b.total_copies;
    }

    //getters
    string getisbn(){ return isbn; }
    int getCopies_available() {return copies_available;}
    int gettotal_copies() {return total_copies;}
    
    //setters
    void updatecopies(int count){
        if(count+total_copies<0) {cout<<"Invalid request! Count becomes negative"<<'\n';}
        else if(count+copies_available<0) {cout<<"Invalid request! Count becomes negative"<<'\n';}
        else{
            total_copies+=count;
            copies_available+=count;
        }    
    }
    
    //utilitymethods
    bool borrow_book(){
        if(copies_available==0) {cout<<"Invalid request! Copy of book not available"<<'\n'; return false;}
        copies_available--;
        return true; 
    }
    bool return_book(){
        if(copies_available==total_copies) {
            cout<<"Invalid request! Copy of book exceeds total copies"<<'\n';
            return false;
            }
        copies_available++;
        return true;
    }
    void print_details(){
        cout<<title<<" "<<author<<'\n';
    }


    private:
    string isbn;
    int copies_available;
    int total_copies;


};


class Member{

    public:
    string name;
    Member(string memberid_inp="",string name_inp="",int borrowlimit_inp=3){
        member_id=memberid_inp;
        name=name_inp;
        borrow_limit=borrowlimit_inp;
    }
    // Member(string memberid_inp,string name_inp){
    //     member_id=memberid_inp;
    //     name=name_inp;
    //     borrow_limit=3;
    // }

    string getmember_id(){return member_id;}
    //utility methos
    bool borrow_book(string isbn){
        int borrowedbooks_count=0;
        for(auto book:borrowed_books){
            borrowedbooks_count+=book.second;
        }
        if(borrowedbooks_count==borrow_limit) {
            cout<<"Invalid request! Borrow limit exceeded"<<'\n';
            return false;
        }
        borrowed_books[isbn]++;
        return true;
    }
    bool return_book(string isbn){
        if(borrowed_books.find(isbn)==borrowed_books.end()||
            borrowed_books.size()==0){
            cout<<"Invalid request! Book not borrowed"<<'\n';
            return false;
        }
        if(borrowed_books[isbn]==1) borrowed_books.erase(isbn);
        else borrowed_books[isbn]--;
        return true;
    }
    void printdetails(){
        if(borrowed_books.size()>0){
            
            for(auto book:borrowed_books){
                cout<<member_id<<" "<<name<<" ";
                cout<<book.first<<' '<<book.second<<'\n';
            }
        }
    }

    private:
    string member_id;
    map<string,int> borrowed_books;
    int borrow_limit;

};
class Library{
    private:
    vector<Book> books;
    vector<Member> members;

    public:
    //
    Book * getbookbyisbn(string isbn){
        Book *b=new Book;
        for(Book & a:books){
            if(a.getisbn()==isbn) return &a; 
        }
        return b;
    }

    Member * getmemberbyid(string memberid){
        Member*m=new Member;
        for(auto & a:members){
            if(a.getmember_id()==memberid) return &a;
            }return m;
    }
    //uitlity methods
    
    bool add_book(Book& b){
        for(auto a:books){
            
            if(a.getisbn()==b.getisbn()) {
                cout<<"Invalid request! Book with same isbn already exists"<<'\n';
                return false;
            }
        
        }
        books.push_back(b);
        return true;
    }
    
    
    bool registerMember(Member& m){
        for(auto a:members){
            if(a.getmember_id()==m.getmember_id()){
                cout<<"Invalid request! Member with same id already exists"<<'\n';
                return false;
            }
        }
        members.push_back(m);
        return true;
    }
    
    
    bool borrowBook(string memberID, string isbn){
        bool there;
        int i=0;
        for(auto & b:books){
            if(b.getisbn()==isbn) {
                there=b.borrow_book();
                //b.print_details();
                break;
            }
            i++;
        }
        if(!there) return false;
        bool possible=false;
        for(auto & m:members){
            if(m.getmember_id()==memberID){
                possible = m.borrow_book(isbn);
                break;
            }
         }
         if(!possible){
            books[i].return_book();
         }
         return possible;
    }
    
    
    bool returnBook(string memberID, string isbn){
        bool possible=false;
        int i=0;
        
        for(auto & b:books){
            if(b.getisbn()==isbn) {
                possible=b.return_book();
                break;
            }
            i++;
        }
        if(!possible) return false;
        int j=0;
        for(auto & m:members){
            if(m.getmember_id()==memberID){
                possible = m.return_book(isbn);
                break;
            }
              j++;
         } 
         if(!possible) {
            books[i].borrow_book();
         }
         return possible;
    }

    void printLibraryDetails(){
        for(auto b:books){
            cout<<b.title<<' '<<b.author<<' '<<b.getCopies_available()<<'\n';
        }
        for(auto m:members){
            cout<<m.getmember_id()<<' '<<m.name<<'\n';
        }
    }
};
int main(){

    Library IITM_library;
    string str;

    cin>>str;
    while(str!="Done"){

        if(str=="Book"){                                //adding book
            string s1;
            cin>>s1;
            if(s1=="None"){
                Book *b=new Book();
                IITM_library.add_book(*b);
            }
            else if(s1=="ExistingBook"){
                string oldisbn,newisbn;
                cin>>oldisbn>>newisbn;
                Book *b=IITM_library.getbookbyisbn(oldisbn);
                Book * copiedbook=new Book(*b,newisbn);
                IITM_library.add_book(*copiedbook);
            }
            else{
                string author,isbn;
                cin>>author>>isbn;
                int copies_available,total_copies;
                cin>>copies_available>>total_copies;
                Book *b=new Book(s1,author,isbn,copies_available,total_copies);
                 IITM_library.add_book(*b);
            }
        }

        else if(str=="UpdateCopiesCount"){              // upadating count of book
            string isbn;
            int new_count;
            cin>>isbn>>new_count;
            Book * b=IITM_library.getbookbyisbn(isbn);
            b->updatecopies(new_count);
        }

        else if(str=="Member"){                         //registering member
            string s1;
            cin>>s1;
            if(s1=="NoBorrowLimit"){
                string memberid,name;
                cin>>memberid>>name;
                Member *m=new Member(memberid,name);
                IITM_library.registerMember(*m);
            }
            else {
                string name;
                int borrowlimit;
                cin>>name>>borrowlimit;
                Member *m=new Member(s1,name,borrowlimit);
                IITM_library.registerMember(*m);
            }
        }

        else if(str=="Borrow"){                         //borrowing book
            string memberid,isbn;
            cin>>memberid>>isbn;
            IITM_library.borrowBook(memberid,isbn);
        }

        else if(str=="Return"){                             //returning book
            string memberid,isbn;
            cin>>memberid>>isbn;
            IITM_library.returnBook(memberid,isbn);
        }

        else if(str=="PrintBook"){                         //printing book
            string isbn;
            cin>>isbn;
            IITM_library.getbookbyisbn(isbn)->print_details();
        }

        else if(str=="PrintMember"){                      //printing member
            string memberid;
            cin>>memberid;
            Member * m=IITM_library.getmemberbyid(memberid);
            m->printdetails();
        }

        else if(str=="PrintLibrary"){
            IITM_library.printLibraryDetails();
        }

        cin>>str;
    
    }
}