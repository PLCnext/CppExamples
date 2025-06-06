/******************************************************************************
 *
 * Copyright (c) 2024 Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 ******************************************************************************/

#include "ComponentWithPorts.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "ComponentPortsLibrary.hpp"

namespace ComponentPorts
{
ComponentWithPorts::ComponentWithPorts(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , programProvider(*this)
    , ProgramComponentBase(::ComponentPorts::ComponentPortsLibrary::GetInstance().GetNamespace(), programProvider)
{
}

void ComponentWithPorts::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here

    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcStarting += make_delegate(this, &ComponentWithPorts::OnPlcStarting);
    // Do not forget to unregister these handlers, e.g. in the dispose() method!
}

void ComponentWithPorts::LoadConfig()
{
    // load project config here
}

void ComponentWithPorts::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void ComponentWithPorts::Dispose()
{
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcStarting -= make_delegate(this, &ComponentWithPorts::OnPlcStarting);

    // never remove next line
    ComponentBase::Dispose();
}

void ComponentWithPorts::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void ComponentWithPorts::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext Control devices with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

void ComponentWithPorts::OnPlcStarting(PlcStartKind startKind)
{
    // this event handler is called before starting the PLC
    log.Info("'{0}({1})' invoked of object with instance name '{2}' from thread '{3}'", __FUNCTION__, startKind, this->GetFullName(), pthread_self());

    if (PlcStartKind::Warm == startKind ||
        PlcStartKind::RestoreWarm == startKind ||
        PlcStartKind::Cold == startKind)
    {
        // initialize non-retain ports anyhow (in all 3 cases)
        // if necessary, further member variables can be initialized, too
        ports.nonretainPort1 = 1;

        if (PlcStartKind::Cold == startKind)
        {   // initialize retain ports, too
            ports.retainPort1 = 1;
        }
    }
    // no special action required in case of PlcStartKind::Hot
}

} // end of namespace ComponentPorts
