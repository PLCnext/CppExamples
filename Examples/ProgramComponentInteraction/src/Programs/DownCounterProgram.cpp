//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "DownCounterProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace ProgramComponentInteraction
{

 
void DownCounterProgram::Execute()
{
// Print the current progress and the counter value to the Output.log file
	Command c = refCounterComponent.get_command();
	
    switch(progress)
    {
         // Check if counting shall be started next cycle
        case Progress::Done : // idle state
        {
           
            // access get_command() funktion of the Component via reference.
            if( c == Command::CountDown)
            {
                log.Info("DC Start");
                progress = Progress::Running;
            }
            break;
        }
        // Decrement the OP_Counter
        case Progress::Running :
        {
            this->OP_Counter--;
            if(  this->OP_Counter == 0 )
            {
                progress = Progress::Stopped;
            }
            break;
        }
        // Reset the Counter
        case Progress::Stopped :// reinitialize state
        {
            log.Info("DC Done");
            this->OP_Counter = 255;
            refCounterComponent.RefreshState();
            progress = Progress::Done;
            break;
        }
        
        default :
            progress = Progress::Stopped;
        break;
    }

    // Push the current progress to the component.
    refCounterComponent.Set_progress_DC(progress);
}

}
