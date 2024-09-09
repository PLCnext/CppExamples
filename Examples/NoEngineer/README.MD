# PLM/ESM/GDS Configuration without PLCnext Engineer

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Prerequisites](#prerequisites)
- [Introduction](#introduction)
- [Guide details](#guide-details)
- [Reference](#reference)
- [Example](#example)

<!-- /TOC -->

## Prerequisites

Users of this guide should be familiar with:

- Creating C++ programs for PLCnext Control devices, and using those programs in PLCnext Engineer projects. There is extensive information on this topic in the [PLCnext Info Center](https://www.plcnext.help/te/Programming/Cpp/Cpp_programming/Cpp_programs_in_PLCnext.htm).

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
|Created | 2.06.2021 |
|Last modified| 27.08.2024 |
|Controller| AXC F 2152 |
|FW| 2024.7 |
|SDK| 2024.7 |
|PLCnext CLI | 2024.6 |

## Reference

- [PLCnext Runtime configuration files](https://plcnext.help/te/PLCnext_Runtime/Configuration_files.htm), in the PLCnext Info Center.

## Example

In this example, a PLCnext Control device is configured as a Profinet device (slave). A real-time C++ program instance, running in an Execution and Synchronisation Manager (ESM) task, uses Global Data Space (GDS) variables to exchange data with the two Profinet Device (PND) system variables `PND_S1_INPUTS` and `PND_S1_OUTPUTS`. The complete project is configured without the use of PLCnext Engineer.

1. Configure the PLC System Services

   This application example uses a PLC that must have the IEC feature disabled, and the PROFINET DEVICE feature enabled. Other applications that use the principles demonstrated in this example may not require these settings.

   Using the PLCs [Web Based Management](https://plcnext.help/te/WBM/Configuration_System_Services.htm) interface, disable the IEC system feature, and enable the PROFINET DEVICE feature. The PLC must be rebooted for changes to take effect.

   ![image](https://user-images.githubusercontent.com/13133969/136402485-6097e087-fc1a-4731-a138-4a6087f6bd04.png)

1. Create the C++ program.

   Using your C++ tool of choice (Eclipse, Visual Studio or the PLCnext CLI), create a new PLCnext C++ project of type "Project". This type of project includes one PLM component and one C++ Program. Name the project “Pnd”, and leave the Component and Program names as the suggested defaults.

1. Create GDS port variables.

   In the PndProgram.hpp file, create the following two port variables:

   ```cpp
     //#port
     //#attributes(Input)
     uint8   PND_S1_INPUTS[512] = {0};

     //#port
     //#attributes(Output)
     uint8   PND_S1_OUTPUTS[512] = {0};
   ```

1. Build the C++ project.

1. Copy the C++ library and metadata to the PLC.

   Recursively copy the entire contents of the project “Release” directory to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Pnd
   ```

   The Pnd directory on the PLC should now contain the following directories and files:

   ```text
     |-auto-deployed-external-libraries
     |-Pnd.libmeta
     |-PndComponent
     |  |-PndComponent.compmeta
     |  |-PndProgram
     |  |  |-PndProgram.progmeta
     |-Pnd.typemeta
     |-lib
     |  |-libPnd.so
   ```

   You don’t need the `auto-deployed-external-libraries` directory, so you can delete that:

   ```text
   rm -r /opt/plcnext/projects/Pnd/auto-deployed-external-libraries
   ```

   Move the library file up one directory in the tree:

   ```text
   mv /opt/plcnext/projects/Pnd/lib/libPnd.so /opt/plcnext/projects/Pnd && rm -r /opt/plcnext/projects/Pnd/lib
   ```

   This is required because some of the following configuration files assume this relative path.

1. Program Library Manager (PLM) configuration.

   Copy the `pnd.plm.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Default/Plc/Plm
   ```

   This file will automatically be loaded by the PLM component of the PLCnext Runtime, and it contains instructions for loading your **Pnd** library and creating an instance of your **PndComponent**.

1. ESM configuration.

   Copy the `pnd.esm.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Default/Plc/Esm
   ```

   This file will automatically be loaded by the ESM component of the PLCnext Runtime, and it contains instructions for creating an ESM task, assigning that task to ESM1, and creating an instance of your **PndProgram** in that task.

1. Library metadata configuration.

   Copy the `pnd.meta.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Default/Plc/Meta
   ```

   This file will automatically be loaded by the PLCnext Runtime, and it contains type information for your library.

1. GDS configuration.

   Copy the `pnd.gds.config` file from this repository to the following directory on the PLC:

   ```text
   /opt/plcnext/projects/Default/Plc/Gds
   ```

   This file will automatically be loaded by the GDS component of the PLCnext Runtime, and it contains the GDS port connection information between your program instance and the PND system variables in the PLC.

1. Activate the configuration.

   Restart the PLCnext Runtime.

   ```text
   sudo systemctl restart plcnext
   ```

   Check the `Arp.log` file for any errors - there should be no errors!

The C++ program is now running and exchanging data with the system variables `PND_S1_INPUTS` and `PND_S1_OUTPUTS`. At the moment this data is all zeroes, which is not very interesting.

The next steps are left up to the user:

1. Write non-zero data to `PND_S1_OUTPUTS`.

   Change the code in the C++ program's `Execute` method, e.g. increment one or more elements of the `PND_S1_OUTPUTS` array, and rebuild the C++ project. If there are no changes to the C++ GDS port definitions, you can simply replace the libPnd.so file on the PLC after every build and restart the PLCnext Runtime.

1. Configure a Profinet controller.

   Using another PLC as a Profinet controller, set up your device on the Profinet network. If required, the GSDML file for your device can be downloaded from the Phoenix Contact website.

   The data written to `PND_S1_OUTPUTS` on the device can now be observed in the Profinet controller.

1. Extend the application.

   For example - use the techniques demonstrated in the [BusConductor example](https://github.com/PLCnext/BusConductor) to enable your C++ component to dynamically configure connected Axioline I/O modules, without using PLCnext Engineer. Your C++ program(s) can then exchange I/O data via GDS port variables.
