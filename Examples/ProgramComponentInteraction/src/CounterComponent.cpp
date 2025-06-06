//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
//

#include "CounterComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "ProgramComponentInteractionLibrary.hpp"

namespace ProgramComponentInteraction
{
CounterComponent::CounterComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , programProvider(*this)
    , ProgramComponentBase(::ProgramComponentInteraction::ProgramComponentInteractionLibrary::GetInstance().GetNamespace(), programProvider)
{
}

void CounterComponent::Initialize()
{
    // Allocate and initialize resources here
    // Remember to free all allocated resources in the Dispose() method
    DEBUG_FUNCTION_CALL
	// never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void CounterComponent::LoadConfig()
{
    // Load project configuration here
    DEBUG_FUNCTION_CALL
}

void CounterComponent::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // Setup project configuration here
    DEBUG_FUNCTION_CALL
}

void CounterComponent::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    DEBUG_FUNCTION_CALL
    this->dataInfoProvider.Reset();}

void CounterComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext Control devices with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

void CounterComponent::RefreshState()
{
    DEBUG_FUNCTION_CALL
    //
    // When RefreshState is called the command gets toggled.
    //

    if (IP_Stop) // Component Port IP_Stop can set the Stop Command.
    {
        command = Command::Stop;
    }
    else
    {
        switch (command)
        {
        case Command::CountDown:
        {
            command = Command::CountUp;
        }
        break;

        case Command::CountUp:
        {
            command = Command::CountDown;
        }
        break;

        case Command::Stop:
        {
            command = Command::CountDown;
        }
        break;
        }
    }
    // Print command and progress to the Custom.log file
    log.Info("command: {2} progress_DC: {0} progress_UC: {1}", (int)progress_DC, (int)progress_UC, (int)command);
}

} // end of namespace ProgramComponentInteraction
