#include "MSM.h"


std::string MSM::getDataLine(std::string line) {
	std::string DataLine;
	int shapedata_count = 0;
	for (const auto& val : file_content) {
		std::size_t found = val.find(line);
		if (found != std::string::npos) {
			DataLine = val;
		}
	}

	return DataLine;
}

int MSM::getDataCount(std::string line) {
	int number = 0;
	for (int i = 0; i < line.size(); i++) {
		if(std::isdigit(line[i]))
			number = number * 10 + line[i] - '0';
	}

	return number;
}

int MSM::getLastBracketPos() {
	int counter = 0;
	for (const auto& val : file_content) {
		std::size_t found = val.find(MSM::getDataLine("Group ShapeData"));
		if (found != std::string::npos) break;
		counter++;
	}

	//WHY THIS WORK?!
	for (int i = counter; i < file_content.size(); i++) {
		std::size_t found = file_content[i].find("}"); // Find first bracket
		if (found != std::string::npos) {
			break;
		}
		counter++;
	}
	
	if (file_content[counter+1].find("}") != std::string::npos) {
		counter++;
		return counter;
	}

	for (int i = counter; i < file_content.size(); i++) {
		std::size_t found = file_content[i].find("}"); // Find second bracket
		if (found != std::string::npos) {
			break;
		}
		counter++;
	}

	return counter;
}

void MSM::insertLine(std::string line) {
	file_content.insert(file_content.begin() + getLastBracketPos(), line);
}