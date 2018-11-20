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

//forward declaration
//class CounterComponent;

// Asigning Program to component for the PLCNCLI
//#component(CounterComponent)
class   DownCounterProgram : 
        public ProgramBase , 
        private Loggable<DownCounterProgram>
{
public: // typedefs

public: // construction/destruction
    DownCounterProgram(CounterComponent& refCounterComponentArg, const String& name);
    DownCounterProgram(const DownCounterProgram& arg) = delete;
    virtual ~DownCounterProgram(void) = default;

public: // operators
    DownCounterProgram&  operator=(const DownCounterProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute(void)override;

private: // fields
    CounterComponent& refCounterComponent;
    Progress progress = Progress::Done;
//    IComponentInteraction& const CCRef= nullptr;
public: 
    // outports;
 //#port(Output)
    uint8 OP_Counter = 255;    
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class DownCounterProgram
inline DownCounterProgram::DownCounterProgram(CounterComponent& refCounterComponentArg, const String& name)
    : ProgramBase(name)
    , refCounterComponent(refCounterComponentArg)  
{
   log.Info("DC Constructor"); 
}


}
