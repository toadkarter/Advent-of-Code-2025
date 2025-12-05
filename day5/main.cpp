#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

struct IdRange
{
    IdRange(const long start, const long end) : start(start), end(end) {};

    long start = 0;
    long end = 0;
};

void merge_id_ranges(std::vector<IdRange>& id_ranges)
{
    std::vector<IdRange> merged_id_ranges;
    merged_id_ranges.reserve(id_ranges.size());

    std::sort(id_ranges.begin(), id_ranges.end(), [](const IdRange& a, const IdRange& b)
    {
        return a.start < b.start;
    });

    std::vector<IdRange>::const_iterator id_range_iterator = id_ranges.begin();
    IdRange previous_id_range = *id_range_iterator++;

    long previous_id_range_start = previous_id_range.start;
    long previous_id_range_end = previous_id_range.end;

    while (id_range_iterator != id_ranges.end())
    {
        IdRange current_id_range = *id_range_iterator++;
        if (current_id_range.start <= previous_id_range_end)
        {
            previous_id_range_end = std::max(current_id_range.end, previous_id_range_end);
        }
        else
        {
            merged_id_ranges.push_back(IdRange(previous_id_range_start, previous_id_range_end));
            previous_id_range_start = current_id_range.start;
            previous_id_range_end = current_id_range.end;
        }

        previous_id_range = current_id_range;
    }

    merged_id_ranges.push_back(IdRange(previous_id_range_start, previous_id_range_end));
    id_ranges = merged_id_ranges;
}

int main()
{
    std::ifstream file("inputs/input.txt");
    std::string line;

    long part_one_answer = 0;
    long part_two_answer = 0;

    std::vector<IdRange> id_ranges;
    std::vector<long> ids;

    bool getting_ranges = true;

    while (getline(file, line))
    {
        if (line.empty())
        {
            getting_ranges = false;
            continue;
        }

        if (getting_ranges)
        {
            int dash_location = line.find('-');
            IdRange id_range = IdRange(stol(line.substr(0, dash_location)), stol(line.substr(dash_location + 1, line.size())));
            id_ranges.push_back(id_range);
        }
        else 
        {
            ids.push_back(stol(line));
        }
    }

    merge_id_ranges(id_ranges);

    for (const long current_id : ids)
    {
        for (const IdRange& current_id_range : id_ranges)
        {
            if (current_id >= current_id_range.start && current_id <= current_id_range.end)
            {
                part_one_answer++;
                break;
            }
        }
    }

    for (const IdRange& current_id_range : id_ranges) 
    {
        part_two_answer += (current_id_range.end - current_id_range.start + 1);
    }

    std::cout << "Part One Answer: " << part_one_answer << std::endl;
    std::cout << "Part Two Answer: " << part_two_answer << std::endl;

    return 0;
}