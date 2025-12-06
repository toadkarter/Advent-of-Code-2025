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

    std::vector<std::string> part_two_input;
};

int main()
{
    std::ifstream file("inputs/sample.txt");
    std::string line;

    long long part_one_answer = 0;
    long long part_two_answer = 0;

    std::vector<Problem> problems{};

    while (getline(file, line))
    {
        if (line[0] == '*' || line[0] == '/' || line[0] == '+' || line[0] == '-')
        {
            // This monstrosity apparently lets you strip out whitespace. Good to know!
            std::istringstream ss(line);
            std::vector<std::string> operands{std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>()};
            for (int i = 0; i < problems.size(); i++)
            {
                problems[i].action = operands[i][0];
            }
        }
        else
        {
            int current_num_index = 0;
            int prev_pos = 0;
            int current_pos = 0;

            while (current_pos < line.size() - 1)
            {
                if (line[0] == ' ')
                {
                    while (line[current_pos] == ' ')
                    {
                        current_pos++;
                    }

                    prev_pos = current_pos;
                }

                while (current_pos < line.size() - 1 && line[current_pos] != ' ')
                {
                    current_pos++;
                }

                while (current_pos < line.size() - 1 && line[current_pos] == ' ')
                {
                    current_pos++;
                }

                std::string operand_with_whitespace = line.substr(prev_pos, current_pos - prev_pos);
                if (current_num_index >= problems.size())
                {
                    problems.push_back(Problem{});
                }

                problems[current_num_index].part_two_input.push_back(operand_with_whitespace);

                std::string::iterator strip = std::remove(operand_with_whitespace.begin(), operand_with_whitespace.end(), ' ');
                operand_with_whitespace.erase(strip, operand_with_whitespace.end());
                problems[current_num_index].operands.push_back(stol(operand_with_whitespace));

                prev_pos = current_pos;
                current_num_index++;
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