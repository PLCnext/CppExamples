#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/IProgramComponent.hpp"
#include "Arp/Plc/Commons/Meta/IMetaComponent.hpp"
#include "Arp/Plc/Commons/Meta/DataInfoProvider.hpp"
#include "ThreadExample/ThreadExampleComponentProgramProvider.hpp"
#include "ThreadExample/ThreadExampleLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"


// Added Stuff
#include "Arp/System/Acf/IControllerComponent.hpp"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Commons/Threading/Thread.hpp"
#include "Arp/System/Commons/Threading/ThreadSettings.hpp"

namespace ThreadExample 
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

class ThreadExampleComponent
		: public ComponentBase
		, public IControllerComponent
		, public IProgramComponent
		, public IMetaComponent
		, private Loggable<ThreadExampleComponent>
{
public: // typedefs

public: // construction/destruction
    ThreadExampleComponent(IApplication& application, const String& name);
    virtual ~ThreadExampleComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadSettings(const String& settingsPath) override;
    void SetupSettings() override;
    void SubscribeServices() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void PublishServices() override;
    void Dispose() override;
    void PowerDown() override;

public: // IControllerComponent operations
    void Start(void)override;
    void Stop(void)override;

private: // ThreadExampleComponent.meta.cpp
    void RegisterComponentPorts();

private: // methods
    ThreadExampleComponent(const ThreadExampleComponent& arg) = delete;
    ThreadExampleComponent& operator= (const ThreadExampleComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& componentName);

public: // IProgramComponent operations
    IProgramProvider & GetProgramProvider(bool useBackgroundDomain) override;

public: // IMetaComponent operations
    IDataInfoProvider & GetDataInfoProvider(bool isChanging) override;
    IDataNavigator*     GetDataNavigator() override;

private: // fields
    ThreadExampleComponentProgramProvider programProvider;
    DataInfoProvider    dataInfoProvider;


    // Worker Thread Example
          WorkerThread workerThreadInstance;
          int x{0};
          int y{1000};
          bool stopTheThread;
          void workerThreadBody(void);

          //Commons/Thread Example
          Thread delegateThreadInstance;
          Thread staticThreadInstance;
          void delegateThreadBody(void * pParameter);

          int myparameter{123};
          static void staticThreadBody(void* pParameter);


public: // ports
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ThreadExampleComponent
inline ThreadExampleComponent::ThreadExampleComponent(IApplication& application, const String& name)
: ComponentBase(application, ::ThreadExample::ThreadExampleLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, dataInfoProvider(::ThreadExample::ThreadExampleLibrary::GetInstance().GetNamespace(), &(this->programProvider))

//// Worker Thread Example
, workerThreadInstance(make_delegate(this, &ThreadExampleComponent::workerThreadBody) , 10000, "WorkerThread1")

//Commons/Thread Example
, delegateThreadInstance(this,&ThreadExampleComponent::delegateThreadBody,(void*)myparameter)
, staticThreadInstance(&ThreadExampleComponent::staticThreadBody,(void*)stopTheThread)
{
}

#pragma region IProgramComponent implementation

inline IProgramProvider& ThreadExampleComponent::GetProgramProvider(bool /*useBackgroundDomain*/)
{
    return this->programProvider;
}

#pragma endregion

#pragma region IMetaComponent implementation

inline IDataInfoProvider& ThreadExampleComponent::GetDataInfoProvider(bool /*useBackgroundDomain*/)
{
    return this->dataInfoProvider;
}

inline IDataNavigator* ThreadExampleComponent::GetDataNavigator()
{
    return nullptr;
}

#pragma endregion

inline IComponent::Ptr ThreadExampleComponent::Create(Arp::System::Acf::IApplication& application, const String& componentName)
{
    return IComponent::Ptr(new ThreadExampleComponent(application, componentName));
}

} // end of namespace ThreadExample
