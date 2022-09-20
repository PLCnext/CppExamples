#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "BufferedExchangeComponentProgramProvider.hpp"

#include "Arp/System/Acf/IControllerComponent.hpp"

#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Commons/Threading/Thread.hpp"

#include "MyWorker.hpp"

namespace BufferedExchange {

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//#component
class BufferedExchangeComponent: public ComponentBase,
        public ProgramComponentBase,
        public IControllerComponent,
        private Loggable<BufferedExchangeComponent> {
public: // typedefs

public: // construction/destruction
    BufferedExchangeComponent(IApplication &application, const String &name);
    virtual ~BufferedExchangeComponent() = default;

public: // Component operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // IControllerComponent
    void Start();
    void Stop();

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    BufferedExchangeComponent(const BufferedExchangeComponent &arg) = delete;
    BufferedExchangeComponent& operator=(const BufferedExchangeComponent &arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication &application,
            const String &name);

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

inline IComponent::Ptr BufferedExchangeComponent::Create(Arp::System::Acf::IApplication &application, const String &name) {
    return IComponent::Ptr(new BufferedExchangeComponent(application, name));
}

} // end of namespace BufferedExchange
