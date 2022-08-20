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

#define LAST_SHAPE_DATA_INCREASE std::to_string(MSM::GetDataCount(vMSM.GetDataLine("Group ShapeData")) + 1)

class MSM
{
	std::vector<std::string> vFileContent;

	/*
	 * Find last bracket pos and return it
	 */
	[[nodiscard]] int GetLastBracketPos() const;

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
	[[nodiscard]] std::string GetDataLine(const std::string& vLine) const;

	/*
	 * We get number from data line. For example: Group ShapeData200 -> 200
	 */
	static int GetDataCount(const std::string& vLine);

	/*
	 * Increase shape data count!
	 */
	void IncreaseDataCount();

	/*
	 * We can insert some line to MSM.
	 */
	void InsertLine(const std::string& vLine);

	/*
	 * Write inserted lines to MSM.
	 */
	void WriteToFile(const std::string& vFile) const;
};
