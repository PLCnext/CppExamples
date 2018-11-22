#include "ThreadExampleComponentProgramProvider.hpp"
#include "ThreadExample/ThreadExampleProgram.hpp"

namespace ThreadExample 
{

IProgram::Ptr ThreadExampleComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "ThreadExampleProgram"){ return std::make_shared<::ThreadExample::ThreadExampleProgram>(this->refThreadExampleComponent, programName); }

    // else unknown program
    return nullptr;
    
}

} // end of namespace ThreadExample
