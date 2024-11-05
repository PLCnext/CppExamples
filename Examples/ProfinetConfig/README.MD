# Profinet Configuration Services

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Introduction](#introduction)
- [Guide details](#guide-details)
- [References](#references)
- [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides an RSC Service named IConfigurationService, which allows some Profinet configuration data items to be read and changed. This example shows how to use the Read and Write methods on this service to read and change the Profinet Device name on a PLCnext Control device.

## Guide details

|Description | Value |
|------------ |-----------|
|Created | 05.11.2024 |
|Last modified| 05.11.2024 |
|Controller| SIM-AXC F 2152 |
|FW| 2024.7 |
|SDK| 2024.7 |
|PLCnext CLI | 2025.0 PREVIEW |

## References

A complete description of the this RSC service is available in the API reference:

- [IConfigurationService Class Reference](https://api.plcnext.help/Preview-2024.7/classArp_1_1Io_1_1ProfinetStack_1_1System_1_1Services_1_1IConfigurationService.html)

## Quick-start example

This example demonstrates the Read and Write methods on the Profinet Configuration service.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://plcnext.help/te/Programming/Cplusplus/Cpp_programs_in_PLCnext.htm).

Prerequisites:

- SIM-AXC F 2152 controller with firmware 2024.7.

- PLCnext Command Line Interface (CLI) tool, version 2025.0 PREVIEW.

- A Software Development Kit (SDK) for the AXC F 2152 PLCnext Control, version 2024.7.

- (optional) Eclipse IDE, with the PLCnext Technology add-in installed.

- (optional) Visual Studio, with the PLCnext Technology extension installed.

Procedure:

- Ensure that the Profinet Device feature is enabled on the PLCnext Control device.

- Clone this repository, e.g.

   ```sh
   git clone https://github.com/PLCnext/CppExamples.git
   ```

- Create a new **ACF project** using either the PLCnext CLI tool, or Eclipse, or Visual Studio, with the following settings:
  - Project name: `ProfinetConfig`
  - Component name: `ProfinetConfigComponent`
  - Project namespace: `ProfinetConfig`

- Copy the contents of the `Examples/ProfinetConfig/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLC.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Custom.log`. It should contain messages from your ACF component, showing that the name of the Profinet Device has been changed.
