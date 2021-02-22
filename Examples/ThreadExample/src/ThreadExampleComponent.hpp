/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 *  ThreadExampleComponent.hpp
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
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
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
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//#component
class ThreadExampleComponent : public ComponentBase
                            , public ProgramComponentBase
                            , public IControllerComponent
                            , private Loggable<ThreadExampleComponent>
{
public: // typedefs

public: // construction/destruction
    ThreadExampleComponent(IApplication& application, const String& name);
    virtual ~ThreadExampleComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // IControllerComponent operations
    void Start(void);
    void Stop(void);

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

    int GetCounterValue();

private: // methods
    ThreadExampleComponent(const ThreadExampleComponent& arg) = delete;
    ThreadExampleComponent& operator= (const ThreadExampleComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    ThreadExampleComponentProgramProvider programProvider;

    // Worker Thread Example
    WorkerThread workerThreadInstance;
    int iStartValue = 0;
    int iEndValue = 1000;
    int iCountervalue = 0;
    bool xStopThread = false;

    void workerThreadBody(void);

    //Commons/Thread Example
    Thread delegateThreadInstance;
    Thread staticThreadInstance;



    void delegateThreadBody(void * pParameter);

    int myparameter{123};
    static void staticThreadBody(void* pParameter);

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
           };

           //#port
           Ports ports;

           Create one (and only one) instance of this struct.
           Apart from this single struct instance, there must be no other Component variables declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */
};

inline IComponent::Ptr ThreadExampleComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new ThreadExampleComponent(application, name));
}

} // end of namespace ThreadExample
