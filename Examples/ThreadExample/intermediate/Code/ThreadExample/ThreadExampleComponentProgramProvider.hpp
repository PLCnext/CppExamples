#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace ThreadExample 
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class ThreadExampleComponent;

class ThreadExampleComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    ThreadExampleComponentProgramProvider(ThreadExampleComponent& refThreadExampleComponentArg);
    virtual ~ThreadExampleComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    ThreadExampleComponentProgramProvider(const ThreadExampleComponentProgramProvider& arg) = delete;
    ThreadExampleComponentProgramProvider& operator=(const ThreadExampleComponentProgramProvider& arg) = delete;

private: // fields
	ThreadExampleComponent& refThreadExampleComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ThreadExampleComponentProgramProvider

inline ThreadExampleComponentProgramProvider::ThreadExampleComponentProgramProvider(ThreadExampleComponent& refThreadExampleComponentArg)
	: refThreadExampleComponent(refThreadExampleComponentArg)
{
}

} // end of namespace ThreadExample
