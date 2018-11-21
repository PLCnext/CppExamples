#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace CppDataTypeTest 
{

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class CppDataTypeTestLibrary : public MetaLibraryBase, public Singleton<CppDataTypeTestLibrary>
{
public: // typedefs
    typedef Singleton<CppDataTypeTestLibrary> SingletonBase;

public: // construction/destruction
    CppDataTypeTestLibrary(AppDomain& appDomain);
    virtual ~CppDataTypeTestLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // methods
    void InitializeTypeDomain();

private: // deleted methods
    CppDataTypeTestLibrary(const CppDataTypeTestLibrary& arg) = delete;
    CppDataTypeTestLibrary& operator= (const CppDataTypeTestLibrary& arg) = delete;

private:  // fields
    TypeDomain typeDomain;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CppDataTypeTestLibrary

} // end of namespace CppDataTypeTest
