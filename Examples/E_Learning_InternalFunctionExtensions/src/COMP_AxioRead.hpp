#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "LIB_AxioReadLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"

//added header
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/Io/Axioline/Services/IAcyclicCommunicationService.hpp"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"

namespace LIB_AxioRead
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;

using namespace Arp::System::Rsc;
using namespace Arp::Io::Axioline::Services;
using namespace Arp::System::Commons::Threading;

//#acfcomponent
class COMP_AxioRead : public ComponentBase, public MetaComponentBase, private Loggable<COMP_AxioRead>
{

public: // typedefs

public: // construction/destruction
	COMP_AxioRead(IApplication& application, const String& name);
	virtual ~COMP_AxioRead() = default;

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
	COMP_AxioRead(const COMP_AxioRead& arg) = delete;
	COMP_AxioRead& operator= (const COMP_AxioRead& arg) = delete;

public: // static factory operations
	static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private:
	IAcyclicCommunicationService::Ptr pAcyclicCommunicationService;

public: // declarations
	FILE * pConfigFile{};

	struct stConfigParam { // structure definition
	uint16 Index = 0;
	uint8 Subindex = 0;
	bool DisplayAsText = false;
	};

	stConfigParam arConfigs[100]; // limit array size to 100 elements
	int n = 0; // counter of configurations (data sets)

	WorkerThread WorkerThreadInstance;
	void WorkerThreadBody(void);


	PdiParam paramProcessData; // definition of the PDI parameter variable

	PdiParam param; // PDI parameters defined by switch status and JSON file

	uint8 switchFlag = 0; // flag to detect change of switch status

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class COMP_AxioRead
inline COMP_AxioRead::COMP_AxioRead(IApplication& application, const String& name)
: ComponentBase(application, ::LIB_AxioRead::LIB_AxioReadLibrary::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::LIB_AxioRead::LIB_AxioReadLibrary::GetInstance().GetNamespace())
// thread with the name Thread_1, called each 10 seconds
, WorkerThreadInstance(make_delegate(this, &COMP_AxioRead::WorkerThreadBody), 100, "Thread_1") {
}

inline IComponent::Ptr COMP_AxioRead::Create(Arp::System::Acf::IApplication& application, const String& name)
{
	return IComponent::Ptr(new COMP_AxioRead(application, name));
}

inline void COMP_AxioRead::RegisterComponentPorts(){}

} // end of namespace LIB_AxioRead
