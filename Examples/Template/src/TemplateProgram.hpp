//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"

namespace Template 
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//TODO not neccessary here. Include header instead
//forwards
class TemplateComponent;

//#component(TemplateComponent)
class TemplateProgram : public ProgramBase, private Loggable<TemplateProgram>
{
public: // typedefs

public: // construction/destruction
    TemplateProgram(TemplateComponent& refTemplateComponentArg, const String& name);
    TemplateProgram(const TemplateProgram& arg) = delete;
    virtual ~TemplateProgram() = default;

public: // operators
    TemplateProgram&  operator=(const TemplateProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: // ports

private: // fields
	TemplateComponent& refTemplateComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline TemplateProgram::TemplateProgram(TemplateComponent& refTemplateComponentArg, const String& name)
: ProgramBase(name)
, refTemplateComponent(refTemplateComponentArg)
{
}

} // end of namespace Template
