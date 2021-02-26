#pragma once
#include <BufferedExchangeComponent.hpp>
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"

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
    BufferedExchangeProgram(const BufferedExchangeProgram& arg) = delete;
    virtual ~BufferedExchangeProgram() = default;

public: // operators
    BufferedExchangeProgram&  operator=(const BufferedExchangeProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

private: // fields
    BufferedExchange::BufferedExchangeComponent& bufferedExchangeComponent;
    int count{0};
    long int count_d{0};

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline BufferedExchangeProgram::BufferedExchangeProgram(BufferedExchange::BufferedExchangeComponent& bufferedExchangeComponentArg, const String& name)
: ProgramBase(name)
, bufferedExchangeComponent(bufferedExchangeComponentArg)
{
}

} // end of namespace BufferedExchange
