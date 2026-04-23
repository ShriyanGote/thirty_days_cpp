#include <iostream>
#include <fstream>



class TodoList {
    public:
        TodoList(const std::string& filename) : _filename(filename) {};
        ~TodoList() = default;
        void add_item(std::string& item);
        void complete_item(int position);
        void print_list();
        void save_file_with_list();
    private:
        std::vector<std::string> _list;
        std::string _filename;
};