#!/bin/bash
#
# How To use:
# Navigate into the ExampleFolder(cd ~/CppExamples/Examples/CppDataTypeTest) and execute this script.
# please set the version and target you wish to add.
#

# Chose project
plcncli new project -c DummyC -p DummyP && ls -la src && rm src/Dummy*
# or acfproject
#plcncli new acfproject -c DummyC && ls -la src && rm src/Dummy*


# Chose target name and version
plcncli set target --add --name AXCF2152 --version 2021.6

# Generate Intermediate files
plcncli generate all
plcncli build
plcncli deploy
