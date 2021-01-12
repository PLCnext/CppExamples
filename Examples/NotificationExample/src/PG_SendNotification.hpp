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
// 1. Added header files
#include "Arp/System/Nm/NotificationManager.hpp"
#include "ExamplePayload.hpp"


namespace NotificationExample
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

// 2. Added namespace use
using namespace Arp::System::Nm;

//#program
//#component(NotificationExample::COMP_Notifications)
class PG_SendNotification : public ProgramBase, private Loggable<PG_SendNotification>
{
public: // typedefs

public: // construction/destruction
    PG_SendNotification(NotificationExample::COMP_Notifications& cOMP_NotificationsArg, const String& name);
    PG_SendNotification(const PG_SendNotification& arg) = delete;
    virtual ~PG_SendNotification() = default;

public: // operators
    PG_SendNotification&  operator=(const PG_SendNotification& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

private:
    // 3. Needed for the time stamp
    DateTime now() const;

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
            // 4. Added port variables
            //#port
            //#attributes(Input)
            uint16 IP_uiInfoValue = 0;

            //#port
            //#attributes(Input)
            uint16 IP_uiWarningValue = 0;

            // 5. Added local variables to save the previous value of the ports
            uint16 uiPrevInfoValue = 0;
            uint16 uiPrevWarningValue = 0;

            // 6. Manager instance and registrations
            NotificationManager& nm = NotificationManager::GetInstance();
            NonBlockingNotificationRegistration<ExamplePayload> MySenderRegistration1;	// non-blocking needed because of real-time code execution
            NonBlockingNotificationRegistration<ExamplePayload> MySenderRegistration2;

private: // fields
    NotificationExample::COMP_Notifications& cOMP_Notifications;
    DateTime TimeStamp;															// 7. Time stamp
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline PG_SendNotification::PG_SendNotification(NotificationExample::COMP_Notifications& cOMP_NotificationsArg, const String& name)
: ProgramBase(name)
, cOMP_Notifications(cOMP_NotificationsArg)
, MySenderRegistration1("My.NameSpace.1", name, Severity::Info, nm)				// 8. Registrations for the two notifications to be sent
, MySenderRegistration2("My.NameSpace.2", name, Severity::Warning, nm)
{
}

} // end of namespace NotificationExample
