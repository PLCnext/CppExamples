# PLCnext Technology - CppExamples

[![Feature Requests](https://img.shields.io/github/issues/PLCnext/CppExamples/feature-request.svg)](https://github.com/PLCnext/CppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc)
[![Bugs](https://img.shields.io/github/issues/PLCnext/CppExamples/bug.svg)](https://github.com/PLCnext/PLCnext_CppExamples/issues?utf8=✓&q=is%3Aissue+is%3Aopen+label%3Abug)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Web](https://img.shields.io/badge/PLCnext-Website-blue.svg)](https://www.phoenixcontact.com/plcnext)
[![Community](https://img.shields.io/badge/PLCnext-Community-blue.svg)](https://www.plcnext-community.net)


The [CppExamples](https://github.com/PLCnext/CppExamples) repository is a collection of various sample code for PLCnext Technology controllers. 
It is assumed that the reader has basic know how in C++ programming and has read the User Manual and the PLCnext Technology Quick Start Guide. 
Each example explains one or more topics. 
Explanations are given in the 'README.md' document and in the comments of the example code.

Each example holds seperate user components wich can be instantiate on a `PLCnext-Control`.

## Table of Contents
|\#| Topic | Content | SourceCode
| ----- | ------ | ------ |------
|[01](Examples/ProgramComponentInteraction/)| [Program Component Interaction](Examples/ProgramComponentInteraction/README.md)| Shows a `PLCnext-Program` interacting with a`PLCnext-Component` by getting or setting variables through reference.| [SourceCode](Examples/ProgramComponentInteraction/src/)
|[02](Examples/CppDataTypeTest/)| [Data Type exchange Example](Examples/CppDataTypeTest/README.md)| This example shows how to transfere data from a C++ Project to the GDS. Variables published to the GDS can be accessed by other Programs (IEC/C++/Matlab/C#) or the IOs| [SourceCode](Examples/CppDataTypeTest/src/)


## Getting Started
[PLCnext Usermanual](https://plcnext-community.net/index.php?option=com_wrapper&view=wrapper&Itemid=353&lang=en)

## Compiling an Example
You have multiple choices how to build your code.

### Compile the Code with the PLCnCLI [HowToPLCnCLI](https://plcnext-community.net/index.php?option=com_content&view=article&id=153:relaunch-22-9&catid=36&Itemid=248&lang=en)
1. Install the SDK,  Eclipse Plugin and PLCNCLI.
2. clone this repository
3. navigate to the Project you want to test for example 'cd Examples/ProgramComponentInteraction' 
3. execute 'plcncli new project -c DummyC -p DummyP && ls -la src && rm src/Dummy*'
4. execute 'plcncli generate all' to generate intermediate code and Config files
5. execute 'plcncli build' to build the code.
6. execute 'plcncli generate library' to generate a pcwlx file that can be included in PLCnext Engineer. 

### Compile using Eclipse Addin
1. create a new empty project named like the example you want to test.
2. remove the source files located at 'ProjectName/src'.
3. move the source files from the example you want to use into your workspace at 'ProjectName/src'
4. build the project
[See also this tutorial video](https://plcnext-community.net/index.php?option=com_content&view=article&id=157:tutorial-video-your-first-steps-with-eclipse-and-c&catid=66&Itemid=343&lang=en)


## Contributing

You can participate in this project by submitting bugs and feature requests. 
Further more you can help us by discussing issues and let us know where you have problems or where others could struggle.

## Feedback

Provide information how feedback can be given e.g.:

* Ask a question in our [Forum](https://www.plcnext-community.net/index.php?option=com_easydiscuss&view=categories&Itemid=221&lang=en).
* Request a new feature or Example to be added on [GitHub](CONTRIBUTING.md).
* Vote for [Popular Feature Requests](https://github.com/PLCnext/CppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc).
* File a bug in [GitHub Issues](https://github.com/PLCnext/CppExamples/issues).

## License

Copyright (c) Phoenix Contact Gmbh & Co KG. All rights reserved.

Licensed under the [MIT](LICENSE) License.
