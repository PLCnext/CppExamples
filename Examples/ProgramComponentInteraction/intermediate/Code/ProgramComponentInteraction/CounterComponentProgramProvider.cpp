//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "CounterComponentProgramProvider.hpp"
#include "Programs/UpCounterProgram.hpp"
#include "Programs/DownCounterProgram.hpp"

namespace ProgramComponentInteraction 
{

IProgram::Ptr CounterComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "UpCounterProgram"){ return std::make_shared<::ProgramComponentInteraction::UpCounterProgram>(this->refCounterComponent, programName); }
    if (programType == "DownCounterProgram"){ return std::make_shared<::ProgramComponentInteraction::DownCounterProgram>(this->refCounterComponent, programName); }

    // else unknown program
    return nullptr;
    
}

} // end of namespace ProgramComponentInteraction
