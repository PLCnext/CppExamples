#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "CppDataTypeTestComponent.hpp"

namespace CppDataTypeTest
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(CppDataTypeTest::CppDataTypeTestComponent)
class CppDataTypeTestProgram : public ProgramBase, private Loggable<CppDataTypeTestProgram>
{
public: // typedefs

public: // construction/destruction
    CppDataTypeTestProgram(CppDataTypeTest::CppDataTypeTestComponent& cppDataTypeTestComponentArg, const String& name);
    CppDataTypeTestProgram(const CppDataTypeTestProgram& arg) = delete;
    virtual ~CppDataTypeTestProgram() = default;

public: // operators
    CppDataTypeTestProgram&  operator=(const CppDataTypeTestProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
           =====
           Ports are defined in the following way:
           //#port
           //#attributes(Input|Retain)
           //#name(NameOfPort)
           boolean portField;

           The attributes comment define the port attributes and is optional.
           The name comment defines the name of the port and is optional. Default is the name of the field.
        */

private: // fields
    CppDataTypeTest::CppDataTypeTestComponent& cppDataTypeTestComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline CppDataTypeTestProgram::CppDataTypeTestProgram(CppDataTypeTest::CppDataTypeTestComponent& cppDataTypeTestComponentArg, const String& name)
: ProgramBase(name)
, cppDataTypeTestComponent(cppDataTypeTestComponentArg)
{
}

} // end of namespace CppDataTypeTest
