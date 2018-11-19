#!/bin/bash
uname -a 
$PathToCLI version

pwd > PLCNCLI.log 2>&1 

#### Move Project content------------------------------------------------------------
echo "#### Move Project content-----------------------------------------------------------" > PLCNCLI.log 2>&1 
cp -r $sourceFiles $build > PLCNCLI.log 2>&1  

#### Check Project content------------------------------------------------------------ 
echo "#### Check Project content-----------------------------------------------------------" > PLCNCLI.log 2>&1 
echo -e "\n Lists all components of a project.\n " > PLCNCLI.log 2>&1 
$PathToCLI get components -p $build --verbose > PLCNCLI.log 2>&1 
echo -e "\n Lists all programs of a project.\n" > PLCNCLI.log 2>&1 
$PathToCLI get programs -p $build --verbose > PLCNCLI.log 2>&1 

#### Build Process ------------------------------------------------------------ 
echo "#### Build Process -----------------------------------------------------------"
echo -e "\n generate meta\n" 
$PathToCLI generate meta --verbose --path $build 
pwd
ls -la $build/intermediate/Config

echo -e "\n generate code \n"
$PathToCLI generate code --verbose --path $build 
ls -la $build/intermediate/Code   

echo -e "\n build \n"
$PathToCLI build    --verbose \
                    --path $build \
                    -t $targetName \
                    --targetversion $targetVersion \
                    --buildtype "Release" \
                    --configure \
                    
#-p, --path         Directory where the .proj file is located.
#  -t, --target       Target for which the build shall be executed.
#  --targetversion    Version of the target for which the build shall be 
#                     executed.
#  -b, --buildtype    Build type for the build , e.g. Release
#  --configure        Force CMake to make a new configuration
#  --noconfigure      Force CMake to do only do a build
#  --verbose          Enables verbose output.

ls -la $build/bin 
ls -la $build 

echo -e "\n generate Library \n"
$PathToCLI generate library --verbose --path $build >> generate.log 
