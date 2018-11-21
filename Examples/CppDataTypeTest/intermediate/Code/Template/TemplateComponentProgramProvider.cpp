#include "TemplateComponentProgramProvider.hpp"
#include "TemplateProgram.hpp"

namespace Template 
{

IProgram::Ptr TemplateComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "TemplateProgram"){ return std::make_shared<::Template::TemplateProgram>(this->refTemplateComponent, programName); }

    // else unknown program
    return nullptr;
    
}

} // end of namespace Template
