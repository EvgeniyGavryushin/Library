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
                    string choice = " ";
                    int relation_choice;
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
                            while (!(atoi(choice.c_str())) && choice != "0") {
                                cout << endl << "Выберите:" << endl
                                     << "1 - книга-автор" << endl
                                     << "2 - книга-издательство" << endl      
                                     << "0 - назад" << endl;  
                                
                                cin >> choice;

                                if (choice == "1" || choice == "2" || choice == "0") relation_choice = atoi(choice.c_str());
                                else choice = " ";
                            }

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
                    string choice = " ";
                    switch (next_choice) {
                        case 1: // author
                            while (!(atoi(choice.c_str())) && choice != "0") {              
                                cout << "Введите id автора для удаления:" << endl;
                                cin >> choice;
                            }

                            long long id;
                            id = atoi(choice.c_str());    
                            
                            Author_Mng::delete_author(id);
                            break;
 
                        case 2: // book
                            while (!(atoi(choice.c_str())) && choice != "0") {
                                cout << "Введите id книги для удаления:" << endl;
                                cin >> choice;
                            }

                            id = atoi(choice.c_str());
                            
                            Book_Mng::delete_book(id);
                            break;
                            
                        case 3: // publisher
                            while (!(atoi(choice.c_str())) && choice != "0") { 
                                cout << "Введите id издательства для удаления:" << endl;
                                cin >> choice;
                            }

                            id = atoi(choice.c_str());
                            
                            Publisher_Mng::delete_publisher(id);
                            break;
                            
                        case 4: // relation
                            int relation_choice;

                            while (!(atoi(choice.c_str())) && choice != "0") { 
                                cout << endl << "Выберите:" << endl
                                     << "1 - книга-автор" << endl
                                     << "2 - книга-издательство" << endl
                                     << "0 - назад" << endl;

                                cin >> choice;

                                if ((choice == "1" || choice == "2" || choice == "0")) relation_choice = atoi(choice.c_str());
                                else choice = " ";
                            }
                        
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
                    string choice = " ";
                
                    switch (next_choice) {
                        case 1: // author
                            while (!(atoi(choice.c_str())) && choice != "0") {              
                                cout << "Введите id автора для изменения:" << endl;
                                cin >> choice;
                            }

                            long long id;
                            id = atoi(choice.c_str());
                            
                            Author_Mng::replace_author(id);
                            break;
                            
                        case 2: // book
                            while (!(atoi(choice.c_str())) && choice != "0") {
                                cout << "Введите id книги для изменения" << endl;
                                cin >> choice;
                            }

                            id = atoi(choice.c_str());
                            
                            Book_Mng::replace_book(id);
                            break;
                            
                        case 3: // publisher
                            while (!(atoi(choice.c_str())) && choice != "0") {
                                cout << "Введите id издательства для изменения" << endl;
                                cin >> choice;
                            }

                            id = atoi(choice.c_str());
                            
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
                    string choice = " ";
                    switch (next_choice) {
                        case 1: // author
                            int show_choice;

                            while (!(atoi(choice.c_str()))) {
                                cout << "Показать 1 - отдельно, 2 - связи" << endl;                            
                                cin >> choice;

                                if (choice == "0") break;

                                if (choice == "1" || choice == "2" || choice == "0") show_choice = atoi(choice.c_str());
                                else choice = " ";
                            }

                            if (choice == "0") {
                                cout << "Отмена операции" << endl;
                                break;
                            }
                            
                            choice = " ";
                            long long id;

                            while (!(atoi(choice.c_str())) && choice != "0") {
                                cout << "Введите id автора:" << endl;
                                cin >> choice;
                            }

                            id = atoi(choice.c_str());
                            
                            if (show_choice == 1) {
                                Author_Mng::show_author(id);
                            }
                            if (show_choice == 2) {                                  
                                Relation_Mng::show_author_relation(id);
                            } 
                            break;
                            
                        case 2: // book
                            while (!(atoi(choice.c_str()))) {
                                cout << "Показать 1 - отдельно, 2 - связи" << endl;
                                cin >> choice;

                                if (choice == "0") break;

                                if (choice == "1" || choice == "2") show_choice = atoi(choice.c_str());
                                else choice = " ";
                            }

                            if (choice == "0") {
                                cout << "Отмена операции" << endl;
                                break;
                            }

                            choice = " ";
                            
                            if (show_choice == 1) {
                                while (!(atoi(choice.c_str()))) {
                                    cout << "Введите id книги:" << endl;
                                    cin >> choice;
                                }
                                
                                id = atoi(choice.c_str());

                                Book_Mng::show_book(id);
                            }
                            if (show_choice == 2) {   
                                int relation_choice;

                                while (!(atoi(choice.c_str()))) {
                                    cout << "1 - книга-автор" << endl
                                         << "2 - книга-издательство" << endl;
                                    cin >> choice;

                                    if (choice == "0") break;

                                    if (choice != "1" && choice != "2") choice = " ";
                                }

                                if (choice == "0") {
                                    cout << "Отмена операции" << endl;
                                    break;
                                }

                                relation_choice = atoi(choice.c_str());

                                choice = " ";
                                
                                while (!(atoi(choice.c_str())) && choice != "0") {
                                    cout << "Введите id книги:" << endl;
                                    cin >> choice;
                                }

                                id = atoi(choice.c_str());
                                
                                if (relation_choice == 1) {
                                    Relation_Mng::show_book_author_relation(id);
                                }
                                if (relation_choice == 2) {   
                                    Relation_Mng::show_book_publisher_relation(id);                                
                                }
                            }                       
                            break;
                            
                        case 3: // publisher
                            while (!(atoi(choice.c_str()))) {
                                cout << "Показать 1 - отдельно, 2 - связи" << endl;
                                cin >> choice;

                                if (choice == "0") break;

                                if (choice != "1" && choice != "2") choice = " ";
                            }

                            if (choice == "0") {
                                cout << "Отмена операции" << endl;
                                break;
                            }

                            show_choice = atoi(choice.c_str());

                            choice = " ";
                            
                            while (!(atoi(choice.c_str())) && choice != "0") {
                                cout << "Введите id издательства:" << endl;
                                cin >> choice;
                            }

                            id = atoi(choice.c_str());
                            
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
    int menuChoice;
    string choice = " ";   

    while (!(atoi(choice.c_str())) && choice != "0") {
        cout << endl << "Выберите:" << endl
             << "1 - создать" << endl
             << "2 - удалить" << endl
             << "3 - изменить" << endl
             << "4 - показать" << endl
             << "0 - выход" << endl;

         cin >> choice;
    }

    return menuChoice = atoi(choice.c_str());  
}

int CreateEnterChoice() {  
    int menuChoice;
    string choice = " ";
    while (!(atoi(choice.c_str())) && choice != "0") {
        cout << endl << "Создать:" << endl 
             << "1 - автора" << endl
             << "2 - книгу" << endl
             << "3 - издательство" << endl
             << "4 - связь" << endl
             << "0 - назад" << endl;

        cin >> choice;
    }
    
    return menuChoice = atoi(choice.c_str());        
}

int DeleteEnterChoice() {  
    int menuChoice;
    string choice = " ";

    while (!(atoi(choice.c_str())) && choice != "0") {
        cout << endl << "Удалить:" << endl 
             << "1 - автора" << endl
             << "2 - книгу" << endl
             << "3 - издательство" << endl
             << "4 - связь" << endl
             << "0 - назад" << endl;

        cin >> choice;
    }
    
    return menuChoice = atoi(choice.c_str());          
}

int ReplaceEnterChoice() {   
    int menuChoice;
    string choice = " ";

    while (!(atoi(choice.c_str())) && choice != "0") {
        cout << endl << "Изменить:" << endl 
             << "1 - автора" << endl
             << "2 - книгу" << endl
             << "3 - издательство" << endl
             << "0 - назад" << endl;

        cin >> choice;
    }

    return menuChoice = atoi(choice.c_str());        
}

int ShowEnterChoice() { 
    int menuChoice;
    string choice = " ";

    while (!(atoi(choice.c_str())) && choice != "0") {
        cout << endl << "Показать:" << endl
             << "1 - автора" << endl
             << "2 - книгу" << endl
             << "3 - издательство" << endl
             << "0 - назад" << endl;
    
    
        cin >> choice;
    }
    
    return menuChoice = atoi(choice.c_str()); 
}