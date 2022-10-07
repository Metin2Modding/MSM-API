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
	File.IncreaseDataCount();

	//
	// If DataCount was increased, we can insert sample group to file.
	// One more thing - use '\t' instead of tabs, I did it just only for a better look.
	//
	File.InsertLine("	Group ShapeData" + MSM_INCREASE_LAST_SHAPE_DATA(File));
	File.InsertLine("	{");
	File.InsertLine("		ShapeIndex			41768");
	File.InsertLine("		Model				""\"\"");
	File.InsertLine("		SourceSkin			""\"\"");
	File.InsertLine("		TargetSkin			""\"\"");
	File.InsertLine("	}");

	//
	// And last thing - save our changes to file.
	//
	File.WriteToFile("WarriorM.msm");
}
