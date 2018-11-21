#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "TemplateProgram.hpp"
#include "TemplateLibrary.hpp"

namespace Template 
{

using namespace Arp::Plc::Commons::Meta;

    void TemplateLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {    // ProgramDefinition: ::Template::TemplateProgram
                    DataType::Program, CTN<::Template::TemplateProgram>(), sizeof(::Template::TemplateProgram), alignof(::Template::TemplateProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                    }
                },

            }
            // End TypeDefinitions
        );
    }

} // end of namespace Template

