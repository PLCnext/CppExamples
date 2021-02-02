# Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

1. [Introduction](#introduction)
2. [Example details](#example-details)
3. [Preconditions](#preconditions)
4. [Project compiling in Eclipse](#project-compiling-in-eclipse)
5. [PLCnext Engineer project](#plcnext-engineer-project)
6. [Start-Up instructions](#start-up-instructions)
7. [Cpp Source Code](#cpp-source-code)  
7.1. [CppDataTypeTestProgram.hpp](#cppdatatypetestprogramhpp)  
7.2. [CppDataTypeTestProgram.cpp](#cppdatatypetestprogramcpp)  

<!-- /TOC -->

## Introduction

This example demonstrates the creation and usage of port variables in PLCnext Engineer and C++ applications for data exchange via elementary data types.
All supported elementary data types are documented in the [PLCnext Info Center](https://www.plcnext.help/te/PLCnext_Runtime/Available_data_types.htm).

## Example details

|Description | Value |
|------------ |-----------|
|Controller| AXC F 2152 |
|FW | 2020.0 LTS or later |
|SDK | 2020.0 LTS or later |
|PLCnext Engineer| 2020.0 LTS |

## Preconditions

- PLCnext Control AXC F 2152 with firmware 2020.0 LTS or later
- PLCnext Engineer 2020.0 LTS or later
- Eclipse<sup>&reg;</sup> IDE "Photon" or later

## Project compiling in Eclipse

1. In Eclipse create a project "CppDataTypeTest" with component "CppDataTypeTestComponent" and program "CppDataTypeTestProgram".
1. In the project replace the files "CppDataTypeTestProgram.cpp" and "CppDataTypeTestProgram.hpp" with files from this repository. Alternatively you can create your own project with component and programs and include the source code of "CppDataTypeTestProgram.cpp" and "CppDataTypeTestProgram.hpp" in your source code files.
1. Compile the Eclipse project.
1. After successful project compilation, the PLCnext Engineer .pcwlx library will be created automatically. You can find it in the Eclipse workspace folder; e.g.: "workspace\CppDataTypeTest\bin\CppDataTypeTest.pcwlx".

## PLCnext Engineer project

1. In PLCnext Engineer create a new project and add the user library "CppDataTypeTest.pcwlx" to the project.
1. Instantiate the program "CppDataTypeTestProgram" under a previously defined task.
1. In the "COMPONENT" area under "Programming" -> "Datatypes" create an new datatype worksheet and include the following user-defined datatypes:

	```text
			TYPE
				STRING420:STRING[420];

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

					outString:STRING;
				END_STRUCT

				
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
			//String
			String_array: ARRAY[0..9] OF STRING;
			END_TYPE
	```

1. Declare one IN port variable for each of the user-defined and elementary datatypes in a program, e.g. "Main". Find a table of elementary datatypes in the [PLCnext Info Center](https://www.plcnext.help/te/PLCnext_Runtime/Available_data_types.htm).
1. Connect the C++ port variables and IEC 61131 port variables under the "PLCnext" node in the "PLANT" area of PLCnext Engineer.
1. Download the PLCnext Engineer project to the PLCnext Control.

## Start-up instructions

- If the project is successfully implemented and downloaded, you can follow the data exchange in PLCnext Engineer running in debug mode and/or in the watch window of PLCnext Engineer.
- If the project did not start successfully, please see the error messages in Output.log file on the PLCnext target: /opt/plcnext/logs/Output.log
