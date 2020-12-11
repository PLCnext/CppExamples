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
/// Record subscription example
/// ###########################
///
/// This example focuses on how to read variable data from a subscription from type 'Recording'.
///
/// Therefore two variables from different tasks ('100ms' and '500ms') are added to the subscription.
/// The read values are printed to the system log.
///
/// Expected log message is:
/// 01.07.20 07:43:31.409 SubscriptionsComponent4   INFO    - Read records of subscription '1':
///        [timestamp, Apps.Demo.Data/RealTimeProgram100ms.varUInt16]
///        [ 2020-07-01T07:43:30.418081, 12 ]
///        [ 2020-07-01T07:43:30.518555, 13 ]
///        [ 2020-07-01T07:43:30.618679, 14 ]
///        [ 2020-07-01T07:43:30.718933, 15 ]
///        [ 2020-07-01T07:43:30.818034, 16 ]
///        [ 2020-07-01T07:43:30.918688, 17 ]
///        [ 2020-07-01T07:43:31.018307, 18 ]
///        [ 2020-07-01T07:43:31.118745, 19 ]
///        [ 2020-07-01T07:43:31.218379, 20 ]
///        [ 2020-07-01T07:43:31.319772, 21 ]
///
///        [timestamp, Apps.Demo.Data/RealTimeProgram500ms.varUInt16]
///        [ 2020-07-01T07:43:30.818019, 4 ]
///        [ 2020-07-01T07:43:31.319814, 5 ]
///
/// It is assumed that all operations succeed, so related return codes are ignored.
///
/// Take a look at the other examples or the subscription SDK reference for more infomation.
/// </summary>
class SubscriptionsComponent4 : public ComponentBase, public IControllerComponent, private Loggable<SubscriptionsComponent4>
{
public: // typedefs
    using RecordVariableInfos = std::vector<std::vector<VariableInfo>>;

public: // construction/destruction
    SubscriptionsComponent4(IApplication& application, const String& name);
    virtual ~SubscriptionsComponent4(void);

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

    void GetRecordVariableInfos(RecordVariableInfos& recordVariableInfos)const;
    void LogRecords(IRscReadEnumerator<RscVariant<512>>& readEnumerator)const;

    void LogRecord(const RscVariant<512>& record, std::ostream& os)const;
    void LogVariant(const RscVariant<512>& variant, std::ostream& os)const;

private: // Plc event handlers
    void OnPlcLoaded(void);
    void OnPlcStarted(void);
    void OnPlcStopping(void);
    void OnPlcUnloading(bool onError);
    void OnPlcChanging(void);
    void OnPlcChanged(bool success);

private: // deleted methods
    SubscriptionsComponent4(const SubscriptionsComponent4& arg) = delete;
    SubscriptionsComponent4& operator=(const SubscriptionsComponent4& arg) = delete;

private: // fields
    // Service thread that reads the data from the subscription and writes it to the system log
    WorkerThread                subscriptionThread;
    ISubscriptionService::Ptr   subscriptionServicePtr = nullptr;

    // The 'subscriptionId' is the ID of a created subscription.
    // A valid value is greater than 0, so the member variable is initialized with 0, meaning uninitialized.
    uint32                      subscriptionId = 0;

    // Storage of variable infos
    RecordVariableInfos         recordVariableInfos;

    // Delegate function which reads the data and writes it to the system log.
    ISubscriptionService::ReadValuesValuesDelegate readRecordDelegate;

private: // static fields
    static const String varTask100msName;
    static const String varTask500msName;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class SubscriptionsComponent4

inline SubscriptionsComponent4::~SubscriptionsComponent4()
{
}

inline IComponent::Ptr SubscriptionsComponent4::Create(IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new SubscriptionsComponent4(application, componentName));
}

}}} // end of namespace Apps::Demo::Subscriptions
