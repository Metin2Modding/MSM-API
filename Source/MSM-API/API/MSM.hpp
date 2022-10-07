//  __  __ ____  __  __      _    ____ ___
// |  \/  / ___||  \/  |    / \  |  _ \_ _|
// | |\/| \___ \| |\/| |   / _ \ | |_) | |
// | |  | |___) | |  | |  / ___ \|  __/| |
// |_|  |_|____/|_|  |_| /_/   \_\_|  |___|
//
// From: https://github.com/Metin2Modding/MSM-API
// Contributors: https://github.com/Thorek777 & https://github.com/YellowSacSpider

#pragma once

#include <string>
#include <vector>
#include <fstream>

#define MSM_INCREASE_LAST_SHAPE_DATA(A) std::to_string(MSM::GetDataCount((A).GetDataLine("Group ShapeData")) + 1)

class MSM
{
	std::vector<std::string> FileContent;

	//
	// Find last bracket pos and return it.
	//
#if __cplusplus >= 201703L
	[[nodiscard]]
#endif

	int32_t GetLastBracketPos() const
	{
		int32_t
			Counter(0);

		const auto
			DataLine(GetDataLine("Group ShapeData"));

		for (const auto& It : FileContent)
		{
			if (It.find(DataLine) != std::string::npos)
				break;

			Counter++;
		}

		for (uint64_t It = Counter; It < FileContent.size(); It++)
		{
			if (FileContent[It].find('}') != std::string::npos)
				break;

			Counter++;
		}

		if (FileContent[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(Counter) + 1].find('}') != std::string::npos)
		{
			Counter++;
			return Counter;
		}

		for (uint64_t It = Counter; It < FileContent.size(); It++)
		{
			if (FileContent[It].find('}') != std::string::npos)
				break;

			Counter++;
		}

		return Counter;
	}

public:
	explicit MSM(const std::string& File)
	{
		std::ifstream Stream(File);

		if (!Stream)
			abort();

		std::string Line;

		while (std::getline(Stream, Line))
			FileContent.emplace_back(Line);
	}

	//
	// Return last data line. For example: We have 200 ShapeData so this function return Group ShapeData200.
	//
#if __cplusplus >= 201703L
	[[nodiscard]]
#endif

	std::string GetDataLine(const std::string& Line) const
	{
		std::string DataLine;

		for (const auto& It : FileContent)
			if (It.find(Line) != std::string::npos)
				DataLine = It;

		return DataLine;
	}

	//
	// We get number from data line. For example: Group ShapeData200 -> 200.
	//
	static int32_t GetDataCount(const std::string& Line)
	{
		int32_t Num(0);

		for (const auto It : Line)
			if (std::isdigit(It) != 0)
				Num = Num * 10 + It - '0';

		return Num;
	}

	//
	// Increase shape data count!
	//
	void IncreaseDataCount()
	{
		const auto
			DataLine(GetDataLine("ShapeDataCount"));

		const auto
			DataCount(GetDataCount(DataLine));

		for (auto& It : FileContent)
		{
			if (It.find(DataLine) != std::string::npos)
			{
				It = "\tShapeDataCount\t\t\t" + std::to_string(DataCount + 1);
				break;
			}
		}
	}

	//
	// We can insert some line to MSM.
	//
	void InsertLine(const std::string& Line)
	{
		FileContent.insert(FileContent.begin() + GetLastBracketPos(), Line);
	}

	//
	// Write inserted lines to MSM.
	//
	void WriteToFile(const std::string& File) const
	{
		std::ofstream Stream(File);

		for (const auto& It : FileContent)
			Stream << It << '\n';
	}
};
