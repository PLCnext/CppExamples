//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "TemplateComponent.hpp"

namespace Template 
{

void TemplateComponent::Initialize()
{
}

void TemplateComponent::LoadSettings(const String& settingsPath)
{
}

void TemplateComponent::SetupSettings()
{
}

void TemplateComponent::SubscribeServices()
{
}

void TemplateComponent::LoadConfig()
{
}

void TemplateComponent::SetupConfig()
{
    // DO NOT REMOVE THIS!
    TemplateComponent::RegisterComponentPorts();
}

void TemplateComponent::ResetConfig()
{
}

void TemplateComponent::PublishServices()
{
}

void TemplateComponent::Dispose()
{
}

void TemplateComponent::PowerDown()
{
}

} // end of namespace Template
