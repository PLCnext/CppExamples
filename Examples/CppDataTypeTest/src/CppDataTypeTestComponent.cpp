#include "CppDataTypeTestComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CppDataTypeTestLibrary.hpp"
namespace CppDataTypeTest
{

CppDataTypeTestComponent::CppDataTypeTestComponent(IApplication& application, const String& name)
: ComponentBase(application, ::CppDataTypeTest::CppDataTypeTestLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::CppDataTypeTest::CppDataTypeTestLibrary::GetInstance().GetNamespace(), programProvider)
{
}
void CppDataTypeTestComponent::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void CppDataTypeTestComponent::LoadConfig()
{
    // load project config here
}

void CppDataTypeTestComponent::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void CppDataTypeTestComponent::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

} // end of namespace CppDataTypeTest
