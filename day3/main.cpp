#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#define INT(c) (c - '0')

int get_part_one_answer(const std::string& line)
{
    int left = 0;
    int right = 1;

    int pointer = 2;

    while (pointer < line.size())
    {
        if (INT(line[left]) < INT(line[pointer]) && pointer != line.size() - 1)
        {
            left = pointer;
            right = pointer + 1;

        } 
        else if (INT(line[right]) < INT(line[pointer]))
        {
            right = pointer;
        } 

        pointer++;
    }

    return (10 * INT(line[left])) + INT(line[right]);
}

long get_part_two_answer(const std::string& line)
{
    constexpr int max_num = 12;
    int number_digits_to_remove = line.size() - max_num;

    std::vector<int> current_digits;

    for (char c : line) {
        int current_digit = INT(c);

        while (!current_digits.empty() && number_digits_to_remove > 0 && current_digits.back() < current_digit) {
            current_digits.pop_back();
            number_digits_to_remove--;
        }

        if (current_digits.size() < max_num) {
            current_digits.push_back(current_digit);
        } else {
            number_digits_to_remove--;
        }
    }

    long answer = 0;
    for (int i = 0; i < current_digits.size(); i++) {
        answer += (current_digits[i] * std::pow(10, current_digits.size() - i - 1));
    }

    return answer;
}

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    long part_one_answer = 0;
    long part_two_answer = 0;

    while (getline(file, line))
    {
        part_one_answer += get_part_one_answer(line);
        part_two_answer += get_part_two_answer(line);
    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;
    std::cout << "Part Two Answer: " << part_two_answer << std::endl;

    return 0;
}