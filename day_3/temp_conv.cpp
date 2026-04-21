#include <iostream>


enum class units : char{
    KELVIN = 'K',
    CELSIUS = 'C',
    FAHRENHEIT = 'F'
};

int main(){
    char startingUnit{};
    char endingUnit{};
    float value{};
    float final{};
    while (true){
        std::cout << "Enter starting and ending units: ";
        std::cin >> startingUnit >> endingUnit;
        std::cout << "Nice! Enter value to convert: ";
        std::cin >> value;
        units s_unit = static_cast<units>(startingUnit);
        units e_unit = static_cast<units>(endingUnit);
        switch (s_unit) {
            case units::KELVIN:
                if (e_unit == units::CELSIUS){
                    final = value - 273.15;
                } else if (e_unit == units::FAHRENHEIT){    
                    final = (value - 273.15) * 1.8 + 32;
                }
                break;
            case units::CELSIUS:
                if (e_unit == units::KELVIN){
                    final = value + 273.15;
                } else if (e_unit == units::FAHRENHEIT){    
                    final = (value) * 1.8 + 32;
                }
                break;
            case units::FAHRENHEIT:
                if (e_unit == units::KELVIN){
                    final = (value - 32) * (5.0 / 9.0) + 273.15;
                } else if (e_unit == units::CELSIUS){    
                    final = (value - 32) * (5.0 / 9.0);
                }
                break;
            default:
                std::cout << "Wrong input!\n";
                return 0;
        }
        std::cout << "Converted Temp: " << final << std::endl;
    }
}