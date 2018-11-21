#include "TemplateLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "TemplateComponent.hpp"

namespace Template 
{

TemplateLibrary::TemplateLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<TemplateLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::Template::TemplateComponent>(), &::Template::TemplateComponent::Create);
    this->InitializeTypeDomain();
}

void TemplateLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    TemplateLibrary::Main(appDomain);
    return  TemplateLibrary::GetInstance();
}

} // end of namespace Template
