#include <iostream>
#include <limits>
#include "todo_list.h"


void print_options(){
    std::cout<< "Enter an option below: " << std::endl;
    std::cout<< "[1] Add Item" << std::endl;
    std::cout<< "[2] Delete Option" << std::endl;
    std::cout<< "[3] Print List" << std::endl;
    std::cout<< "[4] Save File" << std::endl;
    std::cout<< "[5] Quit" << std::endl;
    std::cout<< ">> ";
}

int main(){
    std::string file_name{};
    std::cout << "Hi welcome to the todo list, enter a file name for your list: ";
    std::cin >> file_name;
    TodoList todo_list(file_name);
    while (1){
        int input{};
        print_options();
        std::cin >> input;
        switch(input){
            case 1: {
                std::string item{};
                std::cout << "Enter an item to add: ";
                std::cin.ignore();
                std::getline(std::cin, item);
                todo_list.add_item(item);
                break;
            }
            case 2: {
                int position{};
                todo_list.print_list();
                std::cout << "Enter position of item to complete: ";
                std::cin >> position;
                todo_list.complete_item(position);
                break;
            }
            case 3:
                todo_list.print_list();
                break;
            case 4:
                todo_list.save_file_with_list();
                break;
            case 5:
                return 0;
                break;
        }
    }
}