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
/// ###########################################
/// Read complex variable subscription example
/// ###########################################
///
/// This example focuses on how to read complex variable data (structures and arrays) from a subscription.
///
/// Therefore one complex variable ('Arp.Plc.Eclr/DataProducer100ms.counter') is added to the subscription.
/// Afterwards the read values including the time stamps are printed to the system log.
/// The complex variable has the following type:
///
///     struct SampleStruct
///     {
///         uint16 varUInt16 = false;
///         bool varBool = false;
///         uint16 varUInt16Array_5[5];
///     };
///
/// It is assumed that all operations succeed, so related return codes are ignored.
///
/// Take a look at the other examples or the subscription SDK reference for more information.
/// </summary>

//#acfcomponent
class SubscriptionsComponent3 : public ComponentBase, public MetaComponentBase, private Loggable<SubscriptionsComponent3>
{
public: // typedefs

public: // construction/destruction
    SubscriptionsComponent3(IApplication& application, const String& name);
    virtual ~SubscriptionsComponent3() = default;

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
    void SetupSubscription(void);
    void ResetSubscription(void);
    void StartSubscription(void);
    void StopSubscription(void);
    void LogSubscription(void)const;

    void LogValues(IRscReadEnumerator<RscVariant<512>>& readEnumerator);
    void LogVariant(const RscVariant<512>& value, std::ostream& os)const;

    void LogValue(const RscVariant<512>& variant, std::ostream& os)const;
    void LogArray(RscArrayReader& arrayReader, std::ostream& os)const;
    void LogStruct(RscStructReader<512>& structReader, std::ostream& os)const;

private: // Plc event handlers
    void OnPlcLoaded(void);
    void OnPlcStarted(void);
    void OnPlcStopping(void);
    void OnPlcUnloading(bool onError);
    void OnPlcChanging(void);
    void OnPlcChanged(bool success);

private: // methods
    SubscriptionsComponent3(const SubscriptionsComponent3& arg) = delete;
    SubscriptionsComponent3& operator= (const SubscriptionsComponent3& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    // Service thread that reads the data from the subscription and writes it to the system log
    WorkerThread                subscriptionThread;
    ISubscriptionService::Ptr   subscriptionServicePtr = nullptr;

    // The 'subscriptionId' is the ID of a created subscription.
    // A valid value is greater than 0, so the member variable is initialized with 0, meaning uninitialized.
    uint32                      subscriptionId = 0;

    // Delegate function which reads the data and writes it to the system log.
    ISubscriptionService::ReadValuesValuesDelegate readSubscriptionValuesDelegate;

private: // static fields
    static const String complexVarName;

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

inline IComponent::Ptr SubscriptionsComponent3::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new SubscriptionsComponent3(application, name));
}

} // end of namespace Subscriptions
