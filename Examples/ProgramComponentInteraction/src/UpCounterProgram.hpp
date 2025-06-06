//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
//

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "CounterComponent.hpp"

#include "Helpers/Enums.hpp"

namespace ProgramComponentInteraction
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(ProgramComponentInteraction::CounterComponent)
class UpCounterProgram : public ProgramBase, private Loggable<UpCounterProgram>
{
public: // typedefs

public: // construction/destruction
    UpCounterProgram(ProgramComponentInteraction::CounterComponent& counterComponentArg, const String& name);

public: // operators

public: // properties

public: // operations
    void    Execute() override;

private: // fields
    ProgramComponentInteraction::CounterComponent& counterComponent;

private: // fields
    Progress progress =  Progress::Done;

 public:
	//#port
	//#attributes(Output|Retain)
	//#name(UP_Counter)
    uint8 OP_Counter = 0;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline UpCounterProgram::UpCounterProgram(ProgramComponentInteraction::CounterComponent& counterComponentArg, const String& name)
: ProgramBase(name)
, counterComponent(counterComponentArg)
{
}

} // end of namespace ProgramComponentInteraction
