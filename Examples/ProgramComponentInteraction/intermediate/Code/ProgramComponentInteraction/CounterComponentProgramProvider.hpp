//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace ProgramComponentInteraction 
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class CounterComponent;

class CounterComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    CounterComponentProgramProvider(CounterComponent& refCounterComponentArg);
    virtual ~CounterComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    CounterComponentProgramProvider(const CounterComponentProgramProvider& arg) = delete;
    CounterComponentProgramProvider& operator=(const CounterComponentProgramProvider& arg) = delete;

private: // fields
	CounterComponent& refCounterComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CounterComponentProgramProvider

inline CounterComponentProgramProvider::CounterComponentProgramProvider(CounterComponent& refCounterComponentArg)
	: refCounterComponent(refCounterComponentArg)
{
}

} // end of namespace ProgramComponentInteraction
