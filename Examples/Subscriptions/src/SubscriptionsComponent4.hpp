#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Base/Acf/Commons/ComponentBase.hpp"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/Plc/Gds/Services/ISubscriptionService.hpp"

namespace Subscriptions
{
using namespace Arp::Base::Acf::Commons;
using namespace Arp;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Gds::Services;
using namespace Arp::System::Commons::Threading;

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

//#acfcomponent
class SubscriptionsComponent4 : public ComponentBase, public MetaComponentBase, private Loggable<SubscriptionsComponent4>
{
public: // typedefs
    using RecordVariableInfos = std::vector<std::vector<VariableInfo>>;

public: // construction/destruction
    SubscriptionsComponent4(ILibrary& library, const String& name);

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

private: // methods

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
               // If a component port is attributed with "Retain" additional measures need to be implemented. Fur further details refer to chapter "Component ports" in the topic "IComponent and IProgram" of https://www.plcnext.help
           };
           
           //#port
           Ports ports;

           Create one (and only one) instance of this struct.
           Apart from this single struct instance, it is recommended, that there should be no other Component variables 
           declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional. The attribute
           will hide the structure field and simulate that the struct fields are direct ports of the component. In the
           above example that would mean the component has only one port with the name "NameOfPort".
           When there are two struts with the attribute "Hidden" and both structs have a field with the same name, there
           will be an exception in the firmware. That is why only one struct is recommended. If multiple structs need to
           be used the "Hidden" attribute should be omitted.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */

};

} // end of namespace Subscriptions
