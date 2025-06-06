/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 ******************************************************************************/

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Base/Acf/Commons/ComponentBase.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "BufferedExchangeComponentProgramProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

#include "Arp/System/Acf/IControllerComponent.hpp"

#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Commons/Threading/Thread.hpp"

#include "MyWorker.hpp"

namespace BufferedExchange
{

using namespace Arp;
using namespace Arp::Base::Acf::Commons;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::System::Commons::Threading;

//#component
class BufferedExchangeComponent : public ComponentBase, public ProgramComponentBase, public IControllerComponent, private Loggable<BufferedExchangeComponent>
{
public: // typedefs

public: // construction/destruction
    BufferedExchangeComponent(ILibrary& library, const String& name);

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void PowerDown() override;

public: // IControllerComponent
    void Start();
    void Stop();

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods

private: // fields
    BufferedExchangeComponentProgramProvider programProvider;

public:
    MyWorker<long int> wD; // Thread execution environment
    int RunCounter { 0 };
    Thread delegateThread;

public:
    template<typename S>
    void StopWT(MyWorker<S> &W, WorkerThread &T);

    template<typename S>
    void StopT(MyWorker<S> &W, Thread &T);
};

} // end of namespace BufferedExchange
