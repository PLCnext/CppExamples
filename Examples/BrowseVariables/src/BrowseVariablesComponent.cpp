#include "BrowseVariablesComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "BrowseVariablesLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/Plc/Meta/Services/VariableBrowseResult.hpp"
#include "Arp/Plc/Meta/Services/VariableInformation.hpp"

// Define the delegate method that will be passed to the GetComponentNames method of the IVariableBrowseService.
// In this case, the delegate simply logs the names of all the components in the enumerator.
void LogComponentNames(Arp::Base::Rsc::Commons::IRscReadEnumerator<Arp::Base::Rsc::Commons::RscString<512>>& componentNames)
{
	Arp::Base::Rsc::Commons::RscString<512> componentName;
    auto elements = componentNames.BeginRead();

    Arp::Base::Commons::Logging::Log::Info("*** Here are the names of all components that provide variables:");

    try
    {
        while (componentNames.ReadNext(componentName))
        {
            Arp::Base::Commons::Logging::Log::Info("- {0}", componentName);
        }
    }
    catch (std::exception& e)
    {
        Arp::Base::Commons::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }

    Arp::Base::Commons::Logging::Log::Info("*** End of component names.");
}

// Define the delegate method that will be passed to the GetRoots method of the IVariableBrowseService.
// In this case, the delegate simply logs information about each root in the enumerator.
void LogRoots(Arp::Base::Rsc::Commons::IRscReadEnumerator<Arp::Plc::Meta::Services::VariableBrowseResult>& roots)
{
	Arp::Plc::Meta::Services::VariableBrowseResult root;
    auto elements = roots.BeginRead();

    Arp::Base::Commons::Logging::Log::Info("*** Information about the roots of the Arp.Plc.Esm component:");

    try
    {
        while (roots.ReadNext(root))
        {
            Arp::Base::Commons::Logging::Log::Info("- Name: {0}, Type: {1}", root.VariableInfo.Name, root.VariableInfo.Type);
        }
    }
    catch (std::exception& e)
    {
        Arp::Base::Commons::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }

    Arp::Base::Commons::Logging::Log::Info("*** End of Arp.Plc.Esm roots.");
}

// Define the delegate method that will be passed to the GetRoots method of the IVariableBrowseService.
// In this case, the delegate simply logs information about each root in the enumerator.
void LogChildren(Arp::Base::Rsc::Commons::IRscReadEnumerator<Arp::Plc::Meta::Services::VariableBrowseResult>& children)
{
	Arp::Plc::Meta::Services::VariableBrowseResult child;
    auto elements = children.BeginRead();

    try
    {
        while (children.ReadNext(child))
        {
            Arp::Base::Commons::Logging::Log::Info("- Name: {0}, Type: {1}", child.VariableInfo.Name, child.VariableInfo.Type);
        }
    }
    catch (std::exception& e)
    {
        Arp::Base::Commons::Logging::Log::Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }
}

namespace BrowseVariables
{

using Arp::System::Rsc::ServiceManager;
using namespace Arp::Plc::Commons::Domain;

BrowseVariablesComponent::BrowseVariablesComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , MetaComponentBase(::BrowseVariables::BrowseVariablesLibrary::GetInstance().GetNamespace())
	, browseVariablesThread(this, &BrowseVariablesComponent::BrowseVariablesData, 1000, "BrowseVariablesThread")
{
}

void BrowseVariablesComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &BrowseVariablesComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &BrowseVariablesComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &BrowseVariablesComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &BrowseVariablesComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &BrowseVariablesComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &BrowseVariablesComponent::OnPlcChanged);
}

void BrowseVariablesComponent::SubscribeServices()
{
    // gets the IVariableBrowseService pointer
    this->variableBrowseServicePtr = ServiceManager::GetService<IVariableBrowseService>();
}

void BrowseVariablesComponent::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void BrowseVariablesComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void BrowseVariablesComponent::PublishServices()
{
	// publish the services of this component here
}

void BrowseVariablesComponent::LoadConfig()
{
    // load project config here
}

void BrowseVariablesComponent::SetupConfig()
{
    // setup project config here
}

void BrowseVariablesComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void BrowseVariablesComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &BrowseVariablesComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &BrowseVariablesComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &BrowseVariablesComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &BrowseVariablesComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &BrowseVariablesComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &BrowseVariablesComponent::OnPlcChanged);
}

void BrowseVariablesComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

void BrowseVariablesComponent::OnPlcLoaded()
{
}

void BrowseVariablesComponent::OnPlcStarted()
{
    this->StartBrowseVariables();
}

void BrowseVariablesComponent::OnPlcStopping()
{
    this->StopBrowseVariables();
}

void BrowseVariablesComponent::OnPlcUnloading(bool)
{
}

void BrowseVariablesComponent::OnPlcChanging()
{
    this->StopBrowseVariables();
}

void BrowseVariablesComponent::OnPlcChanged(bool /*success*/)
{
    this->StartBrowseVariables();
}

void BrowseVariablesComponent::StartBrowseVariables()
{
    this->browseVariablesThread.Start();
}

void BrowseVariablesComponent::StopBrowseVariables()
{
    this->browseVariablesThread.Stop();
}

void BrowseVariablesComponent::BrowseVariablesData()
{
    // This is implemented as a step sequencer.
    // Each step demonstrates different features of the VariableBrowse service.
    switch(step)
    {
        case 5:
        {
            // Retrieve a list of all components that provide variables
            this->variableBrowseServicePtr->GetComponentNames(LogComponentNames);
            break;
        }

        case 10:
        {
            // Retrieve a list of root nodes on the Arp.Plc.Esm component
        	// In a real application the component name would not be hard-coded,
        	// but would be one of the strings returned by the GetComponentNames method.
            this->variableBrowseServicePtr->GetRoots("Arp.Plc.Esm", LogRoots);
            break;
        }

        case 15:
        {
            // Get information about a root node that we already know the name of.
        	// In a real application the variable name would not be hard-coded,
        	// but would be retrieved by iterating through component roots and children.
            Arp::Base::Commons::Logging::Log::Info("*** Children of the Arp.Plc.Esm/ESM_DATA variable:");

            // Get the variable info in order to retrieve the Browse Handle.
            // The Browse Handle can also be obtained in the GetRoots delegate,
            // but we'll do it here to demonstrate the GetVariable method.
            VariableQueryResult variableInfo = this->variableBrowseServicePtr->GetVariable("Arp.Plc.Esm/ESM_DATA");

            // Use the Browse Handle to get information about the variable's children.
            this->variableBrowseServicePtr->GetChildren(variableInfo.BrowseHandle, LogChildren);

            Arp::Base::Commons::Logging::Log::Info("*** End of ESM_DATA children.");
            break;
        }

        default:
            break;
    }

    // Increment the step and stop after a time
    if (++step > 100) step = 100;
}

} // end of namespace BrowseVariables
