/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Base/Acf/Commons/ComponentBase.hpp"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/Plc/Domain/Services/IPlcManagerService2.hpp"

namespace OpcPlcManager
{
using namespace Arp::Base::Acf::Commons;
using namespace Arp;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Domain::Services;
using namespace Arp::System::Commons::Threading;

//#acfcomponent
class OpcPlcManagerComponent : public ComponentBase, public MetaComponentBase, private Loggable<OpcPlcManagerComponent>
{
public: // construction/destruction
    OpcPlcManagerComponent(ILibrary& library, const String& name);

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

} // end of namespace OpcPlcManager
