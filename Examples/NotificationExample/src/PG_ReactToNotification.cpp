/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#include "PG_ReactToNotification.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/Base/Core/ByteConverter.hpp"

namespace NotificationExample
{
 
void PG_ReactToNotification::Execute()
{
    //implement program
    this->OP_uiInfoValue = this->cOMP_Notifications.OP_uiValue1;
    this->OP_uiWarningValue = this->cOMP_Notifications.OP_uiValue2;

    // Copy values from Component to Program

    // Do other stuff with component values
    // if(this->cOMP_Notifications.OP_uiValue1 >10){
    //     log.Info("Value1:{0}",this->cOMP_Notifications.OP_uiValue1);
    //     log.Info("Value1:{0}",this->cOMP_Notifications.OP_uiValue2);
    // }
}

} // end of namespace NotificationExample
