#include "ThreadExampleLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "ThreadExample/ThreadExampleComponent.hpp"

namespace ThreadExample 
{

ThreadExampleLibrary::ThreadExampleLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<ThreadExampleLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::ThreadExample::ThreadExampleComponent>(), &::ThreadExample::ThreadExampleComponent::Create);
    this->InitializeTypeDomain();
}

void ThreadExampleLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    ThreadExampleLibrary::Main(appDomain);
    return  ThreadExampleLibrary::GetInstance();
}

} // end of namespace ThreadExample
