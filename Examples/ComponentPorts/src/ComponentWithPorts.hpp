/******************************************************************************
 *
 * Copyright (c) 2024 Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 ******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Base/Acf/Commons/ComponentBase.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "ComponentWithPortsProgramProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

// added to the template
#include "Arp/Plc/Domain/Commons/PlcStartKind.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"

namespace ComponentPorts
{

using namespace Arp;
using namespace Arp::Base::Acf::Commons;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

// "using" added to the template
using namespace Arp::Plc::Domain::Commons;
using namespace Arp::Plc::Commons::Domain;

//#component
class ComponentWithPorts : public ComponentBase, public ProgramComponentBase, private Loggable<ComponentWithPorts>
{
public: // typedefs

public: // construction/destruction
    ComponentWithPorts(ILibrary& library, const String& name);

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    // "Dispose()" added to the template
    void Dispose() override;
    void PowerDown() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

// "Handler methods" added to the template
private: // Plc event handler methods
	void OnPlcStarting(PlcStartKind startKind);

private: // methods

private: // fields
    ComponentWithPortsProgramProvider programProvider;

public: /* Ports
           =====
           Component ports are defined in the following way:
        */

           //#attributes(Hidden)
           struct Ports 
           {
               //#name(retainPort)
               //#attributes(Output|Retain|Opc)
               int16 retainPort1 = 1;
               // The GDS name is "<componentName>/NameOfPort" if the struct is declared as Hidden
               // otherwise the GDS name is "<componentName>/PORTS.NameOfPort"
               //#attributes(Output|Opc)
               int16 nonretainPort1 = 1;
           };
           
           //#port
           Ports ports;

        /*
           Create one (and only one) instance of this struct.
           Apart from this single struct instance, it is recommended, that there should be no other Component variables 
           declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional. The attribute
           will hide the structure field and simulate that the struct fields are direct ports of the component. In the
           above example that would mean the component has only one port with the name "NameOfPort".
           When there are two struts with the attribute "Hidden" and both structs have a field with the same name, there
           will be an exception in the firmware. That is why only one struct is recommended. If multiple structs need to
           be used the "Hidden" attribute should be omitted.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */
};

} // end of namespace ComponentPorts
