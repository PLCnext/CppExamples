//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "../Helpers/Enums.hpp"


#include "../CounterComponent.hpp"

namespace ProgramComponentInteraction
{
using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;



// Asigning Program to component for the PLCNCLI
//#program
//#component(ProgramComponentInteraction::CounterComponent)
class   UpCounterProgram: 
        public ProgramBase, 
        private Loggable<UpCounterProgram>
{
public: // typedefs

public: // construction/destruction
    UpCounterProgram(CounterComponent& refCounterComponentArg, const String& name);
    UpCounterProgram(const UpCounterProgram& arg) = delete;
    virtual ~UpCounterProgram() = default;


public: // operators
    UpCounterProgram&  operator=(const UpCounterProgram& arg) = delete;

public: // properties


public: // operations
    void    Execute(void)override;

private: // fields
    CounterComponent& refCounterComponent;
    Progress progress =  Progress::Done;

 public: 
	//#port
	//#attributes(Output|Retain)
	//#name(UP_Counter)
    uint8 OP_Counter = 0; 
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class UpCounterProgram
inline UpCounterProgram::UpCounterProgram(CounterComponent& refCounterComponentArg, const String& name)
    : ProgramBase(name)
    , refCounterComponent(refCounterComponentArg)
{
    log.Info("UC Constructor");   
} 
}
