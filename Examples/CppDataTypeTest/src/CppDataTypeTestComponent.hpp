#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/IProgramComponent.hpp"
#include "Arp/Plc/Commons/Meta/IMetaComponent.hpp"
#include "Arp/Plc/Commons/Meta/DataInfoProvider.hpp"
#include "CppDataTypeTest/CppDataTypeTestComponentProgramProvider.hpp"
#include "CppDataTypeTest/CppDataTypeTestLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

// Added Stuff
#include "Arp/Plc/Commons/Domain/IPlcComponent.hpp"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"



namespace CppDataTypeTest 
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

class CppDataTypeTestComponent : public ComponentBase, public IProgramComponent, public IMetaComponent, private Loggable<CppDataTypeTestComponent>
{
public: // typedefs

public: // construction/destruction
    CppDataTypeTestComponent(IApplication& application, const String& name);
    virtual ~CppDataTypeTestComponent() = default;

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

private: // CppDataTypeTestComponent.meta.cpp
    void RegisterComponentPorts();

private: // methods
    CppDataTypeTestComponent(const CppDataTypeTestComponent& arg) = delete;
    CppDataTypeTestComponent& operator= (const CppDataTypeTestComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& componentName);

public: // IProgramComponent operations
    IProgramProvider & GetProgramProvider(bool useBackgroundDomain) override;

public: // IMetaComponent operations
    IDataInfoProvider & GetDataInfoProvider(bool isChanging) override;
    IDataNavigator*     GetDataNavigator() override;

private: // fields
    CppDataTypeTestComponentProgramProvider programProvider;
    DataInfoProvider    dataInfoProvider;

public: // ports
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CppDataTypeTestComponent
inline CppDataTypeTestComponent::CppDataTypeTestComponent(IApplication& application, const String& name)
: ComponentBase(application, ::CppDataTypeTest::CppDataTypeTestLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, dataInfoProvider(::CppDataTypeTest::CppDataTypeTestLibrary::GetInstance().GetNamespace(), &(this->programProvider))
{
}

#pragma region IProgramComponent implementation

inline IProgramProvider& CppDataTypeTestComponent::GetProgramProvider(bool /*useBackgroundDomain*/)
{
    return this->programProvider;
}

#pragma endregion

#pragma region IMetaComponent implementation

inline IDataInfoProvider& CppDataTypeTestComponent::GetDataInfoProvider(bool /*useBackgroundDomain*/)
{
    return this->dataInfoProvider;
}

inline IDataNavigator* CppDataTypeTestComponent::GetDataNavigator()
{
    return nullptr;
}

#pragma endregion

inline IComponent::Ptr CppDataTypeTestComponent::Create(Arp::System::Acf::IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new CppDataTypeTestComponent(application, componentName));
}

} // end of namespace CppDataTypeTest
