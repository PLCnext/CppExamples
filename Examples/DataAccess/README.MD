# Data Access Service

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Introduction](#introduction)
- [Guide details](#guide-details)
- [References](#references)
- [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides an RSC service, called `IDataAccessService`, that a client can use to read and write Global Data Space (GDS) variables. From the API documentation for `IDataAccessService`:

> The direct access functionality is a way for reading and writing values from and to variables. This is the fastest way, with a minimum of influence to the real time process, but it is not guaranteed that the data will be read/write in the same task cycle. For task consistent reading the subscription service `Arp.Plc.Gds.Services.ISubscriptionService` has to be used.

## Guide details
|Description | Value |
|------------ |-----------|
|Created | 7.01.2021 |
|Last modified| 06.09.2024 |
|Controller| SIM-AXC F 2152 |
|FW| 2024.7 |
|SDK| 2024.7 |
|PLCnext CLI | 2025.0 PREVIEW |

## References

A complete description of the Data Access service is available from these sources:

- [PLCnext Info Center](https://www.plcnext.help/te/Communication_interfaces/Remote_Service_Calls_RSC/RSC_GDS_services.htm#IDataAccessService)
- [API documentation](https://api.plcnext.help/api_docs_2024-0-LTS/classArp_1_1Plc_1_1Gds_1_1Services_1_1IDataAccessService.html)

## Quick-start example

This example demonstrates features of the Data Access RSC service.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://plcnext.help/te/Programming/Cplusplus/Cpp_programs_in_PLCnext.htm).

Prerequisites:

- PLCnext Command Line Interface (CLI) tool, version 2025.0 PREVIEW.

- A Software Development Kit (SDK) for the AXC F 2152 PLCnext Control, version 2024.7.

- (optional) Eclipse IDE, with the PLCnext Technology add-in installed.

- (optional) Visual Studio, with the PLCnext Technology extension installed.

- PLCnext Engineer version 2024.6.

Procedure:

- Clone this repository, e.g.

   ```sh
   git clone https://github.com/PLCnext/CppExamples.git
   ```

- Create the GDS variables that will be accessed:
  - Create a new PLCnext Engineer project for your target PLC.
  - Create one cyclic task.
  - Add the User Library "DataAccess.pcwlx", which is included in the `Examples/DataAccess` directory of this repository. This library contains one Program, called "DataAccess".
  - Create one instance of the "DataAccess" program in the cyclic task.
  - Name the program instance `DataAccessInstance`.
  - Write and start the project on the PLC.

- Create a new **ACF project** using either the PLCnext CLI tool, or Eclipse, or Visual Studio, with the following settings:
  - Project name: `DataAccess`
  - Component name: `DataAccessComponent`
  - Project namespace: `DataAccess`

- Copy the contents of the `Examples/DataAccess/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLC.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Custom.log`. It should contain messages showing the values of some OUT port variables from the `DataAccessInstance` program instance.

- In the PLCnext Engineer project, in Debug mode, add the IN port variables from `DataAccessInstance` to the Watch window. The values of some of these variables are being written by the C++ component using the Data Access RSC service.
