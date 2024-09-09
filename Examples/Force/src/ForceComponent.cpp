/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#include "ForceComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "ForceLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/Plc/Gds/Services/ForceItem.hpp"

namespace Force
{

using Arp::System::Rsc::ServiceManager;
using namespace Arp::Plc::Commons::Domain;

ForceComponent::ForceComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , MetaComponentBase(::Force::ForceLibrary::GetInstance().GetNamespace())
	, forceThread(this, &ForceComponent::ForceData, 1000, "ForceThread")
{
}

void ForceComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &ForceComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &ForceComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &ForceComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &ForceComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &ForceComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &ForceComponent::OnPlcChanged);
}

void ForceComponent::SubscribeServices()
{
    // gets the IForceService pointer
    this->forceServicePtr = ServiceManager::GetService<IForceService>();
}

void ForceComponent::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void ForceComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void ForceComponent::PublishServices()
{
	// publish the services of this component here
}

void ForceComponent::LoadConfig()
{
    // load project config here
}

void ForceComponent::SetupConfig()
{
    // setup project config here
}

void ForceComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void ForceComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &ForceComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &ForceComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &ForceComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &ForceComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &ForceComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &ForceComponent::OnPlcChanged);
}

void ForceComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

void ForceComponent::OnPlcLoaded()
{
}

void ForceComponent::OnPlcStarted()
{
    this->StartForce();
}

void ForceComponent::OnPlcStopping()
{
    this->StopForce();
}

void ForceComponent::OnPlcUnloading(bool)
{
}

void ForceComponent::OnPlcChanging()
{
    this->StopForce();
}

void ForceComponent::OnPlcChanged(bool /*success*/)
{
    this->StartForce();
}

void ForceComponent::StartForce()
{
    this->forceThread.Start();
}

void ForceComponent::StopForce()
{
    this->forceThread.Stop();
}

void ForceComponent::ForceData()
{
    // This is implemented as a step sequencer.
    // Each step demonstrates different features of the Force service.

    switch(step)
    {
        case 5:
        {
            // Check if certain GDS variables are forceable
            RscString<512> portName;
            boolean isForceable;

            // Global variables not connected to process data are not forceable
            portName = "Arp.Plc.Eclr/Bool_GLOBAL";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Plc.Eclr/Int_GLOBAL";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            // Certain types of global variables connected to process data are forceable
            portName = "Arp.Plc.Eclr/Bool_GLOBAL_IN";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Plc.Eclr/Byte_GLOBAL_IN";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Plc.Eclr/Byte_GLOBAL_OUT";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            // Certain types of program port variables are forceable
            portName = "Arp.Plc.Eclr/MainInstance.Bool_IN";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Plc.Eclr/MainInstance.Bool_OUT";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Plc.Eclr/MainInstance.Int_IN";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Plc.Eclr/MainInstance.Int_OUT";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            // I/O port variables are not directly forceable
            // These are not even recognised as valid variable names
            portName = "Arp.Io.AxlC/0.IN00";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Io.AxlC/0.OUT00";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Io.AxlC/0.~DI8";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            portName = "Arp.Io.AxlC/0.~DO8";
            isForceable = this->forceServicePtr->IsForcable(portName);
            this->log.Info("Is '{0}' forceable? {1}", portName, isForceable);

            break;
        }

        case 6:
        {
            boolean isActive;
            ForceItem forceVariable;

            // Check that forcing is inactive
            isActive = this->forceServicePtr->IsActive();
            this->log.Info("Before adding variables, is forcing active? {0}", isActive);

            // Start forcing by adding a variable to the force list
            forceVariable.VariableName = "Arp.Plc.Eclr/Byte_GLOBAL_OUT";
            forceVariable.ForceValue = true;
            this->forceServicePtr->AddVariable(forceVariable);

            // Check that forcing is active
            isActive = this->forceServicePtr->IsActive();
            this->log.Info("After adding a variable, is forcing active? {0}", isActive);

            // Add another variable to the force list
            forceVariable.VariableName = "Arp.Plc.Eclr/MainInstance.Int_IN";
            forceVariable.ForceValue = (Arp::int16)42;
            this->forceServicePtr->AddVariable(forceVariable);

            break;
        }

        case 10:
        {
            ForceItem forceVariable;

            // Change the value of variables already in the force list
            forceVariable.VariableName = "Arp.Plc.Eclr/Byte_GLOBAL_OUT";
            forceVariable.ForceValue = 0x01;
            this->forceServicePtr->AddVariable(forceVariable);

            forceVariable.VariableName = "Arp.Plc.Eclr/MainInstance.Int_IN";
            forceVariable.ForceValue = 420;
            this->forceServicePtr->AddVariable(forceVariable);

            // Get all the variables currently in the force list
            auto forceVariables = this->forceServicePtr->GetVariables();
            this->log.Info("Current list of forced variables:");
            for (auto& item : forceVariables)
            {
                this->log.Info("- {0}", item.VariableName);
            }

            break;
        }

        case 15:
        {
            boolean isActive;

            // Remove a variable from the force list
            this->forceServicePtr->RemoveVariable("Arp.Plc.Eclr/Byte_GLOBAL_OUT");

            // Check that forcing is still active
            isActive = this->forceServicePtr->IsActive();
            this->log.Info("After removing a variable from the force list, is forcing active? {0}", isActive);

            // Stop forcing by removing the final variable to the force list
            this->forceServicePtr->RemoveVariable("Arp.Plc.Eclr/MainInstance.Int_IN");

            // Check that forcing is active
            isActive = this->forceServicePtr->IsActive();
            this->log.Info("After removing all variables from the force list, is forcing active? {0}", isActive);

            break;
        }

        default:
            break;
    }

    // Increment the step and reset the sequence after a time
    if (++step > 100) step = 0;
}

} // end of namespace Force
