#include "../API/MSM.h"

int main()
{
	// At first, we must type file to edit.
	MSM vMSM("WarriorM.msm");

	// Next, we must increase ShapeDataCount.
	vMSM.IncreaseDataCount();

	// If DataCount was increased, we can insert sample group to created earlier file.
	vMSM.InsertLine("\tGroup ShapeData" + std::to_string(MSM::GetDataCount(vMSM.GetDataLine("Group ShapeData")) + 1));
	vMSM.InsertLine("\t{");
	vMSM.InsertLine("\t\tShapeIndex 81759");
	vMSM.InsertLine("\t\tModel \"warrior_summer_2020.GR2\"");
	vMSM.InsertLine("\t\tSourceSkin \"warrior_summer_2020_1.dds\"");
	vMSM.InsertLine("\t\tTargetSkin \"warrior_summer_2020_2.dds\"");
	vMSM.InsertLine("\t}");

	// And the most important thing - save our changes to new file.
	vMSM.WriteToFile("WarriorM.msm");
}
