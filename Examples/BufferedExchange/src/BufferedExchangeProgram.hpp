/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "BufferedExchangeComponent.hpp"

namespace BufferedExchange
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(BufferedExchange::BufferedExchangeComponent)
class BufferedExchangeProgram : public ProgramBase, private Loggable<BufferedExchangeProgram>
{
public: // typedefs

public: // construction/destruction
    BufferedExchangeProgram(BufferedExchange::BufferedExchangeComponent& bufferedExchangeComponentArg, const String& name);

public: // operators

public: // properties

public: // operations
    void    Execute() override;

private: // fields
    long int count { 0 };
    bool error_LastCycle { false };
public:
    //#port
    //#attributes(Input)
    //#name(retry_sending)
    boolean retry{false};

private: // fields
    BufferedExchange::BufferedExchangeComponent& bufferedExchangeComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline BufferedExchangeProgram::BufferedExchangeProgram(BufferedExchange::BufferedExchangeComponent& bufferedExchangeComponentArg, const String& name)
: ProgramBase(name)
, bufferedExchangeComponent(bufferedExchangeComponentArg)
{
}

} // end of namespace BufferedExchange
