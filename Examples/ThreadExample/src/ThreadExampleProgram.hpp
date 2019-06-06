/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 *  ThreadExampleProgram.hpp
 *
 *  Created on: 16.05.2019
 *  	Author: Eduard Münz, Oliver Warneke
 *
 ******************************************************************************/

/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/


#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "ThreadExampleComponent.hpp"

namespace ThreadExample
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(ThreadExample::ThreadExampleComponent)
class ThreadExampleProgram : public ProgramBase, private Loggable<ThreadExampleProgram>
{
public: // typedefs

public: // construction/destruction
    ThreadExampleProgram(ThreadExample::ThreadExampleComponent& threadExampleComponentArg, const String& name);
    ThreadExampleProgram(const ThreadExampleProgram& arg) = delete;
    virtual ~ThreadExampleProgram() = default;

public: // operators
    ThreadExampleProgram&  operator=(const ThreadExampleProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
           =====
           Ports are defined in the following way:
           //#port
           //#attributes(Input|Retain)
           //#name(NameOfPort)
           boolean portField;

           The attributes comment define the port attributes and is optional.
           The name comment defines the name of the port and is optional. Default is the name of the field.
        */

    //#port
    //#attributes(Output|Retain)
    //#name(i_pCounter)
    int16 i_pCounter;

private: // fields
    ThreadExample::ThreadExampleComponent& threadExampleComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline ThreadExampleProgram::ThreadExampleProgram(ThreadExample::ThreadExampleComponent& threadExampleComponentArg, const String& name)
: ProgramBase(name)
, threadExampleComponent(threadExampleComponentArg)
{
}

} // end of namespace ThreadExample
