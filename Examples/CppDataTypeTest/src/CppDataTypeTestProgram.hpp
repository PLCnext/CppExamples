/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 *  CppDataTypeTestProgram.hpp
 *
 *  Created on: 21.02.2019
 *  	Author: Eduard Münz, Oliver Warneke, Martin Boers
 *
 ******************************************************************************/

/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "CppDataTypeTestComponent.hpp"

namespace CppDataTypeTest
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(CppDataTypeTest::CppDataTypeTestComponent)
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

        boolean outBoolean	=	false;	// BOOL
        uint8	outByte		=	0;	//Byte
        uint16	outWord		=	0;	//Word
        uint32	outDword	=	0;	//DWORD
        uint64	outLword	=	0;	//LWORD

        float32	outFloat32	=	0.0;	//Real
        float64	outFloat64	=	0.0;	//LREAL

        StaticString<80> outString = "";  // String
        StaticWString<80> outWString;  // WString
        // Structs containing custom-length strings  are currently not supported by PLCnext Engineer (version 2020.6).

    };

public: // construction/destruction
    CppDataTypeTestProgram(CppDataTypeTest::CppDataTypeTestComponent& cppDataTypeTestComponentArg, const String& name);
    CppDataTypeTestProgram(const CppDataTypeTestProgram& arg) = delete;
    virtual ~CppDataTypeTestProgram() = default;

public: // operators
    CppDataTypeTestProgram&  operator=(const CppDataTypeTestProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
        =====
        Ports are defined in the following way:
        //#port
        //#attributes(Input|Retain)
        //#name(NameOfPort)
        boolean portField;

        The attributes comment define the port attributes and is optional.
        The name comment defines the name of the port and is optional. Default is the name of the field.
        */



    //#port
    //#attributes(Output|Retain)
    //#name(outBoolean)
    boolean	outBoolean		=	false;	//BOOL

    //#port
    //#attributes(Output|Retain)
    //#name(outInt8)
    int8	outInt8		=	0; 		//SINT

    //#port
    //#attributes(Output|Retain)
    //#name(outUint8)
    uint8	outUint8	=	0;		//USINT

    //#port
    //#attributes(Output|Retain)
    //#name(outInt16)
    int16	outInt16	=	0;		//INT

    //#port
    //#attributes(Output|Retain)
    //#name(outUint16)
    uint16	outUint16	=	0;		//UINT

    //#port
    //#attributes(Output|Retain)
    //#name(outInt32)
    int32	outInt32	=	0;		//DINT

    //#port
    //#attributes(Output|Retain)
    //#name(outUint32)
    uint32	outUint32	=	0;		//UDINT

    //#port
    //#attributes(Output|Retain)
    //#name(outInt64)
    int64 	outInt64	=	0;		//LINT

    //#port
    //#attributes(Output|Retain)
    //#name(outUint64)
    uint64	outUint64	=	0;		//ULINT

    //#port
    //#attributes(Output|Retain)
    //#name(outByte)
    uint8	outByte		=	0;		//Byte

    //#port
    //#attributes(Output|Retain)
    //#name(outWord)
    uint16	outWord		=	0;		//Word

    //#port
    //#attributes(Output|Retain)
    //#name(outDword)
    uint32	outDword	=	0;		//DWORD

    //#port
    //#attributes(Output|Retain)
    //#name(outLword)
    uint64	outLword	=	0;		//LWORD

    //#port
    //#attributes(Output|Retain)
    //#name(outFloat32)
    float32	outFloat32	=	0.0;	//Real

    //#port
    //#attributes(Output|Retain)
    //#name(outFloat64)
    float64	outFloat64	=	0.0;	//LREAL

    //#port
    //#attributes(Output|Retain)
    //#name(outString)
    StaticString<80> outString = "";  // String

    //#port
    //#attributes(Output|Retain)
    //#name(outWString)
    StaticWString<80> outWString;  // WString

    //#port
    //#attributes(Output|Retain)
    //#name(outString420)
    StaticString<420> outString420 = "";  // Custom-length string

    //#port
    //#attributes(Output|Retain)
    //#name(outWString420)
    StaticWString<420> outWString420;  // Custom-length wide string

    //#port
    //#attributes(Output|Retain)
    //#name(outStruct)
    s_alltypes outStruct;

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayBoolean)
    boolean	outarrayBoolean	[10] = {false};	//BOOL

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayInt8)
    int8	outarrayInt8[10] = {0};		//SINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayUint8)
    uint8	outarrayUint8[10] = {0};	//USINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayInt16)
    int16	outarrayInt16[10] = {0};	//INT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayUint16)
    uint16	outarrayUint16[10] = {0};	//UINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayInt32)
    int32	outarrayInt32[10] = {0};	//DINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayUint32)
    uint32	outarrayUint32[10] = {0};	//UDINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayInt64)
    int64 	outarrayInt64[10] = {0};	//LINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayUint64)
    uint64	outarrayUint64[10] = {0};	//ULINT

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayByte)
    uint8	outarrayByte[10] = {0};		//Byte

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayWord)
    uint16	outarrayWord[10] = {0};		//Word

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayDword)
    uint32	outarrayDword[10] = {0};	//DWORD

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayLword)
    uint64	outarrayLword[10] = {0};	//LWORD

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayFloat32)
    float32	outarrayFloat32[10] = {0.0};//Real

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayFloat64)
    float64	outarrayFloat64[10] = {0.0};//LREAL

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayString)
    StaticString<80> outarrayString[10] = {""};  // String

    //#port
    //#attributes(Output|Retain)
    //#name(outarrayWString)
    StaticWString<80> outarrayWString[10];  // WString

    // Array of custom-length strings are currently not supported by PLCnext  Engineer (version 2020.6).

private: // fields
    CppDataTypeTest::CppDataTypeTestComponent& cppDataTypeTestComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline CppDataTypeTestProgram::CppDataTypeTestProgram(CppDataTypeTest::CppDataTypeTestComponent& cppDataTypeTestComponentArg, const String& name)
: ProgramBase(name)
, cppDataTypeTestComponent(cppDataTypeTestComponentArg)
{
}

} // end of namespace CppDataTypeTest
