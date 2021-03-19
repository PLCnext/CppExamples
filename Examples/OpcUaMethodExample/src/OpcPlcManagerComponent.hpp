#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/Plc/Domain/Services/IPlcManagerService2.hpp"

namespace OpcPlcManager
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Domain::Services;

//#acfcomponent
class OpcPlcManagerComponent : public ComponentBase, public MetaComponentBase, private Loggable<OpcPlcManagerComponent>
{
public: // typedefs

public: // construction/destruction
    OpcPlcManagerComponent(IApplication& application, const String& name);
    virtual ~OpcPlcManagerComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void SubscribeServices()override;
    void LoadSettings(const String& settingsPath)override;
    void SetupSettings()override;
    void PublishServices()override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void Dispose()override;
    void PowerDown()override;

public: // MetaComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    OpcPlcManagerComponent(const OpcPlcManagerComponent& arg) = delete;
    OpcPlcManagerComponent& operator= (const OpcPlcManagerComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    WorkerThread workerThreadInstance;
    IPlcManagerService2::Ptr plcManagerService2Ptr = nullptr;

private: // methods
    void workerThreadBody(void);

public: // ports

    // One struct is defined for each OPC UA method
    // Each struct contains the method input and output parameters,
    // and two special UA_* variables.

    struct GET_PLC_STATE
    {
        //#attributes(Input|Opc)
        Arp::int16 UA_MethodState = 0;

        //#attributes(Output|Opc)
        Arp::uint32 state = 0;
        //#attributes(Output|Opc)
        Arp::uint32 UA_StatusCode = 0;
    };

    struct START
    {
        //#attributes(Input|Opc)
        Arp::uint8 startKind = 0;
        //#attributes(Input|Opc)
        Arp::boolean async = false;
        //#attributes(Input|Opc)
        Arp::int16 UA_MethodState = 0;

        //#attributes(Output|Opc)
        Arp::uint32 UA_StatusCode = 0;
    };

    struct STOP
    {
        //#attributes(Input|Opc)
        Arp::boolean async = false;
        //#attributes(Input|Opc)
        Arp::int16 UA_MethodState = 0;

        //#attributes(Output|Opc)
        Arp::uint32 UA_StatusCode = 0;
    };

    // Now the port variables themselves

    //#port
    GET_PLC_STATE GetPlcState;
    //#port
    START Start;
    //#port
    STOP Stop;
};

inline IComponent::Ptr OpcPlcManagerComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new OpcPlcManagerComponent(application, name));
}

} // end of namespace OpcPlcManager
