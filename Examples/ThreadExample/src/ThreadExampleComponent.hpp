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
#include "ThreadExampleLibrary.hpp"
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

// Added: IProgramComponent operations
public:
       IProgramProvider & GetProgramProvider(bool useBackgroundDomain) override;

// Added: IMetaComponent operations
public:
       IDataInfoProvider & GetDataInfoProvider(bool isChanging) override;
       IDataNavigator*     GetDataNavigator() override;


private: // fields
    ThreadExampleComponentProgramProvider programProvider;
    DataInfoProvider    		  		  dataInfoProvider;

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

    ThreadSettings delegateThreadSettings {"DelegateThreadName", 0, 0, 0};
    ThreadSettings staticThreadSettings {"StaticThreadName", 0, 0, 0};

    void delegateThreadBody(void * pParameter);

    int myparameter{123};
    static void staticThreadBody(void* pParameter);


public: /* Ports
           =====
           Component ports are defined in the following way:
           //#port
           //#name(NameOfPort)
           boolean portField;

           The name comment defines the name of the port and is optional. Default is the name of the field.
           Attributes which are defined for a component port are IGNORED. If component ports with attributes
           are necessary, define a single structure port where attributes can be defined foreach field of the
           structure.
        */
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ThreadExampleComponent
inline ThreadExampleComponent::ThreadExampleComponent(IApplication& application, const String& name)
: ComponentBase(application, ::ThreadExample::ThreadExampleLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::ThreadExample::ThreadExampleLibrary::GetInstance().GetNamespace(), programProvider)

// Added: data info provider
, dataInfoProvider(::ThreadExample::ThreadExampleLibrary::GetInstance().GetNamespace(), &(this->programProvider))

//// Worker Thread Example
, workerThreadInstance(make_delegate(this, &ThreadExampleComponent::workerThreadBody) , 10000, "WorkerThreadName")

//Commons/Thread Example
, delegateThreadInstance(delegateThreadSettings,this,&ThreadExampleComponent::delegateThreadBody,(void*)&myparameter)
, staticThreadInstance(staticThreadSettings,&ThreadExampleComponent::staticThreadBody,(void*)&xStopThread)
{
}


#pragma region IProgramComponent implementation

inline IProgramProvider& ThreadExampleComponent::GetProgramProvider(bool /*useBackgroundDomain*/)
{
    return this->programProvider;
}

#pragma endregion


#pragma region IMetaComponent implementation

inline IDataInfoProvider& ThreadExampleComponent::GetDataInfoProvider(bool /*useBackgroundDomain*/)
{
    return this->dataInfoProvider;
}

inline IDataNavigator* ThreadExampleComponent::GetDataNavigator()
{
    return nullptr;
}

#pragma endregion


inline IComponent::Ptr ThreadExampleComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new ThreadExampleComponent(application, name));
}

} // end of namespace ThreadExample
