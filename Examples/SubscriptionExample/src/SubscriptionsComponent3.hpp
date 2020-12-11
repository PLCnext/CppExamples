///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/System/Acf/IControllerComponent.hpp"
#include "Arp/Plc/Gds/Services/ISubscriptionService.hpp"

namespace Apps { namespace Demo { namespace Subscriptions
{

using namespace Arp;
using namespace Arp::System::Acf;
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
///     struct SampleStruct
///     {
///         uint16 varUInt16 = false;
///         bool varBool = false;
///         uint16 varUInt16Array_4[4];
///     };
///
/// It is assumed that all operations succeed, so related return codes are ignored.
///
/// Take a look at the other examples or the subscription SDK reference for more infomation.
/// </summary>
class SubscriptionsComponent3 : public ComponentBase, public IControllerComponent, private Loggable<SubscriptionsComponent3>
{
public: // construction/destruction
    SubscriptionsComponent3(IApplication& application, const String& name);
    virtual ~SubscriptionsComponent3(void);

public: // static factory operation
    static IComponent::Ptr Create(IApplication& application, const String& componentName);

public: // properties

public: // IComponent operations
    void Initialize(void)override;
    void SubscribeServices(void)override;
    void LoadSettings(const String& settingsPath)override;
    void SetupSettings(void)override;
    void PublishServices(void)override;
    void LoadConfig(void)override;
    void SetupConfig(void)override;
    void ResetConfig(void)override;
    void Dispose(void)override;
    void PowerDown(void)override;

public: // IControllerComponent operations
    void Start(void)override;
    void Stop(void)override;

public: // operations

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

private: // deleted methods
    SubscriptionsComponent3(const SubscriptionsComponent3& arg) = delete;
    SubscriptionsComponent3& operator=(const SubscriptionsComponent3& arg) = delete;

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
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class SubscriptionsComponent3

inline SubscriptionsComponent3::~SubscriptionsComponent3()
{
}

inline IComponent::Ptr SubscriptionsComponent3::Create(IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new SubscriptionsComponent3(application, componentName));
}

}}} // end of namespace Apps::Demo::Subscriptions
