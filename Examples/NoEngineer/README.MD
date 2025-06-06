# PLM/ESM/GDS Configuration without PLCnext Engineer

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [PLM/ESM/GDS Configuration without PLCnext Engineer](#plmesmgds-configuration-without-plcnext-engineer)
  - [Table of contents](#table-of-contents)
  - [Prerequisites](#prerequisites)
  - [Introduction](#introduction)
  - [Guide details](#guide-details)
  - [Reference](#reference)
  - [Example](#example)

<!-- /TOC -->

## Prerequisites

Users of this guide should be familiar with:

- Creating C++ programs for PLCnext Control devices, and using those programs in PLCnext Engineer projects. There is extensive information on this topic in the [PLCnext Technology Info Center](https://www.plcnext.help/te/Programming/Cplusplus/Cpp-programming.htm).

- Transferring files from a PC to the PLC using (for example) `scp` or WinSCP.

- Using a Linux shell.

## Introduction

When using C++ programs in a PLCnext Control project, the typical development process includes the following steps:

1. Package the C++ component(s) and program(s) into a PLCnext Engineer library.
1. Add the library to a PLCnext Engineer project.
1. In PLCnext Engineer's "Tasks and Events" window, create one or more C++ program instances in ESM tasks.
1. In PLCnext Engineer's "Port List" window, connect GDS ports to/from the C++ program instances.

In cases where the project does not include any IEC 61131 programs, it is possible to eliminate steps 1 and 2 above, and to complete steps 3 and 4 without using PLCnext Engineer. This guide demonstrates how to do this, using a simple example.

## Guide details

|Description | Value |
|------------ |-----------|
|Created | 02.06.2021 |
|Last modified | 05.06.2025 |
|Controller | AXC F 2152 |
|FW | 2025.0 |
|SDK | 2025.0 |
|PLCnext Technology Toolchain | 2025.0 |

## Reference

- [PLCnext Runtime configuration files](https://plcnext.help/te/PLCnext_Runtime/Configuration_files.htm), in the PLCnext Technology Info Center.

## Example

In this example, a PLCnext Control device is configured as a Profinet device (slave). A real-time C++ program instance, running in an Execution and Synchronisation Manager (ESM) task, uses Global Data Space (GDS) variables to exchange data with the two Profinet Device (PND) system variables `PND_S1_INPUTS` and `PND_S1_OUTPUTS`. The GDS variables are also accessible through the OPC UA Server on the PLCnext Control device. The complete project is configured without the use of PLCnext Engineer.

1. Configure the PLC System Services

   This application example uses a PLC that must have the IEC feature deactivated, the PROFINET DEVICE feature activated, and the OPC UA Server feature activated. Other applications that use the principles demonstrated in this example may not require these settings.

   Using the PLCs [Web Based Management](https://plcnext.help/te/WBM/Configuration_System_Services.htm) interface, deactivate the IEC system feature, activate the OPC UA feature, and activate the PROFINET DEVICE feature. The PLC must be rebooted for changes to take effect.

   ![image](https://user-images.githubusercontent.com/13133969/136402485-6097e087-fc1a-4731-a138-4a6087f6bd04.png)

1. Create the C++ program.

   Using your C++ tool of choice (Eclipse, Visual Studio or the PLCnext Technology CLI), create a new PLCnext C++ project of type "Project". This type of project includes one PLM component and one C++ Program. Name the project “Pnd”, and leave the Component and Program names as the suggested defaults.

1. Create GDS port variables.

   In the PndProgram.hpp file, create the following two port variables:

   ```cpp
     //#port
     //#attributes(Input|Opc)
     uint8   PND_S1_INPUTS[512] = {0};

     //#port
     //#attributes(Output|Opc)
     uint8   PND_S1_OUTPUTS[512] = {0};
   ```

   The `Opc` attribute means that we can see the values of the port variables via the OPC UA Server.

1. Build the C++ project.

1. Create the project directory structure on the PLC.

   Create a new project directory named `Pnd` on the PLCnext Control device:

   ```text
   mkdir /opt/plcnext/projects/Pnd
   ```

   Create the following folder structure inside the Pnd directory:

   ```text
     |-Libs
     |-Plc
     |  |-Esm
     |  |-Gds
     |  |-Plm
     |-Services
     |  |-OpcUA
   ```

   You can see that this is similar to the directory structure in the PCWE directory, which contains the PLCnext Engineer project that runs on the device by default.

1. Copy the C++ library to the PLC.

   Copy the .so (shared object library) file from the C++ project's “Release/lib” directory to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Pnd/Libs
   ```

1. Program Library Manager (PLM) configuration.

   Copy the `pnd.plm.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Pnd/Plc/Plm
   ```

   This file will automatically be loaded by the PLM component of the PLCnext Runtime, and it contains instructions for loading your **Pnd** library and creating an instance of your **PndComponent**.

1. ESM configuration.

   Copy the `pnd.esm.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Pnd/Plc/Esm
   ```

   This file will automatically be loaded by the ESM component of the PLCnext Runtime, and it contains instructions for creating an ESM task, assigning that task to ESM1, and creating an instance of your **PndProgram** in that task.

1. GDS configuration.

   Copy the `pnd.gds.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Pnd/Plc/Gds
   ```

   This file will automatically be loaded by the GDS component of the PLCnext Runtime, and it contains the GDS port connection information between your program instance and the PND system variables in the PLC.

1. OPC UA Server configuration.

   Copy the `PCWE.opcua.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Pnd/Services/OpcUA
   ```

   This file will automatically be loaded by the OPC UA Server component of the PLCnext Runtime. The configuration includes the option to make "Flagged" (or "Marked") GDS variables available through the OPC UA Server, which includes the two variables in our C++ program.

   Note that the name of this file cannot be changed. Unlike other components, the OPC UA Server looks specifically for a "PCWE" configuration file, even in projects that are unrelated to PLCnext Engineer. This behaviour may change in future firmware versions.

1. Change the project that is automatically loaded when the PLCnext Runtime starts.

   The PLCnext Runtime automatically loads the project that is referenced by the `current` symbolic link in the `projects` directory. By default this is the PCWE (PLCnext Engineer) project, but this can be changed. For example, if a [Solution App](https://store.plcnext.help/st/App_types.htm) is installed on the device, then this is placed in a project directory alongside the PCWE directory, and the `current` link is automatically changed to point to the App directory.

   In this case, edit the `current` symlink to point to the Pnd project:

   ```text
   cd /opt/plcnext/projects
   ln -sfn Pnd current
   ```

1. Activate the new configuration.

   Restart the PLCnext Runtime.

   ```text
   sudo systemctl restart plcnext
   ```

   Check the `Arp.log` file for any errors - there should be no errors!

The C++ program is now running and exchanging data with the system variables `PND_S1_INPUTS` and `PND_S1_OUTPUTS`.

1. Check the program GDS ports via the OPC UA Server.

   Use an OPC UA Client like [UaExpert](https://www.unified-automation.com/products/development-tools/uaexpert.html) to connect to the PLCnext Control device and view the two GDS port variables on the PndProgram instance. Note that the value of the array elements in the IN port variable can be changed by the OPC UA client, but the values of the array in the OUT port variable cannot - those values need to be set by the C++ program.
   
The next steps are left up to the user:

1. Write non-zero data to `PND_S1_OUTPUTS`.

   Change the code in the C++ program's `Execute` method, e.g. increment one or more elements of the `PND_S1_OUTPUTS` array, and rebuild the C++ project. If there are no changes to the C++ GDS port definitions, you can simply replace the libPnd.so file on the PLC after every build and restart the PLCnext Runtime.

1. Configure a Profinet controller.

   Using another PLC as a Profinet controller, set up your device on the Profinet network. If required, the GSDML file for your device can be downloaded from the Phoenix Contact website.

   The data written to `PND_S1_OUTPUTS` on the device can now be observed in the Profinet controller.

1. Extend the application.

   For example - use the techniques demonstrated in the [BusConductor example](https://github.com/PLCnext/BusConductor) to enable your C++ component to dynamically configure connected Axioline I/O modules, without using PLCnext Engineer. Your C++ program(s) can then exchange I/O data via GDS port variables.
