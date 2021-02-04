#!/bin/bash
# Compile for list of HW
BUILD_HARDWARE="AXCF2152" # Example: "AXCF2152 RFC4072S"
VERSION_HW="2021.0"

# Project to compile
# does not support array of Projects
PROJECTNAME="ProgramComponentInteraction" # Project
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source $CURRENT_DIR/ask.sh
DIR=$CURRENT_DIR/..
# echo "DIR="$DIR

# Check if build for this project already exists
if [ -d "$DIR/build/$PROJECTNAME" ]; then
    echo "Directory $DIR/build/$PROJECTNAME ALREADY EXISTS!"
    # Default to No if the user presses enter without giving an answer:
    if ask "Do you want to delete it and continue?" N; then
        echo "Deleting directory."; rm -r $DIR/build/$PROJECTNAME; 
    else
        echo "Exiting script."; exit 1;
    fi
fi

# Create Dummy Project
mkdir -p $DIR/build/$PROJECTNAME
# Or define component and program name:
# plcncli new project -c DummyC -p DummyP #README cmd
plcncli new project --name $PROJECTNAME --output $DIR/build/$PROJECTNAME --verbose
ls -la $DIR/build/$PROJECTNAME/src 
# REMOVING files generated from TEMPLATE
rm $DIR/build/$PROJECTNAME/src/*.cpp
rm $DIR/build/$PROJECTNAME/src/*.hpp

## Suppress compiler warning: offsetof within non-standard-layout type
echo -e '\ntarget_compile_options('$PROJECTNAME' PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wno-invalid-offsetof>)' >> $DIR/build/$PROJECTNAME/CMakeLists.txt

cp -r $DIR/Examples/$PROJECTNAME/src/. $DIR/build/$PROJECTNAME/src

plcncli set target --add --name $BUILD_HARDWARE --version $VERSION_HW --verbose --path $DIR/build/$PROJECTNAME
plcncli generate all --path $DIR/build/$PROJECTNAME --verbose
plcncli build --path $DIR/build/$PROJECTNAME --verbose
plcncli deploy --path $DIR/build/$PROJECTNAME --verbose
