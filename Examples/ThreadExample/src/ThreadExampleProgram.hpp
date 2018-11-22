#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"

namespace ThreadExample 
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//TODO not neccessary here. Include header instead
//forwards
class ThreadExampleComponent;

//#component(ThreadExampleComponent)
class ThreadExampleProgram : public ProgramBase, private Loggable<ThreadExampleProgram>
{
public: // typedefs

public: // construction/destruction
    ThreadExampleProgram(ThreadExampleComponent& refThreadExampleComponentArg, const String& name);
    ThreadExampleProgram(const ThreadExampleProgram& arg) = delete;
    virtual ~ThreadExampleProgram() = default;

public: // operators
    ThreadExampleProgram&  operator=(const ThreadExampleProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: // ports

private: // fields
	ThreadExampleComponent& refThreadExampleComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline ThreadExampleProgram::ThreadExampleProgram(ThreadExampleComponent& refThreadExampleComponentArg, const String& name)
: ProgramBase(name)
, refThreadExampleComponent(refThreadExampleComponentArg)
{
}

} // end of namespace ThreadExample
