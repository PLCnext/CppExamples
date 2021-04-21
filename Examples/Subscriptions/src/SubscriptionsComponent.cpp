///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "SubscriptionsComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "SubscriptionsLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

namespace Subscriptions
{

using Arp::System::Rsc::ServiceManager;
using namespace Arp::Plc::Commons::Domain;

SubscriptionsComponent::SubscriptionsComponent(IApplication& application, const String& name)
: ComponentBase(application, ::Subscriptions::SubscriptionsLibrary::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::Subscriptions::SubscriptionsLibrary::GetInstance().GetNamespace())
, subscriptionThread(this, &SubscriptionsComponent::LogSubscription, 1000, "SubscriptionLogThread"){
}

void SubscriptionsComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, false);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &SubscriptionsComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &SubscriptionsComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &SubscriptionsComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &SubscriptionsComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &SubscriptionsComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &SubscriptionsComponent::OnPlcChanged);
}

void SubscriptionsComponent::SubscribeServices()
{
    // gets the ISubscritpionService pointer
    this->subscriptionServicePtr = ServiceManager::GetService<ISubscriptionService>();
}

void SubscriptionsComponent::LoadSettings(const String& /*settingsPath*/)
{
    // load firmware settings here
}

void SubscriptionsComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

    // setup firmware settings here
}

void SubscriptionsComponent::PublishServices()
{
    // publish the services of this component here
}

void SubscriptionsComponent::LoadConfig()
{
    // load project config here
}

void SubscriptionsComponent::SetupConfig()
{
    // setup project config here
}

void SubscriptionsComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void SubscriptionsComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &SubscriptionsComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &SubscriptionsComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &SubscriptionsComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &SubscriptionsComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &SubscriptionsComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &SubscriptionsComponent::OnPlcChanged);
}

void SubscriptionsComponent::PowerDown()
{
    // implement this only if data must be retained even on power down event
}

void SubscriptionsComponent::OnPlcLoaded()
{
}

void SubscriptionsComponent::OnPlcStarted()
{
    this->StartSubscription();
}

void SubscriptionsComponent::OnPlcStopping()
{
    this->StopSubscription();
}

void SubscriptionsComponent::OnPlcUnloading(bool)
{
}

void SubscriptionsComponent::OnPlcChanging()
{
    this->StopSubscription();
}

void SubscriptionsComponent::OnPlcChanged(bool /*success*/)
{
    this->StartSubscription();
}

void SubscriptionsComponent::StartSubscription()
{
    // First the subscription has to be created.
    // There exists several subscription kinds, in this simple example the 'HightPerformance' kind is used,
    // which operates with a double-buffer and ensures that the read data are task consistent.
    // Check the description of Subscription/SubscriptionKind for more information.
    this->subscriptionId = this->subscriptionServicePtr->CreateSubscription(SubscriptionKind::HighPerformance);

    // The previous call should return a valid, non-zero subscription id otherwise something failed.

    // After the subscription has been created, at least one variable has to be added.
    // To add more than one variable, this function could be called another time or the 'AddVariables' function could be used
    // to add a set of variables.
    this->subscriptionServicePtr->AddVariable(this->subscriptionId, "Arp.Plc.Eclr/RealTimeProgram100ms.varUInt16");

    // Finally the 'Subscribe' function has to be called to start the data sampling of the previous added variables.
    this->subscriptionServicePtr->Subscribe(this->subscriptionId, 0);

    // now the subscription is created, configured and subscribed and the sampled date might be processed in the function
    // 'LogSubscription' which is triggered by the 'subscriptionThread'.

    this->subscriptionThread.Start();
}

void SubscriptionsComponent::StopSubscription()
{
    this->subscriptionServicePtr->Unsubscribe(this->subscriptionId);
    this->subscriptionThread.Stop();
}

void SubscriptionsComponent::LogSubscription()const
{
    // To read the data from the subscription a delegate function is required.
    // In this example the delegate is created locally in this method and in every thread cycle because we don't
    // care about the performance, but it is recommended, to create it in
    // the same context in which the subscription is created, e.g. SetupConfig()

    // declare a more handy delegate typename
    using ReadValuesDelegate = ISubscriptionService::ReadValuesValuesDelegate;

    ReadValuesDelegate readSubscriptionDelegate = ReadValuesDelegate::create([&](IRscReadEnumerator<RscVariant<512>>& readEnumerator)
    {
        // This call should return '1' because just one variable was added
        size_t count = readEnumerator.BeginRead();
        if (count != 1)
        {
            log.Error("LogSubscription: count != 1");
        }

        RscVariant<512> current;
        while (readEnumerator.ReadNext(current))
        {
            // The variable port has the type 'UInt16'
            if (current.GetType() == RscType::Uint16)
            {
                log.Info("Value: {}", current.GetValue<uint16>());
            }
            else
            {
                log.Warning("Unexpeted type: '{}'", current.GetType());
            }
        }
        readEnumerator.EndRead();
    });

    // Now ReadValues function could be called with the previous created read-delegate to log the values.
    this->subscriptionServicePtr->ReadValues(this->subscriptionId, readSubscriptionDelegate);
}

} // end of namespace Subscriptions
