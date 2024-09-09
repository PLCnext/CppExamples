/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#include "OpcPlcManagerComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "OpcPlcManagerLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

namespace OpcPlcManager
{

using namespace Arp::Plc::Commons::Domain;
using Arp::System::Rsc::ServiceManager;

OpcPlcManagerComponent::OpcPlcManagerComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , MetaComponentBase(::OpcPlcManager::OpcPlcManagerLibrary::GetInstance().GetNamespace())
    , workerThreadInstance(make_delegate(this, &OpcPlcManagerComponent::workerThreadBody) , 1000, "WorkerThreadName")
{
}

void OpcPlcManagerComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // subscribe events from the event system (Nm) here
}

void OpcPlcManagerComponent::SubscribeServices()
{
    // gets the IDataAccessService pointer
    this->plcManagerService2Ptr = ServiceManager::GetService<IPlcManagerService2>();
}

void OpcPlcManagerComponent::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void OpcPlcManagerComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void OpcPlcManagerComponent::PublishServices()
{
	// publish the services of this component here
}

void OpcPlcManagerComponent::LoadConfig()
{
    // load project config here
}

void OpcPlcManagerComponent::SetupConfig()
{
    // setup project config here
    Log::Info("OpcPlcManagerComponent: Starting worker thread.");
    workerThreadInstance.Start();
}

void OpcPlcManagerComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
    Log::Info("OpcPlcManagerComponent: Stopping worker thread.");
    workerThreadInstance.Stop();
}

void OpcPlcManagerComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

	// implement this inverse to SetupSettings(), LoadSettings() and Initialize()
}

void OpcPlcManagerComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

// Thread Body
void OpcPlcManagerComponent::workerThreadBody(void)
{
    // Check if each method has been called from the UA Client.
    // If so, call the corresponding method on the RSC service,
    // and return the result.

    if (this->GetPlcState.UA_MethodState == 1)
    {
        Log::Info("OpcPlcManagerComponent: GetPlcState.");

        // Get the PLC state from the RSC service
        this->GetPlcState.state = static_cast<Arp::uint32>(this->plcManagerService2Ptr->GetPlcState());

        // Signal that the method has completed successfully
        this->GetPlcState.UA_StatusCode = 0;
        this->GetPlcState.UA_MethodState = 0;
    }

    if (this->Start.UA_MethodState == 1)
    {
        Log::Info("OpcPlcManagerComponent: Start: {0:d} {1}", this->Start.startKind, (this->Start.async ? "asynchronous" : "synchronous"));

        // Start the PLC via the RSC service
        this->plcManagerService2Ptr->Start((PlcStartKind)this->Start.startKind, this->Start.async);

        // Signal that the method has completed successfully
        this->Start.UA_StatusCode = 0;
        this->Start.UA_MethodState = 0;
    }

    if (this->Stop.UA_MethodState == 1)
    {
        Log::Info("OpcPlcManagerComponent: Stop {0}.", (this->Stop.async ? "asynchronous" : "synchronous"));

        // Stop the PLC via the RSC service
        this->plcManagerService2Ptr->Stop(this->Stop.async);

        // Signal that the method has completed successfully
        this->Stop.UA_StatusCode = 0;
        this->Stop.UA_MethodState = 0;
    }
}

} // end of namespace OpcPlcManager
