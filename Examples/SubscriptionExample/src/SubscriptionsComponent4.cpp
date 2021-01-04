///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "SubscriptionsComponent4.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "SubscriptionsLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/System/Rsc/Services/RscArrayReader.hpp"
#include "Arp/System/Rsc/Services/RscStructReader.hxx"

namespace Subscriptions
{

using namespace Arp::Plc::Commons::Domain;
using Arp::System::Rsc::ServiceManager;

const String SubscriptionsComponent4::varTask100msName = "Arp.Plc.Eclr/RealTimeProgram100ms.varUInt16";
const String SubscriptionsComponent4::varTask500msName = "Arp.Plc.Eclr/RealTimeProgram500ms.varUInt16";

SubscriptionsComponent4::SubscriptionsComponent4(IApplication& application, const String& name)
: ComponentBase(application, ::Subscriptions::SubscriptionsLibrary::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::Subscriptions::SubscriptionsLibrary::GetInstance().GetNamespace())
, subscriptionThread(this, &SubscriptionsComponent4::LogSubscription, 1000, "SubscriptionLogThread")
{
}

void SubscriptionsComponent4::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, false);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &SubscriptionsComponent4::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &SubscriptionsComponent4::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &SubscriptionsComponent4::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &SubscriptionsComponent4::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &SubscriptionsComponent4::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &SubscriptionsComponent4::OnPlcChanged);
}

void SubscriptionsComponent4::SubscribeServices()
{
    // gets the ISubscritpionService pointer
    this->subscriptionServicePtr = ServiceManager::GetService<ISubscriptionService>();
}

void SubscriptionsComponent4::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void SubscriptionsComponent4::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void SubscriptionsComponent4::PublishServices()
{
	// publish the services of this component here
}

void SubscriptionsComponent4::LoadConfig()
{
    // load project config here
}

void SubscriptionsComponent4::SetupConfig()
{
    // setup project config here
}

void SubscriptionsComponent4::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void SubscriptionsComponent4::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &SubscriptionsComponent4::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &SubscriptionsComponent4::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &SubscriptionsComponent4::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &SubscriptionsComponent4::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &SubscriptionsComponent4::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &SubscriptionsComponent4::OnPlcChanged);
}

void SubscriptionsComponent4::PowerDown()
{
	// implement this only if data must be retained even on power down event
}

void SubscriptionsComponent4::OnPlcLoaded()
{
}

void SubscriptionsComponent4::OnPlcStarted()
{
    this->StartSubscription();
}

void SubscriptionsComponent4::OnPlcStopping()
{
    this->StopSubscription();
}

void SubscriptionsComponent4::OnPlcUnloading(bool)
{
}

void SubscriptionsComponent4::OnPlcChanging()
{
    this->StopSubscription();
}

void SubscriptionsComponent4::OnPlcChanged(bool /*success*/)
{
    this->StartSubscription();
}

void SubscriptionsComponent4::StartSubscription()
{
    // First the subscription has to be created.
    // This example creates a subscription of kind 'Recording' and add two variables from different
    // tasks ('100ms' and '500ms').
    // After that the subscription will be subscribed.
    // Have a look at the example in 'SubscriptionsComponent' for detailed information about how to
    // create a subscription.

    // create the recording subscription with a capacity of 15 records
    this->subscriptionId = this->subscriptionServicePtr->CreateRecordingSubscription(15);

    // After the subscription is created, at least one variable has to be added.
    // To add more than one variable, this function might be called another time or the 'AddVariables' function could be used
    // to add a set of variables. In this example the 2 variables from tow different tasks are added.
    this->subscriptionServicePtr->AddVariable(this->subscriptionId, varTask100msName);
    this->subscriptionServicePtr->AddVariable(this->subscriptionId, varTask500msName);

    // Finally the 'Subscribe' function has to be called to start the data sampling of the previous added variables.
    this->subscriptionServicePtr->Subscribe(this->subscriptionId, 0);

    // create the delegate which will write the read variable values to the info log:
    //
    // expected log output:
    // 01.07.20 07:43:31.409 SubscriptionsComponent4   INFO    - Read records of subscription '1':
    //        [timestamp, Arp.Plc.Eclr/RealTimeProgram100ms.varUInt16]
    //        [ 2020-07-01T07:43:30.418081, 12 ]
    //        [ 2020-07-01T07:43:30.518555, 13 ]
    //        [ 2020-07-01T07:43:30.618679, 14 ]
    //        [ 2020-07-01T07:43:30.718933, 15 ]
    //        [ 2020-07-01T07:43:30.818034, 16 ]
    //        [ 2020-07-01T07:43:30.918688, 17 ]
    //        [ 2020-07-01T07:43:31.018307, 18 ]
    //        [ 2020-07-01T07:43:31.118745, 19 ]
    //        [ 2020-07-01T07:43:31.218379, 20 ]
    //        [ 2020-07-01T07:43:31.319772, 21 ]
    //
    //        [timestamp, Arp.Plc.Eclr/RealTimeProgram500ms.varUInt16]
    //        [ 2020-07-01T07:43:30.818019, 4 ]
    //        [ 2020-07-01T07:43:31.319814, 5 ]
    this->readRecordDelegate = make_delegate(*this, &SubscriptionsComponent4::LogRecords);

    // The subscription API tells us that all the variable data belonging to the same task
    // comes in separate records, regardless of the order in which the variables were added.
    // Because two variables from two different tasks were added, the exact order is unknown.
    // So to make sure which variable belongs to which record it is necessary to get the subscription
    // variable information.
    this->GetRecordVariableInfos(this->recordVariableInfos);

    this->subscriptionThread.Start();
}

void SubscriptionsComponent4::StopSubscription()
{
    this->subscriptionServicePtr->Unsubscribe(this->subscriptionId);
    this->subscriptionThread.Stop();
}

void SubscriptionsComponent4::LogSubscription()const
{
    // Reads the recorded subscription data and writes it to the log.
    // The ellaborate descitpion might be found in the function 'LogRecords' which is invoked by the delegate.
    this->subscriptionServicePtr->ReadRecords(this->subscriptionId, 0, readRecordDelegate);
}

void SubscriptionsComponent4::LogRecords(IRscReadEnumerator<RscVariant<512>>& readEnumerator)const
{
    // This call returns '2' because the subscription contain variables of two different tasks.
    size_t taskCount = readEnumerator.BeginRead();

    RscVariant<512> currentTask;
    std::ostringstream ss;
    ss << String::Format("Read records of subscription '{}':\n", this->subscriptionId);

    for (size_t i = 0; i < taskCount; i++)
    {
        // read the task records
        readEnumerator.ReadNext(currentTask);

        // This variant contains an array of records even though if no records has been recorded yet.
        // So this variant always is of type 'RscType::Array'!
        if (currentTask.GetType() == RscType::Array)
        {
            ss << "\t[" << this->recordVariableInfos[i][0].Name << ", " << this->recordVariableInfos[i][1].Name << "]\n";
            RscArrayReader taskRecordReader(currentTask);
            // Obtain number of available records of this task
            size_t recordCount = taskRecordReader.GetSize();
            for (size_t j = 0; j < recordCount; j++)
            {
                // The variant 'currentRecord' represents an array containing the data of the
                // variables including the prepending timestamp
                RscVariant<512> currentRecord;
                taskRecordReader.ReadNext(currentRecord);
                ss << "\t";
                // The variant containing the read variable values of the current task is passed to the function 'LogRecord'.
                this->LogRecord(currentRecord, ss);
                ss << std::endl;
            }
        }
        else
        {
            log.Error("Task record type '{}' is unexpectedly not '{}'.", currentTask.GetType(), RscType::Array);
        }
        ss << std::endl;
    }
    readEnumerator.EndRead();

    log.Info("{}", ss.str());
}

void SubscriptionsComponent4::LogRecord(const RscVariant<512>& record, std::ostream& os)const
{
    // The variant 'record' contains an array of variable values of teh current task
    // So this variant always has the type 'RscType::Array'!
    if (record.GetType() == RscType::Array)
    {
        RscArrayReader recordReader(record);
        // Number of variables of the current task with one timestamp
        // In this example the count is '2' for both tasks.
        size_t elementCount = recordReader.GetSize();

        // Start reading the timestamp and variable data of the current record
        os << "[ ";
        for (size_t i = 0; i < elementCount; i++)
        {
            RscVariant<512> currentElement;
            recordReader.ReadNext(currentElement);

            // The first element is always the timestamp of type 'int64' which stores Unix us ticks.
            if (i == 0)
            {
                // Logs the timestamp
                int64 t = currentElement.GetValue<int64>();
                os << DateTime::FromUnixTimeMicroseconds(t).ToIso8601String();
            }
            else
            {
                // Logs the variable value
                this->LogVariant(currentElement, os);
            }

            if (i + 1 != elementCount)
            {
                os << ", ";
            }
        }
        os << " ]";
    }
    else
    {
        log.Error("Record type '{}' is unexpectedly not '{}'.", record.GetType(), RscType::Array);
    }
}

void SubscriptionsComponent4::GetRecordVariableInfos(RecordVariableInfos& recordVariableInfosArg)const
{
    using GetInfoDelegate = ISubscriptionService::GetTimeStampedVariableInfosVariableInfoDelegate;

    GetInfoDelegate infoDelegate = GetInfoDelegate::create([&](IRscReadEnumerator<VariableInfo>& readEnumerator)
    {
        recordVariableInfosArg.clear();

        size_t taskCount = readEnumerator.BeginRead();
        RecordVariableInfos::iterator currentRecordInfos = recordVariableInfosArg.end();

        VariableInfo currentInfo;
        while (readEnumerator.ReadNext(currentInfo))
        {
            if (currentInfo.Name.ToString() == "timestamp")
            {
                if (recordVariableInfosArg.size() == 0)
                {
                    recordVariableInfosArg.resize(taskCount);
                    currentRecordInfos = recordVariableInfosArg.begin();
                }
                else
                {
                    currentRecordInfos++;
                }
            }
            if (currentRecordInfos == recordVariableInfosArg.end())
            {
                throw InvalidOperationException("Unexpected order while reading timestamped variable information!");
            }
            else
            {
                currentRecordInfos->push_back(currentInfo);
            }
        }
        readEnumerator.EndRead();
    });

    this->subscriptionServicePtr->GetTimeStampedVariableInfos(this->subscriptionId, infoDelegate);
}

void SubscriptionsComponent4::LogVariant(const RscVariant<512>& rscVariant, std::ostream& os)const
{
    const RscType& type = rscVariant.GetValueType();

    switch (type)
    {
        // Actually there is no RscVariant::ToString() for DateTime (exception!) available (but from FW version >= 21.3)
        case RscType::DateTime:
            os << rscVariant.GetValue<Arp::DateTime>().ToIso8601String();
            break;

        // The rsc type 'void' stands for a Null object, therefore NULL will print to the log.
        case RscType::Void:
            os << "NULL";
            break;

        default:
            os << rscVariant.ToString();
            break;
    }
}

} // end of namespace Subscriptions
