///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/Plc/Gds/Services/ISubscriptionService.hpp"

namespace Subscriptions
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Gds::Services;

/// <summary>
/// ###########################
/// Simple subscription example
/// ###########################
///
/// In this example we read a variable (type 'uint16') and log the data to the Output.log file.
///
/// To implement this the subscription service is used.
/// This example is just like a 'Hello-World' example and shows the easiest way to set up and use a subscription.
/// Other components in this example show more complex uses.
///
/// It is assumed that all operations succeed, so related return codes are ignored.
///
/// Look at the subscription SDK reference for more information.
/// </summary>

//#acfcomponent
class SubscriptionsComponent : public ComponentBase, public MetaComponentBase, private Loggable<SubscriptionsComponent>
{
public: // typedefs

public: // construction/destruction
    SubscriptionsComponent(IApplication& application, const String& name);
    virtual ~SubscriptionsComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void SubscribeServices()override;
    void LoadSettings(const String& settingsPath)override;
    void SetupSettings()override;
    void PublishServices()override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void Dispose()override;
    void PowerDown()override;

public: // MetaComponentBase operations
    void RegisterComponentPorts() override;

private: // subscription methods
    void StartSubscription(void);
    void StopSubscription(void);
    void LogSubscription(void)const;

private: // Plc event handlers
    void OnPlcLoaded(void);
    void OnPlcStarted(void);
    void OnPlcStopping(void);
    void OnPlcUnloading(bool onError);
    void OnPlcChanging(void);
    void OnPlcChanged(bool success);

private: // methods
    SubscriptionsComponent(const SubscriptionsComponent& arg) = delete;
    SubscriptionsComponent& operator= (const SubscriptionsComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    // Service thread that reads the data from the subscription and writes it to the system log
    WorkerThread                subscriptionThread;
    ISubscriptionService::Ptr   subscriptionServicePtr = nullptr;

    // The 'subscriptionId' is the ID of a created subscription.
    // A valid value is greater than 0, so the member variable is initialized with 0, meaning uninitialized.
    uint32                      subscriptionId = 0;

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

inline IComponent::Ptr SubscriptionsComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new SubscriptionsComponent(application, name));
}

} // end of namespace Subscriptions
