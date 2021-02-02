#!/bin/bash
#
# How To use:
# Navigate into the ExampleFolder(cd ~/CppExamples/Examples/CppDataTypeTest) and execute this script.
# please set the version and target you wish to add.
#

plcncli new project -c DummyC -p DummyP && ls -la src && rm src/Dummy*
plcncli set target --add --name AXCF2152 --version 2021.0
plcncli generate all
plcncli build
plcncli deploy