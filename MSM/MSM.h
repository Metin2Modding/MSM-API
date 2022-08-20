#pragma once

#include <string>
#include <vector>
#include <fstream>

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

		if (!vMSMFile)
			return;

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
	 * We can insert some line to MSM.
	 */
	void InsertLine(const std::string& vLine);

	/*
	 * Increase shape data count!
	 */
	void IncreaseDataCount();

	/*
	 * Write inserted lines to MSM.
	 */
	void WriteToFile(const std::string& vFile) const;
};
