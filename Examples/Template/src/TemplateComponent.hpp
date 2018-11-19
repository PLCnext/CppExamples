//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/IProgramComponent.hpp"
#include "Arp/Plc/Commons/Meta/IMetaComponent.hpp"
#include "Arp/Plc/Commons/Meta/DataInfoProvider.hpp"
#include "Template/TemplateComponentProgramProvider.hpp"
#include "Template/TemplateLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

namespace Template 
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

class TemplateComponent : public ComponentBase, public IProgramComponent, public IMetaComponent, private Loggable<TemplateComponent>
{
public: // typedefs

public: // construction/destruction
    TemplateComponent(IApplication& application, const String& name);
    virtual ~TemplateComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadSettings(const String& settingsPath) override;
    void SetupSettings() override;
    void SubscribeServices() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void PublishServices() override;
    void Dispose() override;
    void PowerDown() override;

private: // TemplateComponent.meta.cpp
    void RegisterComponentPorts();

private: // methods
    TemplateComponent(const TemplateComponent& arg) = delete;
    TemplateComponent& operator= (const TemplateComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& componentName);

public: // IProgramComponent operations
    IProgramProvider & GetProgramProvider(bool useBackgroundDomain) override;

public: // IMetaComponent operations
    IDataInfoProvider & GetDataInfoProvider(bool isChanging) override;
    IDataNavigator*     GetDataNavigator() override;

private: // fields
    TemplateComponentProgramProvider programProvider;
    DataInfoProvider    dataInfoProvider;

public: // ports
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class TemplateComponent
inline TemplateComponent::TemplateComponent(IApplication& application, const String& name)
: ComponentBase(application, ::Template::TemplateLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, dataInfoProvider(::Template::TemplateLibrary::GetInstance().GetNamespace(), &(this->programProvider))
{
}

#pragma region IProgramComponent implementation

inline IProgramProvider& TemplateComponent::GetProgramProvider(bool /*useBackgroundDomain*/)
{
    return this->programProvider;
}

#pragma endregion

#pragma region IMetaComponent implementation

inline IDataInfoProvider& TemplateComponent::GetDataInfoProvider(bool /*useBackgroundDomain*/)
{
    return this->dataInfoProvider;
}

inline IDataNavigator* TemplateComponent::GetDataNavigator()
{
    return nullptr;
}

#pragma endregion

inline IComponent::Ptr TemplateComponent::Create(Arp::System::Acf::IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new TemplateComponent(application, componentName));
}

} // end of namespace Template
