//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "CounterComponent.hpp"

namespace ProgramComponentInteraction 
{

void CounterComponent::RegisterComponentPorts()
{
    this->dataInfoProvider.AddRoot("IP_Stop", this->IP_Stop);
}

} // end of namespace ProgramComponentInteraction
