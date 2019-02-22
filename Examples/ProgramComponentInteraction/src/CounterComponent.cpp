//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  

#include "CounterComponent.hpp"

namespace ProgramComponentInteraction
{

void CounterComponent::Initialize()
{
    // Allocate and initialize resources here
    // Remember to free all allocated resources in the Dispose() method
    DEBUG_FUNCTION_CALL
}

void CounterComponent::LoadSettings(const String& settingsPath)
{
    // Load firmware settings here
    // You can use any configuration format of your choice
    // The settingsPath can be defined in the *.acf.config file
    DEBUG_FUNCTION_CALL
}

void CounterComponent::SetupSettings()
{
    // Setup firmware settings here
    DEBUG_FUNCTION_CALL
}

void CounterComponent::SubscribeServices()
{
    // Subscribe to services here
    DEBUG_FUNCTION_CALL
}

void CounterComponent::LoadConfig()
{
    // Load project configuration here
    DEBUG_FUNCTION_CALL
}

void CounterComponent::SetupConfig()
{
     CounterComponent::RegisterComponentPorts();

    // Setup project configuration here
    DEBUG_FUNCTION_CALL
}

void CounterComponent::ResetConfig()
{
    DEBUG_FUNCTION_CALL
	  this->dataInfoProvider.Reset();
}

void CounterComponent::PublishServices()
{
    // Reserved for future extension
    DEBUG_FUNCTION_CALL
}

void CounterComponent::Dispose()
{
    // Implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    DEBUG_FUNCTION_CALL
}

void CounterComponent::PowerDown()
{
    // Reserved for future extension
    DEBUG_FUNCTION_CALL
}

void CounterComponent::RefreshState()
{
    DEBUG_FUNCTION_CALL
//
// When RefreshState is called the command gets toggled.
//

    if(IP_Stop) // Component Port IP_Stop can set the Stop Command.  
    {
        command = Command::Stop;
    }
    else{  
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
    // Print command and progress to the Output.log file
    log.Info("command: {2} progress_DC: {0} progress_UC: {1}",(int)progress_DC,progress_UC,(int)command);
}


} // end of namespace ExampleLibrary
