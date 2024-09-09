# Force Service

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Introduction](#introduction)
- [Guide details](#guide-details)
- [References](#references)
- [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides an RSC service, called `IForceService`, that a client can use to force some Global Data Space (GDS) variables. From the PLCnext Engineer help system:

> What is the difference between forcing and overwriting?
>
> Overwriting is possible for local and global variables (marker variables without assigned process data item) as well as for I/O variables (assigned to process data item). The value is overwritten (set) only once at the beginning of the task execution cycle. Then, the variable is processed normally. Thus, the new value of the variable remains until a write access is performed. A write access can be performed by a programmed store operation or by remote access (e.g. by the OPC server) or by initializing the variable in case of a controller cold start.
>
> Forcing is possible for variables and ports which are connected to process data items, i.e., I/O variables/ports. Forcing means setting the I/O variable/port permanently to the force value until forcing is reset by the user.

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

A complete description of the Force service is available from this source:

- [API documentation](https://api.plcnext.help/api_docs_2024-0-LTS/classArp_1_1Plc_1_1Gds_1_1Services_1_1IForceService.html)

## Quick-start example

This example demonstrates features of the Force RSC service.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://plcnext.help/te/Programming/Cplusplus/Cpp_programs_in_PLCnext.htm).

Prerequisites:

- AXC F 2152 controller with AXL F DI8/3 DO8/3 2H (2702071) digital input/output module. Other hardware arrangements will require modifications to the sample code.

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

- Create the variables that will be forced:
  - In PLCnext Engineer, open the PLCnext Engineer project in the `Examples/Force` directory of this repository.
  - Check that the controller model and firmware version in the project matches the controller you are using.
  - Send the project to the PLC and check that the PLC starts OK.

- Create a new **ACF project** using either the PLCnext CLI tool, or Eclipse, or Visual Studio, with the following settings:
  - Project name: `Force`
  - Component name: `ForceComponent`
  - Project namespace: `Force`

- Copy the contents of the `Examples/Force/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLC.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Custom.log`. It should contain messages from your ACF component.

- Check the contents of the file `/opt/plcnext/logs/Arp.log`. It should contain messages from the `GdsForceManager` firmware component.
