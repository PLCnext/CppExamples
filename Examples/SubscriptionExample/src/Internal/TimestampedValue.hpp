///////////////////////////////////////////////////////////////////////////////
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"

namespace Apps { namespace Demo { namespace Subscriptions { namespace Internal
{

using namespace Arp;

struct TimestampedValue
{
    String varName;
    DateTime timestamp;
    uint16 value;
};

}}}} // end of namespace Apps::Demo::Subscriptions::Internal

