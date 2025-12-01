#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    int part_one_answer = 0;
    int part_two_answer = 0;
    int current_amount = 50;

    while (getline(file, line))
    {
        const int rotation_amount_raw = stoi(line.substr(1, line.size()));
        part_two_answer += rotation_amount_raw / 100;
        const int rotation_amount = rotation_amount_raw % 100;

        if (line[0] == 'L') 
        {
            const int raw_value = current_amount - rotation_amount;
            if (current_amount != 0 && raw_value < 0) { part_two_answer++; }
            current_amount = raw_value < 0 ? 100 + raw_value : raw_value;
        }
        else 
        {
            if (current_amount + rotation_amount > 100) { part_two_answer++; }
            current_amount = (current_amount + rotation_amount) % 100;
        }

        if (current_amount == 0)
        {
            part_one_answer++;
            part_two_answer++;
        }
    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;
    std::cout << "Part Two Answer: " << part_two_answer << std::endl;

    return 0;
}