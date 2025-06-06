# Dynamic Ports

## Table of contents

<!-- TOC depthFrom:2 orderedList:true -->

- [Dynamic Ports](#dynamic-ports)
  - [Table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Guide details](#guide-details)
  - [Example - Home automation controller](#example---home-automation-controller)
    - [Requirements](#requirements)
    - [Solution A - static, hard-coded ports](#solution-a---static-hard-coded-ports)
    - [Solution B - static, hard-coded "generic" ports](#solution-b---static-hard-coded-generic-ports)
    - [Solution C - dynamic ports](#solution-c---dynamic-ports)
    - [Complete example](#complete-example)
  - [Explore unlimited possibilities ...](#explore-unlimited-possibilities-)
  - [Notes and limitations](#notes-and-limitations)

<!-- /TOC -->

## Introduction

In PLCnext Control projects, it has always been possible to hard-code Global Data Space (GDS) port definitions in C++ programs. SDK version 2021.6 introduced a new feature that allows programs to instead create _dynamic_ program ports at run-time.

The benefits of this feature will be demonstrated using a simple example.

## Guide details

|Description | Value |
|------------ |-----------|
|Created | 26.07.2021 |
|Last modified| 27.05.2025 |
|Controller| AXC F 2152 |
|FW| 2025.0 |
|SDK| 2025.0 |
|Toolchain | 2025.0 |
|PLCnext Engineer | 2025.0 |

## Example - Home automation controller

This example project will implement a simple home automation controller, which can be configured using a text file.

### Requirements

- The software must control multiple devices in a single house.
- Each device in the house has either a single digital input or a single digital output.
- The total number of devices must be configurable, up to a maximum of 20 devices.
- The name of each device must be configurable.
- The physical I/O connection for each device must be configurable.
- It must be possible to add and/or remove devices by changing the configuration.
- Configuration is via one or more text files.
- It is acceptable to have a brief interruption in control in order to load a new configuration.
- All device data must be visible and (where applicable) controllable via an OPC UA server.
- Initial configuration should include the following devices:
  - Sitting Room light (output)
  - Outside light (output)
  - Outside movement (input)
  - Outside daytime (input)

### Solution A - static, hard-coded ports

The "simplest" solution to this problem would be to create a new PLCnext Control project in Eclipse or Visual Studio with one component and one program. The program could define static GDS ports similar to the following:

  ```cpp
  //#port
  //#attributes(Output,Opc)
  bool sitting_room_light = false;

  //#port
  //#attributes(Output,Opc)
  bool outside_light = false;

  //#port
  //#attributes(Input,Opc)
  bool outside_movement = false;

  //#port
  //#attributes(Input,Opc)
  bool outside_daytime = false;
  ```

A simple program like this would satisfy some of the project requirements, but the major problem is with the configuration requirements. If any devices are added or removed from the house, the program source code must be edited and the entire project rebuilt and sent to the PLC. This is not something that the average user of a home automation system should be expected to do.

### Solution B - static, hard-coded "generic" ports

The next solution tries to address some of the configuration issues of our first attempt. We now define arrays of "generic" port variables, so that we do not need to change the source code when adding or removing devices.

  ```cpp
  //#port
  //#attributes(Output,Opc)
  bool digital_output_devices [20] = {false};

  //#port
  //#attributes(Input,Opc)
  bool digital_input_devices [20] = {false};
  ```

The problems with this solution include:

- Because we don't know how many of each type of device will be configured, we must define the maximum number of _each type_ of port (input and output). This is quite wasteful, and will only get worse if other device types (e.g. with analog I/O) are added to the requirements.
- The names of the generic ports do not give any clue as to what physical device each port is connected to. It might be possible to give the "generic" OPC tags a more meaningful name in the OPC UA client, but this will involve additional (possibly manual) configuration steps. And in any case ...
- All the unused port variables will also be visible in the OPC UA server, which is messy at best.

### Solution C - dynamic ports

PLCnext Control SDK version 2021.6 introduced the ability to add GDS ports to a program during the creation of a program instance.

Starting from a default C++ project template, this can be achieved in the following steps. This example uses a C++ project that was created with the following parameters:

- Project name: DynamicPorts
- Component Name: DynamicPortsComponent
- Program name: DynamicPortsProgram
- Project namespace: DynamicPorts

In the C++ program header file:

1. Include the `DynamicPortsProgramBase.hpp` header file, instead of `ProgramBase.hpp`.

   ```cpp
   #include "Arp/Plc/Commons/Esm/DynamicPortsProgramBase.hpp"
   ```

1. Include the project's library header file.

   ```cpp
   #include "DynamicPortsLibrary.hpp"
   ```

1. Inherit from the `DynamicPortsProgramBase<>` class template, instead of from the `ProgramBase` class.

   ```cpp
   //#program
   //#component(DynamicPorts::DynamicPortsComponent)
   class DynamicPortsProgram : public DynamicPortsProgramBase<DynamicPortsProgram,20>, private Loggable<DynamicPortsProgram>
   ```

   The second parameter on the `DynamicPortsProgramBase<>` template represents the maximum number of ports that can be created by this program. This information is required because the GDS component needs to know **in advance** how many port resources to allocate for this program.

1. Update the program constructor to initialise the new base class.

   ```cpp
   ///////////////////////////////////////////////////////////////////////////////
   // inline methods of class ProgramBase
   inline DynamicPortsProgram::DynamicPortsProgram(DynamicPorts::DynamicPortsComponent& dynamicPortsComponentArg, const String& name)
   : DynamicPortsProgramBase(name, DynamicPortsLibrary::GetInstance().GetTypeDomain())
   , dynamicPortsComponent(dynamicPortsComponentArg)
   ```

1. In the section where you would normally declare static ports, declare the port variable(s) without any attributes.

   ```cpp
   // An empty double-ended queue that will hold digital device values
   // (note that a vector of booleans will not work in this case).
   std::deque<boolean> digital_device;
   ```

   In this example, we do not know how many digital devices the user will configure. We will add items to this queue as required.

1. In the program constructor, create GDS ports.

   Similar to static ports, each dynamic GDS port is:
  
   - given a meaningful name,
   - associated with a program variable,
   - assigned standard attributes.

   ```cpp
   // Allocate the configured number of digital devices
   digital_device.resize(4, false);

   this->AddPort("sitting_room_light", digital_device.at(0), StandardAttribute::Output | StandardAttribute::Opc);
   this->AddPort("outside_light", digital_device.at(1), StandardAttribute::Output | StandardAttribute::Opc);
   this->AddPort("outside_movement", digital_device.at(2), StandardAttribute::Input | StandardAttribute::Opc);
   this->AddPort("outside_daytime", digital_device.at(3), StandardAttribute::Input | StandardAttribute::Opc);
   ```

   The snippet above hard-codes port attributes, but these could also be read from a configuration file.

1. After creating all the GDS ports, call `ReplaceProgramTypeDefinition()`

   ```cpp
   // Change the program type definition to use dynamic ports
   this->ReplaceProgramTypeDefinition();
   ```

   After calling this method, GDS ports for this program will be based on the dynamic port definitions, and static port definitions (if any) will be ignored.

1. Optional: Get the number of ports used.

   It is possible to get the number of ports actually used, as follows:

   ```cpp
   TypeDefinition typeDefinition(this->GetDynamicPortsBuilder().GetTypeDefinition());
   Log::Info("Number of dynamic ports used: {0}", static_cast<uint16>(typeDefinition.GetFields().size()));
   ```

   Since the number of ports cannot be changed after the program instance has been constructed, this code only needs to be called once, e.g. at the end of the program constructor.

### Complete example

The source files in this repository demonstrate a complete solution, including port configuration via a JSON file. To run this solution:

1. Copy the file `dynaports.json` to the `/opt/plcnext` directory on the PLC. This contains the port configuration information in JSON format.

1. Create a new C++ project using either the PLCnext Technology CLI tool, or Eclipse, or Visual Studio, with the following settings:

   - Project name: `DynamicPorts`
   - Component name: `DynamicPortsComponent`
   - Program name: `DynamicPortsProgram`
   - Project namespace: `DynamicPorts`

1. Copy the contents of the `Examples/DynamicPorts/src` directory in this repository, to the `src` directory of the C++ project. Replace the existing source files with the same name.

1. Build the C++ project and create the PLCnext Engineer library.

1. Create a new PLCnext Engineer project for the target PLC.

1. [Enable the OPC UA server](https://plcnext.help/te/Communication_interfaces/OPC_UA/OPCUA_server_configuration.htm) in the PLCnext Engineer project.

1. Add the library containing the C++ program to the PLCnext Engineer project.

1. Create an instance of the C++ program in a cyclic task.

1. Send the project to the PLC.

1. Check that there are no errors in the `Arp.log` file on the PLC, and that the `Custom.log` file contains an entry similar to this:

   ```text
   26.07.21 15:29:54.004 root      INFO  - Number of dynamic ports used: 4
   ```

1. In an OPC UA client like [UaExpert](https://www.unified-automation.com/products/development-tools/uaexpert.html), connect to the PLC's OPC UA server.

1. Confirm that the C++ program port variables are visible in UaExpert, and that the Input port variables can be written.

## Explore unlimited possibilities ...

- Additional port types can be added, e.g. Analog Inputs, or complex types representing complete devices with multiple inputs and/or outputs.

- A set of logic blocks can be defined in C++, e.g. analog scaling blocks, mathematical operators, or timer blocks. These blocks could be instantiated, connected to port variables, and chained together, using entries in configuration file(s). In the above example, the user could configure the outside light to turn on for a preset time if movement is detected during the night.

- The example above uses PLCnext Engineer to create a program instance in an ESM task. It is also possible to achieve this without PLCnext Engineer, using [file-based configuration](https://github.com/PLCnext/CppExamples/blob/master/Examples/NoEngineer/README.MD).

- A GDS configuration file (XML) can be used to set up data exchange between the C++ program ports and physical I/O, or between any two GDS ports of compatible type. An example of this type of file is given in the `dynaports.gds.config` file in this repository. This file can be copied to the PLC directory `/opt/plcnext/projects/Default/Plc/Gds`. When the PLCnext Runtime restarts, this file will be used to set up the GDS, and data will automatically be exchanged between the start ports and end ports named in that file.

- There are various techniques for configuring Axioline and/or Profinet I/O without using PLCnext Engineer, so it is possible to implement a complete solution without requiring the use of PLCnext Engineer.

## Notes and limitations

- There is currently no PLCnext Technology CLI template for this type of program.

- The dynamic ports feature is currently only available for C++ programs, not for C++ components.

- It is not possible to have a mix of static and dynamic GDS ports on a program.

- The maximum number of ports allowed in each program must be specified at build time, since a fixed amount of resources must be pre-allocated for port variables for each program instance.

- This feature does **not** allow:

  - Program ports to be added outside the program constructor.
  - Program ports to be deleted by the user at run-time.
  - Program ports to be different on different instances of a single program. All instances of a program **must** have the same set of dynamic port variables.

- GDS ports of type `struct` require a library meta (C++) file to define the fields of the structure. For static ports, this file is generated automatically by the PLCnext Technology CLI during the build process. For dynamic GDS ports of type `struct`, the struct definition must include the `//#typeinformation` decorator, like this:

   ```cpp
   // Define the struct that will be used to declare port variables.
   // The typeinformation attribute means that the plcncli will generate GDS metadata for this struct.
   //#typeinformation
   struct SampleStruct
   {
      float64 ElemA;
      uint32 ElemB;
      uint16 ElemC;
      boolean ElemD;
   };
   ```

- Metadata (XML) is not generated for dynamic ports during the build process, and without this information PLCnext Engineer is unable to display dynamic ports in the GDS Port List window. GDS connections to dynamic ports can be made manually in a custom `.gds.config` file ([as described in the PLCnext Technology Info Center](https://plcnext.help/te/PLCnext_Runtime/Global_Data_Space_configuration.htm)) or else at run-time using the [DataAccess or Subscription RSC services](https://plcnext.help/te/Communication_interfaces/Remote_Service_Calls_RSC/RSC_GDS_services.htm).

- Building a C++ project with dynamic GDS ports will give similar compiler warnings to those generated for static GDS ports, [as described in the PLCnext Technology Info Center](https://plcnext.help/te/Programming/Cplusplus/Creating_a_Cpp_project_in_Eclipse.htm).
