#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "todo_list.h"



void TodoList::add_item(std::string& item){
    _list.push_back(item);
};
void TodoList::complete_item(int position){
    if (position >= _list.size()){
        std::cout << "Unfortunately, this item is not in the list!\n";
        return;
    }
    _list.erase(_list.begin() + position);
};

void TodoList::print_list(){
    for (size_t x = 0; x < _list.size(); ++x ){
        std::cout << "["<<x<<"]: "<< _list[x] <<std::endl;
    }
};

void TodoList::save_file_with_list(){
    std::ofstream file(_filename, std::ios::trunc);
    if (file.is_open()){
        for (size_t x = 0; x < _list.size(); ++x ){
            file << "["<<x<<"]: "<< _list[x] << std::endl;
        }
    }
};

// class TodoList {
//     public:
//         TodoList(std::ofstream file);
//         ~TodoList() = default;
//         bool add_item(std::string& item);
//         bool complete_item(int position);
//         void print_list();
//     private:
//         std::vector<std::string> _list;
//         std::ofstream _file;
// };