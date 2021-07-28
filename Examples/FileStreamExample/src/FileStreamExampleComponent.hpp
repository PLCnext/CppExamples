#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "FileStreamExampleComponentProgramProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

namespace FileStreamExample {

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//#component
class FileStreamExampleComponent: public ComponentBase,
		public ProgramComponentBase,
		private Loggable<FileStreamExampleComponent> {
public: // typedefs

public: // construction/destruction
	FileStreamExampleComponent(IApplication &application, const String &name);
	virtual ~FileStreamExampleComponent() = default;

public: // IComponent operations
	void Initialize() override;
	void LoadConfig() override;
	void SetupConfig() override;
	void ResetConfig() override;

public: // ProgramComponentBase operations
	void RegisterComponentPorts() override;

private: // methods
	FileStreamExampleComponent(const FileStreamExampleComponent &arg) = delete;
	FileStreamExampleComponent& operator=(const FileStreamExampleComponent &arg) = delete;

	void WriteToFile(String textToWrite);
	String ReadFromFile();

public: // static factory operations
	static IComponent::Ptr Create(Arp::System::Acf::IApplication &application,
			const String &name);

private: // fields
	FileStreamExampleComponentProgramProvider programProvider;
	const Arp::String filePath = "/opt/plcnext/logs/TestFile.txt";
	bool newbin{false};
	bool nofile{false};
public:
	boolean bReset { false };
};

inline IComponent::Ptr FileStreamExampleComponent::Create(Arp::System::Acf::IApplication &application, const String &name) {
	return IComponent::Ptr(new FileStreamExampleComponent(application, name));
}

} // end of namespace FileStreamExample
