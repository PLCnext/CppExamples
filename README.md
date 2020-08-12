# PLCnext Technology - CppExamples

[![Feature Requests](https://img.shields.io/github/issues/PLCnext/CppExamples/feature-request.svg)](https://github.com/PLCnext/CppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc)
[![Bugs](https://img.shields.io/github/issues/PLCnext/CppExamples/bug.svg)](https://github.com/PLCnext/PLCnext_CppExamples/issues?utf8=✓&q=is%3Aissue+is%3Aopen+label%3Abug)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Web](https://img.shields.io/badge/PLCnext-Website-blue.svg)](https://www.phoenixcontact.com/plcnext)
[![Community](https://img.shields.io/badge/PLCnext-Community-blue.svg)](https://www.plcnext-community.net)


The [CppExamples](https://github.com/PLCnext/CppExamples) repository is a collection of various sample code for PLCnext Technology controllers. 
It is assumed that the reader has basic know-how of C++ programming and has read the key parts of the [PLCnext Info Center](https://www.plcnext.help/).  
Each example explains one or more topics on how to use C++11 with PLCnext Technology. Explanations are given in the *README.md* document and via comments in the example code. 
Each example holds separate user components which can be instantiated on a *PLCnext Control*. 

This project aims to supply, over time, examples and best practices of PLCnext Technology functions regarding C++11.

## Table of Contents

|\#| Topic | Content | SourceCode
| ----- | ------ | ------ |------
|[01](Examples/ProgramComponentInteraction/)| [Program Component Interaction](Examples/ProgramComponentInteraction/README.md)| This example shows two *PLCnext programs* interacting with a *PLCnext component* by getting or setting variables through reference.| [SourceCode](Examples/ProgramComponentInteraction/src/)
|[02](Examples/CppDataTypeTest/)| [Data Type Exchange Example](Examples/CppDataTypeTest/README.md)| This example shows how to transfer data from a C++ project to the GDS. Variables published to the GDS can be accessed by other programs (IEC/C++/Simulink/C#) or the IOs| [SourceCode](Examples/CppDataTypeTest/src/)
|[03](Examples/IncludeOpenSourceLibrary/)| [Include an Open Source Library](Examples/IncludeOpenSourceLibrary/README.md)| This describes how to use a third-party open-source library in a C++ project that is built for PLCnext Control using Eclipse|
|[04](Examples/ThreadExample/)| [Thread Example](Examples/ThreadExample/README.md)| This describes how to implement Threads in a component of C++ project.| [SourceCode](Examples/ThreadExample/src/)
|[05](Examples/NotificationExample/)| [Notification Example](Examples/NotificationExample/README.MD)| This describes how to use the Notification Manager.| [SourceCode](Examples/NotificationExample/src/)
|[06](Examples/E_Learning_InternalFunctionExtensions/)| [E-Learning: InternalFunctionExtensions](Examples/E_Learning_InternalFunctionExtensions/README.MD)| This describes how to use the Internal Function Extensions.| [SourceCode](Examples/E_Learning_InternalFunctionExtensions/src/)

## Getting started

- [C++ programs in PLCnext Technology](https://www.plcnext.help/te/Programming/Cpp/Cpp_programming/Cpp_programs_in_PLCnext.htm)
- [Required Installations for C++ programming](https://www.plcnext.help/te/Programming/Cpp/Cpp_programming/Required_Installations.htm)
- [Creating a new C++ project in Eclipse](https://www.plcnext.help/te/Programming/Cpp/Cpp_programming/Creating_a_Cpp_project_in_Eclipse.htm)

## Compiling an example

There are different ways how to build your code:

### Compile the code with the PLCnext CLI 

1. Install Eclipse IDE, CLI, SDK and Eclipse Add-in (how-to guide: see links in the "Getting started" section above)
1. Clone this repository
1. Navigate to the project you want to test, e.g. `cd Examples/ProgramComponentInteraction` 
1. Execute `plcncli new project -c DummyC -p DummyP && ls -la src && rm src/Dummy*`
1. Execute `plcncli set target --add --name AXCF2152 --version 2020.6` to specify details of the build target
1. Execute `plcncli generate all` to generate intermediate code and Config files
1. Execute `plcncli build` to build the code.
1. Execute `plcncli deploy` to generate a *.pcwlx* file that can be included in PLCnext Engineer 

### Compile using the Eclipse Add-in

1. Create a new empty project named like the example you want to test
1. Remove the source files located at `ProjectName/src`
1. Move the source files from the example you want to use into your workspace at `ProjectName/src`
1. Build the project

### Compile using [build-local.sh](tools/build-local.sh) script

1. Clone this Repository
1. Modify the [build-local.sh](tools/build-local.sh) script to fit your needs
    1. select Hardware
    1. select Project
1. Make sure it is executable for example with ```chmod +x tools/build-local.sh```
1. Execute the script ```./tools/build-local.sh``` or  ```sh tools/build-local.sh ```

## Contributing

You can participate in this project by submitting bugs and feature requests.  
Furthermore you can help us by discussing issues and letting us know where you have problems or where others could struggle.

## Feedback
* Ask a question in our [Forum](https://www.plcnext-community.net/en/discussions-2-offcanvas/forums.html)
* Request a new feature or example to be added on [GitHub](CONTRIBUTING.md)
* Vote for [Popular Feature Requests](https://github.com/PLCnext/CppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc)
* File a bug in [GitHub Issues](https://github.com/PLCnext/CppExamples/issues)

## License

Copyright (c) Phoenix Contact GmbH & Co KG. All rights reserved.

Licensed under the [MIT](/LICENSE) License.
