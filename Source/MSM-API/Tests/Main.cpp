#include "../API/MSM.hpp"

const std::string MSM_EMPTY_STRING("\"\"");

int main()
{
	// At first, we must type file to edit.
	MSM vMSM("WarriorM.msm");

	// Next, we must increase ShapeDataCount.
	vMSM.IncreaseDataCount();

	// If DataCount was increased, we can insert sample group to created earlier file.
	// One more thing - use '\t' instead of tabs, I did it just only for a better look.
	vMSM.InsertLine("	Group ShapeData" + MSM_INCREASE_LAST_SHAPE_DATA);
	vMSM.InsertLine("	{");
	vMSM.InsertLine("		ShapeIndex 41768");
	vMSM.InsertLine("		Model " + MSM_EMPTY_STRING);
	vMSM.InsertLine("		SourceSkin " + MSM_EMPTY_STRING);
	vMSM.InsertLine("		TargetSkin " + MSM_EMPTY_STRING);
	vMSM.InsertLine("	}");

	// And the most important thing - save our changes to new file.
	vMSM.WriteToFile("WarriorM.msm");
}
