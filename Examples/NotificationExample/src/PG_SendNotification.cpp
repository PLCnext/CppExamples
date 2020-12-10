///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////

#include "PG_SendNotification.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace NotificationExample
{
// Get Time for time stamp
Arp::DateTime PG_SendNotification::now() const
{
	return DateTime::FromUnixTimeMicroseconds(std::chrono::duration_cast<std::chrono::microseconds>
											 (std::chrono::system_clock::now().time_since_epoch()).count());
}


void PG_SendNotification::Execute()
{
		// Date time stamp in each cycle
		TimeStamp = now();
		// Compare port value of "IP_uiInfoValue" with previous value to detect a change
		if(IP_uiInfoValue != uiPrevInfoValue)
		{
			MySenderRegistration1.SendNotificationWithTimestamp(TimeStamp, ExamplePayload{IP_uiInfoValue,"This is a placeholder message" });
			uiPrevInfoValue = IP_uiInfoValue;
		}

		// Compare port value of "IP_uiWarningValue" with previous value to detect a change
		if(IP_uiWarningValue != uiPrevWarningValue)
		{
            String aStringVariable = "What happens when I pass in a String Variable";
			MySenderRegistration2.SendNotificationWithTimestamp(TimeStamp, ExamplePayload{IP_uiWarningValue, aStringVariable});
            aStringVariable = "And now I do change the String content.";
            aStringVariable = "And now I do change the String but make it way way way Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooonger";
            MySenderRegistration2.SendNotificationWithTimestamp(TimeStamp, ExamplePayload{IP_uiWarningValue, aStringVariable});
			uiPrevWarningValue = IP_uiWarningValue;
		}

}

} // end of namespace NotificationExample
