/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#include "FileStreamExampleProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/Base/Core/ByteConverter.hpp"

namespace FileStreamExample
{
 
void FileStreamExampleProgram::Execute()
{
    //implement program
    //log.Info("bReset={0} , portfield={1}", fileStreamExampleComponent.bReset, portField);
    fileStreamExampleComponent.bReset =  portField;
}

} // end of namespace FileStreamExample
