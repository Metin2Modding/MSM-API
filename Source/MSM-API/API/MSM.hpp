//  __  __ ____  __  __      _    ____ ___
// |  \/  / ___||  \/  |    / \  |  _ \_ _|
// | |\/| \___ \| |\/| |   / _ \ | |_) | |
// | |  | |___) | |  | |  / ___ \|  __/| |
// |_|  |_|____/|_|  |_| /_/   \_\_|  |___|
//
// https://github.com/Metin2Modding/MSM-API

#pragma once

#include <string>
#include <vector>
#include <fstream>

#define MSM_INCREASE_LAST_SHAPE_DATA std::to_string(MSM::GetDataCount(vMSM.GetDataLine("Group ShapeData")) + 1)

class MSM
{
	std::vector<std::string> vFileContent;

	/*
	 * Find last bracket pos and return it
	 */
	[[nodiscard]] int GetLastBracketPos() const
	{
		int vCounter = 0; const std::string& vDataLine(GetDataLine("Group ShapeData"));

		for (const std::string& vIt : vFileContent)
		{
			if (vIt.find(vDataLine) != std::string::npos)
				break;

			vCounter++;
		}

		for (unsigned long long vIt = vCounter; vIt < vFileContent.size(); vIt++)
		{
			// Find first bracket.
			if (vFileContent[vIt].find('}') != std::string::npos)
				break;

			vCounter++;
		}

		if (vFileContent[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(vCounter) + 1].find('}') != std::string::npos)
		{
			vCounter++;
			return vCounter;
		}

		for (unsigned long long vIt = vCounter; vIt < vFileContent.size(); vIt++)
		{
			// Find second bracket.
			if (vFileContent[vIt].find('}') != std::string::npos)
				break;

			vCounter++;
		}

		return vCounter;
	}

public:
	explicit MSM(const std::string& vFilePath)
	{
		std::ifstream vMSMFile(vFilePath);

		if (!vMSMFile.is_open())
			_Exit(1);

		std::string vFileLine;

		while (std::getline(vMSMFile, vFileLine))
			vFileContent.emplace_back(vFileLine);
	}

	/*
	 * Return last data line. For example: We have 200 ShapeData so this function return Group ShapeData200
	 */
	[[nodiscard]] std::string GetDataLine(const std::string& vLine) const
	{
		std::string vDataLine;

		for (const std::string& vIt : vFileContent)
			if (vIt.find(vLine) != std::string::npos)
				vDataLine = vIt;

		return vDataLine;
	}

	/*
	 * We get number from data line. For example: Group ShapeData200 -> 200
	 */
	static int GetDataCount(const std::string& vLine)
	{
		int vNum = 0;

		for (const char& vIt : vLine)
			if (std::isdigit(vIt) != 0)
				vNum = vNum * 10 + vIt - '0';

		return vNum;
	}

	/*
	 * Increase shape data count!
	 */
	void IncreaseDataCount()
	{
		const std::string& vDataLine(GetDataLine("ShapeDataCount")); const int& vDataCount(GetDataCount(vDataLine));

		for (std::string& vIt : vFileContent)
		{
			if (vIt.find(vDataLine) != std::string::npos)
			{
				vIt = "\tShapeDataCount\t\t" + std::to_string(vDataCount + 1);
				break;
			}
		}
	}

	/*
	 * We can insert some line to MSM.
	 */
	void InsertLine(const std::string& vLine)
	{
		vFileContent.insert(vFileContent.begin() + GetLastBracketPos(), vLine);
	}

	/*
	 * Write inserted lines to MSM.
	 */
	void WriteToFile(const std::string& vFile) const
	{
		std::ofstream vFileStream(vFile);

		if (!vFileStream)
			return;

		for (const std::string& vIt : vFileContent)
			vFileStream << vIt << '\n';
	}
};
