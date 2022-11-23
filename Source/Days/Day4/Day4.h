#pragma once

#include "Day.h"

#include <vector>

//#define TEST_INPUT

struct BingoEntry
{
public:
	BingoEntry(int value)
		: value(value)
		, marked(false)
	{
	}

	int value;
	bool marked;
};

struct BingoCard
{
public:
	BingoCard()
		: numbers()
		, winningOrder(-1)
		, winningValue(-1)
	{
	}

	void ParseLine(const std::string& line)
	{
		const auto& ints = SplitStringIntoInts(line, ' ');
		numbers.insert(numbers.end(), ints.begin(), ints.end());
	}

	void MarkEntry(int value)
	{
		for (BingoEntry& entry : numbers)
		{
			if (entry.value == value)
			{
				entry.marked = true;
			}
		}
	}

	int MapIndex(int x, int y) const
	{
		return x + 5 * y;
	}

	bool CheckForWinner() const
	{
		bool result = false;

		for (int y = 0; y < 5; y++)
		{
			bool winner = true;
			for (int x = 0; x < 5; x++)
			{
				if (!numbers.at(MapIndex(x, y)).marked)
				{
					winner = false;
					break;
				}
			}

			if (winner)
			{
				result = true;
				break;
			}
		}

		if (result)
		{
			return true;
		}

		for (int x = 0; x < 5; x++)
		{
			bool winner = true;
			for (int y = 0; y < 5; y++)
			{
				if (!numbers.at(MapIndex(x, y)).marked)
				{
					winner = false;
					break;
				}
			}

			if (winner)
			{
				result = true;
				break;
			}
		}

		if (result)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int SumUnmarked() const
	{
		int sum = 0;

		for (const BingoEntry& entry : numbers)
		{
			if (!entry.marked)
			{
				sum += entry.value;
			}
		}

		return sum;
	}

	std::vector<BingoEntry> numbers;
	int winningOrder;
	int winningValue;
};

class Day4
	: public AocDay
{
public:
	Day4()
		: AocDay(1)
	{
	}

	std::vector<std::string> GetLines(const std::string& filename)
	{
#ifdef TEST_INPUT
		return {
			"7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
			"",
			"22 13 17 11  0",
			" 8  2 23  4 24",
			"21  9 14 16  7",
			" 6 10  3 18  5",
			" 1 12 20 15 19",
			"",
			" 3 15  0  2 22",
			" 9 18 13 17  5",
			"19  8  7 25 23",
			"20 11 10 24  4",
			"14 21 16 12  6",
			"",
			"14 21 17 24  4",
			"10 16 15  9 19",
			"18  8 23 26 20",
			"22 11 13  6  5",
			" 2  0 12  3  7"
		};
#endif

		std::vector<std::string> lines;
		ReadAsStrings(filename, lines);
		return lines;
	}

	std::vector<int> ReadDraws(const std::string& filename)
	{
		std::vector<std::string> lines = GetLines(filename);
		return SplitStringIntoInts(lines[0], ',');
	}

	std::vector<BingoCard> ReadCards(const std::string& filename)
	{
		std::vector<std::string> lines = GetLines(filename);
		std::vector<BingoCard> cards;

		lines.erase(lines.begin(), lines.begin() + 2);

		while (!lines.empty())
		{
			BingoCard card;
			if ((*lines.begin()).empty())
			{
				lines.erase(lines.begin());
			}

			for (size_t i = 0; i < 5; i++)
			{
				card.ParseLine(*(lines.begin() + i));
			}

			lines.erase(lines.begin(), lines.begin() + 5);
			cards.push_back(card);
		}

		return cards;
	}

	int CheckForWinner(const std::vector<BingoCard>& cards)
	{
		for (size_t i = 0; i < cards.size(); i++)
		{
			if (cards.at(i).CheckForWinner())
			{
				return (int)i;
			}
		}

		return -1;
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		std::vector<int> draws = ReadDraws(filename);
		std::vector<BingoCard> cards = ReadCards(filename);

		int winningCardIndex;
		int winningCardValue;

		for (size_t i = 0; i < draws.size(); i++)
		{
			int draw = draws.at(i);
			
			for (BingoCard& card : cards)
			{
				card.MarkEntry(draw);
			}

			int index = CheckForWinner(cards);
			if (index != -1)
			{
				winningCardIndex = index;
				winningCardValue = draw;
				break;
			}
		}

		const BingoCard& winningCard = cards.at(winningCardIndex);
		const int unmarkedSum = winningCard.SumUnmarked();

		return std::to_string(unmarkedSum * winningCardValue);
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		std::vector<int> draws = ReadDraws(filename);
		std::vector<BingoCard> cards = ReadCards(filename);

		int winningOrder = -1;

		for (size_t i = 0; i < draws.size(); i++)
		{
			int draw = draws.at(i);

			for (BingoCard& card : cards)
			{
				card.MarkEntry(draw);
			}

			bool finished = true;
			for (size_t i = 0; i < cards.size(); i++)
			{
				BingoCard& card = cards.at(i);
				if (card.CheckForWinner())
				{
					if (card.winningOrder == -1)
					{
						winningOrder++;
						card.winningOrder = winningOrder;
						card.winningValue = draw;
					}
				}
				else
				{
					finished = false;
				}
			}

			if (finished)
			{
				break;
			}
		}

		int lastWinningOrder = -1;
		int lastWinningIndex = -1;

		for (int i = 0; i < cards.size(); i++)
		{
			BingoCard& card = cards.at(i);
			if (card.winningOrder > lastWinningOrder)
			{
				lastWinningOrder = card.winningOrder;
				lastWinningIndex = i;
			}
		}

		const BingoCard& losingCard = cards.at(lastWinningIndex);
		const int unmarkedSum = losingCard.SumUnmarked();

		return std::to_string(unmarkedSum * losingCard.winningValue);
	}
};