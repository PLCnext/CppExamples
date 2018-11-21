#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace CppDataTypeTest 
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class CppDataTypeTestComponent;

class CppDataTypeTestComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    CppDataTypeTestComponentProgramProvider(CppDataTypeTestComponent& refCppDataTypeTestComponentArg);
    virtual ~CppDataTypeTestComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    CppDataTypeTestComponentProgramProvider(const CppDataTypeTestComponentProgramProvider& arg) = delete;
    CppDataTypeTestComponentProgramProvider& operator=(const CppDataTypeTestComponentProgramProvider& arg) = delete;

private: // fields
	CppDataTypeTestComponent& refCppDataTypeTestComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CppDataTypeTestComponentProgramProvider

inline CppDataTypeTestComponentProgramProvider::CppDataTypeTestComponentProgramProvider(CppDataTypeTestComponent& refCppDataTypeTestComponentArg)
	: refCppDataTypeTestComponent(refCppDataTypeTestComponentArg)
{
}

} // end of namespace CppDataTypeTest
