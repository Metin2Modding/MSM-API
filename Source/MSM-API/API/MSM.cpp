//  __  __ ____  __  __      _    ____ ___
// |  \/  / ___||  \/  |    / \  |  _ \_ _|
// | |\/| \___ \| |\/| |   / _ \ | |_) | |
// | |  | |___) | |  | |  / ___ \|  __/| |
// |_|  |_|____/|_|  |_| /_/   \_\_|  |___|
//
// https://github.com/Metin2Modding/MSM-API

#include "MSM.hpp"

std::string MSM::GetDataLine(const std::string& vLine) const
{
	std::string vDataLine;

	for (auto& vIt : vFileContent)
		if (vIt.find(vLine) != std::string::npos)
			vDataLine = vIt;

	return vDataLine;
}

int MSM::GetDataCount(const std::string& vLine)
{
	int vNum = 0;

	for (const char vIt : vLine)
		if (std::isdigit(vIt) != 0)
			vNum = vNum * 10 + vIt - '0';

	return vNum;
}

int MSM::GetLastBracketPos() const
{
	int vCounter = 0;

	const std::string vDataLine = GetDataLine("Group ShapeData");

	for (const auto& vIt : vFileContent)
	{
		if (vIt.find(vDataLine) != std::string::npos)
			break;

		vCounter++;
	}

	for (unsigned long long i = vCounter; i < vFileContent.size(); i++)
	{
		// Find first bracket.
		if (vFileContent[i].find('}') != std::string::npos)
			break;

		vCounter++;
	}

	if (vFileContent[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(vCounter) + 1].find('}') != std::string::npos)
	{
		vCounter++;
		return vCounter;
	}

	for (unsigned long long i = vCounter; i < vFileContent.size(); i++)
	{
		// Find second bracket.
		if (vFileContent[i].find('}') != std::string::npos)
			break;

		vCounter++;
	}

	return vCounter;
}

void MSM::IncreaseDataCount()
{
	const auto vDataLine = GetDataLine("ShapeDataCount");
	const auto vDataCount = GetDataCount(vDataLine);

	for (auto& vIt : vFileContent)
	{
		if (vIt.find(vDataLine) != std::string::npos)
		{
			vIt = "\tShapeDataCount\t\t" + std::to_string(vDataCount + 1);
			break;
		}
	}
}

void MSM::InsertLine(const std::string& vLine)
{
	vFileContent.insert(vFileContent.begin() + GetLastBracketPos(), vLine);
}

void MSM::WriteToFile(const std::string& vFile) const
{
	std::ofstream vFileStream(vFile);

	if (!vFileStream)
		return;

	for (const auto& vIt : vFileContent)
		vFileStream << vIt << '\n';
}
