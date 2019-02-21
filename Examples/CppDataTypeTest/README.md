# Table of contents

<!-- TOC depthFrom:1 orderedList:true -->

1. [Table of contents](#table-of-contents)
2. [Introduction](## Introduction)
3. [Example details](## Example details)
4. [Preconditions](## Preconditions)
5. [Project compiling in Eclipse](## Project compiling in Eclipse)
6. [PLCnext Engineer project](## PLCnext Engineer project)
7. [Start-Up instructions](#start-up-instructions)
8. [Cpp SourceCode](## Cpp SourceCode)
 8.1. [](### )
 8.2. [](### )

<!-- /TOC -->


## Introduction

This example demonstrates the creating and using of port variables in PLCnext Enginner and C++ application for data exchange via elementary data types.
All supported elementary data types are documented in the user manual "PLCnext Technology".

## Example details

|Description | Value |
|------------ |-----------|
|Controller| AXC F 2152 | 
|FW | 2019.0|
|SDK | 2019.0|
|PLCnext Engineer| 2019.0 | 


## Preconditions

- AXC F 2152 controller with firmware 2019.0
- Eclipse IDE "Photon" 
- PLCnext Engineer 2019.0


## Project compiling in Eclipse

1. Create in Eclipse the project "CppDataTypeTest" with Component "CppDataTypeTestComponent" and Program "CppDataTypeTestProgram".
2. Replace in the project the files "CppDataTypeTestProgram.cpp" and "CppDataTypeTestProgram.hpp" with files from this repository. Alternatively you can create your own project with component and programs and include the source code of "CppDataTypeTestProgram.cpp" and "CppDataTypeTestProgram.hpp" in your source code files.
3. Compile the Eclipse project. 
4. After successfull project compilation, the PLCnext Engineer library will be created automatically. You can find it under eclipse workspace folder: e.g.: "workspace\CppDataTypeTest\bin\CppDataTypeTest.pcwlx" 


## PLCnext Engineer project 

1. Create in PLCnext Engineer a new project and include the "CppDataTypeTest.pcwlx" in the project.
2. Instantiate the Program "CppDataTypeTestProgram" under previously defined task.
3. Create in the "COMPONENT" Area under Programming -> Datatypes an new datatype-worksheet and include the following user defined datatypes:

```cpp
		TYPE
			s_alltypes : STRUCT
			
				outInt8: SINT;
				outUint8:USINT;
				
				outInt16:Int;
				outUint16:UInt;
			   
				outInt32:DInt;
				outUint32:UDInt;
				
				outInt64:LInt;
				outUint64:ULInt;
				
				outBoolean:Bool;
				outByte:Byte;
				outWord:Word;
				outDword:Dword;
				outLword:LWord;
				
				outFloat32:Real;
				outFloat64:LREAL;
			 END_STRUCT

		PLCnEng_STRING_80:STRING[80];
			
		bool_array: ARRAY[0..9] OF BOOL;  
		//8Bit
		sint_array: ARRAY[0..9] OF SINT;  
		usint_array: ARRAY[0..9] OF USINT;  
		//16Bit
		int_array: ARRAY[0..9] OF INT;  
		uint_array: ARRAY[0..9] OF UINT;  
		//32Bit
		dint_array: ARRAY[0..9] OF DINT;  
		udint_array: ARRAY[0..9] OF UDINT;  
		//64Bit
		lint_array: ARRAY[0..9] OF LINT;  
		ulint_array: ARRAY[0..9] OF ULINT;  
		//8Bit
		byte_array: ARRAY[0..9] OF BYTE;  
		//16Bit
		word_array: ARRAY[0..9] OF WORD;  
		//32Bit
		doubleword_array: ARRAY[0..9] OF DWORD;  
		//64Bit
		Lword_array: ARRAY[0..9] OF LWORD;  
		//xx digit precision
		real_array: ARRAY[0..9] OF REAL;  
		//xx digit precision
		Lreal_array: ARRAY[0..9] OF LREAL;  
		END_TYPE
```
4. Declare the portvariables of user defined and elementary datatypes e.g. in "main" program. Please find the table of elementary datatypes in user manual "PLCnext Technology".
5. Connect the C++ Prortvariables and IEC61131 Portvariables in PLCnext Engineer under "PLCnext"-Node in tne "PLANT" area.
6. Download the PLCnext Engineer project to the plcnext controller.


## Start-Up instructions

- If the project is successfully implemented and downloaded, you can follow the data exchange in PLCnext Engineer debug mode and/or in watch-window. 
- If the project is not started successfully, please see the error messages in Output.log File on the plcnext target e.g. /opt/plcnext/logs/Output.log

## Cpp SourceCode

### CppDataTypeTestProgram.hpp

```cpp
		/******************************************************************************
		 * 
		 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
		 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
		 *
		 *  CppDataTypeTestProgram.hpp
		 *
		 *  Created on: 21.02.2019
		 *  	Author: Eduard Münz, Oliver Warneke
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

```



### CppDataTypeTestProgram.cpp
```cpp
		/******************************************************************************
		 * 
		 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.  
		 * Licensed under the MIT. See LICENSE file in the project root for full license information.  
		 *
		 *  CppDataTypeTestProgram.cpp
		 *
		 *  Created on: 21.02.2019
		 *  	Author: Eduard Münz, Oliver Warneke
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
			}
		}

		} // end of namespace CppDataTypeTest
```