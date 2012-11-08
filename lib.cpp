#include "lib_facilities.h"

int MenuEnterChoice();
int CreateEnterChoice();
int DeleteEnterChoice();
int ReplaceEnterChoice();
int ShowEnterChoice();

int main(int argc, char** argv) {
    cout << endl;
    cout << "База данных 'Библиотека'" << endl;
    
    int choice;
    
    while ((choice = MenuEnterChoice()) != 0) {
        int next_choice;
        
        switch (choice) {            
            case 1:  // create
                while ((next_choice = CreateEnterChoice()) != 0) { 
                    
                    switch (next_choice) {
                        case 1: // author
                            Author_Mng::create_author();
                            break;
                            
                        case 2: // book
                            Book_Mng::create_book();
                            break;
                            
                        case 3: // publisher
                            Publisher_Mng::create_publisher();
                            break;
                            
                        case 4: // relation
                            int relation_choice;
                            cout << endl << "Выберите:" << endl
                                 << "1 - книга-автор" << endl
                                 << "2 - книга-издательство" << endl;        
                            cin >> relation_choice;
                        
                            Relation_Mng::create_relation(relation_choice);
                            break;
                                                    
                        default:
                            cout << "Ошибка ввода." << endl;
                            break; 
                    }
                } 
                break;
            
            case 2: // delete
                while ((next_choice = DeleteEnterChoice()) != 0) { 
                    
                    switch (next_choice) {
                        case 1: // author              
                            cout << "Введите id автора для удаления:" << endl;
                            long long id;
                            cin >> id;     
                            
                            Author_Mng::delete_author(id);
                            break;
 
                        case 2: // book
                            cout << "Введите id книги для удаления:" << endl;
                            cin >> id;
                            
                            Book_Mng::delete_book(id);
                            break;
                            
                        case 3: // publisher
                            cout << "Введите id издательства для удаления:" << endl;
                            cin >> id;
                            
                            Publisher_Mng::delete_publisher(id);
                            break;
                            
                        case 4: // relation
                            int relation_choice;
                            cout << endl << "Выберите:" << endl
                                 << "1 - книга-автор" << endl
                                 << "2 - книга-издательство" << endl;
                            cin >> relation_choice;
                        
                            Relation_Mng::delete_relation(relation_choice);
                            break;
                            
                        default:
                            cout << "Ошибка ввода." << endl;
                            break;
                    }
                }
                break;
                
            case 3: // replace
                while ((next_choice = ReplaceEnterChoice()) != 0) {
                    
                    switch (next_choice) {
                        case 1: // author
                            long long id;
                            cout << "Введите id книги для изменения:" << endl;
                            cin >> id;
                            
                            Author_Mng::replace_author(id);
                            break;
                            
                        case 2: // book
                            cout << "Введите id книги для изменения" << endl;
                            cin >> id;
                            
                            Book_Mng::replace_book(id);
                            break;
                            
                        case 3: // publisher
                            cout << "Введите id издательства для изменения" << endl;
                            cin >> id;
                            
                            Publisher_Mng::replace_publisher(id);
                            break;
                                                       
                        default:
                            cout << "Ошибка ввода." << endl;
                            break;
                    }                   
                }
                break;
                
            case 4: // show
                while ((next_choice = ShowEnterChoice()) != 0) {
                    
                    switch (next_choice) {
                        case 1: // author
                            int show_choice;
                            cout << "Показать 1 - отдельно, 2 - связи" << endl;                            
                            cin >> show_choice;
                            
                            long long id;
                            cout << "Введите id автора:" << endl;
                            cin >> id;
                            
                            if (show_choice == 1) {
                                Author_Mng::show_author(id);
                            }
                            if (show_choice == 2) {                                  
                                Relation_Mng::show_author_relation(id);
                            }
                            break;
                            
                        case 2: // book
                            cout << "Показать 1 - отдельно, 2 - связи" << endl;
                            cin >> show_choice;
                            
                            if (show_choice == 1) {
                                cout << "Введите id книги:" << endl;
                                cin >> id;
                                
                                Book_Mng::show_book(id);
                            }
                            if (show_choice == 2) {   
                                int relation_choice;
                                cout << "1 - книга-автор" << endl
                                     << "2 - книга-издательство" << endl;
                                cin >> relation_choice;
                                
                                cout << "Введите id книги:" << endl;
                                cin >> id;
                                
                                if (relation_choice == 1) {
                                    Relation_Mng::show_book_author_relation(id);
                                }
                                if (relation_choice == 2) {   
                                    Relation_Mng::show_book_publisher_relation(id);                                
                                }
                            }                       
                            break;
                            
                        case 3: // publisher
                            cout << "Показать 1 - отдельно, 2 - связи" << endl;
                            cin >> show_choice;
                            
                            cout << "Введите id издательства:" << endl;
                            cin >> id;
                            
                            if (show_choice == 1) {
                                Publisher_Mng::show_publisher(id);
                            }
                            
                            if (show_choice == 2) {
                                Relation_Mng::show_publisher_relation(id);
                            }
                            break;
                            
                        default:
                            cout << "Ошибка ввода" << endl;
                            break;
                    }
                }
                break;
            
            default:
                cout << "Ошибка ввода." << endl;
                break;
        }
    }
    
    return 0;
}

int MenuEnterChoice() {   
    cout << endl << "Выберите:" << endl
         << "1 - создать" << endl
         << "2 - удалить" << endl
         << "3 - изменить" << endl
         << "4 - показать" << endl
         << "0 - выход" << endl;
    
    int menuChoice;
    cin >> menuChoice;
    
    return menuChoice;  
}

int CreateEnterChoice() {  
    cout << endl << "Создать:" << endl 
         << "1 - автора" << endl
         << "2 - книгу" << endl
         << "3 - издательство" << endl
         << "4 - связь" << endl
         << "0 - назад" << endl;

    int menuChoice;
    cin >> menuChoice;
    
    return menuChoice;        
}

int DeleteEnterChoice() {  
    cout << endl << "Удалить:" << endl 
         << "1 - автора" << endl
         << "2 - книгу" << endl
         << "3 - издательство" << endl
         << "4 - связь" << endl
         << "0 - назад" << endl;

    int menuChoice;
    cin >> menuChoice;
    
    return menuChoice;          
}

int ReplaceEnterChoice() {   
    cout << endl << "Изменить:" << endl 
         << "1 - автора" << endl
         << "2 - книгу" << endl
         << "3 - издательство" << endl
         << "4 - связь" << endl
         << "0 - назад" << endl;

    int menuChoice;
    cin >> menuChoice;
    
    return menuChoice;        
}

int ShowEnterChoice() { 
    cout << endl << "Показать:" << endl
         << "1 - автора" << endl
         << "2 - книгу" << endl
         << "3 - издательство" << endl
         << "0 - назад" << endl;
    
    int menuChoice;
    cin >> menuChoice;
    
    return menuChoice;
}