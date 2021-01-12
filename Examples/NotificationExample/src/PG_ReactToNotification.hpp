///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "COMP_Notifications.hpp"

namespace NotificationExample
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(NotificationExample::COMP_Notifications)
class PG_ReactToNotification : public ProgramBase, private Loggable<PG_ReactToNotification>
{
public: // typedefs

public: // construction/destruction
    PG_ReactToNotification(NotificationExample::COMP_Notifications& cOMP_NotificationsArg, const String& name);
    PG_ReactToNotification(const PG_ReactToNotification& arg) = delete;
    virtual ~PG_ReactToNotification() = default;

public: // operators
    PG_ReactToNotification&  operator=(const PG_ReactToNotification& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
        =====
        Ports are defined in the following way:
        //#port
        //#attributes(Input|Retain)
        //#name(NameOfPort)
        boolean portField;

        The attributes comment define the port attributes and is optional.
        The name comment defines the name of the port and is optional. Default is the name of the field.
        */
        //#port
        //#attributes(Output)
        uint16 OP_uiInfoValue = 0;

        //#port
        //#attributes(Output)
        uint16 OP_uiWarningValue = 0;

private: // fields
    NotificationExample::COMP_Notifications& cOMP_Notifications;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline PG_ReactToNotification::PG_ReactToNotification(NotificationExample::COMP_Notifications& cOMP_NotificationsArg, const String& name)
: ProgramBase(name)
, cOMP_Notifications(cOMP_NotificationsArg)
{
}

} // end of namespace NotificationExample
