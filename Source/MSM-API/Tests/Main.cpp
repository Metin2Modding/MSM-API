#include "../API/MSM.hpp"

int main()
{
	//
	// At first, open specified file.
	//
	MSM File("WarriorM.msm");

	//
	// Increase HairDataCount / ShapeDataCount.
	//
	File.IncreaseDataCount("ShapeDataCount");

	//
	// If DataCount was increased, we can insert sample group to file.
	// One more thing - use '\t' instead of tabs, I did it just only for a better look.
	//
	const std::string Group("Group ShapeData");

	File.InsertLine(Group, "	" + Group, true);
	File.InsertLine(Group, "	{");
	File.InsertLine(Group, "		ShapeIndex			41768");
	File.InsertLine(Group, "		Model				""\"\"");
	File.InsertLine(Group, "		SourceSkin			""\"\"");
	File.InsertLine(Group, "		TargetSkin			""\"\"");
	File.InsertLine(Group, "	}");

	//
	// And last thing - save our changes to file.
	//
	File.WriteToFile("WarriorM.msm");
}
