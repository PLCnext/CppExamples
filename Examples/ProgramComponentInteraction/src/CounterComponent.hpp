//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#pragma once

#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"

#include "Arp/System/Commons/Logging.h"
#include "Arp/Plc/Commons/Esm/IProgramComponent.hpp"
#include "CounterComponentProgramProvider.hpp"


#include "Arp/Plc/Commons/Meta/IMetaComponent.hpp"
#include "Arp/Plc/Commons/Meta/DataInfoProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "ProgramComponentInteractionLibrary.hpp"

#include "Helpers/Enums.hpp"


namespace ProgramComponentInteraction // Library name
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

#ifdef DEBUG
#define DEBUG_FUNCTION_CALL log.Info("'{0}' invoked of object with instance name '{1}'", __FUNCTION__, this->GetFullName());
#else
#define DEBUG_FUNCTION_CALL
#endif

//component
class CounterComponent : 
public ComponentBase, 
public IProgramComponent, 
public IMetaComponent,
private Loggable<CounterComponent> 
{


public: // typedefs

public: // construction/destruction
    CounterComponent(IApplication& application, const String& name);
    virtual ~CounterComponent() = default;

public: // IComponent operations
    void Initialize(void)override;
    void LoadSettings(const String& settingsPath)override;
    void SetupSettings(void)override;
    void SubscribeServices(void)override;
    void LoadConfig(void)override;
    void SetupConfig(void)override;
    void ResetConfig(void)override;
    void PublishServices(void)override;
    void Dispose(void)override;
    void PowerDown(void)override;


private: // CounterComponent.meta.cpp 
    void RegisterComponentPorts();

private: // methods
    CounterComponent(const CounterComponent& arg) = delete;
    CounterComponent& operator= (const CounterComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& componentName);

public: // IProgramComponent operations
   
      IProgramProvider & GetProgramProvider(bool useBackgroundDomain) override;

public: // IMetaComponent operations
    IDataInfoProvider & GetDataInfoProvider(bool isChanging) override;
    IDataNavigator*     GetDataNavigator() override;


private: // fields
    CounterComponentProgramProvider programProvider;
    DataInfoProvider    dataInfoProvider;

public: // Component Interaction operations   
    
    /// Toggles the Command
    void RefreshState();
     
    // Set progress of the DownCounterProgram
    void SetProgressDC(Progress p){progress_DC = p;}
    // Set progress of the UpCounterProgram
    void SetProgressUC(Progress p){progress_UC = p;}   
    
    // returns the current command
    Command GetCommand(void){return command;}

private: // member variables for Program Component Interaction
    Progress progress_UC = Progress::Stopped;
    Progress progress_DC = Progress::Stopped;
    Command command{Command::CountDown};

public: // ports
    //#port
    //#name(StopCounting)
    boolean IP_Stop{false};
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CounterComponent
inline CounterComponent::CounterComponent(IApplication& application, const String& name)
: ComponentBase(application, ::ProgramComponentInteraction::ProgramComponentInteractionLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, dataInfoProvider(::ProgramComponentInteraction::ProgramComponentInteractionLibrary::GetInstance().GetNamespace(), &(this->programProvider))
{
    DEBUG_FUNCTION_CALL
}

#pragma region IProgramComponent implementation

inline IProgramProvider& CounterComponent::GetProgramProvider(bool /*useBackgroundDomain*/)
{
    DEBUG_FUNCTION_CALL
    return this->programProvider;
}

#pragma endregion

#pragma region IMetaComponent implementation

inline IDataInfoProvider& CounterComponent::GetDataInfoProvider(bool /*useBackgroundDomain*/)
{
    DEBUG_FUNCTION_CALL
    return this->dataInfoProvider;
}

inline IDataNavigator* CounterComponent::GetDataNavigator()
{
    DEBUG_FUNCTION_CALL
    return nullptr;
}

#pragma endregion

inline IComponent::Ptr CounterComponent::Create(Arp::System::Acf::IApplication& application, const String& componentName)
{
    DEBUG_FUNCTION_CALL
    return IComponent::Ptr(new CounterComponent(application, componentName));
}

} // end of namespace ExampleLibrary
