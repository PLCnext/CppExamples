#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace Template 
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class TemplateComponent;

class TemplateComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    TemplateComponentProgramProvider(TemplateComponent& refTemplateComponentArg);
    virtual ~TemplateComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    TemplateComponentProgramProvider(const TemplateComponentProgramProvider& arg) = delete;
    TemplateComponentProgramProvider& operator=(const TemplateComponentProgramProvider& arg) = delete;

private: // fields
	TemplateComponent& refTemplateComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class TemplateComponentProgramProvider

inline TemplateComponentProgramProvider::TemplateComponentProgramProvider(TemplateComponent& refTemplateComponentArg)
	: refTemplateComponent(refTemplateComponentArg)
{
}

} // end of namespace Template
