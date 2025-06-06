/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 *  ThreadExampleComponent.hpp
 *
 *  Created on: 16.05.2019
 *      Author: Eduard Münz, Oliver Warneke
 *
 ******************************************************************************/

/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Base/Acf/Commons/ComponentBase.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "ThreadExampleComponentProgramProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

//ADDED
#include "Arp/System/Acf/IControllerComponent.hpp"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Commons/Threading/Thread.hpp"
#include "Arp/System/Commons/Threading/ThreadSettings.hpp"
//ADDED

namespace ThreadExample
{

using namespace Arp;
using namespace Arp::Base::Acf::Commons;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::System::Commons::Threading;

//#component
class ThreadExampleComponent : public ComponentBase, public ProgramComponentBase, public IControllerComponent, private Loggable<ThreadExampleComponent>
{
public: // typedefs

public: // construction/destruction
    ThreadExampleComponent(ILibrary& library, const String& name);

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void PowerDown() override;

public: // IControllerComponent operations
    void Start(void);
    void Stop(void);

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

    int GetCounterValue();

private: // methods

private: // Thread Bodys
    void workerThreadBody(void);
    void delegateThreadBody(void * pParameter);
    static void staticThreadBody(void* pParameter);

private: // fields
    ThreadExampleComponentProgramProvider programProvider;

    // WorkerThread Example
    WorkerThread workerThreadInstance;
    int iStartValue = 0;
    int iEndValue = 1000;
    int iCountervalue = 0;
    bool xStopThread = false;

    // delegate Thread Example
    Thread delegateThreadInstance;

    // static Thread Example
    int myparameter{123};
    Thread staticThreadInstance;

public: /* Ports
           =====
           Component ports are defined in the following way:

           //#attributes(Hidden)
           struct Ports 
           {
               //#name(NameOfPort)
               //#attributes(Input|Retain|Opc)
               Arp::boolean portField = false;
               // The GDS name is "<componentName>/NameOfPort" if the struct is declared as Hidden
               // otherwise the GDS name is "<componentName>/PORTS.NameOfPort"
			   // If a component port is attributed with "Retain" additional measures need to be implemented. Fur further details refer to chapter "Component ports" in the topic "IComponent and IProgram" of https://www.plcnext.help
           };
           
           //#port
           Ports ports;

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

} // end of namespace ThreadExample
