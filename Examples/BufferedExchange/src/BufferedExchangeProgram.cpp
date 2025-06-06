/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#include "BufferedExchangeProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/Base/Core/ByteConverter.hpp"

namespace BufferedExchange
{
 
void BufferedExchangeProgram::Execute()
{
    //implement program
    if (count % 1000 == 0)
    {
        log.Info("---------------- Execute: {0} ", count);
    }
    count++;

    //Watch out this is blocking!
    if(!error_LastCycle || retry )
    {
        if (!bufferedExchangeComponent.wD.SetData( count))
        {
            // ensure the log does not get flooded.
            if(!error_LastCycle){
            log.Warning("-------------- Instance:{1} DataLost: {0} ",  count, this->GetFullName());
            error_LastCycle = true;
            }
        }else{
            error_LastCycle = false;
        }
    }
}

} // end of namespace BufferedExchange
