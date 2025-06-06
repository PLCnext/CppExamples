# Trace Controller Service

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Trace Controller Service](#trace-controller-service)
  - [Table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Guide details](#guide-details)
  - [References](#references)
  - [Quick-start example](#quick-start-example)

<!-- /TOC -->

## Introduction

The PLCnext Runtime provides an RSC service, called `ITraceControllerService`, that a client application written in C++ can use to manage LTTng trace sessions. This example demonstrates the use of the Trace Controller service using an LTTng trace configuration file that is installed on every PLCnext Control device. This example provides an alternative to the manual setup of the same LTTng configuration, described in the following Knowledge Base article:

[How to activate the PLCnext Trace Controller (LTTtng)](https://pxc1.esc-eu-central-1.empolisservices.com/gatekeeper/guesttoken/45?app=/service-express/portal/cb?redirect=https://pxc1.esc-eu-central-1.empolisservices.com/service-express/portal/object/esc/en-so-5a5c4287-9d80-4116-9b0a-9b4f01fbc0f7)

When started, the LTTng session described in the configuration file creates a snapshot trace when triggered by specific fault conditions on the device.

As with the knowledge base article, this example is not intended to describe how LTTng works, or how to create LTTng configurations, or how to analyse LTTng trace results.

## Guide details

|Description | Value |
|------------ |-----------|
|Created | 4.05.2021 |
|Last modified | 05.06.2025 |
|Controller | AXC F 2152 |
|FW | 2025.0 |
|SDK | 2025.0 |
|PLCnext Technology Toolchain | 2025.0 |

## References

A complete description of the Trace Controller service is available from this source:

- [API documentation](https://api.plcnext.help/api_docs_2025-0/classArp_1_1Services_1_1TraceController_1_1Services_1_1ITraceControllerService.html)

General information on LTTng is available from the [LTTng website](https://lttng.org/).

## Quick-start example

This example demonstrates features of the Trace Controller RSC service.

It is assumed that the user has some experience [building C++ Components and Programs for PLCnext Control](https://www.plcnext-community.net/infocenter/cpp_programs_in_plcnext/).

Prerequisites:

- AXC F 2152 controller.

- PLCnext Command Line Interface (CLI) tool, version 2025.0.

- A Software Development Kit (SDK) for the AXC F 2152 PLCnext Control, version 2025.0.

- (optional) Eclipse IDE, with the PLCnext Technology add-in installed.

- (optional) Visual Studio, with the PLCnext Technology extension installed.

Procedure:

- Clone this repository, e.g.

   ```sh
   git clone https://github.com/PLCnext/CppExamples.git
   ```

- Create a new **ACF project** using either the PLCnext Technology CLI tool, or Eclipse, or Visual Studio, with the following settings:
  - Project name: `TraceControl`
  - Component name: `TraceControlComponent`
  - Project namespace: `TraceControl`

- Copy the contents of the `Examples/TraceControl/src` directory in this repository, to the `src` directory of the ACF project. Replace the existing source files with the same name.

- Build the ACF project.

- Deploy the ACF project to the PLC.

- Restart the PLCnext Runtime.

- Check the contents of the file `/opt/plcnext/logs/Custom.log`. It should contain messages from your ACF component. In the component source code, you can see where these messages are generated in each step of the call sequence.
