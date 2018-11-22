#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace ThreadExample 
{

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class ThreadExampleLibrary : public MetaLibraryBase, public Singleton<ThreadExampleLibrary>
{
public: // typedefs
    typedef Singleton<ThreadExampleLibrary> SingletonBase;

public: // construction/destruction
    ThreadExampleLibrary(AppDomain& appDomain);
    virtual ~ThreadExampleLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // methods
    void InitializeTypeDomain();

private: // deleted methods
    ThreadExampleLibrary(const ThreadExampleLibrary& arg) = delete;
    ThreadExampleLibrary& operator= (const ThreadExampleLibrary& arg) = delete;

private:  // fields
    TypeDomain typeDomain;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ThreadExampleLibrary

} // end of namespace ThreadExample
