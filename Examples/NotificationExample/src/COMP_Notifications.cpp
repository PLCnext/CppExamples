#include "COMP_Notifications.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"

namespace NotificationExample
{

void COMP_Notifications::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();
        log.Info("Notifications:");
    for (auto &x : nm.GetAllKnownNotificationNameIds()){
    log.Info("Name:{1} Value:{0}",x.GetValue(), nm.GetNotificationName(x));

    }
    // subscribe events from the event system (Nm) here
    this->Custom_subscription.OnNotification += make_delegate(this, &COMP_Notifications::NM_Subscription1_Callback);
	this->Custom_subscription2.OnNotification += make_delegate(this, &COMP_Notifications::NM_Subscription2_Callback);
    this->NetworkConfigurationChanged_subscription.OnNotification += make_delegate(this, &COMP_Notifications::NetworkConfigurationChanged_Callback);
    this->PlcStateChanged_subscription.OnNotification += make_delegate(this, &COMP_Notifications::PlcStateChanged_Callback);
}

void COMP_Notifications::LoadConfig()
{
    // load project config here
}

void COMP_Notifications::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void COMP_Notifications::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}
// Receive first self-defined notification
void COMP_Notifications::NM_Subscription1_Callback(const Arp::System::Nm::Notification& notification)
{
    //
    auto payload = notification.GetPayloadAs<ExamplePayload>();
    OP_uiValue1  = payload.GetMyValue();
    auto MyString = payload.GetMyString();
    log.Info( "1 MyValue:{0} MyString{1}",OP_uiValue1,MyString );
}

// Receive second notification
void COMP_Notifications::NM_Subscription2_Callback(const Arp::System::Nm::Notification& notification)
{
    // within the "ExamplePayload" string
    auto payload = notification.GetPayloadAs<ExamplePayload>();
    OP_uiValue2  = payload.GetMyValue();
    auto MyString = payload.GetMyString();
    log.Info( "2 MyValue:{0} MyString{1}",OP_uiValue2,MyString );
}

// Receive Network Configuration Changes.
void COMP_Notifications::NetworkConfigurationChanged_Callback(const Arp::System::Nm::Notification& notification)
{
auto payload = notification.GetPayloadAs<Arp::System::NmPayload::Device::NetworkConfigurationChangedPayload>();

//Configuration of network interface {num­ber} changed: {Parameter} = {Value}
auto parameter = payload.GetChangedParameter();
auto deviceId = payload.GetDeviceId();
auto id = payload.GetId();
auto name = payload.GetName();
auto value = payload.GetValued();
log.Info("Parameter:{0},devieId:{1},id:{2},name:{3},value:{4}",parameter,deviceId,id,name,value);
}

// This notification informs you about the latest PLC Status changes.
// And allows you to react accordingly.
void COMP_Notifications::PlcStateChanged_Callback(const Arp::System::Nm::Notification& notification)
{
//Plc state changed: {"None"|"Ready"|"Stop"|"Running"|"Halt"|"Changing","Warning"|"Er­ror"|"SuspendedBySwitch"|"DcgNotPossi­ble"|"DcgRealTimeViolation"}
//               ==> {"None"|"Ready"|"Stop"|"Running"|"Halt"|"Changing","Warning"|"Er­ror"|"SuspendedBySwitch"|"DcgNotPossi­ble"|"DcgRealTimeViolation"}
	auto payload = notification.GetPayloadAs<Arp::System::NmPayload::Plc::PlcStateChangedPayload>();
    Arp::Plc::Commons::Domain::PlcState NewState = payload.GetNewState();
    Arp::Plc::Commons::Domain::PlcState LastState = payload.GetLastState();

    log.Info("Component noticed a PLC State change from '{0}' to  '{1}' ." ,LastState , NewState);

    switch( NewState )
    {
        case  Arp::Plc::Commons::Domain::PlcState::Stop:
            log.Info( "Handling Stop State" );
        break;

        case  Arp::Plc::Commons::Domain::PlcState::Running:
            if(LastState ==  Arp::Plc::Commons::Domain::PlcState::Halt){
             log.Info( "Continue doing Something" );
             }

            if(LastState ==  Arp::Plc::Commons::Domain::PlcState::Stop){
             log.Info( "Reinitialise Something");
             }
        break;

        case  Arp::Plc::Commons::Domain::PlcState::Halt:
            log.Info( "Handling Halt State" );
            log.Info( "Stop execution store next free commands be prepared to continue.");
        break;

        case  Arp::Plc::Commons::Domain::PlcState::Changing:
        break;

        case  Arp::Plc::Commons::Domain::PlcState::Warning:

        break;

        case  Arp::Plc::Commons::Domain::PlcState::Error:
        break;

        case  Arp::Plc::Commons::Domain::PlcState::SuspendedBySwitch:
        break;
        default:
         log.Info( "Handling Halt State:{0} LastState:{1}", NewState,LastState );
        break;

    }

}

}
