///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT GmbH
//
///////////////////////////////////////////////////////////////////////////////

/*
 * ExamplePayload.hpp
 *
 *  Created on: 07.05.2019
 *
 */

#ifndef EXAMPLEPAYLOAD_HPP_
#define EXAMPLEPAYLOAD_HPP_

#pragma once
// 1. Include header "SpecializedPayload.hpp"
#include "Arp/System/Nm/SpecializedPayload.hpp"

// 2. Use project namespace
namespace NotificationExample{
// 3. Use Arp namespace
using namespace Arp;
//    and namespace of the notification manager
using namespace Arp::System::Nm;
// 4. Define payload
class ExamplePayload : public SpecializedPayload<ExamplePayload>
{
    public:
    // definition of the payload values
    ExamplePayload(const uint16& uiPortValue, const String & sMyMessage)
    : SpecializedPayload("The value is: {0}")                               // definition of the payload string
    {
        this->SetFieldValue(this->fieldIndexMyValue, uiPortValue);         // relation variable value to index
        this->SetFieldValue(this->fieldIndexMyString, sMyMessage);         // relation variable value to index
    }

    ExamplePayload(const Notification& notification)
            : SpecializedPayload(notification)
    {
    }
    // 5. Method for receiving the notification
    const uint16 GetMyValue() const
    {
    return this->GetFieldValueAs<uint16>( this->fieldIndexMyValue);
    }

    const String GetMyString() const
    {
    return this->GetFieldValueAs<String>( this->fieldIndexMyString);
    }

    private:
    // 6. Define field index
    size_t fieldIndexMyValue = this->AddField<uint16>();
    size_t fieldIndexMyString = this->AddField<String>();

};

} // end of namespace

#endif /* EXAMPLEPAYLOAD_HPP_ */
