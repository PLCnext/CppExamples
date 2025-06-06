# Component Ports

## Table of contents

<!-- TOC depthfFrom:2 orderedList:true -->

- [Component Ports](#component-ports)
  - [Table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Background](#background)
  - [Details](#details)

<!-- /TOC -->

## Introduction

In PLM projects it is possible to implement Inports and Outports for programs. Additionally member variables of the component can be declared as ports. This declaration is basically explained in the components header file created by PLCnCLI. Since the life-time of a component differs from the programs life-time, **some additional implementation is necessary if the component ports shall be initialized similar to program ports regarding to the Cold/Warm Start behavior of the PLC application!** This example demonstrates the necessary implementation.

## Background

The PLCnext Technology firmware creates program instances according to the ESM configuration when the PLC program is loaded. Program instances are deleted when the PLC application is unloaded. This holds true for component instances as well. Additionally (and in contrast to component instances) program instances are also deleted and created again when the PLC application is started (Cold as well as Warm Start). During this creation all member variables of the program are initialized by the C++ code. If the PLC is started by a warm start, program ports which are marked with the `Retain` attribute are restored to their last saved value. This is handled for program instances by the firmware but for component instances dedicated C++ code has to be provided within the component.

This dedicated C++ code consists basically of one method added to the component. This method has to be registered at the firmware to be called when the PLC application is started. The input parameter of this method then indicates the start kind (warm/cold) of the PLC application.

## Details

**Precondition:** The header files `Arp/Plc/Commons/Domain/PlcStartKind.hpp` and `Arp/Plc/Commons/Domain/PlcDomainProxy.hpp` need to be included as well as the namespace `Arp::Plc::Commons::Domain` needs to be used.

The `ComponentWithPort` in this example declares the ports `retainPort1` and `nonretainPort1` and the first port is marked with the `Retain` attribute. Furthermore the method **`OnPlcStarting(PlcStartKind)`** is defined. The component registers this method to the firmware `PlcDomainProxy` within its `Initialize()` method. <u>It is important to unregister this method</u> when the components life-time ends. This is done within the `Dispose()` method. Please note that this method may not be declared automatically when PLCnCLI creates a new component.

Within the `OnPlcStarting(PlcStartKind)` method the input `startkind` is checked:

- The value `Warm` indicates a Warm Start of the PLC application. Such Warm Start can be performed using PLCnext Engineer or after the PLC has booted.
- The value `RestoreWarm` indicates a Warm Start of the PLC application in the context of the PLCnext Engineer function "Restore last saved retain data".
- The value `Cold` indicates a Cold Start of the PLC application which can be performed using PLCnext Engineer.
- The value `Hot` indicates a Hot Start of the PLC application which can be performed using PLCnext Engineer. In this case all ports are expected to keep their values, so no action is required.

Note: The program in this example is created by PLCnCLI and has not been changed. In PLCnext Engineer this program needs to be instantiated in order to create an instance of `ComponentWithPorts`.
