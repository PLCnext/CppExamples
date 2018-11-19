//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "Programs/UpCounterProgram.hpp"
#include "Programs/DownCounterProgram.hpp"
#include "ProgramComponentInteractionLibrary.hpp"

namespace ProgramComponentInteraction 
{

using namespace Arp::Plc::Commons::Meta;

    void ProgramComponentInteractionLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {    // ProgramDefinition: ::ProgramComponentInteraction::UpCounterProgram
                    DataType::Program, CTN<::ProgramComponentInteraction::UpCounterProgram>(), sizeof(::ProgramComponentInteraction::UpCounterProgram), alignof(::ProgramComponentInteraction::UpCounterProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "OP_Counter",offsetof(::ProgramComponentInteraction::UpCounterProgram, OP_Counter), DataType::UInt8, "", sizeof(uint8), alignof(uint8), { }, StandardAttribute::Output | StandardAttribute::Opc },
                    }
                },

                {    // ProgramDefinition: ::ProgramComponentInteraction::DownCounterProgram
                    DataType::Program, CTN<::ProgramComponentInteraction::DownCounterProgram>(), sizeof(::ProgramComponentInteraction::DownCounterProgram), alignof(::ProgramComponentInteraction::DownCounterProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "OP_Counter",offsetof(::ProgramComponentInteraction::DownCounterProgram, OP_Counter), DataType::UInt8, "", sizeof(uint8), alignof(uint8), { }, StandardAttribute::Output },
                    }
                },

            }
            // End TypeDefinitions
        );
    }

} // end of namespace ProgramComponentInteraction

