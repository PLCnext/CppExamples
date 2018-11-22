#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "ThreadExample/ThreadExampleProgram.hpp"
#include "ThreadExampleLibrary.hpp"

namespace ThreadExample 
{

using namespace Arp::Plc::Commons::Meta;

    void ThreadExampleLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {    // ProgramDefinition: ::ThreadExample::ThreadExampleProgram
                    DataType::Program, CTN<::ThreadExample::ThreadExampleProgram>(), sizeof(::ThreadExample::ThreadExampleProgram), alignof(::ThreadExample::ThreadExampleProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                    }
                },

            }
            // End TypeDefinitions
        );
    }

} // end of namespace ThreadExample

