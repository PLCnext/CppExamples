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
#include "Internal/TimestampedValue.hpp"

namespace Apps { namespace Demo { namespace Subscriptions
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Gds::Services;
using Apps::Demo::Subscriptions::Internal::TimestampedValue;

/// <summary>
/// ######################################
/// Read Time-stamped subscription example
/// ######################################
///
/// This example focuses on how to read subscription data including time stamps.
/// Therefore two variables from different tasks('100ms' and '500ms') are added to the subscription.
/// Afterwards the read values including the time stamps are printed to the system log.
///
/// It is assumed that all operations succeed, so related return codes are ignored.
///
/// Take a look at the other examples or the subscription SDK reference for more infomation.
/// </summary>
class SubscriptionsComponent2 : public ComponentBase, public IControllerComponent, private Loggable<SubscriptionsComponent2>
{
public: // construction/destruction
    SubscriptionsComponent2(IApplication& application, const String& name);
    virtual ~SubscriptionsComponent2(void);

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
    void LogSubscription(void);

private: // Plc event handlers
    void OnPlcLoaded(void);
    void OnPlcStarted(void);
    void OnPlcStopping(void);
    void OnPlcUnloading(bool onError);
    void OnPlcChanging(void);
    void OnPlcChanged(bool success);

private: // deleted methods
    SubscriptionsComponent2(const SubscriptionsComponent2& arg) = delete;
    SubscriptionsComponent2& operator=(const SubscriptionsComponent2& arg) = delete;

private: // fields
    // Service thread that reads the data from the subscription and writes it to the system log
    WorkerThread                subscriptionThread;
    ISubscriptionService::Ptr   subscriptionServicePtr = nullptr;

    // The 'subscriptionId' is the ID of a created subscription.
    // A valid value is greater than 0, so the member variable is initialized with 0, meaning uninitialized.
    uint32                      subscriptionId = 0;

    // Storage for the read values
    TimestampedValue            value1;
    TimestampedValue            value2;

private: // static fields
    static const String varTask100msName;
    static const String varTask500msName;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class SubscriptionsComponent2

inline SubscriptionsComponent2::~SubscriptionsComponent2()
{
}

inline IComponent::Ptr SubscriptionsComponent2::Create(IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new SubscriptionsComponent2(application, componentName));
}

}}} // end of namespace Apps::Demo::Subscriptions
