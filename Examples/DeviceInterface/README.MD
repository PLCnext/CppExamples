# Device Interface Services

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Introduction](#introduction)
- [Guide details](#guide-details)
- [References](#references)
- [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides four RSC services related to the device interface - Device Info service, Device Status service, Device Settings service, and Device Control service. This example shows how to use the methods on these four services to access and change information, status, and settings data in a PLCnext Control device.

## Guide details

|Description | Value |
|------------ |-----------|
|Created | 27.09.2024 |
|Last modified| 27.09.2024 |
|Controller| SIM-AXC F 2152 |
|FW| 2024.7 |
|SDK| 2024.7 |
|PLCnext CLI | 2025.0 PREVIEW |

## References

A complete description of the these services is available in the PLCnext Info Center:

- [RSC Device Interface Services](https://www.plcnext.help/te/Communication_interfaces/Remote_Service_Calls_RSC/RSC_device_interface_services.htm)

## Quick-start example

This example demonstrates each of the methods on the four Device Interface services.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://plcnext.help/te/Programming/Cplusplus/Cpp_programs_in_PLCnext.htm).

Prerequisites:

- SIM-AXC F 2152 controller with firmware 2024.7.

- PLCnext Command Line Interface (CLI) tool, version 2025.0 PREVIEW.

- A Software Development Kit (SDK) for the AXC F 2152 PLCnext Control, version 2024.7.

- (optional) Eclipse IDE, with the PLCnext Technology add-in installed.

- (optional) Visual Studio, with the PLCnext Technology extension installed.

Procedure:

- Clone this repository, e.g.

   ```sh
   git clone https://github.com/PLCnext/CppExamples.git
   ```

- Create a new **ACF project** using either the PLCnext CLI tool, or Eclipse, or Visual Studio, with the following settings:
  - Project name: `DeviceInterface`
  - Component name: `DeviceInterfaceComponent`
  - Project namespace: `DeviceInterface`

- Copy the contents of the `Examples/DeviceInterface/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLC.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Custom.log`. It should contain messages from your ACF component.
