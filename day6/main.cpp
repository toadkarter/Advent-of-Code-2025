#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Problem
{
    std::vector<long> operands {};
    char action = ' ';
};

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    long long part_one_answer = 0;
    long long part_two_answer = 0;

    std::vector<Problem> problems;

    while (getline(file, line))
    {
        // This monstrosity apparently lets you strip out whitespace. Good to know!
        std::istringstream ss(line);
        std::vector<std::string> numbers{std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()};

        if (problems.size() == 0)
        {
            problems.resize(numbers.size());
        }

        bool is_action = false;

        if (numbers[0] == "*" || numbers[0] == "/" || numbers[0] == "+" || numbers[0] == "-")
        {
            is_action = true;
        }

        for (int i = 0; i < numbers.size(); i++)
        {
            if (is_action)
            {
                problems[i].action = numbers[i][0];
            }
            else
            {
                problems[i].operands.push_back(stol(numbers[i]));
            }
        }
    }

    for (const Problem& problem : problems)
    {
        long long current_amount = 0;
        for (const long& current_num : problem.operands)
        {
            if (problem.action == '*')
            {
                current_amount = current_amount == 0 ? current_num : current_amount * current_num;
            }
            else if (problem.action == '/')
            {
                current_amount /= current_num;
            }
            else if (problem.action == '+')
            {
                current_amount += current_num;
            }
            else if (problem.action == '-')
            {
                current_amount -= current_num;
            }
        }

        part_one_answer += current_amount;
    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;
    std::cout << "Part Two Answer: " << part_two_answer << std::endl;

    return 0;
}