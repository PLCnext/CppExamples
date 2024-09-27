/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 ******************************************************************************/

#include "DeviceInterfaceComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "DeviceInterfaceLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

namespace DeviceInterface
{

using namespace Arp::Plc::Commons::Domain;
using Arp::System::Rsc::ServiceManager;

DeviceInterfaceComponent::DeviceInterfaceComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , MetaComponentBase(::DeviceInterface::DeviceInterfaceLibrary::GetInstance().GetNamespace())
{
}

void DeviceInterfaceComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // subscribe events from the event system (Nm) here
}

void DeviceInterfaceComponent::SubscribeServices()
{
    // gets the Device Interface Service pointers
    this->infoServicePtr = ServiceManager::GetService<IDeviceInfoService>();
    this->statusServicePtr = ServiceManager::GetService<IDeviceStatusService>();
    this->settingsServicePtr = ServiceManager::GetService<IDeviceSettingsService>();
    this->controlServicePtr = ServiceManager::GetService<IDeviceControlService>();
}

void DeviceInterfaceComponent::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void DeviceInterfaceComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void DeviceInterfaceComponent::PublishServices()
{
	// publish the services of this component here
}

void DeviceInterfaceComponent::LoadConfig()
{
    // load project config here
}

void DeviceInterfaceComponent::SetupConfig()
{
    // For simplicity, call all the Service methods here.
	// In a real application, these calls would be made on other
	// thread(s) as required.

	DeviceInfoDemo();
	DeviceStatusDemo();
	DeviceSettingsDemo();
	DeviceControlDemo();
}

void DeviceInterfaceComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void DeviceInterfaceComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

	// implement this inverse to SetupSettings(), LoadSettings() and Initialize()
}

void DeviceInterfaceComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

void DeviceInterfaceComponent::GetInfoItemNames(IRscWriteEnumerator<RscString<512>>& infoItemNamesEnum)
{
    // This function writes the names of a list of items that will be read from the Device Info service.
	infoItemNamesEnum.BeginWrite(infoItemNames.size());  // Specifies the number of items.
	for(const RscString<512>& itemName : infoItemNames)
		infoItemNamesEnum.WriteNext(itemName);
    infoItemNamesEnum.EndWrite();
}

void DeviceInterfaceComponent::InfoItems(IRscReadEnumerator<RscVariant<512>>& infoItems)
{
    // This function reads a list of item values that are returned by the Device Info service.
    // The items in the ReadEnumerator appear in the order that the variable names were added in the "Identifiers" delegate.
    // The names of the variables are not available here, so it must be known what order the variable names were added.
	RscVariant<512> item;
	int i = 0;
	auto elements = infoItems.BeginRead();
    try
    {
        while (infoItems.ReadNext(item))
        {
            switch (item.GetType())
            {
                case RscType::Uint8:
                {
            		log.Info("{0} = {1}", infoItemNames[i], item.GetValue<Arp::uint8>());
                    break;
                }

                case RscType::Uint32:
                {
            		log.Info("{0} = {1}", infoItemNames[i], item.GetValue<Arp::uint32>());
                    break;
                }

                case RscType::Utf8String:
                {
            		log.Info("{0} = {1}", infoItemNames[i], item.ToString());
                    break;
                }

                case RscType::Void:
                {
            		log.Info("Item {0} not supported on this device", infoItemNames[i]);
                    break;
                }

                default:
                {
                    log.Info("{0} has unhandled type '{1}'", infoItemNames[i], item.GetType());
                    break;
                }
            }
            i++;
        }
        infoItems.EndRead();
    }
    catch (std::exception& e)
    {
        log.Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }
}

void DeviceInterfaceComponent::DeviceInfoDemo()
{
	// Add all the item names to a Vector
	infoItemNames.push_back("General.DeviceClass");
	infoItemNames.push_back("General.VendorName");
	infoItemNames.push_back("General.ArticleName");
	infoItemNames.push_back("General.ArticleNumber");
	infoItemNames.push_back("General.SerialNumber");
	infoItemNames.push_back("General.CloudUuid");
	infoItemNames.push_back("General.Firmware.Version");
	infoItemNames.push_back("General.Firmware.VersionMajor");
	infoItemNames.push_back("General.Firmware.VersionMinor");
	infoItemNames.push_back("General.Firmware.VersionPatch");
	infoItemNames.push_back("General.Firmware.VersionBuild");
	infoItemNames.push_back("General.Firmware.VersionStatus");
	infoItemNames.push_back("General.Firmware.BuildDate");
	infoItemNames.push_back("General.Firmware.BuildTime");
	infoItemNames.push_back("General.Hardware.Version");
	infoItemNames.push_back("General.Fpga.Version");
	infoItemNames.push_back("General.Fpga.VersionMajor");
	infoItemNames.push_back("General.Fpga.VersionMinor");
	infoItemNames.push_back("General.Fpga.VersionPatch");
	infoItemNames.push_back("General.UniqueHardwareId");
	infoItemNames.push_back("General.SPNS.Fpga.Version");
	infoItemNames.push_back("General.SPNS.Fpga.VersionMajor");
	infoItemNames.push_back("General.SPNS.Fpga.VersionMinor");
	infoItemNames.push_back("General.SPNS.Fpga.BuildVersion");
	infoItemNames.push_back("General.SPNS.Firmware.Version");
	infoItemNames.push_back("General.SPNS.Firmware.VersionMajor");
	infoItemNames.push_back("General.SPNS.Firmware.VersionMinor");
	infoItemNames.push_back("General.SPNS.Firmware.BuildVersion");
	infoItemNames.push_back("Interfaces.Ethernet.Count");
	infoItemNames.push_back("Interfaces.Ethernet.1.0.Mac");
	infoItemNames.push_back("Interfaces.Ethernet.1.1.Mac");
	infoItemNames.push_back("Interfaces.Ethernet.2.0.Mac");
	infoItemNames.push_back("Cpu.Cores.Count");

	log.Info("****************************************");
	log.Info("*** DEVICE INFO SERVICE - BULK ITEMS ***");
	log.Info("****************************************");
	infoServicePtr->GetItems(GetInfoItemNames, InfoItems);

	log.Info("**********************************************");
	log.Info("*** DEVICE INFO SERVICE - INDIVIDUAL ITEMS ***");
	log.Info("**********************************************");
	RscVariant<512> result;
	for(const RscString<512>& itemName : infoItemNames)
	{
		result = infoServicePtr->GetItem(itemName);
        switch (result.GetType())
        {
            case RscType::Uint8:
            {
        		log.Info("{0} = {1}", itemName, result.GetValue<Arp::uint8>());
                break;
            }

            case RscType::Uint32:
            {
        		log.Info("{0} = {1}", itemName, result.GetValue<Arp::uint32>());
                break;
            }

            case RscType::Utf8String:
            {
        		log.Info("{0} = {1}", itemName, result.ToString());
                break;
            }

            case RscType::Void:
            {
        		log.Info("Item {0} not supported on this device", itemName);
                break;
            }

            default:
            {
                log.Info("{0} has unhandled type '{1}'", itemName, result.GetType());
                break;
            }
        }
	}
}

void DeviceInterfaceComponent::GetStatusItemNames(IRscWriteEnumerator<RscString<512>>& statusItemNamesEnum)
{
    // This function writes the names of a list of items that will be read from the Device Status service.
	statusItemNamesEnum.BeginWrite(statusItemNames.size());  // Specifies the number of items.
	for(const RscString<512>& itemName : statusItemNames)
		statusItemNamesEnum.WriteNext(itemName);
    statusItemNamesEnum.EndWrite();
}

void DeviceInterfaceComponent::StatusItems(IRscReadEnumerator<RscVariant<512>>& statusItems)
{
    // This function reads a list of item values that are returned by the Device Status service.
    // The items in the ReadEnumerator appear in the order that the variable names were added in the "Identifiers" delegate.
    // The names of the variables are not available here, so it must be known what order the variable names were added.
	RscVariant<512> item;
	int i = 0;
	auto elements = statusItems.BeginRead();
    try
    {
        while (statusItems.ReadNext(item))
        {
            switch (item.GetType())
            {
				case RscType::Bool:
				{
					log.Info("{0} = {1}", statusItemNames[i], item.GetValue<Arp::boolean>());
					break;
				}

                case RscType::Int8:
                {
            		log.Info("{0} = {1}", statusItemNames[i], item.GetValue<Arp::int8>());
                    break;
                }

                case RscType::Uint8:
                {
            		log.Info("{0} = {1}", statusItemNames[i], item.GetValue<Arp::uint8>());
                    break;
                }

                case RscType::Uint32:
                {
            		log.Info("{0} = {1}", statusItemNames[i], item.GetValue<Arp::uint32>());
                    break;
                }

                case RscType::Utf8String:
                {
            		log.Info("{0} = {1}", statusItemNames[i], item.ToString());
                    break;
                }

                case RscType::Void:
                {
            		log.Info("Item {0} not supported on this device", statusItemNames[i]);
                    break;
                }

                default:
                {
                    log.Info("{0} has unhandled type '{1}'", statusItemNames[i], item.GetType());
                    break;
                }
            }
            i++;
        }
        statusItems.EndRead();
    }
    catch (std::exception& e)
    {
        log.Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }
}

void DeviceInterfaceComponent::DeviceStatusDemo()
{
	// Add all the item names to a Vector
	statusItemNames.push_back("Status.Cpu.0.Load.Percent");
	statusItemNames.push_back("Status.Cpu.1.Load.Percent");
	statusItemNames.push_back("Status.Cpu.2.Load.Percent");
	statusItemNames.push_back("Status.Cpu.3.Load.Percent");
	statusItemNames.push_back("Status.Memory.Usage.Percent");
	statusItemNames.push_back("Status.Memory.Usage.Percent.Actual");
	statusItemNames.push_back("Status.ProgramMemoryIEC.Usage.Percent");
	statusItemNames.push_back("Status.DataMemoryIEC.Usage.Percent");
	statusItemNames.push_back("Status.RetainMemory.Usage.Percent");
	statusItemNames.push_back("Status.Board.Temperature.Centigrade");
	statusItemNames.push_back("Status.Board.Humidity");
	statusItemNames.push_back("Status.Cpu.Temperature.Centigrade");
	statusItemNames.push_back("Status.Overlay.BootDevice");
	statusItemNames.push_back("Status.RemovableStorage.1.Present");
	statusItemNames.push_back("Status.RemovableStorage.1.State");
	statusItemNames.push_back("Status.Fan.Supported");
	statusItemNames.push_back("Status.Fan.Plugged");
	statusItemNames.push_back("Status.Fan.Defect");
	statusItemNames.push_back("Status.Fan.Maintenance");
	statusItemNames.push_back("Status.Fan.Speed.Level");
	statusItemNames.push_back("Status.Fan.Timestamp");
	statusItemNames.push_back("Status.RamDisk.1.Usage.Percent");
	statusItemNames.push_back("Status.RamDisk.2.Usage.Percent");
	statusItemNames.push_back("Status.RamDisk.1.Usage");
	statusItemNames.push_back("Status.RamDisk.2.Usage");
	statusItemNames.push_back("Status.Ups.ChargeLevel");
	statusItemNames.push_back("Status.Ups.Health");
	statusItemNames.push_back("Status.Ups.Diagnostics");
	statusItemNames.push_back("Status.RunStopSwitch.Position");
	statusItemNames.push_back("Status.RunStopSwitch.Supported");
	statusItemNames.push_back("Status.PowerSupply.X1");
	statusItemNames.push_back("Status.PowerSupply.X2");
	statusItemNames.push_back("Status.Leds.Runtime.Run");
	statusItemNames.push_back("Status.Leds.Runtime.Fail");
	statusItemNames.push_back("Status.Leds.Runtime.Debug");
	statusItemNames.push_back("Status.Leds.Axio.D");
	statusItemNames.push_back("Status.Leds.Axio.E");
	statusItemNames.push_back("Status.Leds.Pnio.Bf_C");
	statusItemNames.push_back("Status.Leds.Pnio.Bf_D");
	statusItemNames.push_back("Status.Leds.Pnio.Sf");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.1.Baudrate");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.2.Baudrate");
	statusItemNames.push_back("Status.Interfaces.Ethernet.2.1.Baudrate");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.1.Duplex");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.2.Duplex");
	statusItemNames.push_back("Status.Interfaces.Ethernet.2.1.Duplex");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.1.Link");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.2.Link");
	statusItemNames.push_back("Status.Interfaces.Ethernet.2.1.Link");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.Ip");
	statusItemNames.push_back("Status.Interfaces.Ethernet.2.Ip");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.Subnet");
	statusItemNames.push_back("Status.Interfaces.Ethernet.2.Subnet");
	statusItemNames.push_back("Status.Interfaces.Ethernet.1.DefaultGateway");
	statusItemNames.push_back("Status.Interfaces.Ethernet.2.DefaultGateway");

	log.Info("******************************************");
	log.Info("*** DEVICE STATUS SERVICE - BULK ITEMS ***");
	log.Info("******************************************");
	statusServicePtr->GetItems(GetStatusItemNames, StatusItems);

	log.Info("************************************************");
	log.Info("*** DEVICE STATUS SERVICE - INDIVIDUAL ITEMS ***");
	log.Info("************************************************");
	RscVariant<512> result;
	for(const RscString<512>& itemName : statusItemNames)
	{
		result = statusServicePtr->GetItem(itemName);
        switch (result.GetType())
        {
			case RscType::Bool:
			{
				log.Info("{0} = {1}", itemName, result.GetValue<Arp::boolean>());
				break;
			}

            case RscType::Int8:
            {
        		log.Info("{0} = {1}", itemName, result.GetValue<Arp::int8>());
                break;
            }

            case RscType::Uint8:
            {
        		log.Info("{0} = {1}", itemName, result.GetValue<Arp::uint8>());
                break;
            }

            case RscType::Uint32:
            {
        		log.Info("{0} = {1}", itemName, result.GetValue<Arp::uint32>());
                break;
            }

            case RscType::Utf8String:
            {
        		log.Info("{0} = {1}", itemName, result.ToString());
                break;
            }

            case RscType::Void:
            {
        		log.Info("Item {0} not supported on this device", itemName);
                break;
            }

            default:
            {
                log.Info("{0} has unhandled type '{1}'", itemName, result.GetType());
                break;
            }
        }
	}
}

void DeviceInterfaceComponent::GetSettingsItemNames(IRscWriteEnumerator<RscString<512>>& settingsItemNamesEnum)
{
    // This function writes the names of a list of items that will be read from the Device Settings service.
	settingsItemNamesEnum.BeginWrite(settingsItemNames.size());  // Specifies the number of items.
	for(const RscString<512>& itemName : settingsItemNames)
		settingsItemNamesEnum.WriteNext(itemName);
	settingsItemNamesEnum.EndWrite();
}

void DeviceInterfaceComponent::SettingsItems(IRscReadEnumerator<DeviceSettingResult>& settingsItems)
{
    // This function reads a list of item values that are returned by the Device Settings service.
    // The items in the ReadEnumerator appear in the order that the variable names were added in the "Identifiers" delegate.
    // The names of the variables are not available here, so it must be known what order the variable names were added.
	DeviceSettingResult item;
	int i = 0;
	auto elements = settingsItems.BeginRead();
    try
    {
        while (settingsItems.ReadNext(item))
        {
            switch (item.Value.GetType())
            {
                case RscType::Uint8:
                {
            		log.Info("{0} = {1}", settingsItemNames[i], item.Value.GetValue<Arp::uint8>());
                    break;
                }

                case RscType::Utf8String:
                {
            		log.Info("{0} = {1}", settingsItemNames[i], item.Value.ToString());
                    break;
                }

                case RscType::Void:
                {
            		log.Info("Item {0} could not be read. Error code = {1}", settingsItemNames[i], item.ErrorCode);
                    break;
                }

                default:
                {
                    log.Info("{0} has unhandled type '{1}'", settingsItemNames[i], item.Value.GetType());
                    break;
                }
            }
            i++;
        }
        settingsItems.EndRead();
    }
    catch (std::exception& e)
    {
        log.Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }
}

void DeviceInterfaceComponent::SetSettingsItems(IRscWriteEnumerator<DeviceSettingItem>& settingsItemsEnum)
{
    // This function writes the items that will be set by the Device Settings service.
	settingsItemsEnum.BeginWrite(1);  // Specifies the number of items to be set.

	RscString<512> settingName = "General.Location";
	RscString<512> settingValue = "Bulk Write Test";

	DeviceSettingItem settingItem;
	settingItem.Setting	= settingName;
	settingItem.Value = settingValue;

	settingsItemsEnum.WriteNext(settingItem);
	// More items can be written with additional calls to WriteNext.
	settingsItemsEnum.EndWrite();
}

void DeviceInterfaceComponent::SettingsResults(IRscReadEnumerator<AccessErrorCode>& settingsResults)
{
    // This function reads a list of Error Codes that are returned by the Device Settings service.
    // The items in the ReadEnumerator appear in the order that the variable names were added in the "Identifiers" delegate.
    // The names of the variables are not available here, so it must be known what order the variable names were added.
	AccessErrorCode result;
	auto elements = settingsResults.BeginRead();
    try
    {
        while (settingsResults.ReadNext(result))
        {
    		log.Info("Error code returned from the write operation = {0}", result);
        }
        settingsResults.EndRead();
    }
    catch (std::exception& e)
    {
        log.Error("Error occurred in {0}:\n{1}", __FUNCTION__, e.what());
    }
}

void DeviceInterfaceComponent::DeviceSettingsDemo()
{
	// Add all the item names to a Vector
	settingsItemNames.push_back("General.Function");
	settingsItemNames.push_back("General.Location");
	settingsItemNames.push_back("Interfaces.Ethernet.1.IpAssign");
	settingsItemNames.push_back("Interfaces.Ethernet.1.Ip");
	settingsItemNames.push_back("Interfaces.Ethernet.1.Subnet");
	settingsItemNames.push_back("Interfaces.Ethernet.1.DefaultGateway");
	settingsItemNames.push_back("Interfaces.Ethernet.1.DnsNameservers");
	settingsItemNames.push_back("Interfaces.Ethernet.2.IpAssign");
	settingsItemNames.push_back("Interfaces.Ethernet.2.Ip");
	settingsItemNames.push_back("Interfaces.Ethernet.2.Subnet");
	settingsItemNames.push_back("Interfaces.Ethernet.2.DefaultGateway");
	settingsItemNames.push_back("Interfaces.Ethernet.2.DnsNameservers");
	settingsItemNames.push_back("Ntp.NtpServers");
	settingsItemNames.push_back("Rtc.DateTime");
	settingsItemNames.push_back("Rtc.Time");
	settingsItemNames.push_back("Rtc.Date");
	settingsItemNames.push_back("RemovableStorage.1.State");
	settingsItemNames.push_back("General.Watchdog.Plc.Restart");

	log.Info("*************************************************");
	log.Info("*** DEVICE SETTINGS SERVICE - READ BULK ITEMS ***");
	log.Info("*************************************************");
	settingsServicePtr->ReadValues(GetSettingsItemNames, SettingsItems);

	log.Info("**************************************************");
	log.Info("*** DEVICE SETTINGS SERVICE - WRITE BULK ITEMS ***");
	log.Info("**************************************************");
	settingsServicePtr->WriteValues(SetSettingsItems, SettingsResults);

	log.Info("********************************************************");
	log.Info("*** DEVICE SETTINGS SERVICE - WRITE INDIVIDUAL ITEMS ***");
	log.Info("********************************************************");
	RscString<512> settingName = "General.Function";
	RscString<512> settingValue = "Individual Write Test";

	DeviceSettingItem settingItem;
	settingItem.Setting	= settingName;
	settingItem.Value = settingValue;

	AccessErrorCode errorCode = settingsServicePtr->WriteValue(settingItem);

	log.Info("{0} has been set to '{1}'. Error code = {2}", settingName, settingValue, errorCode);

	log.Info("*******************************************************");
	log.Info("*** DEVICE SETTINGS SERVICE - READ INDIVIDUAL ITEMS ***");
	log.Info("*******************************************************");
	DeviceSettingResult result;
	for(const RscString<512>& itemName : settingsItemNames)
	{
		result = settingsServicePtr->ReadValue(itemName);
        switch (result.Value.GetType())
        {
            case RscType::Uint8:
            {
        		log.Info("{0} = {1}", itemName, result.Value.GetValue<Arp::uint8>());
                break;
            }

            case RscType::Utf8String:
            {
        		log.Info("{0} = {1}", itemName, result.Value.ToString());
                break;
            }

            case RscType::Void:
            {
        		log.Info("Item {0} could not be read. Error code = {1}", itemName, result.ErrorCode);
                break;
            }

            default:
            {
                log.Info("{0} has unhandled type '{1}'", itemName, result.Value.GetType());
                break;
            }
        }
	}
}

void DeviceInterfaceComponent::DeviceControlDemo()
{
	// These method calls can be uncommented as required.
//	controlServicePtr->RestartDevice();
//	AccessErrorCode resetResult = controlServicePtr->ResetToFactoryDefaults(1);
//	AccessErrorCode fwUpdateResult = controlServicePtr->StartFirmwareUpdate(0);
}

} // end of namespace DeviceInterface
