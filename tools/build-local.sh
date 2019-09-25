#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
# Build type
BUILDTYPE="RELEASE" 
# Compile for list of HW
BUILD_HARDWARE="AXCF2152" # Example: "AXCF2152 RFC4072S"

# Project to compile
# does not support array of Projects
PROJECTNAME="CppDataTypeTest" # Project

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"


##
# Create Dummy Project
mkdir -p $DIR/build/$PROJECTNAME
plcncli new project --name $PROJECTNAME --output $DIR/build/$PROJECTNAME --force --verbose
rm build/$PROJECTNAME/src/*.cpp
rm build/$PROJECTNAME/src/*.hpp
cp -r $DIR/Examples/$PROJECTNAME/src/. build/$PROJECTNAME/src

##
# Create Config and Code
tools/generate-config.sh -p ${PROJECTNAME}
tools/generate-code.sh -p ${PROJECTNAME}
tools/before-script.sh

##
# Re-Check Code Generation
find build/$PROJECTNAME  -name "${PROJECTNAME}Library.hpp" | egrep '.*'
find build/$PROJECTNAME  -name "${PROJECTNAME}Library.cpp" | egrep '.*'
find build/$PROJECTNAME  -name "${PROJECTNAME}Library.meta.cpp"  | egrep '.*'

Components=($(plcncli get components -p build/${PROJECTNAME}/ | grep -oPe "(?<=\:)[A-Z][a-zA-Z0-9_]+"))
for c in "${ARR[@]}"; \
do \
    find build/$PROJECTNAME  -name "${c}.meta.cpp" | egrep '.*'; \
    find build/$PROJECTNAME -name "${c}ProgramProvider.hpp" | egrep '.*'; \
    find build/$PROJECTNAME  -name "${c}ProgramProvider.cpp" | egrep '.*'; \
done
##
# Re-Check Config Generation
for c in "${Components[@]}"; \
do \
    find build/$PROJECTNAME  -name "${c}.compmeta" | egrep '.*'; \
done
#
Programs=($(plcncli get programs -p build/${PROJECTNAME}/ | grep -oPe "(?<=\:)[A-Z][a-zA-Z0-9_]+"))
for p in "${Programs[@]}"; \
do \
    find build/$PROJECTNAME  -name "${p}.progmeta" | egrep '.*'; \
done

##
# Build / Compile
tools/build-all.sh -p  "${PROJECTNAME}"  -h "${BUILD_HARDWARE}" -t "${BUILDTYPE}"

##
# Generate PLCnext Engineer Library
tools/assemble-library.sh -p ${PROJECTNAME} -t ${BUILD_HARDWARE}
