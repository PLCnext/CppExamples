// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
// Licensed under the MIT. See LICENSE file in the project root for full license information. 

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/Plc/Commons/PlcTypes.h"
#include "Arp/Plc/Commons/Gds/StaticString.hxx"

namespace CppDataTypeTest 
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//TODO not neccessary here. Include header instead
//forwards
class CppDataTypeTestComponent;

//#component(CppDataTypeTestComponent)
class CppDataTypeTestProgram : public ProgramBase, private Loggable<CppDataTypeTestProgram>
{
public: // typedefs

struct s_alltypes{

	int8	outInt8		=	0; 	//SINT
	uint8	outUint8	=	0;	//USINT

	int16	outInt16	=	0;	//INT
	uint16	outUint16	=	0;	//UINT

	int32	outInt32	=	0;	//DINT
	uint32	outUint32	=	0;	//UDINT

	int64 	outInt64	=	0;	//LINT
	uint64	outUint64	=	0;	//ULINT

	//boolean outBoolean	=	false;	// BOOL
	uint8	outByte		=	0;	//Byte
	uint16	outWord		=	0;	//Word
	uint32	outDword	=	0;	//DWORD
	uint64	outLword	=	0;	//LWORD

	float32	outFloat32	=	0;	//Real
	float64	outFloat64	=	0;	//LREAL

 	//StaticString<80> outString = "Test StructString";		//STRING
};

public: // construction/destruction
    CppDataTypeTestProgram(CppDataTypeTestComponent& refCppDataTypeTestComponentArg, const String& name);
    CppDataTypeTestProgram(const CppDataTypeTestProgram& arg) = delete;
    virtual ~CppDataTypeTestProgram() = default;

public: // operators
    CppDataTypeTestProgram&  operator=(const CppDataTypeTestProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: // ports

    //ARP-type Variablename = 	Init.	//corresponding PCWorxDatatype
	//#port(Output)
	boolean	outBoolean		=	false;	//BOOL

	//StaticString<80> outStaticString;		//STRING
	//StaticString<80> inStaticString;		//STRING

	//#port(Output)
	int8	outInt8		=	0; 		//SINT
	//#port(Output)
	uint8	outUint8	=	0;		//USINT

	//#port(Output)
	int16	outInt16	=	0;		//INT
	//#port(Output)
	uint16	outUint16	=	0;		//UINT

	//#port(Output)
	int32	outInt32	=	0;		//DINT
	//#port(Output)
	uint32	outUint32	=	0;		//UDINT

	//#port(Output)
	int64 	outInt64	=	0;		//LINT
	//#port(Output)
	uint64	outUint64	=	0;		//ULINT

	//#port(Output)
	uint8	outByte		=	0;		//Byte
	//#port(Output)
	uint16	outWord		=	0;		//Word
	//#port(Output)
	uint32	outDword	=	0;		//DWORD
	//#port(Output)
	uint64	outLword	=	0;		//LWORD

	//#port(Output)
	float32	outFloat32	=	0;		//Real
	//#port(Output)
	float64	outFloat64	=	0;		//LREAL

	//#port(Output)
	s_alltypes outStruct;

	//#port(Output)
    boolean	outarrayBoolean	[10]={false};	//BOOL
    //#port(Output)
 	int8	outarrayInt8[10]={0};	//SINT
 	//#port(Output)
 	uint8	outarrayUint8[10]={0};	//USINT

 	//#port(Output)
 	int16	outarrayInt16[10]={0};	//INT
 	//#port(Output)
 	uint16	outarrayUint16[10]={0};	//UINT

 	//#port(Output)
 	int32	outarrayInt32[10]={0};	//DINT
 	//#port(Output)
 	uint32	outarrayUint32[10]={0};	//UDINT

 	//#port(Output)
 	int64 	outarrayInt64[10]={0};	//LINT
 	//#port(Output)
 	uint64	outarrayUint64[10]={0};	//ULINT

 	//#port(Output)
 	uint8	outarrayByte[10]={0};	//Byte
 	//#port(Output)
 	uint16	outarrayWord[10]={0};	//Word
 	//#port(Output)
 	uint32	outarrayDword[10]={0};	//DWORD
 	//#port(Output)
 	uint64	outarrayLword[10]={0};	//LWORD

 	//#port(Output)
 	float32	outarrayFloat32[10]={0.0};//Real
 	//#port(Output)
 	float64	outarrayFloat64[10]={0.0};//LREAL

private: // fields
	CppDataTypeTestComponent& refCppDataTypeTestComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline CppDataTypeTestProgram::CppDataTypeTestProgram(CppDataTypeTestComponent& refCppDataTypeTestComponentArg, const String& name)
: ProgramBase(name)
, refCppDataTypeTestComponent(refCppDataTypeTestComponentArg)
{
}

} // end of namespace CppDataTypeTest
