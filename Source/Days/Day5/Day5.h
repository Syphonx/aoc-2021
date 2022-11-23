#pragma once

#include "Day.h"
#include <algorithm>

//#define TEST_INPUT

struct Vector2
{
	Vector2()
		: x(0)
		, y(0)
	{
	}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	int x, y;
};

struct AABB
{
	int minX, maxX;
	int minY, maxY;
};

struct Segment
{
	Segment()
		: start()
		, end()
	{
	}

	void Parse(const std::string& input)
	{
		std::vector<std::string> parts = SplitLineToStrings(input, ' ');
		std::vector<std::string> numbers = SplitLineToStrings(parts[0], ',');
		start.x = std::stoi(numbers[0]);
		start.y = std::stoi(numbers[1]);
		numbers = SplitLineToStrings(parts[2], ',');
		end.x = std::stoi(numbers[0]);
		end.y = std::stoi(numbers[1]);
	}

	bool operator ==(const Segment& other) const
	{
		return start == other.start && end == other.end;
	}

	bool IsHorizontalOrVertical() const
	{
		return start.x == end.x || start.y == end.y;
	}

	AABB GetAABB() const
	{
		AABB aabb;
		aabb.minX = std::min(start.x, end.x);
		aabb.minY = std::min(start.y, end.y);
		aabb.maxX = std::max(start.x, end.x);
		aabb.maxY = std::max(start.y, end.y);
		return aabb;
	}

	static bool Intersect(const AABB left, const AABB& right)
	{
		return
			(left.minX <= right.maxX && left.maxX >= right.minX) &&
			(left.minY <= right.maxY && left.maxY >= right.minY);
	}

	Vector2 start;
	Vector2 end;
};

class Day5
	: public AocDay
{
public:
	Day5()
		: AocDay(5)
	{
	}

	std::vector<std::string> GetLines(const std::string& filename)
	{
#ifdef TEST_INPUT
		return {
			"0,9 -> 5,9",
			"8,0 -> 0,8",
			"9,4 -> 3,4",
			"2,2 -> 2,1",
			"7,0 -> 7,4",
			"6,4 -> 2,0",
			"0,9 -> 2,9",
			"3,4 -> 1,4",
			"0,0 -> 8,8",
			"5,5 -> 8,2"
		};
#endif
		std::vector<std::string> lines;
		ReadAsStrings(filename, lines);
		return lines;
	}

	std::vector<Segment> ParseSegments(const std::string& filename)
	{
		std::vector<std::string> input = GetLines(filename);
		std::vector<Segment> data;

		for (const std::string& line : input)
		{
			Segment segment;
			segment.Parse(line);
			data.push_back(segment);
		}

		return data;
	}

	bool inRange(int low, int high, unsigned x)
	{
		return  ((x - low) <= (high - low));
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		std::vector<Segment> segments = ParseSegments(filename);
		int sum = 0;

		for (int i = 0; i < (int)segments.size(); i++)
		{
			Segment& left = segments[i];
			AABB laabb = left.GetAABB();

			if (!left.IsHorizontalOrVertical())
			{
				continue;
			}

			for (int j = i + 1; j < (int)segments.size(); j++)
			{
				Segment& right = segments[j];
				AABB raabb = right.GetAABB();

				if (left == right)
				{
					continue;
				}

				if (!right.IsHorizontalOrVertical())
				{
					continue;
				}

				if (Segment::Intersect(laabb, raabb))
				{
					if (left.start.x == left.end.x) // vertical
					{
						if (right.start.x == right.end.x) // vertical
						{
							for (int x = std::min(left.start.y, left.end.y); x <= std::max(left.start.y, left.end.y); x++)
							{
								if (inRange(std::min(right.start.y, right.end.y), std::max(right.start.y, right.end.y), x))
								{
									sum++;
								}
							}
						}
						else if (right.start.y == right.end.y) // horizontal
						{
							sum++;
						}
					}
					else if (left.start.y == left.end.y) // horizontal
					{
						if (right.start.x == right.end.x) // vertical
						{
							sum++;
						}
						else if (right.start.y == right.end.y) // horizontal
						{
							for (int x = std::min(right.start.x, right.end.x); x <= std::max(right.start.x, right.end.x); x++)
							{
								if (inRange(std::min(left.start.x, left.end.x), std::max(left.start.x, left.end.x), x))
								{
									sum++;
								}
							}
						}
					}
				}
			}
		}

		return std::to_string(sum);
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		return std::to_string(0);
	}
};
