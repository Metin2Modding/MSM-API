#include "../API/MSM.hpp"

int main()
{
	// At first, we must type file to edit.
	MSM vMSM("WarriorM.msm");

	// Next, we must increase ShapeDataCount.
	vMSM.IncreaseDataCount();

	// If DataCount was increased, we can insert sample group to created earlier file.
	// One more thing - use '\t' instead of tabs, I did it just only for a better look.
	vMSM.InsertLine("	Group ShapeData" + LAST_SHAPE_DATA_INCREASE);
	vMSM.InsertLine("	{");
	vMSM.InsertLine("		ShapeIndex 81759");
	vMSM.InsertLine("		Model \"warrior_summer_2020.gr2\"");
	vMSM.InsertLine("		SourceSkin \"warrior_summer_2020_1.dds\"");
	vMSM.InsertLine("		TargetSkin \"warrior_summer_2020_2.dds\"");
	vMSM.InsertLine("	}");

	// And the most important thing - save our changes to new file.
	vMSM.WriteToFile("WarriorM.msm");
}
