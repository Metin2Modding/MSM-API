#include "../API/MSM.hpp"

const std::string MSM_EMPTY_STRING("\"\"");

int main()
{
	// At first, we must type file to edit.
	MSM File("WarriorM.msm");

	// Next, we must increase ShapeDataCount.
	File.IncreaseDataCount();

	// If DataCount was increased, we can insert sample group to created earlier file.
	// One more thing - use '\t' instead of tabs, I did it just only for a better look.
	File.InsertLine("	Group ShapeData" + MSM_INCREASE_LAST_SHAPE_DATA(File));
	File.InsertLine("	{");
	File.InsertLine("		ShapeIndex 41768");
	File.InsertLine("		Model " + MSM_EMPTY_STRING);
	File.InsertLine("		SourceSkin " + MSM_EMPTY_STRING);
	File.InsertLine("		TargetSkin " + MSM_EMPTY_STRING);
	File.InsertLine("	}");

	// And the most important thing - save our changes to new file.
	File.WriteToFile("WarriorM.msm");
}
