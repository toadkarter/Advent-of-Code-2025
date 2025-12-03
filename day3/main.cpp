#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#define INT(c) (c - '0')

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    long part_one_answer = 0;
    long part_two_answer = 0;

    while (getline(file, line))
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

        const int current_answer = (10 * INT(line[left])) + INT(line[right]);
        part_one_answer += current_answer;

    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;

    return 0;
}