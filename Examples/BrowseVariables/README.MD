# VariableBrowse Service

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [VariableBrowse Service](#variablebrowse-service)
  - [Table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Guide details](#guide-details)
  - [References](#references)
  - [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides an RSC service called `IVariableBrowseService`, that a client can use to get information about the  structure of the Global Name Space (GDS). There are many possible applications for the VariableBrowse service. For example: the VariableBrowse service is often used with the DataAccess service, because the DataAccess service returns struct data without any information about the struct field names. The VariableBrowse service allows this missing information to be filled in.

## Guide details

|Description | Value |
|------------ |-----------|
|Created | 2.04.2026 |
|Last modified | 02.04.2026 |
|Controller | AXC F 1252 |
|FW | 2026.0.1 |
|SDK | 2026.0.1 |
|PLCnext Technology Toolchain | 2025.6 |

## References

A complete description of the VariableBrowse service is available from this source:

- [API documentation](https://api.plcnext.help/api_docs_2026-0-LTS/classArp_1_1Plc_1_1Meta_1_1Services_1_1IVariableBrowseService.html)

## Quick-start example

This example demonstrates features of the VariableBrowse RSC service.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://plcnext.help/te/Programming/Cplusplus/Cpp_programs_in_PLCnext.htm).

Prerequisites:

- AXC F 1252 controller.

- PLCnext Technology Command Line Interface (CLI) tool, version 2025.6.

- A Software Development Kit (SDK) for the AXC F 1252 PLCnext Control device, version 2026.0.1.

- (optional) Eclipse IDE, with the PLCnext Technology add-in installed.

- (optional) Visual Studio, with the PLCnext Technology extension installed.

Procedure:

- Clone this repository, e.g.

   ```sh
   git clone https://github.com/PLCnext/CppExamples.git
   ```

- Create a new **ACF project** using either the PLCnext Technology CLI tool, or Eclipse, or Visual Studio, with the following settings:
  - Project name: `BrowseVariables`
  - Component name: `BrowseVariablesComponent`
  - Project namespace: `BrowseVariables`

- Copy the contents of the `Examples/BrowseVariables/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLCnext Control device.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Arp.log`. It should contain messages from your ACF component.
