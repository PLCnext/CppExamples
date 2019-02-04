#include "CppDataTypeTestComponent.hpp"

namespace CppDataTypeTest 
{

void CppDataTypeTestComponent::Initialize()
{
}

void CppDataTypeTestComponent::LoadSettings(const String& settingsPath)
{
}

void CppDataTypeTestComponent::SetupSettings()
{
}

void CppDataTypeTestComponent::SubscribeServices()
{
}

void CppDataTypeTestComponent::LoadConfig()
{
}

void CppDataTypeTestComponent::SetupConfig()
{
    // DO NOT REMOVE THIS!
    CppDataTypeTestComponent::RegisterComponentPorts();
}

void CppDataTypeTestComponent::ResetConfig()
{
	 this->dataInfoProvider.Reset();
}

void CppDataTypeTestComponent::PublishServices()
{
}

void CppDataTypeTestComponent::Dispose()
{
}

void CppDataTypeTestComponent::PowerDown()
{
}

} // end of namespace CppDataTypeTest
