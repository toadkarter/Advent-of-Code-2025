#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#define NUMBER_OF_DIGITS(n) (static_cast<int>(log10(n)) + 1)
#define DIGITS_IN_CHUNK(n, number_of_parts) ((static_cast<double>(NUMBER_OF_DIGITS(n))) / number_of_parts)
#define DIVISOR(n, number_of_parts) (static_cast<long>(std::pow(10, (DIGITS_IN_CHUNK(n, number_of_parts)))))
#define CHUNK(n, divisor) (n % divisor)

long get_sum_invalid_ids_part_one(const long lower_range, const long upper_range)
{
    long invalid_ids = 0;

    for (long i = lower_range; i <= upper_range; i++)
    {
        const int number_of_digits = NUMBER_OF_DIGITS(i);
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

bool number_of_parts_makes_invalid_id(const long number, const long number_of_parts) 
{
    long current_number = number;
    double divisor = DIVISOR(current_number, number_of_parts);
    long current_chunk = CHUNK(current_number, static_cast<long>(divisor));
    const long digits_target = NUMBER_OF_DIGITS(divisor) - 1;

    while (digits_target <= NUMBER_OF_DIGITS(current_number)) 
    {
        const long chunk_to_compare = NUMBER_OF_DIGITS(current_number) == digits_target ? current_number : CHUNK(current_number, static_cast<long>(divisor));
        if (current_chunk != chunk_to_compare) 
        {
            return false;
        }

        current_number = static_cast<double>(current_number - chunk_to_compare) / divisor;
    }

    return true;
}

long get_sum_invalid_ids_part_two(const long lower_range, const long upper_range)
{
    long invalid_ids = 0;

    for (long i = lower_range; i <= upper_range; i++)
    {
        const long number_of_digits = NUMBER_OF_DIGITS(i);
        for (long number_of_parts = 2; number_of_parts <= number_of_digits; number_of_parts++) 
        {
            if (number_of_digits % number_of_parts == 0) 
            {
                bool is_invalid = number_of_parts_makes_invalid_id(i, number_of_parts);
                if (is_invalid) {
                    invalid_ids += i;
                    break;
                }
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
    long part_two_answer = 0;

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

            part_one_answer += get_sum_invalid_ids_part_one(lower_id_range, upper_id_range);
            part_two_answer += get_sum_invalid_ids_part_two(lower_id_range, upper_id_range);
        }
    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;
    std::cout << "Part Two Answer: " << part_two_answer << std::endl;

    return 0;
}