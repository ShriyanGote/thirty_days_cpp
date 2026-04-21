#include <iostream>
#include <fstream>
#include <random>


static std::string options = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

std::string generate_password(int size){
    std::string password{};
    for (int i = 0; i < size; ++i){
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, options.size()-1);
        int val = dist(rng);
        std::cout << options[val];
        password += options[val];
    }
    return password;
}

int main(){
    int pass_len{};
    while (true){
        std::cout << "\nEnter length of password: ";
        std::cin >> pass_len;
        if (pass_len < 1){
            return 0;
        }
        std::ofstream file("pass.txt");
        if (file.is_open())
            file << generate_password(pass_len);
        else std::cout<<"error opening file\n";
        file.close();
    }
}