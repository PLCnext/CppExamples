#include "FileStreamExampleProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace FileStreamExample
{
 
void FileStreamExampleProgram::Execute()
{
    //implement program 
    //log.Info("bReset={0} , portfield={1}", fileStreamExampleComponent.bReset, portField);
    fileStreamExampleComponent.bReset =  portField;
}

} // end of namespace FileStreamExample
