#pragma once

#include "Day.h"
#include <algorithm>

//#define TEST_INPUT

class Day3
	: public AocDay
{
public:
	Day3()
		: AocDay(1)
	{
	}

	std::vector<std::string> ReadInput(const std::string& filename)
	{
#ifdef TEST_INPUT
		return {
			"00100",
			"11110",
			"10110",
			"10111",
			"10101",
			"01111",
			"00111",
			"11100",
			"10000",
			"11001",
			"00010",
			"01010"
		};
#endif
		std::vector<std::string> lines;
		ReadAsStrings(filename, lines);
		return lines;
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		std::vector<std::string> input = ReadInput(filename);
		int width = (int)input[0].size();
		int gamma = 0;
		int epsilon = 0;

		for (int j = 0; j < width; j++)
		{
			int one_count = 0;
			int size = (int)input.size();

			for (int i = 0; i < size; i++)
			{
				if (input[i][j] == '1')
				{
					one_count++;
				}
			}

			if (size - one_count < size / 2)
			{
				gamma ^= (1 << (width - 1 - j));
			}
			else
			{
				epsilon ^= (1 << (width - 1 - j));
			}
		}

		return std::to_string(gamma * epsilon);
	}

	int binary_string_to_int(const std::string& str)
	{
		int result = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] == '1')
			{
				result ^= (1 << (str.size() - 1 - i));
			}
		}
		return result;
	}

	std::string parse(std::vector<std::string> input, bool removeMostCommon)
	{
		std::string answer;
		int width = (int)input[0].size();

		for (int index = 0; index < width; index++)
		{
			int ones = 0;
			int size = (int)input.size();

			for (int i = 0; i < size; i++)
			{
				if (input[i][index] == '1')
				{
					ones++;
				}
			}

			char common = '0';
			if (size - ones <= std::ceil(size / 2))
			{
				common = '1';
			}

			input.erase(
				std::remove_if(input.begin(), input.end(),
					[index, common, removeMostCommon](const std::string& x)
					{
						if (removeMostCommon)
						{
							return x[index] != common;
						}
						else
						{
							return x[index] == common;
						}
					}),
				input.end());

			if (input.size() <= 1)
			{
				answer = input[0];
				break;
			}
		}

		return answer;
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		std::vector<std::string> input = ReadInput(filename);

		int oxy = binary_string_to_int(parse(input, true));
		int co2 = binary_string_to_int(parse(input, false));

		return std::to_string(oxy * co2);
	}
};