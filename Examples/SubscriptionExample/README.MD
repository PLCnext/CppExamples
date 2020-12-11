# Subscription Service

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Introduction](#introduction)
- [Guide details](#guide-details)
- [References](#references)
- [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides an RSC service, called `ISubscriptionService`, that a client can use to subscribe to Global Data Space (GDS) variables. From the API documentation for `ISubscriptionService`:

> The subscription functionality is a more elegant way reading values from [Global Data Space (GDS)] variables, in contrast to permanently reading (polling). A client can subscribe a selection of variables of interest and the subscription will copy the data values to a internal buffer. This is the recommended mechanism to “read” variable values from the PLC system. All read data are always task consistent, because the data is written by the task itself.

## Guide details
|Description | Value |
|------------ |-----------|
|Created | 10.12.2020 |
|Last modified| 10.12.2020 |
|Controller| AXC F 2152 |
|FW| 2020.6.1 |
|Arpversion| 20.6.1.30859 |
|SVN Revision| 30859 |
|SDK| 20.6.1.30859 |
|PLCnext CLI | 2020.0 (20.0.0.243) |

## References

A complete description of the Subscription service is available from these sources:

- [PLCnext Info Center](https://www.plcnext.help/te/Service_Components/Remote_Service_Calls_RSC/RSC_GDS_services.htm#ISubscriptionService)
- [API documentation](https://api.plcnext.help/api_docs_2020-6/classArp_1_1Plc_1_1Gds_1_1Services_1_1ISubscriptionService.html)

## Quick-start example

This example demonstrates features of the Subscription service.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://www.plcnext.help/te/Programming/Cpp/Cpp_programming/Cpp_programs_in_PLCnext.htm).

Prerequisites:

- PLCnext Command Line Interface (CLI) tool, version 2020.0. This is included in the "PLCnext Technology C++ tool chain", available on the Phoenix Contact website.

- A Software Development Kit (SDK) for the AXC F 2152 PLCnext Control, version 2020.6.1 or later. This is also included in the "PLCnext Technology C++ tool chain".

- (optional) Eclipse IDE, with the PLCnext Technology feature installed.

- (optional) Visual Studio, with the PLCnext Technology add-in installed.

- PLCnext Engineer version 2020.6 or later.

Procedure:

- Clone this repository, e.g.

   ```sh
   git clone https://github.com/PLCnext/CppExamples.git
   ```

- Create the GDS variables that will be subscribed to:
   - Create a new PLCnext Engineer project for your target PLC.
   - Create two cyclic tasks, with interval values of 100ms and 500ms.
   - Add the User Library "SubscriptionData.pcwlx", which is included in the `Examples/SubscriptionExample` directory of this repository. This library contains one Program, called "RealTimeProgram".
   - Create two instances of "RealTimeProgram", one in each of the two cyclic tasks.
   - Name the two program instances `RealTimeProgram100ms` and `RealTimeProgram500ms`.
   - Write and start the project on the PLC.

- Create a new **ACF project** using either the PLCnext CLI tool, or Eclipse, or Visual Studio, with the following settings:
   - Project name: `Subscriptions`
   - Component name: `SubscriptionsComponent`
   - Project namespace: `Subscriptions`

- Copy the contents of the `Examples/SubscriptionExample/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLC.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Output.log`. It should contain messages showing the value of variable `varUInt16` from the program `RealTimeProgram100ms`.

- Change the .acf.config file to instantiate SubscriptionsComponent2.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Output.log`. It should contain messages ...
