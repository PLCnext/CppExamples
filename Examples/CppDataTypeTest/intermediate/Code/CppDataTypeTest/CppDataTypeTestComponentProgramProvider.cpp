#include "CppDataTypeTestComponentProgramProvider.hpp"
#include "CppDataTypeTest/CppDataTypeTestProgram.hpp"

namespace CppDataTypeTest 
{

IProgram::Ptr CppDataTypeTestComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "CppDataTypeTestProgram"){ return std::make_shared<::CppDataTypeTest::CppDataTypeTestProgram>(this->refCppDataTypeTestComponent, programName); }

    // else unknown program
    return nullptr;
    
}

} // end of namespace CppDataTypeTest
