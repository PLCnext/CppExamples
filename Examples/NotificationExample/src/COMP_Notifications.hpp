///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "COMP_NotificationsProgramProvider.hpp"
#include "NotificationExampleLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Domain/PlcState.hpp"
#include "Arp/System/Commons/Logging.h"

#include "Arp/System/Nm/NotificationManager.hpp"
#include "Arp/System/NmPayload/Plc/PlcStateChangedPayload.hpp"
#include "Arp/System/NmPayload/Device/NetworkConfigurationChangedPayload.hpp"
#include "ExamplePayload.hpp"

namespace NotificationExample
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//#component
class COMP_Notifications : public ComponentBase, public ProgramComponentBase, private Loggable<COMP_Notifications>
{
public: // typedefs

public: // construction/destruction
    COMP_Notifications(IApplication& application, const String& name);
    virtual ~COMP_Notifications() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    COMP_Notifications(const COMP_Notifications& arg) = delete;
    COMP_Notifications& operator= (const COMP_Notifications& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // SubscriptionCallbacks
    void NM_Subscription1_Callback(const Arp::System::Nm::Notification& notification);
    void NM_Subscription2_Callback(const Arp::System::Nm::Notification& notification);
    void NetworkConfigurationChanged_Callback(const Arp::System::Nm::Notification& notification);
    void PlcStateChanged_Callback(const Arp::System::Nm::Notification& notification);


private: // fields
    COMP_NotificationsProgramProvider programProvider;

    Arp::System::Nm::NotificationManager&   nm = NotificationManager::GetInstance();
    Arp::System::Nm::NotificationSubscriber Custom_subscription;
    Arp::System::Nm::NotificationSubscriber Custom_subscription2;
    Arp::System::Nm::NotificationSubscriber NetworkConfigurationChanged_subscription;
    Arp::System::Nm::NotificationSubscriber PlcStateChanged_subscription;


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
       int OP_uiValue1{};
       int OP_uiValue2{};
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class COMP_Notifications
inline COMP_Notifications::COMP_Notifications(IApplication& application, const String& name)
: ComponentBase(application, ::NotificationExample::NotificationExampleLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::NotificationExample::NotificationExampleLibrary::GetInstance().GetNamespace(), programProvider)
,    Custom_subscription("My.NameSpace.1")
,    Custom_subscription2("My.NameSpace.2")
,    NetworkConfigurationChanged_subscription("Arp.Device.Interface.NetworkConfigurationChanged")
,    PlcStateChanged_subscription("Arp.Plc.Domain.PlcManager.StateChanged")
{

}

inline IComponent::Ptr COMP_Notifications::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new COMP_Notifications(application, name));
}

} // end of namespace NotificationExample
