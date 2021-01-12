///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "SubscriptionsComponent2.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "SubscriptionsLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

namespace Subscriptions
{

using Arp::System::Rsc::ServiceManager;
using namespace Arp::Plc::Commons::Domain;

const String SubscriptionsComponent2::varTask100msName = "Arp.Plc.Eclr/RealTimeProgram100ms.varUInt16";
const String SubscriptionsComponent2::varTask500msName = "Arp.Plc.Eclr/RealTimeProgram500ms.varUInt16";

SubscriptionsComponent2::SubscriptionsComponent2(IApplication& application, const String& name)
: ComponentBase(application, ::Subscriptions::SubscriptionsLibrary::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::Subscriptions::SubscriptionsLibrary::GetInstance().GetNamespace())
, subscriptionThread(this, &SubscriptionsComponent2::LogSubscription, 1000, "SubscriptionLogThread"){
}

void SubscriptionsComponent2::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, false);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &SubscriptionsComponent2::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &SubscriptionsComponent2::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &SubscriptionsComponent2::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &SubscriptionsComponent2::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &SubscriptionsComponent2::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &SubscriptionsComponent2::OnPlcChanged);
}

void SubscriptionsComponent2::SubscribeServices()
{
    // gets the ISubscritpionService pointer
    this->subscriptionServicePtr = ServiceManager::GetService<ISubscriptionService>();
}

void SubscriptionsComponent2::LoadSettings(const String& /*settingsPath*/)
{
    // load firmware settings here
}

void SubscriptionsComponent2::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

    // setup firmware settings here
}

void SubscriptionsComponent2::PublishServices()
{
    // publish the services of this component here
}

void SubscriptionsComponent2::LoadConfig()
{
    // load project config here
}

void SubscriptionsComponent2::SetupConfig()
{
    // setup project config here
}

void SubscriptionsComponent2::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void SubscriptionsComponent2::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &SubscriptionsComponent2::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &SubscriptionsComponent2::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &SubscriptionsComponent2::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &SubscriptionsComponent2::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &SubscriptionsComponent2::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &SubscriptionsComponent2::OnPlcChanged);
}

void SubscriptionsComponent2::PowerDown()
{
    // implement this only if data must be retained even on power down event
}

void SubscriptionsComponent2::OnPlcLoaded()
{
}

void SubscriptionsComponent2::OnPlcStarted()
{
    this->StartSubscription();
}

void SubscriptionsComponent2::OnPlcStopping()
{
    this->StopSubscription();
}

void SubscriptionsComponent2::OnPlcUnloading(bool)
{
}

void SubscriptionsComponent2::OnPlcChanging()
{
    this->StopSubscription();
}

void SubscriptionsComponent2::OnPlcChanged(bool /*success*/)
{
    this->StartSubscription();
}

void SubscriptionsComponent2::StartSubscription()
{
    // First the subscription has to be created.
    // There exists several subscription kinds, in this simple example the 'HightPerformance' kind is used,
    // which operates with a double-buffer and ensures that the read data is task consistent.
    // Check the description of Subscription/SubscriptionKind for more information.
    this->subscriptionId = this->subscriptionServicePtr->CreateSubscription(SubscriptionKind::HighPerformance);

    // The previous call should return a valid, non-zero subscription id otherwise anything failed.

    // After the subscription has been created, at least one variable has to be added.
    // To add more than one variable, this function could be called another time or the 'AddVariables' function could be used
    // to add a set of variables. In this example the 2 variables from tow different tasks are added.
    this->subscriptionServicePtr->AddVariable(this->subscriptionId, varTask100msName);
    this->subscriptionServicePtr->AddVariable(this->subscriptionId, varTask500msName);

    // Finally the 'Subscribe' function has to be called to start the data sampling of the previous added variables.
    this->subscriptionServicePtr->Subscribe(this->subscriptionId, 0);

    // now the subscription is created, configured and subscribed and the sampled data might be processed in the function
    // 'LogSubscription' which is triggered by the 'subscriptionThread'.

    // When reading data from a subscription, the values are sorted by the belonging write task regardless of the order
    // in which the variables were added.
    // So it is neccessary to obtain variable infos describing the order of the read variables.
    // All variable values belonging to the same task are compound in a data record which begins with the recording timestamp.
    // Because two variables from two different tasks were added in this example the exact order is unknown in advance.
    // So before the data could be read, a mapping has to be applied to ensure the data is copied to the correct
    // destination.
    std::vector<VariableInfo> variableInfos;

    // To get the varialbe values order the function 'GetTimeStampedVariableInfos' is used, and a delegate is required:

    // declare a more handy delegate typename
    using GetInfosDelegate = ISubscriptionService::GetTimeStampedVariableInfosVariableInfoDelegate;

    GetInfosDelegate infosDelegate = GetInfosDelegate::create([&variableInfos](IRscReadEnumerator<VariableInfo>& readEnumerator)
    {
        // This call should return '4', the two added variables with one timestamp each.
        size_t size = readEnumerator.BeginRead();
        variableInfos.reserve(size);

        VariableInfo currentInfo;
        while (readEnumerator.ReadNext(currentInfo))
        {
            variableInfos.push_back(currentInfo);
        }
        readEnumerator.EndRead();
    });
    // Now the read function is called using the info-delegate is called to get the current order of variables
    this->subscriptionServicePtr->GetTimeStampedVariableInfos(this->subscriptionId, infosDelegate);

    // Using the previously obtained infos, the variables might be assigned to the correct values.
    // As long as the subscription is not modified, the variable infos remain exactly the same.
    if (variableInfos[1].Name.CStr() == varTask100msName)
    {
        this->value1->varName = varTask100msName;
        this->value2->varName = varTask500msName;
    }
    else
    {
        this->value1->varName = varTask500msName;
        this->value2->varName = varTask100msName;
    }

    this->subscriptionThread.Start();
}

void SubscriptionsComponent2::StopSubscription()
{
    this->subscriptionServicePtr->Unsubscribe(this->subscriptionId);
    this->subscriptionThread.Stop();
}

void SubscriptionsComponent2::LogSubscription()
{
    // To read the data from the subscription a delegate function is required.
    // In this example the delegate is created locally in this method and in every thread cycle because we don't
    // care about the performance, but it is recommended, to create it in
    // the same context in which the subscription is created, e.g. SetupConfig()

    // declare a more handy delegate typename
    using ReadValuesDelegate = ISubscriptionService::ReadTimeStampedValuesValuesDelegate;

    ReadValuesDelegate readValuesDelegate = ReadValuesDelegate::create([this](IRscReadEnumerator<RscVariant<512>>& readEnumerator)
    {
        // This call should return '4' the two added variables with one timestamp each.
        auto varCount = readEnumerator.BeginRead();

        // Since the exact sequence of incoming data is known, we can easily read
        // the data and store it directly at its destination.
        RscVariant<512> value;
        for (size_t i = 0; i < varCount; i++)
        {
            readEnumerator.ReadNext(value);

            switch (value.GetType())
            {
                case RscType::Int64:
                {
                    int64 usTicks = value.GetValue<int64>();
                    if ((i / 2) == 0)
                    {
                        this->value1->timestamp = DateTime::FromUnixTimeMicroseconds(usTicks);
                    }
                    else
                    {
                        this->value2->timestamp = DateTime::FromUnixTimeMicroseconds(usTicks);
                    }
                    break;
                }
                case RscType::Uint16:
                {
                    uint16 v = value.GetValue<uint16>();
                    if ((i / 2) == 0)
                    {
                        this->value1->value = v;
                    }
                    else
                    {
                        this->value2->value = v;
                    }

                    break;
                }
                default:
                    break;
            }
        }
        readEnumerator.EndRead();
    });

    // Now read function could be called with the previous created read-delegate to write the value to the system log.
    this->subscriptionServicePtr->ReadTimeStampedValues(this->subscriptionId, readValuesDelegate);

    log.Info("{}: {} - {}", this->value1->varName, this->value1->timestamp.ToIso8601String(), this->value1->value);
    log.Info("{}: {} - {}", this->value2->varName, this->value2->timestamp.ToIso8601String(), this->value2->value);
}

} // end of namespace Subscriptions
