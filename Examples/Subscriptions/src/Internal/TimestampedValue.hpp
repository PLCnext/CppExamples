///////////////////////////////////////////////////////////////////////////////
//
//  Copyright PHOENIX CONTACT GmbH
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"

namespace Subscriptions { namespace Internal
{

using namespace Arp;

struct TimestampedValue
{
    String varName;
    DateTime timestamp;
    uint16 value;
};

}} // end of namespace Subscriptions::Internal
