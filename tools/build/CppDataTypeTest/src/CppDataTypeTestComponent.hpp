#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CppDataTypeTestComponentProgramProvider.hpp"
#include "CppDataTypeTestLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

namespace CppDataTypeTest
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//#component
class CppDataTypeTestComponent : public ComponentBase, public ProgramComponentBase, private Loggable<CppDataTypeTestComponent>
{
public: // typedefs

public: // construction/destruction
    CppDataTypeTestComponent(IApplication& application, const String& name);
    virtual ~CppDataTypeTestComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    CppDataTypeTestComponent(const CppDataTypeTestComponent& arg) = delete;
    CppDataTypeTestComponent& operator= (const CppDataTypeTestComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    CppDataTypeTestComponentProgramProvider programProvider;

public: /* Ports
           =====
           Component ports are defined in the following way:
           //#port
           //#name(NameOfPort)
           boolean portField;

           The name comment defines the name of the port and is optional. Default is the name of the field.
           Attributes which are defined for a component port are IGNORED. If component ports with attributes
           are necessary, define a single structure port where attributes can be defined foreach field of the
           structure.
        */
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CppDataTypeTestComponent
inline CppDataTypeTestComponent::CppDataTypeTestComponent(IApplication& application, const String& name)
: ComponentBase(application, ::CppDataTypeTest::CppDataTypeTestLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::CppDataTypeTest::CppDataTypeTestLibrary::GetInstance().GetNamespace(), programProvider)
{
}

inline IComponent::Ptr CppDataTypeTestComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new CppDataTypeTestComponent(application, name));
}

} // end of namespace CppDataTypeTest
