#include <iostream>

using namespace std;


int main(){
    char in;
    int x{};
    int y{};
    while (in != 'Q'){
        bool status = true;
        cout<<"Hi enter your operation!"<<endl;
        cout<<"1: Addition\n2: Subtraction\n3: Multuplcation\n4: Division\nQ: quit\n";
        cin >> in;

        switch (in){
            case '1':
                cout<<"Addition"<<endl;
                break;
            case '2':
                cout<<"Subtraction"<<endl;
                break;
            case '3':
                cout<<"Multiplication"<<endl;
                break;
            case '4':
                cout<<"Division"<<endl;
                break;
            case 'Q':
                cout << "Thank you for playing!\n";
                return 0;
            default:
                cout << "Not a valid command!\n";
                status = false;
        }
        if (status){
            cout << "Okay, enter 2 numbers!\n";
            cin >> x >> y;
            cout << "Answer: "<< x * y << endl;
        }
    }
    return 0;
}