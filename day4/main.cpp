#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

bool coordinates_have_roll(const int row, const int column, const std::vector<std::vector<bool>>& grid)
{
    if (row < 0 || row >= grid.size()) return false;
    if (column < 0 || column >= grid[row].size()) return false;

    return grid[row][column];
}

int get_num_surrounding_coordinates(const int row, const int column, const std::vector<std::vector<bool>>& grid)
{
    int num_surrounding_coordinates = 0;

    if (coordinates_have_roll(row - 1, column, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row + 1, column, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row, column - 1, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row, column + 1, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row - 1, column - 1, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row - 1, column + 1, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row + 1, column - 1, grid)) num_surrounding_coordinates++;
    if (coordinates_have_roll(row + 1, column + 1, grid)) num_surrounding_coordinates++;

    return num_surrounding_coordinates;
}

int get_part_one_answer(const std::vector<std::vector<bool>>& grid)
{
    int accessible_rolls = 0;

    for (int row = 0; row < grid.size(); row++)
    {
        const std::vector<bool>& current_row = grid[row];
        for (int column = 0; column < current_row.size(); column++)
        {
            if (coordinates_have_roll(row, column, grid))
            {
                if (get_num_surrounding_coordinates(row, column, grid) < 4)
                {
                    accessible_rolls++;
                }
            }
        }
    }

    return accessible_rolls;
}

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    long part_one_answer = 0;
    long part_two_answer = 0;

    std::vector<std::vector<bool>> grid;

    while (getline(file, line))
    {
        std::vector<bool> current_line;

        for (char c : line)
        {
            if (c == '.')
            {
                current_line.push_back(false);
            }
            else if (c == '@')
            {
                current_line.push_back(true);
            }
        }

        grid.push_back(current_line);
    }

    part_one_answer = get_part_one_answer(grid);

    std::cout << "Part One Answer: " << part_one_answer << std::endl;
    std::cout << "Part Two Answer: " << part_two_answer << std::endl;

    return 0;
}