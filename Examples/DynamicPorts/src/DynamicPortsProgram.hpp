﻿/******************************************************************************
 *
 * Copyright (c) 2025 Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 ******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/DynamicPortsProgramBase.hpp"
#include "Arp/Base/Commons/Logging/Log.hpp"
#include "DynamicPortsComponent.hpp"
#include "DynamicPortsLibrary.hpp"

#include <fstream>
#include "nlohmann/json.hpp"

namespace DynamicPorts
{

using namespace Arp;
using namespace Arp::Base::Commons::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(DynamicPorts::DynamicPortsComponent)
class DynamicPortsProgram : public DynamicPortsProgramBase<DynamicPortsProgram,20>, private Loggable<DynamicPortsProgram>
{
public: // typedefs

public: // construction/destruction
    DynamicPortsProgram(DynamicPorts::DynamicPortsComponent& dynamicPortsComponentArg, const String& name);
    DynamicPortsProgram(const DynamicPortsProgram& arg) = delete;
    virtual ~DynamicPortsProgram() = default;

public: // operators
    DynamicPortsProgram&  operator=(const DynamicPortsProgram& arg) = delete;

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

    // An empty double-ended queue that will hold digital device values
    // (note that a vector of booleans will not work in this case).
    std::deque<boolean> digital_device;

private: // fields
    DynamicPorts::DynamicPortsComponent& dynamicPortsComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline DynamicPortsProgram::DynamicPortsProgram(DynamicPorts::DynamicPortsComponent& dynamicPortsComponentArg, const String& name)
: DynamicPortsProgramBase(name, DynamicPortsLibrary::GetInstance().GetTypeDomain())
, dynamicPortsComponent(dynamicPortsComponentArg)
{
    // Initialise the logger
    Log::Initialize("Dynamic Ports Example");

    // Read configuration from a specific file, in JSON format.
    // For simplicity, no error checks are done on the configuration.
    using json = nlohmann::json;

    std::ifstream ifs("/opt/plcnext/dynaports.json", std::ios::in);
    json config = json::parse(ifs);

    // Allocate the configured number of digital devices
    digital_device.resize(config["digital_device"].size(), false);

    // Create one GDS port for each digital device, with the user-specified configuration
    int i = 0;
    for (auto dd : config["digital_device"])
    {
        this->AddPort(dd["name"], digital_device.at(i), dd["attributes"]);
        i++;
    }

    // Change the program type definition to use dynamic ports
    this->ReplaceProgramTypeDefinition();

    TypeDefinition typeDefinition(this->GetDynamicPortsBuilder().GetTypeDefinition());
    Log::Info("Number of dynamic ports used: {0}", static_cast<uint16>(typeDefinition.GetFields().size()));
}

} // end of namespace DynamicPorts
