//  
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information.  
//  
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace ProgramComponentInteraction 
{

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class ProgramComponentInteractionLibrary : public MetaLibraryBase, public Singleton<ProgramComponentInteractionLibrary>
{
public: // typedefs
    typedef Singleton<ProgramComponentInteractionLibrary> SingletonBase;

public: // construction/destruction
    ProgramComponentInteractionLibrary(AppDomain& appDomain);
    virtual ~ProgramComponentInteractionLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // methods
    void InitializeTypeDomain();

private: // deleted methods
    ProgramComponentInteractionLibrary(const ProgramComponentInteractionLibrary& arg) = delete;
    ProgramComponentInteractionLibrary& operator= (const ProgramComponentInteractionLibrary& arg) = delete;

private:  // fields
    TypeDomain typeDomain;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramComponentInteractionLibrary

} // end of namespace ProgramComponentInteraction
