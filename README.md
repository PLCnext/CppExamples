# PLCnext Technology - PLCnext_CppExamples

[![Feature Requests](https://img.shields.io/github/issues/PLCnext/PLCnext_CppExamples/feature-request.svg)](https://github.com/PLCnext/PLCnext_CppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc)
[![Bugs](https://img.shields.io/github/issues/PLCnext/PLCnext_CppExamples/bug.svg)](https://github.com/PLCnext/PLCnext_CppExamples/issues?utf8=✓&q=is%3Aissue+is%3Aopen+label%3Abug)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Web](https://img.shields.io/badge/PLCnext-Website-blue.svg)](https://www.phoenixcontact.com/plcnext)
[![Community](https://img.shields.io/badge/PLCnext-Community-blue.svg)](https://www.plcnext-community.net)

Write an introduction for your Project.

The PLCnext_CppExamples repository is a collection of various sample code for PLCnext Technology controllers. 
It is assumed that the reader has basic know how in C++ programming and has read the User Manual and the PLCnext Technology Quick Start Guide. 
Each example explains one or more topics. 
Explanations are given in the README.md document and in the comments of the example code.

Each example is a seperate user component wich can be instantiate on a `PLCnext-Control`.

## Table of Contents
|\#| Topic | Content | SourceCode
| ----- | ------ | ------ |------
|[01](Examples/ProgramComponentInteraction/)| [Program Component Interaction](Examples/ProgramComponentInteraction/README.md)| Shows a `PLCnext-Program` interacting with a`PLCnext-Component` by getting or setting variables through reference.| [SourceCode](Examples/ProgramComponentInteraction/src/)

## Getting Started
[PLCnext Usermanual](https://plcnext-community.net/index.php?option=com_wrapper&view=wrapper&Itemid=353&lang=en)

### Compiling a Example
    (CMAKE instructions to build a Shared Object)[someFile]

<!--
## Compile the Code with the PLCnCLI
1. Install the SDK,  Eclipse Plugin and PLCNCLI.[HowTo](https://plcnext-community.net/index.php?option=com_content&view=article&id=153:relaunch-22-9&catid=36&Itemid=248&lang=en)
2. Create a new empty Eclipse project named `ProgramComponentInteraction`
3. Delete the auto generated `Component.hpp` and `Program.hpp`
4. Insert the content of the folder `src` into the Eclipse projects `src` folder.
5. Press build
-->

### Deploying a Example
  Exampleconfig files: 
  [ESM](Template/intermediate/Config/ESM*),
  [GDS](Template/intermediate/Config/GDS*),
  [Progmeta](Template/intermediate/Config/Progmeta*),
  [Compmeta](Template/intermediate/Config/Compmeta*),
  [Libmeta](Template/intermediate/Config/Libmeta*)

## Contributing

You can participate in this project by submitting bugs and feature requests. 
Further more you can help us by discussing issues and let us know where you have problems or where others could struggle.

## Feedback

Provide information how feedback can be given e.g.:

* Ask a question in our [Forum](https://www.plcnext-community.net/index.php?option=com_easydiscuss&view=categories&Itemid=221&lang=en).
* Request a new feature on [GitHub](CONTRIBUTING.md).
* Vote for [Popular Feature Requests](https://github.com/PLCnext/PLCnext_CppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc).
* File a bug in [GitHub Issues](https://github.com/PLCnext/PLCnext_CppExamples/issues).

## License

Copyright (c) Phoenix Contact Gmbh & Co KG. All rights reserved.

Licensed under the [MIT](LICENSE) License.
