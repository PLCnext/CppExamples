//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "UpCounterProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace ProgramComponentInteraction
{

void UpCounterProgram::Execute()
{
	 Command c = refCounterComponent.GetCommand();
    
    // This method will be executed each cycle
    // We just increase the counter by one here
switch(progress)
    {
        // Check if counting shall be started next cycle
		case Progress::Done :// idle state
		{
            
			if( c == Command::CountUp)
            {   log.Info("UC Start");
                progress = Progress::Running;
            }
         break;
        }
        // Count Up
        case Progress::Running :
        {
            this->OP_Counter++;
            if(  this->OP_Counter >= 255 )
            {
                progress = Progress::Stopped;
            }
            break;
        }
        // Reset the Counter
        case Progress::Stopped :// reinitialize state
        {
             log.Info("UC Done");
            this->OP_Counter = 0;
            refCounterComponent.RefreshState();
            progress = Progress::Done;
            break;
        }

        default :
            progress = Progress::Stopped;
        break;
    } 
        // Push the Progress to the Component.
    refCounterComponent.SetProgressUC(progress); 
}
}
