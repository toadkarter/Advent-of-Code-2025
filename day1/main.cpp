#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file("inputs/part1.txt");
    std::string line;

    int number_of_zeros = 0;
    int current_amount = 50;

    while (getline(file, line))
    {
        const int rotation_amount = stoi(line.substr(1, line.size())) % 100;

        if (line[0] == 'L') 
        {
            const int raw_value = current_amount - rotation_amount;
            current_amount = raw_value < 0 ? 100 + raw_value : raw_value;
        }
        else 
        {
            current_amount = (current_amount + rotation_amount) % 100;
        }

        if (current_amount == 0)
        {
            number_of_zeros++;
        }
    }

    std::cout << "Part One Answer: " << number_of_zeros << std::endl;

    return 0;
}