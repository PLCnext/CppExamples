/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 *  ThreadExampleProgram.cpp
 *
 *  Created on: 16.05.2019
 *  	Author: Eduard Münz, Oliver Warneke
 *
 ******************************************************************************/

/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/

#include "ThreadExampleProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace ThreadExample
{
 
void ThreadExampleProgram::Execute()
{
    //implement program 

	i_pCounter = threadExampleComponent.GetCounterValue();
	Log::Info("-------------------------------Program Cyclic Call:  i_pCounter = {0}", i_pCounter);
}

} // end of namespace ThreadExample
