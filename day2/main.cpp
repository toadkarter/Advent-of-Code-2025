#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

long get_sum_invalid_ids(const long lower_range, const long upper_range)
{
    long invalid_ids = 0;

    for (long i = lower_range; i <= upper_range; i++)
    {
        const int number_of_digits = static_cast<int>(log10(i)) + 1;
        if (number_of_digits % 2 == 0)
        {
            const long divisor = pow(10, std::floor(static_cast<float>(number_of_digits) / 2));
            const long second_half = i % divisor;
            const long first_half = (i - second_half) / divisor;

            if (first_half == second_half)
            {
                invalid_ids += i;
            }
        }
    }

    return invalid_ids;
}

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    long part_one_answer = 0;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string current_id_range;
        char delimiter = ',';

        while (getline(ss, current_id_range, delimiter))
        {
            int dash_location = current_id_range.find('-');
            long lower_id_range = stol(current_id_range.substr(0, dash_location));
            long upper_id_range = stol(current_id_range.substr(dash_location + 1, current_id_range.size()));

            part_one_answer += get_sum_invalid_ids(lower_id_range, upper_id_range);
        }
    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;

    return 0;
}