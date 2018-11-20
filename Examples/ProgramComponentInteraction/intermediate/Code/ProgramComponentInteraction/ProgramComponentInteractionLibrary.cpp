//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#include "ProgramComponentInteractionLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "CounterComponent.hpp"

namespace ProgramComponentInteraction 
{

ProgramComponentInteractionLibrary::ProgramComponentInteractionLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<ProgramComponentInteractionLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::ProgramComponentInteraction::CounterComponent>(), &::ProgramComponentInteraction::CounterComponent::Create);
    this->InitializeTypeDomain();
}

void ProgramComponentInteractionLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    ProgramComponentInteractionLibrary::Main(appDomain);
    return  ProgramComponentInteractionLibrary::GetInstance();
}

} // end of namespace ProgramComponentInteraction
