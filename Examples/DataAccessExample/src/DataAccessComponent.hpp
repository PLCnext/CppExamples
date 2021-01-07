﻿///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/Plc/Gds/Services/IDataAccessService.hpp"

namespace DataAccess
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Gds::Services;

/// <summary>
/// ###########################
/// Data Access example
/// ###########################
///
/// In this example the following Data Access methods are demonstrated:
///
/// - ReadSingle
/// - WriteSingle
/// - Read
/// - Write
///
/// Variables of both primitive and complex data types (including structs and arrays) are read and written.
///
/// It is assumed that all operations succeed, so return codes are ignored.
/// </summary>

//#acfcomponent
class DataAccessComponent : public ComponentBase, public MetaComponentBase, private Loggable<DataAccessComponent>
{
public: // typedefs

public: // construction/destruction
    DataAccessComponent(IApplication& application, const String& name);
    virtual ~DataAccessComponent() = default;

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

private: // data access methods
    void StartDataAccess(void);
    void StopDataAccess(void);
    void AccessData(void);

private: // Plc event handlers
    void OnPlcLoaded(void);
    void OnPlcStarted(void);
    void OnPlcStopping(void);
    void OnPlcUnloading(bool onError);
    void OnPlcChanging(void);
    void OnPlcChanged(bool success);

private: // methods
    DataAccessComponent(const DataAccessComponent& arg) = delete;
    DataAccessComponent& operator= (const DataAccessComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    // Service thread that reads and writes data and writes log messages
    WorkerThread                dataAccessThread;
    IDataAccessService::Ptr   dataAccessServicePtr = nullptr;
    int16 Int_IN {0};
    int16 Int_OUT {0};

public: /* Ports
           =====
           Component ports are defined in the following way:

           //#attributes(Hidden)
           struct Ports 
           {
               //#name(NameOfPort)
               //#attributes(Input|Retain|Opc)
               Arp::boolean portField = false;
               // The GDS name is "<componentName>/NameOfPort" if the struct is declared as Hidden
               // otherwise the GDS name is "<componentName>/PORTS.NameOfPort"
           };
           
           //#port
           Ports ports;

           Create one (and only one) instance of this struct.
           Apart from this single struct instance, there must be no other Component variables declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */

};

inline IComponent::Ptr DataAccessComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new DataAccessComponent(application, name));
}

} // end of namespace DataAccess
