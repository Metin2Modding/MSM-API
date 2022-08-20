#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>




class MSM {
private:
	std::ifstream msm_file;
	std::vector<std::string> file_content;
	std::string file_line;
public:
	MSM() {}
	~MSM() {}

	MSM(std::string file_path) {
		msm_file.open(file_path);
		if (!msm_file.good())
		{
			std::cout << "error while reading - no file or something wrong\n";
		}
		else {
			while (std::getline(msm_file, file_line)) {
				file_content.emplace_back(file_line);
			}
			for (int i = 0; i < file_content.size(); i++) {
				std::size_t found = file_content[i].find(getDataLine("ShapeDataCount"));
				if (found != std::string::npos) {
					file_content[i] = "\tShapeDataCount\t\t" + std::to_string(getDataCount(getDataLine("ShapeDataCount")) + 1);
					break;
				}
			}
			file_content.insert(file_content.begin() + getLastBracketPos(), "\tGroup ShapeData" + std::to_string(getDataCount(getDataLine("Group ShapeData"))+1));
			file_content.insert(file_content.begin() + getLastBracketPos(), "\t{");
			file_content.insert(file_content.begin() + getLastBracketPos(), "\t\tShapeIndex			41767");
			file_content.insert(file_content.begin() + getLastBracketPos(), "\t\tModel				\"warrior_summer_2020.GR2\"");
			file_content.insert(file_content.begin() + getLastBracketPos(), "\t\tSourceSkin			\"warrior_summer_2020_1.dds\"");
			file_content.insert(file_content.begin() + getLastBracketPos(), "\t\tTargetSkin			\"warrior_summer_2020_2.dds\"");
			file_content.insert(file_content.begin() + getLastBracketPos(), "\t}");

			for (const auto& val : file_content) {
				std::cout << val << "\n";
			}

		}

	}

	std::string getDataLine(std::string line); // Return last data line. For example: We have 200 ShapeData so this function return Group ShapeData200
	int getDataCount(std::string line); //we get number from data line. For example: Group ShapeData200 -> 200
	int getLastBracketPos(); // find last bracket pos and return it
	void insertLine(std::string line);

};




