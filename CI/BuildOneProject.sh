#!/bin/sh

while getopts p:d:nv option
do
case "${option}"
in
p) PROJECTNAME=${OPTARG};;
d) DIRECTORY=${OPTARG};;
n) TARGETNAME=${OPTARG};;
v) TARGETVERSION=${OPTARG};;
esac
done

mkdir build
mkdir build/$PROJECTNAME
mkdir build/$PROJECTNAME/AUTO
mkdir build/$PROJECTNAME/RELEASE

plcncli new project \
            -n $PROJECTNAME \
            -o build/$PROJECTNAME \
            -s TCS \
            --verbose \
            &> build/newProject.logl

cp -r $DIRECTORY/$PROJECTNAME/src build/$PROJECTNAME/src


plcncli generate code \
            -p build/$PROJECTNAME \
            -o build/$PROJECTNAME/AUTO \
            --verbose \
            &> build/GenerateCode.log

plcncli generate config \
            -p build/$PROJECTNAME \
            -o build/$PROJECTNAME/AUTO \
            --verbose \
            &> build/GenerateConfig.log

plcncli set target \
  -n $TARGETNAME \
  -v $TARGETVERSION \
  -a \
  -p build/$PROJECTNAME \
  --verbose \
  &> build/SetTarget.log

plcncli build \
        -p build/$PROJECTNAME \        
        -b RELEASE \
        --configure \
        -o build/$PROJECTNAME/src \
        --verbose \
        -- \
        -DCMAKE_STAGING_PREFIX build/$PROJECTNAME/RELEASE \
        &> build/Build.log

