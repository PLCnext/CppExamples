///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "SubscriptionsComponent3.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "SubscriptionsLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

namespace Subscriptions
{

using namespace Arp::Plc::Commons::Domain;
using Arp::System::Rsc::ServiceManager;

const String SubscriptionsComponent3::complexVarName = "Arp.Plc.Eclr/RealTimeProgram100ms.varSampleStruct";

SubscriptionsComponent3::SubscriptionsComponent3(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , MetaComponentBase(::Subscriptions::SubscriptionsLibrary::GetInstance().GetNamespace())
	, subscriptionThread(this, &SubscriptionsComponent3::LogSubscription, 1000, "SubscriptionLogThread")
{
}

void SubscriptionsComponent3::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &SubscriptionsComponent3::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &SubscriptionsComponent3::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &SubscriptionsComponent3::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &SubscriptionsComponent3::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &SubscriptionsComponent3::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &SubscriptionsComponent3::OnPlcChanged);
}

void SubscriptionsComponent3::SubscribeServices()
{
    // gets the ISubscritpionService pointer
    this->subscriptionServicePtr = ServiceManager::GetService<ISubscriptionService>();
}

void SubscriptionsComponent3::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void SubscriptionsComponent3::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void SubscriptionsComponent3::PublishServices()
{
	// publish the services of this component here
}

void SubscriptionsComponent3::LoadConfig()
{
    // load project config here
}

void SubscriptionsComponent3::SetupConfig()
{
    // setup project config here
}

void SubscriptionsComponent3::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void SubscriptionsComponent3::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &SubscriptionsComponent3::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &SubscriptionsComponent3::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &SubscriptionsComponent3::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &SubscriptionsComponent3::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &SubscriptionsComponent3::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &SubscriptionsComponent3::OnPlcChanged);
}

void SubscriptionsComponent3::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

void SubscriptionsComponent3::OnPlcLoaded()
{
}

void SubscriptionsComponent3::OnPlcStarted()
{
    this->StartSubscription();
}

void SubscriptionsComponent3::OnPlcStopping()
{
    this->StopSubscription();
}

void SubscriptionsComponent3::OnPlcUnloading(bool)
{
}

void SubscriptionsComponent3::OnPlcChanging()
{
    this->StopSubscription();
}

void SubscriptionsComponent3::OnPlcChanged(bool /*success*/)
{
    this->StartSubscription();
}

void SubscriptionsComponent3::StartSubscription()
{
    // First the subscription has to be created.
        // There exists several subscription kinds, in this simple example the 'HightPerformance' kind is used,
        // which operates with a double-buffer and ensures that the read data is task consistent.
        // Check the description of Subscription/SubscriptionKind for more information.
        this->subscriptionId = this->subscriptionServicePtr->CreateSubscription(SubscriptionKind::HighPerformance);

        // The previous call should return a valid, non-zero subscription id otherwise something went wrong.

        // After the subscription has been created, at least one variable has to be added.
        // To add more than one variable, this function could be called another time or the 'AddVariables' function could be used
        // to add a set of variables. In this example a complex variable of the following type is added:
        //     struct SampleStruct
        //     {
        //         uint16 varUInt16 = false;
        //         bool varBool = false;
        //         uint16 varUInt16Array_5[5];
        //     };
        this->subscriptionServicePtr->AddVariable(this->subscriptionId, SubscriptionsComponent3::complexVarName);

        // Finally the 'Subscribe' function has to be called to start the data sampling of the previous added variables.
        this->subscriptionServicePtr->Subscribe(this->subscriptionId, 0);

        // now the subscription is created, configured and subscribed and the sampled date might be processed in the function
        // 'LogSubscription' which is triggerd by the 'subscriptionThread'.

        // At least the delegate which will write the current read variables data to the info log is created
        // and stored in a member variable
        //
        // expected log output:
        //   SubscriptionsComponent3 INFO  - Struct( 101, true, Array[5]( 101, 102, 103, 104, 105))
        this->readSubscriptionValuesDelegate = make_delegate(*this, &SubscriptionsComponent3::LogValues);

        this->subscriptionThread.Start();
}

void SubscriptionsComponent3::StopSubscription()
{
    this->subscriptionServicePtr->Unsubscribe(this->subscriptionId);
    this->subscriptionThread.Stop();
}

void SubscriptionsComponent3::LogSubscription(void)const
{
    // Reads the recording subscription data and logs it.
    // How this works exactly is described in the function 'LogRecords' which is invoked from within the delegate.
    this->subscriptionServicePtr->ReadValues(this->subscriptionId, this->readSubscriptionValuesDelegate);
}

void SubscriptionsComponent3::LogValues(IRscReadEnumerator<RscVariant<512>>& readEnumerator)
{
    // The subscription contains only one variable, so this call should return '1'.
    size_t valueCount = readEnumerator.BeginRead();

    // Only one value is expected and the exact type of this data is known, but nevertheless this function
    // is created in a more general way to better illustrate the pattern of how complex variables are read.
    RscVariant<512> current;
    for (size_t i = 0; i < valueCount; i++)
    {
        readEnumerator.ReadNext(current);

        std::ostringstream os;

        // The 'current' variable should now contain the struct info of the recorded variable from type
        // 'SampleStruct', and the function 'LogValue' might create a 'RscStructReader' to log the values
        this->LogValue(current, os);

        log.Info("{}", os.str());
    }
    readEnumerator.EndRead();
}

void SubscriptionsComponent3::LogValue(const RscVariant<512>& variant, std::ostream& os)const
{
    RscType rscType = variant.GetValueType();

    if (rscType == RscType::Array)
    {
        // 4. Call: The variant is from type 'RscType::Array'
        RscArrayReader arrayReader(variant);
        this->LogArray(arrayReader, os);
    }
    else if (rscType == RscType::Struct)
    {
        // 1. Call: The variant is from type 'RscType::Struct'
        RscStructReader structReader(variant);
        this->LogStruct(structReader, os);
    }
    else
    {
        // 2. Call: The variant is from type 'RscType::Int'
        // 3. Call: The variant is from type 'RscType::Bool'
        // 5. Call: The variant is from type 'RscType::Int'
        // 6. Call: The variant is from type 'RscType::Int'
        // 7. Call: The variant is from type 'RscType::Int'
        // 8. Call: The variant is from type 'RscType::Int'
        // 9. Call: The variant is from type 'RscType::Int'
        this->LogVariant(variant, os);
    }
}

void SubscriptionsComponent3::LogArray(RscArrayReader& arrayReader, std::ostream& os)const
{
    // Get the element count of the passed array, in this example the size should be 5
    size_t arraySize = arrayReader.GetSize();

    os << String::Format("Array[{0}]( ", arraySize);

    // Iterates over each array element
    for (size_t i = 0; i < arraySize; i++)
    {
        // Not relevant for this example but if we would have a array with more than one dimension,
        // you have to call the function ReadNextArray until we reached the last dimension ('1')
        if (arrayReader.GetDimensions() > 1)
        {
            RscArrayReader subArrayReader = arrayReader.ReadNextArray();
            this->LogArray(subArrayReader, os);
        }
        // Not relevant for this example but if the array were a structure array we have to call the function
        // 'ReadNextStruct'
        else if (arrayReader.GetElementType() == RscType::Struct)
        {
            RscStructReader structReader = arrayReader.ReadNextStruct<512>();
            this->LogStruct(structReader, os);
        }
        // If the type is not a structure or an array the elements have to be read with the function
        // 'ReadNext'
        else
        {
            RscVariant<512> currentElement;
            // In this example we call this five times and each element is of type 'Int'
            arrayReader.ReadNext(currentElement);
            this->LogValue(currentElement, os);
        }
        if (i + 1 != arraySize)
        {
            os << ", ";
        }
    }
    os << ")";
}

void SubscriptionsComponent3::LogStruct(RscStructReader& structReader, std::ostream& os)const
{
    RscVariant<512> currentElement;
    size_t fieldCount = structReader.GetFieldCount();

    os << "Struct( ";

    for (size_t i = 0; i < fieldCount; i++)
    {
        // Read the the field of the struct
        structReader.ReadNextField(currentElement);
        // and pass the variant to the function 'LogValue'
        this->LogValue(currentElement, os);
        if (i + 1 != fieldCount)
        {
            os << ", ";
        }
    }
    os << ")";
}

void SubscriptionsComponent3::LogVariant(const RscVariant<512>& rscVariant, std::ostream& os)const
{
    RscType type = rscVariant.GetValueType();

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
