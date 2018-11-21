#include "CppDataTypeTestLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "CppDataTypeTest/CppDataTypeTestComponent.hpp"

namespace CppDataTypeTest 
{

CppDataTypeTestLibrary::CppDataTypeTestLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<CppDataTypeTestLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::CppDataTypeTest::CppDataTypeTestComponent>(), &::CppDataTypeTest::CppDataTypeTestComponent::Create);
    this->InitializeTypeDomain();
}

void CppDataTypeTestLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    CppDataTypeTestLibrary::Main(appDomain);
    return  CppDataTypeTestLibrary::GetInstance();
}

} // end of namespace CppDataTypeTest
