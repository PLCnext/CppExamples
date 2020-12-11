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
/// ###########################
/// Simple subscription example
/// ###########################
///
/// In this example we read a variable (type 'uint16') and log the date to the systemlog
///
/// To implement this the subscription service is used.
/// This example is just like a 'Hello-World' example and shall show in the easiest way how a subscription
/// works and how it has to use. Take a look at the other examples of a more complex use.
///
/// It is assumed that all operations succeed, so related return codes are ignored.
///
/// Take a look at the other examples or the subscription SDK reference for more infomation.
/// </summary>
class SubscriptionsComponent : public ComponentBase, public IControllerComponent, private Loggable<SubscriptionsComponent>
{
public: // construction/destruction
    SubscriptionsComponent(IApplication& application, const String& name);
    virtual ~SubscriptionsComponent(void);

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

private: // Plc event handlers
    void OnPlcLoaded(void);
    void OnPlcStarted(void);
    void OnPlcStopping(void);
    void OnPlcUnloading(bool onError);
    void OnPlcChanging(void);
    void OnPlcChanged(bool success);

private: // deleted methods
    SubscriptionsComponent(const SubscriptionsComponent& arg) = delete;
    SubscriptionsComponent& operator=(const SubscriptionsComponent& arg) = delete;

private: // fields
    // Service thread that reads the data from the subscription and writes it to the system log
    WorkerThread                subscriptionThread;
    ISubscriptionService::Ptr   subscriptionServicePtr = nullptr;

    // The 'subscriptionId' is the ID of a created subscription.
    // A valid value is greater than 0, so the member variable is initialized with 0, meaning uninitialized.
    uint32                      subscriptionId = 0;

private: // static fields
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class SubscriptionsComponent

inline SubscriptionsComponent::~SubscriptionsComponent()
{
}

inline IComponent::Ptr SubscriptionsComponent::Create(IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new SubscriptionsComponent(application, componentName));
}

}}} // end of namespace Apps::Demo::Subscriptions
