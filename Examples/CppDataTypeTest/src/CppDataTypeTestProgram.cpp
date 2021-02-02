/******************************************************************************
 * 
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
 *
 *  CppDataTypeTestProgram.cpp
 *
 *  Created on: 21.02.2019
 *  	Author: Eduard Münz, Oliver Warneke, Martin Boers
 *
 ******************************************************************************/

/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/

#include "CppDataTypeTestProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace CppDataTypeTest
{

void CppDataTypeTestProgram::Execute()
{
    //implement program 
    
    if(outBoolean == true)
            outBoolean = false;
        else
            outBoolean = true;

    outInt8++; 	//SINT
    outUint8++;	//USINT
    outStruct.outInt8++; //StructElement
    outStruct.outUint8++; //StructElement

    outInt16++;	//INT
    outUint16++;//UINT
    outStruct.outInt16++; //StructElement
    outStruct.outUint16++; //StructElement

    outInt32++;	//DINT
    outUint32++;//UDINT
    outStruct.outInt32++; //StructElement
    outStruct.outUint32++; //StructElement

    outInt64++;	//LINT
    outUint64++;//ULINT
    outStruct.outInt64++; //StructElement
    outStruct.outUint64++; //StructElement

    outFloat32++;//REAL
    outFloat64++;//LREAL
    outStruct.outFloat32++; //StructElement
    outStruct.outFloat64++; //StructElement

    outByte++;	//Byte
    outWord++;	//Word
    outDword++;	//DWORD
    outLword++;	//Lword
    outStruct.outByte++; //StructElement
    outStruct.outWord++; //StructElement
    outStruct.outDword++; //StructElement
    outStruct.outLword++; //StructElement

    outString = "This is a standard IEC 61131 string (max. 80 char).";
    outString420 = "This is a custom length string - in this case, with a maximum of 420 chars, but can be up to 32766 chars.";
    outStruct.outString = "This is a standard IEC 61131 string (max. 80 char).";  //StructElement

    for(int i=0; i < 10;i++)
    {
        if(outarrayBoolean[i] == true)
            outarrayBoolean[i] = false;
        else
            outarrayBoolean[i] = true;

        outarrayInt8[i]++; 	//SINT
        outarrayUint8[i]++;	//USINT

        outarrayInt16[i]++;	//INT
        outarrayUint16[i]++;//UINT

        outarrayInt32[i]++;	//DINT
        outarrayUint32[i]++;//UDINT

        outarrayInt64[i]++;	//LINT
        outarrayUint64[i]++;//ULINT

        outarrayFloat32[i]++;//REAL
        outarrayFloat64[i]++;//LREAL

        outarrayByte[i]++;	//Byte
        outarrayWord[i]++;	//Word
        outarrayDword[i]++;	//DWORD
        outarrayLword[i]++;	//Lword

        outarrayString[i] = "This is a standard IEC 61131 string (max. 80 chars).";
    }
}

} // end of namespace CppDataTypeTest
