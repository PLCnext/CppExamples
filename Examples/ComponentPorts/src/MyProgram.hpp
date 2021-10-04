/******************************************************************************
 *
 * Copyright (c) 2021 Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 ******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "ComponentWithPorts.hpp"

namespace ComponentPorts
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(ComponentPorts::ComponentWithPorts)
class MyProgram : public ProgramBase, private Loggable<MyProgram>
{
public: // typedefs

public: // construction/destruction
    MyProgram(ComponentPorts::ComponentWithPorts& componentWithPortsArg, const String& name);
    MyProgram(const MyProgram& arg) = delete;
    virtual ~MyProgram() = default;

public: // operators
    MyProgram&  operator=(const MyProgram& arg) = delete;

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

private: // fields
    ComponentPorts::ComponentWithPorts& componentWithPorts;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline MyProgram::MyProgram(ComponentPorts::ComponentWithPorts& componentWithPortsArg, const String& name)
: ProgramBase(name)
, componentWithPorts(componentWithPortsArg)
{
}

} // end of namespace ComponentPorts
