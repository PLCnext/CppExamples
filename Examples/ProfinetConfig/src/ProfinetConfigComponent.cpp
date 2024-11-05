/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 ******************************************************************************/

#include "ProfinetConfigComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "ProfinetConfigLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

// Function for generating a random lower-case string
// Source: https://stackoverflow.com/a/12468109
std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

namespace ProfinetConfig
{

using namespace Arp::Plc::Commons::Domain;
using Arp::System::Rsc::ServiceManager;

ProfinetConfigComponent::ProfinetConfigComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , MetaComponentBase(::ProfinetConfig::ProfinetConfigLibrary::GetInstance().GetNamespace())
{
}

void ProfinetConfigComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // subscribe events from the event system (Nm) here
}

void ProfinetConfigComponent::SubscribeServices()
{
	// subscribe the services used by this component here
    // gets the Device Interface Service pointers
    this->configServicePtr = ServiceManager::GetService<IConfigurationService>();
}

void ProfinetConfigComponent::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void ProfinetConfigComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void ProfinetConfigComponent::PublishServices()
{
	// publish the services of this component here
}

void ProfinetConfigComponent::LoadConfig()
{
    // load project config here
}

void ProfinetConfigComponent::SetupConfig()
{
	// For simplicity, call all the RSC service methods here.
	// In a real application these methods would be called elsewhere.
	RscVariant<512> deviceName;
	RscString<512> newDeviceName;

	// Get the Profinet device name (i.e. the Station Name)
	ConfigurationErrorCode result = configServicePtr->Read("Arp.Io.PnD/StationName", deviceName);
	log.Info("Result of Config Read: {0}", result);
	log.Info("Profinet device name is {0}", deviceName.ToString());

	// Write a new Profinet device name
	newDeviceName = random_string(16);
	log.Info("Writing new Profinet device name : {0}", newDeviceName.ToString());
	result = configServicePtr->Write("Arp.Io.PnD/StationName", newDeviceName);
	log.Info("Result of Config Write: {0}", result);

	// Read back the Profinet device name
	result = configServicePtr->Read("Arp.Io.PnD/StationName", deviceName);
	log.Info("Result of Config Read: {0}", result);
	log.Info("Profinet device name is {0}", deviceName.ToString());

	// You can check that the Profinet device name has been written to the following file on the device:
    // /opt/plcnext/config/Io/PnS/PnS.local.config
}

void ProfinetConfigComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void ProfinetConfigComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

	// implement this inverse to SetupSettings(), LoadSettings() and Initialize()
}

void ProfinetConfigComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

} // end of namespace ProfinetConfig
