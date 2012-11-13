#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>

using namespace std;

#define AUTHORS "files/authors.txt"
#define BOOKS "files/books.txt"
#define PUBLISHERS "files/publishers.txt"
#define LAST_ID "files/last_id.txt"
#define REMOVED_AUTHOR "files/removed_author.txt"
#define REMOVED_BOOK "files/removed_book.txt"
#define REMOVED_PUBLISHER "files/removed_publisher.txt"
#define BOOK_AUTHOR "files/book_author.txt"
#define BOOK_PUBLISHER "files/book_publisher.txt"
#define REMOVED_BA "files/removed_BA.txt"
#define REMOVED_BP "files/removed_BP.txt"

//------------------------------------------------------------------------------


// declaration of the functions

void check_stream(char *s) {
    fstream stream(s);
    if (!stream) {
        cerr << "Невозможно открыть файл " << s << endl
             << "Обратитесь к администратору!" << endl;
        exit(1);
    }
    stream.close();
}

long long create_id(string choice, ifstream &inRemoved) {
    ifstream inLastId(LAST_ID, ios::in);
    
    long long author_id, book_id, publisher_id;

    int inFileSize;
    
    inRemoved.seekg(0, ios::end);
    inFileSize = static_cast <int> (inRemoved.tellg());
            
    if (inFileSize != 0) {
        inRemoved.seekg(0);
        
        long long removed_id;
        long long r;
        vector <long long> removedId;
        
        inRemoved >> removed_id;
        
        if (choice == "author") author_id = removed_id;
        if (choice == "book") book_id = removed_id;
        if (choice == "publisher") publisher_id = removed_id;
        
        while (inRemoved >> r)
            removedId.push_back(r);
              
        if (choice == "author") {
            ofstream outRemovedAuthor(REMOVED_AUTHOR);
            check_stream(REMOVED_AUTHOR);
            
            for (int i = 0; i < removedId.size(); i++)
                outRemovedAuthor << removedId[i] << endl;
        }
        if (choice == "book") {
            ofstream outRemovedBook(REMOVED_AUTHOR);
            check_stream(REMOVED_AUTHOR);
            
            for (int i = 0; i < removedId.size(); i++)
                outRemovedBook << removedId[i] << endl;
        }
        if (choice == "publisher") {
            ofstream outRemovedPublisher(REMOVED_BOOK);
            check_stream(REMOVED_BOOK);
            
            for (int i = 0; i < removedId.size(); i++)
                outRemovedPublisher << removedId[i] << endl;
        }
    }
    else {
        inLastId >> author_id >> book_id >> publisher_id;
        
        if (choice == "author") author_id++;
        if (choice == "book") book_id++;
        if (choice == "publisher") publisher_id++;
        
        ofstream outLastId(LAST_ID);
        
        check_stream(LAST_ID);
        
        outLastId << author_id << endl
              << book_id << endl
              << publisher_id;
    }
    
    if (choice == "author") return author_id;
    if (choice == "book") return book_id;
    if (choice == "publisher") return publisher_id;
}

int enter_choice() {
    int menuChoice;
    string choice = " ";
    while (!(atoi(choice.c_str())) && choice != "0") {
        cout << endl << "Выберите, что будем изменять:" << endl
             << "1 - название" << endl
             << "2 - год издания" << endl
             << "3 - ISBN" << endl
             << "4 - ББК" << endl
             << "5 - обложка" << endl
             << "6 - аннотация" << endl
             << "0 - назад" << endl;
   
        cin >> choice;
    }
    
    return menuChoice = menuChoice = atoi(choice.c_str());
}

//------------------------------------------------------------------------------

// structurka

struct Id {
    long long book_id;
    long long relation_id;
};

//------------------------------------------------------------------------------

// parent class

class ClassWithId {
public:
    long long id;
};

//------------------------------------------------------------------------------


// descendants of the parent class

class Author : public ClassWithId {
public:
    Author(char *);
    Author();
    char author_name[30];
};

Author::Author(char *author_name) {
    strcpy(Author::author_name, author_name);
}

Author::Author() {
   
}

//------------------------------------------------------------------------------

class Book : public ClassWithId {
public:
    Book(char *, int, char *, char *, bool, char *);
    Book();
    char book_name[20];
    int book_release_year;
    char ISBN[13];
    char BBK[15];
    bool cover;
    char annotation[100];
};

Book::Book(char *book_name, int book_release_year, char *ISBN, char *BBK, bool cover, char *annotation) {
    strcpy(Book::book_name, book_name);
    Book::book_release_year = book_release_year;
    strcpy(Book::ISBN, ISBN);
    strcpy(Book::BBK, BBK);
    Book::cover = cover;
    strcpy(Book::annotation, annotation);
}

Book::Book() {

}

//------------------------------------------------------------------------------

class Publisher : public ClassWithId {
public:
    Publisher(char *);
    Publisher();
    char publisher_name[20];
};

Publisher::Publisher(char *publisher_name) {
    strcpy(Publisher::publisher_name, publisher_name);
}

Publisher::Publisher() {

}

//------------------------------------------------------------------------------

// check

bool CheckBook_AuthorRelation(long long book_id, long long author_id) {
    ifstream inLastId(LAST_ID, ios::in);
    ifstream inBook(BOOKS, ios::in);
    ifstream inAuthor(AUTHORS, ios::in);

    check_stream(LAST_ID);
    check_stream(BOOKS);
    check_stream(AUTHORS);

    Book book;
    Author author;

    long long author_last_id, book_last_id;
    inLastId >> author_last_id >> book_last_id;

    inBook.seekg((book_id - 1) * sizeof(book));
    inBook.read((char *) &book, sizeof(book));

    inAuthor.seekg((author_id - 1) * sizeof(author));
    inAuthor.read((char *) &author, sizeof(author));

    if ((strcmp(book.book_name, " ") != 0) && (book_id <= book_last_id) && (book_id > 0) && (strcmp(author.author_name, " ") != 0) && (author_id <= author_last_id) && (author_id > 0))
        return true;
    else return false;
}

bool CheckBook_PublisherRelation(long long book_id, long long publisher_id) {
    ifstream inLastId(LAST_ID, ios::in);
    ifstream inBook(BOOKS, ios::in);
    ifstream inPublisher(PUBLISHERS, ios::in);

    check_stream(LAST_ID);
    check_stream(AUTHORS);
    check_stream(PUBLISHERS);

    Book book;
    Publisher publisher;
    
    long long book_last_id;
    long long publisher_last_id;
    inLastId >> book_last_id >> book_last_id >> publisher_last_id;

    inBook.seekg((book_id - 1) * sizeof(book));
    inBook.read((char *) &book, sizeof(book));

    inPublisher.seekg((publisher_id - 1) * sizeof(publisher));
    inPublisher.read((char *) &publisher, sizeof(publisher));

    if ((strcmp(book.book_name, " ") != 0) && (book_id <= book_last_id) && (book_id > 0) && (strcmp(publisher.publisher_name, " ") != 0) && (publisher_id <= publisher_last_id) && (publisher_id > 0))
        return true;
    else return false;
}

bool CheckAuthor(long long author_id, Author author) {
    fstream inAuthor(AUTHORS, ios::in);
    ifstream inLastId(LAST_ID);
    
    check_stream(AUTHORS);
    check_stream(LAST_ID);
    
    long long last_id;
    inLastId >> last_id;

    inAuthor.seekg((author_id - 1) * sizeof(author));
    inAuthor.read((char *) &author, sizeof(author));
    
    if ((author_id <= last_id) && (author_id > 0) && (strcmp(author.author_name, " ") != 0)) return true;
    else return false;
}

bool CheckBook(long long book_id, Book book) {
    ifstream inBook(BOOKS, ios::in);
    ifstream inLastId(LAST_ID);
    
    check_stream(BOOKS);
    check_stream(LAST_ID);
    
    long long last_id;
    inLastId >> last_id >> last_id;

    inBook.seekg((book_id - 1) * sizeof(book));
    inBook.read((char *) &book, sizeof(book));
    
    if ((book_id <= last_id) && (book_id > 0) && (strcmp(book.book_name, " ") != 0)) return true;
    else return false;
}

bool CheckPublisher(long long publisher_id, Publisher publisher) {
    ifstream inPublisher(PUBLISHERS, ios::in);
    ifstream inLastId(LAST_ID, ios::in);
    
    check_stream(BOOKS);
    check_stream(LAST_ID);
    
    long long last_id;
    inLastId >> last_id >> last_id >> last_id;

    inPublisher.seekg((publisher_id - 1) * sizeof(publisher));
    inPublisher.read((char *) &publisher, sizeof(publisher));
    
    if ((publisher_id <= last_id) && (publisher_id > 0) && (strcmp(publisher.publisher_name, " ") != 0)) return true;
    else return false;
}

bool noBook_AuthorRelation(Id x) {
    bool notExist = true;

    ifstream inBook_Author(BOOK_AUTHOR, ios::in);

    check_stream(BOOK_AUTHOR);

    Id x1;

    int i = 0;
    while (!inBook_Author.eof()) {
        inBook_Author.seekg(i * sizeof(x1));
        inBook_Author.read((char *) &x1, sizeof(x1));

        if (x.book_id == x1.book_id && x.relation_id == x1.relation_id) {
            notExist = false;
            break;
        }

        i++;
    }

    return notExist;
}

bool noBook_PublisherRelation(Id x) {
    bool notExist = true;

    ifstream inBook_Publisher(BOOK_PUBLISHER, ios::in);

    check_stream(BOOK_PUBLISHER);

    Id x1;

    int i = 0;
    while (!inBook_Publisher.eof()) {
        inBook_Publisher.seekg(i * sizeof(x1));
        inBook_Publisher.read((char *) &x1, sizeof(x1));

        if (x.book_id == x1.book_id && x.relation_id == x1.relation_id) {
            notExist = false;
            break;
        }

        i++;
    }

    return notExist;    
}

//------------------------------------------------------------------------------


// _Mng classes

class Author_Mng {
public:
    static long long create_author();
    static long long delete_author(long long);
    static long long replace_author(long long);
    static long long show_author(long long);
};

long long Author_Mng::create_author() {
    fstream inOutAuthor(AUTHORS, ios::in | ios::out);
    ofstream outBook_Author(BOOK_AUTHOR, ios::app);
    ifstream inRemovedAuthor(REMOVED_AUTHOR, ios::in);
   
    check_stream(AUTHORS);
    check_stream(BOOK_AUTHOR);
    check_stream(REMOVED_AUTHOR);
    
    Author author;
    string str_name;
    
    cin.ignore();
    
    cout << endl << "Введите:" << endl;
    
    cout << "Имя автора" << endl;
    getline(cin, str_name);

    if (str_name == "0") {
        cout << "Отмена операции" << endl;
        return 0;
    }

    for (int i = 0; i < 30; i++) author.author_name[i] = str_name[i];

    author.id = create_id("author", inRemovedAuthor);
    
    inOutAuthor.seekp((author.id - 1) * sizeof(author));
    inOutAuthor.write((char *) &author, sizeof(author));

    cout << "Запись успешно создана." << endl;
    
    string choice = " ";
    while (!(atoi(choice.c_str()))) {
        cout << "Создать связь? (1 - да, 2 - нет):" << endl;

        cin >> choice;

        if (choice == "1" || choice == "2") {}
        else choice = " "; 
    }
    
              
        if (choice == "1") {
            choice = " ";

            while (!(atoi(choice.c_str())) && choice != "0") {
                cout << "Введите Id книги, с которой будет создана связь:" << endl;
                cin >> choice;
            } 

                Id x;
                x.relation_id = author.id;
                x.book_id = atoi(choice.c_str());

                if (choice == "0") {
                    cout << "Отмена операции" << endl;
                    return 0;
                }

                bool checked = CheckBook_AuthorRelation(x.book_id, author.id);
                                    
                if (checked == true) {
                    outBook_Author.write((char *) &x, sizeof(x));
                    cout << "Связь успешно создана." << endl;
                }
                else cout << "Книга не существует!" << endl;
        }

    return author.id;
}

long long Author_Mng::delete_author(long long id) { 
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    fstream inOutAuthor(AUTHORS, ios::in |ios::out);
    ofstream outRemovedAuthor(REMOVED_AUTHOR, ios::app);
    fstream inOutLastId(LAST_ID);
    
    check_stream(AUTHORS);
    check_stream(REMOVED_AUTHOR);
    check_stream(LAST_ID);
    
    long long last_id;
    inOutLastId >> last_id;
    
    Author author;
    
    inOutAuthor.seekg((id - 1) * sizeof(author));
    inOutAuthor.read((char *) &author, sizeof(author));
    inOutAuthor.clear();
 
    if ((strcmp(author.author_name, " ") != 0) && (id <= last_id) && (id > 0)) {
        Author author(" ");
        
        inOutAuthor.seekp((id - 1) * sizeof (author));
        inOutAuthor.write((char *) &author, sizeof (author));

        cout << "Запись " << id << " удалена" << endl;
        outRemovedAuthor << id << endl;
    }
    else cout << "Запись не существует" << endl;
}

//------------------------------------------------------------------------------

long long Author_Mng::replace_author(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    fstream inOutAuthor(AUTHORS, ios::in | ios::out);
    ifstream inLastId(LAST_ID, ios::in);

    check_stream(AUTHORS);
    
    Author author;
    string str_name;
    long long last_id;

    inLastId >> last_id;

    cin.ignore();
    
    inOutAuthor.seekg((id - 1) * sizeof(author));
    inOutAuthor.read((char *) &author, sizeof(author));

    if ((strcmp(author.author_name, " ") != 0) && (id <= last_id) && (id > 0)) { 
        cout << "Введите новое имя автора" << endl;
    
        getline(cin, str_name);
        for (int i = 0; i < 30; i++) author.author_name[i] = str_name[i];
    
        inOutAuthor.seekp((id - 1) * sizeof(author));
        inOutAuthor.write((char *) &author, sizeof(author));

        cout << "Запись успешно изменена." << endl;
    }
    else cout << "Запись не существует" << endl;
}

long long Author_Mng::show_author(long long id) {
    if (id == 0) {
        cout << "Операция отменена" << endl;
        return 0;
    }

    fstream inAuthor(AUTHORS, ios::in);
    check_stream(AUTHORS);

    Author author;

    bool checked = CheckAuthor(id, author);

    if (checked == true) {
        inAuthor.seekg((id - 1) * sizeof(author));
        inAuthor.read((char *) &author, sizeof(author));

        cout << "id: " << author.id << endl
             << "Имя автора: " << author.author_name << endl;
    }
    else cout << "Автор не существует!" << endl;
}

//------------------------------------------------------------------------------

class Book_Mng {
public:
    static long long create_book();
    static long long delete_book(long long);
    static long long replace_book(long long);
    static long long show_book(long long);
};

long long Book_Mng::create_book() {
    fstream inOutBook(BOOKS, ios::in | ios::out);
    ofstream outBook_Author(BOOK_AUTHOR, ios::app);
    ofstream outBook_Publisher(BOOK_PUBLISHER, ios::app);
    ifstream inRemovedBook(REMOVED_BOOK);

    check_stream(BOOKS);
    check_stream(BOOK_AUTHOR);
    check_stream(BOOK_PUBLISHER);
    check_stream(REMOVED_BOOK);
            
    Book book;
    string str_name, str_year, str_ISBN, str_BBK, str_cover, str_annotation;
    
    cin.ignore();
    
    cout << endl << "Введите:" << endl;

    cout << "Название книги" << endl << "? ";
    getline(cin, str_name);

    if (str_name == "0") {
        cout << "Отмена операции" << endl;
        return 0;
    }

    for (int i = 0; i < 20; i++) book.book_name[i] = str_name[i];
    
    str_year = " ";
    while (!(atoi(str_year.c_str()))) {
        cout << "Год издания" << endl << "? ";
        cin >> str_year;

        if (str_year == "0") {
            cout << "Отмена операции" << endl;
            return 0;
        }
        if (atoi(str_year.c_str()) > 2012 || atoi(str_year.c_str()) < 1400) str_year = " ";
    }
    
    cin.ignore();
    
    cout << "ISBN" << endl << "? ";
    getline(cin, str_ISBN);

    if (str_ISBN == "0") {
        cout << "Отмена операции" << endl;
        return 0;
    }

    for (int i = 0; i < 13; i++) book.ISBN[i] = str_ISBN[i];

    cout << "ББК" << endl << "? ";
    getline(cin, str_BBK);

    if (str_BBK == "0") {
        cout << "Отмена операции" << endl;
        return 0;
    }

    for (int i = 0; i < 10; i++) book.BBK[i] = str_BBK[i];

    str_cover = " ";
    
    while (!atoi(str_cover.c_str())) {
        cout << "Супер-обложка (1 - есть; 2 - нет)" << endl << "? ";
        cin >> str_cover;

        if (str_cover == "0") {
            cout << "Отмена оперции" << endl;
            return 0;
        } 

        if (str_cover != "1" && str_cover != "2") str_cover = " ";
    }

    book.cover = atoi(str_cover.c_str());

    cin.ignore();

    cout << "Аннотация" << endl << "? ";
    getline(cin, str_annotation);

    if (str_annotation == "0") {
        cout << "Отмена операции" << endl;
        return 0;
    }

    for (int i = 0; i < 100; i++) book.annotation[i] = str_annotation[i];

    book.id = create_id("book", inRemovedBook);
    
    inOutBook.seekp((book.id - 1) * sizeof(book));
    inOutBook.write((char *) &book, sizeof(book));

    cout << "Книга успешно создана." << endl;
    
    int choice;
    string str_choice = " ";

    while (!(atoi(str_choice.c_str()))) {
        cout << "Создать связь (1 - да, 2 - нет)" << endl;
        cin >> str_choice;

        if (str_choice != "1" && str_choice != "2") str_choice = " ";
    }

    choice = atoi(str_choice.c_str()); 
    
    if (choice == 1) {
        int next_choice;
        str_choice = " ";

        while (!(atoi(str_choice.c_str()))) {
            cout << "Связь с 1 - автором, 2 - издательством" << endl;
            cin >> str_choice;

            if (str_choice == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }

            if (str_choice != "1" && str_choice != "2") str_choice = " ";
        }

        next_choice = atoi(str_choice.c_str());

        bool checked;

        switch (next_choice) {
            case 1:
                str_choice = " ";
                while (!(atoi(str_choice.c_str()))) {
                    cout << "Введите Id автора, с которым будет создана связь:" << endl;
                    cin >> str_choice;

                    if (str_choice == "0") {
                        cout << "Отмена операции" << endl;
                        return 0;
                    }
                }
                  
                Id x;
                x.book_id = book.id;
                x.relation_id = atoi(str_choice.c_str());

                checked = CheckBook_AuthorRelation(x.book_id, x.relation_id);

                if (checked == true) {
                    outBook_Author.write((char *) &x, sizeof(x));
                    cout << "Связь успешно создана." << endl;
                }
                else cout << "Автор не существует!" << endl;
                
                break;
                
            case 2:
                str_choice = " ";

                while (!(atoi(str_choice.c_str()))) {
                    cout << "Введите Id издательства, с которым будет создана связь:" << endl;
                    cin >> str_choice;

                    if (str_choice == "0") {
                        cout << "Отмена операции" << endl;
                        return 0;
                    }
                }
                
                Id x1;
                x1.book_id = book.id;
                x1.relation_id = atoi(str_choice.c_str());
                               
                checked = CheckBook_PublisherRelation(book.id, x1.relation_id);

                if (checked == true) {
                    outBook_Publisher.write((char *) &x1, sizeof(x1));
                    cout << "Связь успешно создана." << endl;
                }
                else cout << "Издательство не существует!" << endl;
                
                break;

            default:
                cout << "Ошибка ввода!" << endl;
                break;
        }
    }
            
    return book.id;
}

long long Book_Mng::delete_book(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    fstream inOutBook(BOOKS, ios::in |ios::out);
    ofstream outLastId(REMOVED_BOOK, ios::app);
    ifstream inLastId(LAST_ID);
    
    check_stream(BOOKS);
    check_stream(REMOVED_BOOK);
    check_stream(LAST_ID);
    
    long long last_id;
    inLastId >> last_id >> last_id;
    
    Book book;
    
    inOutBook.seekg((id - 1) * sizeof(book));
    inOutBook.read((char *) &book, sizeof(book));
    inOutBook.clear();
 
    if ((strcmp(book.book_name, " ") != 0) && (id <= last_id) && (id > 0)) {
        Book book(" ", 0, " ", " ", 0, " ");
        
        inOutBook.seekp((id - 1) * sizeof (book));
        inOutBook.write((char *) &book, sizeof (book));

        cout << "Запись " << id << " удалена" << endl;
        outLastId << id << endl;
    }
    else cout << "Запись не существует" << endl;
}

long long Book_Mng::replace_book(long long id) {
    if (id == 0) {
        cout << "Отмена оперции" << endl;
        return 0;
    }

    fstream inOutBook(BOOKS, ios::in | ios::out);
    ifstream inLastId(LAST_ID, ios::in);

    check_stream(LAST_ID);
    check_stream(BOOKS);
    
    Book book;
    int choice;
    int i;

    long long last_id;
    inLastId >> last_id >> last_id;

    inOutBook.seekg((id - 1) * sizeof(book));
    inOutBook.read((char *) &book, sizeof(book));

if ((strcmp(book.book_name, " ") != 0) && (id <= last_id) && (id > 0)) { 
            
    while ((choice = enter_choice()) != 0) {
      string str_name, str_year, str_ISBN, str_BBK, str_cover, str_annotation;
      
      switch (choice) {
          case 1: // new name
              cin.ignore();
              
              cout << "Введите новое название книги:" << endl;
              getline(cin, str_name);

              if (str_name == "0") {
                cout << "Отмена операции" << endl;
                break;
              }

              for (i = 0; i < 20; i++) book.book_name[i] = str_name[i];
              
              inOutBook.seekp((id - 1) * sizeof(book));
              inOutBook.write((char *) &book, sizeof(book));

              cout << "Запись успешно изменена." << endl;
              break;
          
          case 2: // new book_release_year
              str_year = " ";
              
              while (!(atoi(str_year.c_str()))) {
                cout << "Введите новый год издания:" << endl;
                cin >> str_year;

                if (str_year == "0") {
                    cout << "Отмена операции" << endl;
                    break;
                }

                if (atoi(str_year.c_str()) > 2012 && atoi(str_year.c_str()) < 1400) str_year = " ";
              }

              book.book_release_year = atoi(str_year.c_str());
              
              inOutBook.seekp((id - 1) * sizeof(book));
              inOutBook.write((char *) &book, sizeof(book));

              cout << "Запись успешно изменена." << endl;
              break;
              
          case 3: // new ISNB
              cin.ignore();
              
              cout << "Введите новый ISBN:" << endl;
              getline(cin, str_ISBN);

              if (str_ISBN == "0") {
                cout << "Отмена оперции" << endl;
                break;
              }

              for (i = 0; i < 13; i++) book.ISBN[i] = str_ISBN[i];
              
              inOutBook.seekp((id - 1) * sizeof(book));
              inOutBook.write((char *) &book, sizeof(book));

              cout << "Запись успешно изменена." << endl;
              break;
              
          case 4: // new BBK
              cin.ignore();

              cout << "Введите новый ББК:" << endl;
              getline(cin, str_BBK);

              if (str_BBK == "0") {
                cout << "Отмена операции" << endl;
                break; 
              }

              for (i = 0; i < 15; i++) book.BBK[i] = str_BBK[i];
              
              inOutBook.seekp((id - 1) * sizeof(book));
              inOutBook.write((char *) &book, sizeof(book));

              cout << "Запись успешно изменена." << endl;
              break;
              
          case 5: // new cover
              str_cover = " ";

              while (!(atoi(str_cover.c_str()))) {
                cout << "Изменеие обложки:" << endl;
                cin >> str_cover;

                if (str_cover == "0") {
                    cout << "Отмена операции" << endl;
                    break;
                }

                if (str_cover != "1" && str_cover != "2") str_cover = " ";
              }

              book.cover = atoi(str_cover.c_str());

              inOutBook.seekp((id - 1) * sizeof(book));
              inOutBook.write((char *) &book, sizeof(book));

              cout << "Запись успешно изменена." << endl;
              break;
              
          case 6: // new annotation
              cin.ignore();
              
              cout << "Введите новую аннотацию:" << endl;
              getline(cin, str_annotation);
              for (i = 0; i < 100; i++) book.annotation[i] = str_annotation[i];
              
              inOutBook.seekp((id - 1) * sizeof(book));
              inOutBook.write((char *) &book, sizeof(book));

              cout << "Запись успешно изменена." << endl;
              break;
              
          default:
              cout << "Ошибка ввода." << endl;
              break;
      }
    }
}
else cout << "Книга не существует" << endl;
}

long long Book_Mng::show_book(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    } 
    fstream inBook(BOOKS, ios::in);
    
    check_stream(BOOKS);
    
    Book book;

    bool checked = CheckBook(id, book);

    if (checked == true) {
        inBook.seekg((id - 1) * sizeof(book));
        inBook.read((char *) &book, sizeof(book));

    string cover;
    if (book.cover == 1) cover = "Есть";
    else cover = "Отсутствует";

        cout << "id: " << book.id << endl
             << "Название книги: " << book.book_name << endl
             << "Год издания: " << book.book_release_year << endl
             << "ISBN: " << book.ISBN << endl
             << "ББК: " << book.BBK << endl
             << "Супер-обложка: " << cover << endl
             << "Аннотация: " << book.annotation << endl;
    }
    else cout << "Книга не существует!" << endl;
}

//------------------------------------------------------------------------------

class Publisher_Mng {
public:
    static long long create_publisher();
    static long long delete_publisher(long long);
    static long long replace_publisher(long long);
    static long long show_publisher(long long);
};

long long Publisher_Mng:: create_publisher() {
    fstream inOutPublisher(PUBLISHERS, ios::in | ios::out);
    ofstream outBook_Publisher(BOOK_PUBLISHER, ios::app);
    ifstream inRemovedPublisher(REMOVED_PUBLISHER);
    
    check_stream(PUBLISHERS);
    check_stream(BOOK_PUBLISHER);
    check_stream(REMOVED_PUBLISHER);
    
    Publisher publisher;
    string str_name;
    
    cin.ignore();
    
    cout << endl << "Введите:" << endl;
    
    cout << "Название издательства:" << endl;
    getline(cin, str_name);
    for (int i = 0; i < 20; i++) publisher.publisher_name[i] = str_name[i];
    
    publisher.id = create_id("publisher", inRemovedPublisher);
    
    inOutPublisher.seekp((publisher.id - 1) * sizeof(publisher));
    inOutPublisher.write((char *) &publisher, sizeof(publisher));

    cout << "Запись успешно создана." << endl;
    
    int choice;
    string str_choice = " ";

    while (!(atoi(str_choice.c_str()))) {
        cout << "Создать связь? (1 - да, 2 - нет):" << endl;
        cin >> str_choice;

        if (str_choice != "1" && str_choice != "2") str_choice = " ";
    }

    choice = atoi(str_choice.c_str());
              
    if (choice == 1) {
        str_choice = " ";

        while (!(atoi(str_choice.c_str()))) {
            cout << "Введите Id книги, с которой будет создана связь:" << endl;
            cin >> str_choice;
        }
                
        Id x;
        x.relation_id = publisher.id;
        x.book_id = atoi(str_choice.c_str());
            
        bool checked = CheckBook_PublisherRelation(x.book_id, publisher.id);

        if (checked == true) {
            outBook_Publisher.write((char *) &x, sizeof(x));
            cout << "Связь успешно создана." << endl;
        }
        else cout << "Книга не существует!" << endl;
    }
    
    return publisher.id;
}

long long Publisher_Mng::delete_publisher(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    fstream inOutPublisher(PUBLISHERS, ios::in |ios::out);
    ofstream outLastId(REMOVED_PUBLISHER, ios::app);
    ifstream inLastId(LAST_ID);
    
    check_stream(PUBLISHERS);
    check_stream(REMOVED_PUBLISHER);
    check_stream(LAST_ID);
    
    long long last_id;
    inLastId >> last_id >> last_id >> last_id;
    
    Publisher publisher;
    
    inOutPublisher.seekg((id - 1) * sizeof(publisher));
    inOutPublisher.read((char *) &publisher, sizeof(publisher));
    inOutPublisher.clear();
 
    if ((strcmp(publisher.publisher_name, " ") != 0) && (id <= last_id) && (id > 0)) {
        Publisher publisher(" ");
        
        inOutPublisher.seekp((id - 1) * sizeof (publisher));
        inOutPublisher.write((char *) &publisher, sizeof (publisher));

        cout << "Запись " << id << " удалена" << endl;
        outLastId << id << endl;
    }
    else cout << "Запись не существует" << endl;
}

long long Publisher_Mng::replace_publisher(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

   fstream inOutPublisher(PUBLISHERS, ios::in | ios::out);
   ifstream inLastId(LAST_ID, ios::in);
    
   check_stream(PUBLISHERS);
    
   Publisher publisher;
   string str_name;
   long long last_id;

   inLastId >> last_id >> last_id >> last_id;

   inOutPublisher.seekg((id - 1) * sizeof(publisher));
   inOutPublisher.read((char *) &publisher, sizeof(publisher));

   if (strcmp(publisher.publisher_name, " ") != 0 && id <= last_id && id > 0) {
        cin.ignore();

        cout << "Введите новое имя автора" << endl;
        getline(cin, str_name);
        
        for (int i = 0; i < 20; i++) publisher.publisher_name[i] = str_name[i];
    
        inOutPublisher.seekp((id - 1) * sizeof(publisher));
        inOutPublisher.write((char *) &publisher, sizeof(publisher));

        cout << "Запись успешно изменена." << endl;
   }
   else cout << "Издательство не существует" << endl;
}

long long Publisher_Mng::show_publisher(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }
    ifstream inPublisher(PUBLISHERS, ios::in);
        
    check_stream(PUBLISHERS);
    
    Publisher publisher;
    
    bool checked = CheckPublisher(id, publisher);

    if (checked == true) {
        inPublisher.seekg((id - 1) * sizeof(publisher));
        inPublisher.read((char *) &publisher, sizeof(publisher));

         cout << "id: " << publisher.id << endl
              << "Имя издательства: " << publisher.publisher_name << endl;
    }
    else cout << "Издательство не существует!" << endl;
}

//------------------------------------------------------------------------------

class Relation_Mng {
public:
    static int create_relation(int);
    static int delete_relation(int);
    static int show_author_relation(long long);
    static int show_book_author_relation(long long);
    static int show_book_publisher_relation(long long);
    static int show_publisher_relation(long long);
};

int Relation_Mng::create_relation(int relation_choice) {
    if (relation_choice == 0) return 0;
    
    if (relation_choice == 1) {
        ifstream inRemoved_BA(REMOVED_BA);
        
        check_stream(REMOVED_BA);
        
        Id x;
        string str_id = " ";
        
        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id книги" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        x.book_id = atoi(str_id.c_str());

        str_id = " ";
        
        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id автора" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        x.relation_id = atoi(str_id.c_str());

        bool checked = CheckBook_AuthorRelation(x.book_id, x.relation_id);
        bool notExist = noBook_AuthorRelation(x);

        if (checked == false) {
            cout << "Невозможно создать связь, заданные записи не существуют!" << endl;
            return 0;
        }

        if (notExist == false) {
            cout << "Невозможно создать, заданная связь уже существует!" << endl;
            return 0;
        }
        
        int inFileSize;
        inRemoved_BA.seekg(0, ios::end);
        inFileSize = static_cast <int> (inRemoved_BA.tellg());
        
        if (inFileSize != 0) {
            fstream inOutBook_AuthorRelation(BOOK_AUTHOR, ios::in | ios::out);
            
            check_stream(BOOK_AUTHOR);
            
            long long pos;
            inRemoved_BA.seekg(0);
            inRemoved_BA >> pos;
            
            long long r;
            vector <long long> removedId;
        
            while (inRemoved_BA >> r) {
                removedId.push_back(r);
            }

            ofstream outRemoved_BA(REMOVED_BA);
            
            check_stream(REMOVED_BA);

            for (int i = 0; i < removedId.size(); i++) {
                 outRemoved_BA << removedId[i];
            }
            
            inOutBook_AuthorRelation.seekp((pos - 1) * sizeof(x));
            inOutBook_AuthorRelation.write((char *) &x, sizeof(x));
        }
        else {
            ofstream outBook_AuthorRelation(BOOK_AUTHOR, ios::app);
            
            check_stream(BOOK_AUTHOR);
            
            outBook_AuthorRelation.write((char *) &x, sizeof(x));
        }
    }
    if (relation_choice == 2) {
        ifstream inRemoved_BP(REMOVED_BP);
        
        check_stream(REMOVED_BP);
        
        Id x;
        string str_id = " ";
        
        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id книги" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        x.book_id = atoi(str_id.c_str());
        
        str_id = " ";

        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id издательства" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        x.relation_id = atoi(str_id.c_str());

        bool checked = CheckBook_PublisherRelation(x.book_id, x.relation_id);
        bool notExist = noBook_PublisherRelation(x);

        if (checked == false) {
            cout << "Невозможно создать связь, заданные элементы не существуют!" << endl;
            return 0;
        }

        if (notExist == false) {
            cout << "Невозможно создать, связь уже существует!" << endl;
            return 0;
        }
        
        int inFileSize;
        inRemoved_BP.seekg(0, ios::end);
        inFileSize = static_cast <int> (inRemoved_BP.tellg());
        
        if (inFileSize != 0) {
            fstream inOutBook_Publisher(BOOK_PUBLISHER, ios::in | ios::out);
            
            check_stream(BOOK_PUBLISHER);
            
            long long pos;
            inRemoved_BP.seekg(0);
            inRemoved_BP >> pos;
            
            long long r;
            vector <long long> removedId;
        
            while (inRemoved_BP >> r) {
                removedId.push_back(r);
            }

            ofstream outRemoved_BP(REMOVED_BP);
            
            check_stream(REMOVED_BP);

            for (int i = 0; i < removedId.size(); i++) {
                 outRemoved_BP << removedId[i];
            }
            
            inOutBook_Publisher.seekp((pos - 1) * sizeof(x));
            inOutBook_Publisher.write((char *) &x, sizeof(x));
        }
        else {
            ofstream outBook_Author(BOOK_PUBLISHER, ios::app);
            
            check_stream(BOOK_PUBLISHER);
            
            outBook_Author.write((char *) &x, sizeof(x));
        }
    }

    cout << "Связь успешно создана." << endl;
}

int Relation_Mng::delete_relation(int choice) {
    if (choice == 0) return 0;

    if (choice == 1) {
        fstream inOutBook_Author(BOOK_AUTHOR, ios::in | ios::out);
        ofstream outRemoved_BA(REMOVED_BA, ios::app);
        
        check_stream(BOOK_AUTHOR);
        check_stream(REMOVED_BA);
        
        Id x;
        string str_id = " ";
        
        long long a, b;
        
        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id книги для удаления из связей" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        b = atoi(str_id.c_str());

        str_id = " ";
        
        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id автора для удаления из связей" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        a = atoi(str_id.c_str());

        bool checked = CheckBook_AuthorRelation(b, a);

        if (checked == false) {
            cout << "Невозможно удалить связь, заданные элементы не существуют!" << endl;
            return 0;
        }
            
        long long i = 1;
        
        while (!inOutBook_Author.eof()) {
            inOutBook_Author.seekg((i - 1) * sizeof(x));
            inOutBook_Author.read((char *) &x, sizeof(x));
            
            if ((a == x.relation_id) && (b == x.book_id)) {
                x.relation_id = 0;
                x.book_id = 0;
                
                inOutBook_Author.seekp((i - 1) * sizeof(x));
                inOutBook_Author.write((char *) &x, sizeof(x));
                
                outRemoved_BA << i;
                break;
            }
            i++;
        }
    }
    if (choice == 2) {
        fstream inOutBook_Publisher(BOOK_PUBLISHER, ios::in | ios::out);
        ofstream outRemoved_BP(REMOVED_BP, ios::app);
              
        check_stream(BOOK_PUBLISHER);
        check_stream(REMOVED_BP);
        
        Id x;
        string str_id;

        long long p, b;
        
        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id книги для удаления из связей" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена оперции" << endl;
                return 0;
            }
        }
        
        b = atoi(str_id.c_str());

        str_id = " ";

        while (!(atoi(str_id.c_str()))) {
            cout << "Введите id издательства для удаления из связей" << endl;
            cin >> str_id;

            if (str_id == "0") {
                cout << "Отмена операции" << endl;
                return 0;
            }
        }

        p = atoi(str_id.c_str());

        bool checked = CheckBook_PublisherRelation(b, p);

        if (checked == false) {
            cout << "Невозможно создать связь, заданные элементы не существуют!" << endl;
            return 0;
        }
            
        long long i = 1;;
        
        while (!inOutBook_Publisher.eof()) {
            inOutBook_Publisher.seekg((i - 1) * sizeof(x));
            inOutBook_Publisher.read((char *) &x, sizeof(x));
            
            if ((p == x.relation_id) && (b == x.book_id)) {
                x.relation_id = 0;
                x.book_id = 0;
                
                inOutBook_Publisher.seekp((i - 1) * sizeof(x));
                inOutBook_Publisher.write((char *) &x, sizeof(x));
                
                outRemoved_BP << i;
                break;
            }
            i++;
        }
    }

    cout << "Связь успешно удалена." << endl;
}

int Relation_Mng::show_author_relation(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    ifstream inBook_Author(BOOK_AUTHOR);
    ifstream inBook(BOOKS);
    ifstream inAuthor(AUTHORS);

    check_stream(BOOK_AUTHOR);
    check_stream(BOOKS);
    check_stream(AUTHORS);
    
    Book book;
    Author author;

    bool checked = CheckAuthor(id, author);

    if (checked == false) {
        cout << "Автор не существует!" << endl;
        return 0;
    }
    
    inAuthor.seekg((id - 1) * sizeof(author));
    inAuthor.read((char *) &author, sizeof(author));
    
    cout << "Книги " << author.author_name << ":" << endl;
    
    long long i = 1;
    
    Id x;
    
    while (!inBook_Author.eof()) {
        inBook_Author.seekg((i - 1) * sizeof(x));
        inBook_Author.read((char *) &x, sizeof(x));
        
        if (x.relation_id == id) {
            inBook.seekg((x.book_id - 1) * sizeof(book));
            inBook.read((char *) &book, sizeof(book));
            
            cout << book.id << " " << book.book_name << endl;
        }
        i++;
    }
}

int Relation_Mng::show_book_author_relation(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    ifstream inBook_Author(BOOK_AUTHOR);
    ifstream inBook(BOOKS);
    ifstream inAuthor(AUTHORS);
    
    check_stream(BOOK_AUTHOR);
    check_stream(BOOKS);
    check_stream(AUTHORS);
    
    Book book;
    Author author;

    bool checked = CheckBook(id, book);

    if (checked == false) {
        cout << "Книга не существует!" << endl;
        return 0;
    }

    inBook.seekg((id - 1) * sizeof(book));
    inBook.read((char *) &book, sizeof(book));
    
    cout << "Авторы книги " << book.book_name << ":" << endl;
    
    long long i = 1;
    
    Id x;
    
    while (!inBook_Author.eof()) {
        inBook_Author.seekg((i - 1) * sizeof(x));
        inBook_Author.read((char *) &x, sizeof(x));
        
        if (x.book_id == id) {
            inAuthor.seekg((x.relation_id - 1) * sizeof(author));
            inAuthor.read((char *) &author, sizeof(author));
            
            cout << author.id << " " << author.author_name << endl;
        }
        i++;
    }
}

int Relation_Mng::show_book_publisher_relation(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    ifstream inBook_Publisher(BOOK_PUBLISHER);
    ifstream inBook(BOOKS);
    ifstream inPublisher(PUBLISHERS);
    
    check_stream(BOOK_PUBLISHER);
    check_stream(BOOKS);
    check_stream(PUBLISHERS);
    
    Book book;
    Publisher publisher;

    bool checked = CheckBook(id, book);

    if (checked == false) {
        cout << "Книга не существует!" << endl;
        return 0;
    }
    
    inBook.seekg((id - 1) * sizeof(book));
    inBook.read((char *) &book, sizeof(book));
    
    cout << "Издательства книги " << book.book_name << ":" << endl;
    
    long long i = 1;
    
    Id x;
    
    while (!inBook_Publisher.eof()) {
        inBook_Publisher.seekg((i - 1) * sizeof(x));
        inBook_Publisher.read((char *) &x, sizeof(x));
        
        if (x.book_id == id) {
            inPublisher.seekg((x.relation_id - 1) * sizeof(publisher));
            inPublisher.read((char *) &publisher, sizeof(publisher));
            
            cout << publisher.id << " " << publisher.publisher_name << endl;
        }
        i++;
    }
}

int Relation_Mng::show_publisher_relation(long long id) {
    if (id == 0) {
        cout << "Отмена операции" << endl;
        return 0;
    }

    ifstream inBook_Publisher(BOOK_PUBLISHER);
    ifstream inBook(BOOKS);
    ifstream inPublisher(PUBLISHERS);
    
    check_stream(BOOK_PUBLISHER);
    check_stream(BOOKS);
    check_stream(PUBLISHERS);
    
    Book book;
    Publisher publisher;

    bool checked = CheckPublisher(id, publisher);

    if (checked == false) {
        cout << "Издательство не существует!" << endl;
        return 0;
    }
    
    inPublisher.seekg((id - 1) * sizeof(publisher));
    inPublisher.read((char *) &publisher, sizeof(publisher));
    
    cout << "Книги издательства " << publisher.publisher_name << ":" << endl;
    
    long long i = 1;
    
    Id x;
    
    while (!inBook_Publisher.eof()) {
        inBook_Publisher.seekg((i - 1) * sizeof(x));
        inBook_Publisher.read((char *) &x, sizeof(x));
        
        if (x.relation_id == id) {
            inBook.seekg((x.book_id - 1) * sizeof(book));
            inBook.read((char *) &book, sizeof(book));
        
            cout << book.id << " " << book.book_name << endl;
        }
        i++;
    }
}

//------------------------------------------------------------------------------