#include <iostream>
#include <random>
#include <thread>

#define DICE_SIZE 6

class BaseDiceGame {
    public:
        BaseDiceGame(int sides) : _sides(sides) {};
        ~BaseDiceGame() = default;
        virtual int roll() {
            static std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(1, _sides);
            return dist(rng);
        }
        int _sides;
};

class UserDiceGame : public BaseDiceGame {
    public:
        UserDiceGame(int sides) : BaseDiceGame(sides) {};
        ~UserDiceGame() = default;
        int roll() override{
            int rand_val = BaseDiceGame::roll();
            return rand_val < 6 ? rand_val + 1 : rand_val;
        }
};

int main (){
    BaseDiceGame cpu(DICE_SIZE);
    UserDiceGame user(DICE_SIZE);
    int total_money{};
    int cur_bet{};
    while (1){
        UserDiceGame* user_temp = new UserDiceGame(DICE_SIZE);
        std::cout << "Just checking: " << user_temp->roll() << std::endl;
        std::cout <<  "Enter bet amt: ";
        std::cin >> cur_bet;
        total_money -= cur_bet;
        int cpu_roll = cpu.roll();
        int user_roll = user.roll();
        std::cout << "User rolled: " << user_roll << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Cpu rolled: " << cpu_roll << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (cpu_roll < user_roll){
            total_money += cur_bet * 2;
            std::cout << "Good win! Total cash: " << total_money << std::endl;
        } else if (cpu_roll > user_roll){
            std::cout << "Unforunate, try again! Total cash: " << total_money << std::endl;
        } else {
            total_money += cur_bet;
            std::cout << "Tie game! Try again\n";
        }
        delete user_temp;
    } 

    return 0;
}