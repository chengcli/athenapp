// athena
#include <athena/outputs/user_outputs.hpp>

void DebugOutput::WriteOutputFile(Mesh *pm, ParameterInput *pin, bool flag)
{}

void NetcdfOutput::WriteOutputFile(Mesh *pm, ParameterInput *pin, bool flag)
{}

void NetcdfOutput::CombineBlocks()
{}

void PnetcdfOutput::WriteOutputFile(Mesh *pm, ParameterInput *pin, bool flag)
{}

void FITSOutput::WriteOutputFile(Mesh *pm, ParameterInput *pin, bool flag)
{}

void OutputType::loadUserOutputData(MeshBlock *pmb)
{}
