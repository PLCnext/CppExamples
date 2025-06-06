# Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Example details](#example-details)
  - [Preconditions](#preconditions)
  - [Project compiling in Eclipse](#project-compiling-in-eclipse)
  - [PLCnext Engineer project](#plcnext-engineer-project)
  - [Start-up instructions](#start-up-instructions)

<!-- /TOC -->

## Introduction

This example demonstrates the creation and usage of port variables in PLCnext Engineer and C++ applications for data exchange via elementary data types.
All supported elementary data types are documented in the [PLCnext Technology Info Center](https://plcnext.help/te/PLCnext_Runtime/Supported_elementary_data_types.htm).

## Example details

|Description | Value |
|------------ |-----------|
|Controller| AXC F 2152 |
|FW | 2025.0 |
|SDK | 2025.0 |
|Toolchain | 2025.0 |
|PLCnext Engineer| 2025.0 |

## Preconditions

- PLCnext Control AXC F 2152 with firmware 2025.0
- PLCnext Engineer 2025.0
- Eclipse<sup>&reg;</sup> IDE for C/C++ Developers version 2025-03

## Project compiling in Eclipse

1. In Eclipse create a project "CppDataTypeTest" with component "CppDataTypeTestComponent" and program "CppDataTypeTestProgram".
1. In the project replace the files "CppDataTypeTestProgram.cpp" and "CppDataTypeTestProgram.hpp" with files from this repository. Alternatively you can create your own project with component and programs and include the source code of "CppDataTypeTestProgram.cpp" and "CppDataTypeTestProgram.hpp" in your source code files.
1. Compile the Eclipse project.
1. After successful project compilation, the PLCnext Engineer .pcwlx library will be created automatically. You can find it in the Eclipse workspace folder; e.g.: "workspace\CppDataTypeTest\bin\CppDataTypeTest.pcwlx".

## PLCnext Engineer project

1. In PLCnext Engineer create a new project and add the user library "CppDataTypeTest.pcwlx" to the project.
1. Instantiate the program "CppDataTypeTestProgram" under a previously defined task.
1. In the "COMPONENTS" area, under "Programming" -> "Local" -> "Data Types", create a new datatype worksheet and include the following user-defined datatypes:

	```text
            TYPE
                byte_array : ARRAY[0..9] OF BYTE;
                word_array : ARRAY[0..9] OF WORD;
                doubleword_array : ARRAY[0..9] OF DWORD;
                Lword_array : ARRAY[0..9] OF LWORD;
            END_TYPE
	```

	(all other custom types are generated automatically).

1. Declare one IN port variable for each of the user-defined and elementary datatypes in a program, e.g. "Main". Find a table of elementary datatypes in the [PLCnext Technology Info Center](https://plcnext.help/te/PLCnext_Runtime/Supported_elementary_data_types.htm). To make this easier, a .csv file containing these variable definitions is included in this repository, which you can import into a Variable Table in the PLCnext Engineer project.
1. Connect the C++ port variables and IEC 61131 port variables under the "PLCnext" node in the "PLANT" area of PLCnext Engineer.
1. Download the PLCnext Engineer project to the PLCnext Control device.

## Start-up instructions

- If the project is successfully implemented and downloaded, you can follow the data exchange in PLCnext Engineer running in debug mode and/or in the watch window of PLCnext Engineer.
- If the project did not start successfully, please check for error messages in [the diagnostic log files](https://www.plcnext.help/te/PLCnext_Runtime/output_log.htm) on the PLCnext Control device.
