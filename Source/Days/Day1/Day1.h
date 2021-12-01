#pragma once

#include "Day.h"

// #define TEST_INPUT

class Day1
	: public AocDay
{
public:
	Day1()
		: AocDay(1)
	{
	}

	std::vector<int> ReadInput(std::string filename)
	{
#ifdef TEST_INPUT
		return {
			199,
			200,
			208,
			210,
			200,
			207,
			240,
			269,
			260,
			263
		};
#endif
		std::vector<std::string> lines;
		std::vector<int> data;

		if (!ReadAsStrings(filename, lines))
		{
			std::cerr << "Error reading in the data from " << filename << std::endl;
			return data;
		}

		for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
		{
			int l;
			std::string to_convert = *iter;
			l = strtol(to_convert.c_str(), NULL, 10);
			data.push_back(l);
		}

		return data;
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		int count = 0;
		int prev = -1;

		for (int depth : ReadInput(filename))
		{
			if (prev != -1)
			{
				if (prev < depth)
				{
					count++;
				}
			}

			prev = depth;
		}

		return std::to_string(count);
	}

	int sum(const int* arr, const int size) const
	{
		int count = 0;
		for (int i = 0; i < size; i++)
		{
			count += arr[i];
		}
		return count;
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		int count = 0;
		int wind_a[3] = { 0, 0, 0 };
		int wind_b[3] = { 0, 0, 0 };

		std::vector<int> input = ReadInput(filename);
		for (int i = 0; i < (int)input.size() - 2; i++)
		{
			wind_a[0] = input[i];
			wind_a[1] = input[i + 1];
			wind_a[2] = input[i + 2];

			int sum_a = sum(wind_a, 3);

			wind_b[0] = input[i + 1];
			wind_b[1] = input[i + 2];
			wind_b[2] = input[i + 3];

			int sum_b = sum(wind_b, 3);

			if (sum(wind_b, 3) > sum(wind_a, 3))
			{
				count++;
			}
		}

		return std::to_string(count);
	}
};