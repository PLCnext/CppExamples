#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "FileStreamExampleComponent.hpp"

namespace FileStreamExample
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(FileStreamExample::FileStreamExampleComponent)
class FileStreamExampleProgram : public ProgramBase, private Loggable<FileStreamExampleProgram>
{
public: // typedefs

public: // construction/destruction
    FileStreamExampleProgram(FileStreamExample::FileStreamExampleComponent& fileStreamExampleComponentArg, const String& name);
    FileStreamExampleProgram(const FileStreamExampleProgram& arg) = delete;
    virtual ~FileStreamExampleProgram() = default;

public: // operators
    FileStreamExampleProgram&  operator=(const FileStreamExampleProgram& arg) = delete;

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
		//#port
		//#attributes(Input)
		//#name(DeleteFileAtNextStart)
		boolean portField{false};
private: // fields
    FileStreamExample::FileStreamExampleComponent& fileStreamExampleComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline FileStreamExampleProgram::FileStreamExampleProgram(FileStreamExample::FileStreamExampleComponent& fileStreamExampleComponentArg, const String& name)
: ProgramBase(name)
, fileStreamExampleComponent(fileStreamExampleComponentArg)
{
	log.Info("---Constructor:{0}",GetFullName());
}

} // end of namespace FileStreamExample
