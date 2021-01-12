///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "DataAccessComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "DataAccessLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/System/Rsc/Services/RscArrayReader.hpp"
#include "Arp/System/Rsc/Services/RscArrayWriter.hpp"
#include "Arp/System/Rsc/Services/RscStructReader.hxx"
#include "Arp/System/Rsc/Services/RscStructWriter.hxx"
#include "Arp/System/Rsc/Services/RscString.hxx"

void ReadPortNames(Arp::System::Rsc::Services::IRscWriteEnumerator<RscString<512>>& portNames)
{
    // In this case the values of three GDS variables will be read.
    // The names of these variables are specified using the write enumerator.
    portNames.BeginWrite(3);
    try
    {
        portNames.WriteNext("Arp.Plc.Eclr/DataAccessInstance.Int_OUT");
        portNames.WriteNext("Arp.Plc.Eclr/DataAccessInstance.Array_OUT");
        portNames.WriteNext("Arp.Plc.Eclr/DataAccessInstance.Struct_OUT");
        portNames.EndWrite();
    }
    catch (std::exception& e)
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
        Arp::System::Commons::Diagnostics::Logging::Log::Info("<- ReadPortNames()");
    }
}

void ReadResult(Arp::System::Rsc::Services::IRscReadEnumerator<Arp::Plc::Gds::Services::ReadItem>& dataItems)
{
    Arp::Plc::Gds::Services::ReadItem item;
    auto elements = dataItems.BeginRead();
    try
    {
        // The items in the ReadEnumerator appear in the order that the variable names were added in the "Port Names" delegate.
        // The names of the variables are not available here, so it must be known what order the variable names were added.
        // In this case, because each variable happens to have a different type, the variables can be identified by the type.
        while (dataItems.ReadNext(item))
        {
            switch (item.Value.GetType())
            {
                case RscType::Int16:
                {
                    Arp::int16 value;
                    item.Value.CopyTo(value);
                    Arp::System::Commons::Diagnostics::Logging::Log::Info("Int_OUT from DataAccess Read() = {0}", value);
                    break;
                }

                case RscType::Array:
                {
                    RscArrayReader arrayReader{item.Value};

                    // Use the following RscArrayReader methods to get information about the array:
                    // - GetElementType()
                    // - GetSize()
                    // - GetDimensions();

                    RscVariant<512> current;
                    arrayReader.ReadNext(current);

                    Arp::int16 value;
                    current.CopyTo(value);
                    Arp::System::Commons::Diagnostics::Logging::Log::Info("Array_OUT[0] from DataAccess Read() = {0}", value);

                    // Use the ReadNext() method to iterate through all array elements.

                    break;
                }

                case RscType::Struct:
                {
                    RscStructReader<512> structReader{item.Value};

                    // Use the following RscStructReader method to get information about the struct:
                    // - GetFieldCount()
                    // Struct element values will appear in the order that the elements are declared.
                    // The names of the struct elements are not available.

                    RscVariant<512> current;
                    structReader.ReadNextField(current);
                    // Process the MyBool field if necessary.

                    structReader.ReadNextField(current);
                    Arp::int16 intValue;
                    current.CopyTo(intValue);
                    Arp::System::Commons::Diagnostics::Logging::Log::Info("Struct_OUT.MyInt16 from DataAccess Read() = {0}", intValue);

                    structReader.ReadNextField(current);
                    // Process the MyFloat32 field if necessary.

                    structReader.ReadNextField(current);
                    const char * stringValue = current.GetChars();
                    Arp::System::Commons::Diagnostics::Logging::Log::Info("Struct_OUT.MyString from DataAccess Read() = {0}", stringValue);

                    break;
                }

                default:
                {
                    Arp::System::Commons::Diagnostics::Logging::Log::Info("Unhandled type = {0}", item.Value.GetType());
                    break;
                }
            }
        }
        dataItems.EndRead();
    }
    catch (std::exception& e)
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
        Arp::System::Commons::Diagnostics::Logging::Log::Info("<- ReadResult()");
    }
}

void WriteData(Arp::System::Rsc::Services::IRscWriteEnumerator<Arp::Plc::Gds::Services::WriteItem>& dataItems)
{
    // This function writes values to three GDS variables - an Int16, a struct, and an array.
    dataItems.BeginWrite(3);
    try
    {
        // 1. Write the Integer port name and value.
        Arp::Plc::Gds::Services::WriteItem intItem;
        intItem.PortName="Arp.Plc.Eclr/DataAccessInstance.Int_IN";
        intItem.Value=(Arp::int16)42;
        dataItems.WriteNext(intItem);

        // 2. Write the Array port name and value
        // Create the RscVariant representing the array
        Arp::Plc::Gds::Services::WriteItem arrayItem;
        arrayItem.PortName="Arp.Plc.Eclr/DataAccessInstance.Array_IN";
        arrayItem.Value=RscVariant<512>::CreateArrayVariant(10,RscType::Int16);

        // Write the array item to the enumerator *before* creating the RscArrayWriter
        dataItems.WriteNext(arrayItem);

        // Create an RscArrayWriter for the array
        // This must be done *after* the array WriteItem has been written to the enumerator,
        // otherwise this error appears: "WriteElementFunction in RscVariant has to be defined"
        RscArrayWriter arrayWriter{arrayItem.Value};

        // Fill the RSC Array Variant with RscType::Int16 values
        arrayWriter.WriteNext((Arp::int16)42);
        arrayWriter.WriteNext((Arp::int16)142);
        arrayWriter.WriteNext((Arp::int16)242);
        arrayWriter.WriteNext((Arp::int16)342);
        arrayWriter.WriteNext((Arp::int16)442);
        arrayWriter.WriteNext((Arp::int16)542);
        arrayWriter.WriteNext((Arp::int16)642);
        arrayWriter.WriteNext((Arp::int16)742);
        arrayWriter.WriteNext((Arp::int16)842);
        arrayWriter.WriteNext((Arp::int16)942);

        // 3. Write the Struct port name and value
        // Create the RscVariant representing the struct, with four fields
        Arp::Plc::Gds::Services::WriteItem structItem;
        structItem.PortName="Arp.Plc.Eclr/DataAccessInstance.Struct_IN";
        structItem.Value=RscVariant<512>::CreateStructVariant(4);

        // Write the struct item to the enumerator *before* creating the RscStructWriter
        dataItems.WriteNext(structItem);

        // Create an RscStructWriter for the struct
        RscStructWriter<512> structWriter{structItem.Value};

        // Fill the RSC Struct Variant with values
        // The fields are written in the order that they are declared
        structWriter.WriteNextField((Arp::boolean)true);
        structWriter.WriteNextField((Arp::int16)42);
        structWriter.WriteNextField((Arp::float32)42.31);
        // Create an RscString variable to write to the next struct element
        // IMPORTANT: The maximum size of the RscString MUST be the same as the maximum string size of the RscStructWriter object,
        Arp::System::Rsc::Services::RscString<512> myString("String from C++");
        structWriter.WriteNextField(myString);

        dataItems.EndWrite();
    }
    catch (std::exception& e)
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
        Arp::System::Commons::Diagnostics::Logging::Log::Info("<- WriteData()");
    }
}

void WriteResult(Arp::System::Rsc::Services::IRscReadEnumerator<Arp::Plc::Gds::Services::DataAccessError>& errors)
{
    Arp::Plc::Gds::Services::DataAccessError error;
    auto elements = errors.BeginRead();
    try
    {
        while (errors.ReadNext(error))
        {
            // TODO: Handle the error.
        }
        errors.EndRead();
    }
    catch (std::exception& e)
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
        Arp::System::Commons::Diagnostics::Logging::Log::Info("<- WriteResult()");
    }
}

namespace DataAccess
{

using Arp::System::Rsc::ServiceManager;
using namespace Arp::Plc::Commons::Domain;

DataAccessComponent::DataAccessComponent(IApplication& application, const String& name)
: ComponentBase(application, ::DataAccess::DataAccessLibrary::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::DataAccess::DataAccessLibrary::GetInstance().GetNamespace())
, dataAccessThread(this, &DataAccessComponent::AccessData, 1000, "DataAccessThread")
{
}

void DataAccessComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, false);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &DataAccessComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &DataAccessComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &DataAccessComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &DataAccessComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &DataAccessComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &DataAccessComponent::OnPlcChanged);
}

void DataAccessComponent::SubscribeServices()
{
    // gets the IDataAccessService pointer
    this->dataAccessServicePtr = ServiceManager::GetService<IDataAccessService>();
}

void DataAccessComponent::LoadSettings(const String& /*settingsPath*/)
{
    // load firmware settings here
}

void DataAccessComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

    // setup firmware settings here
}

void DataAccessComponent::PublishServices()
{
    // publish the services of this component here
}

void DataAccessComponent::LoadConfig()
{
    // load project config here
}

void DataAccessComponent::SetupConfig()
{
    // setup project config here
}

void DataAccessComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void DataAccessComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &DataAccessComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &DataAccessComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &DataAccessComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &DataAccessComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &DataAccessComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &DataAccessComponent::OnPlcChanged);
}

void DataAccessComponent::PowerDown()
{
    // implement this only if data must be retained even on power down event
}

void DataAccessComponent::OnPlcLoaded()
{
}

void DataAccessComponent::OnPlcStarted()
{
    this->StartDataAccess();
}

void DataAccessComponent::OnPlcStopping()
{
    this->StopDataAccess();
}

void DataAccessComponent::OnPlcUnloading(bool)
{
}

void DataAccessComponent::OnPlcChanging()
{
    this->StopDataAccess();
}

void DataAccessComponent::OnPlcChanged(bool /*success*/)
{
    this->StartDataAccess();
}

void DataAccessComponent::StartDataAccess()
{
    this->dataAccessThread.Start();
}

void DataAccessComponent::StopDataAccess()
{
    this->dataAccessThread.Stop();
}

void DataAccessComponent::AccessData()
{
    // 1. Read a single variable
    // "ReadSingle" can only be used with primitive types
    int16 Int_IN = 0;
    ReadItem readPortData = this->dataAccessServicePtr->ReadSingle("Arp.Plc.Eclr/DataAccessInstance.Int_OUT");
    if (readPortData.Error == DataAccessError::None)
    {
        readPortData.Value.CopyTo(Int_IN);
        this->log.Info("Int_OUT '{0}' read from ReadSingle()", Int_IN);
    }
    else this->log.Info("Error reading single Int from GDS");

    // 2. Write a single variable
    // "WriteSingle" can only be used with primitive types
    WriteItem writePortData;
    writePortData.PortName = "Arp.Plc.Eclr/DataAccessInstance.Int_IN";
    writePortData.Value = this->Int_OUT++;
    if (this->dataAccessServicePtr->WriteSingle(writePortData) == DataAccessError::None)
    {
        // Success
    }
    else this->log.Info("Error writing single Int to GDS");

    // 3. Read multiple variables
    // "Read" can be used with both primitive and complex types (e.g. arrays and structs)
    this->dataAccessServicePtr->Read(make_delegate(ReadPortNames), make_delegate(ReadResult));

    // 4. Write multiple variables
    // "Write" can be used with both primitive and complex types (e.g. arrays and structs)
    this->dataAccessServicePtr->Write(make_delegate(WriteData), make_delegate(WriteResult));
}

} // end of namespace DataAccess
