#!/bin/bash
uname -a 
$PathToCLI version


#### Check PLCNCLI -----------------------------------------------------------------
echo "#### Check PLCNCLI -----------------------------------------------------------" > PLCNCLI.log 2>&1 
echo -e "\n Lists all available targets.\n" > PLCNCLI.log 2>&1 
echo "available: " > PLCNCLI.log 2>&1 
$PathToCLI get  targets -a  --verbose > PLC NCLI.log 2>&1 

echo -e "\n Lists all available sdks \n" > PLCNCLI.log 2>&1  
echo "available: " > PLCNCLI.log 2>&1 
$PathToCLI get  sdks -a --verbose > PLCNCLI.log 2>&1 

#### Create Empty Project -----------------------------------------------------------
echo "#### Create Empty Project-----------------------------------------------------------" > PLCNCLI.log 2>&1 
$PathToCLI new project -n $projectName -o $build -c dummy_C -p dummy_P --verbose > PLCNCLI.log 2>&1 

#### Check Project content------------------------------------------------------------ 
echo "#### Check Project content-----------------------------------------------------------" > PLCNCLI.log 2>&1 
echo -e "\n Lists all components of a project.\n " > PLCNCLI.log 2>&1 
$PathToCLI get components -p $build --verbose > PLCNCLI.log 2>&1 
echo -e "\n Lists all programs of a project.\n" > PLCNCLI.log 2>&1 
$PathToCLI get programs -p $build --verbose > PLCNCLI.log 2>&1 

#### remove Project content----------------------------------------------------------
echo "#### remove Project content-----------------------------------------------------------" > PLCNCLI.log 2>&1 
$PathToCLI delete program -p $build -n dummy_P -c dummy_C --verbose > PLCNCLI.log 2>&1 
$PathToCLI delete component -p $build -n dummy_C --verbose > PLCNCLI.log 2>&1 

#### Add Targets to Project ------------------------------------------------------------ 
echo "#### Add Targets to Project-----------------------------------------------------------" > PLCNCLI.log 2>&1 
#-n, --name       Required. The target to be added or removed.
#  -v, --version    The version of the target to be added or removed.
#  -a, --add        Indicates that the target should be added to existing targets.
#  -r, --remove     Indicates that the target should be removed from existing targets.
#  -p, --path       Directory where the .proj file is located.
#  --verbose        Enables verbose output.
#  --help           Display this help screen.

$PathToCLI set target --path $build --name $targetName --version $targetVersion --add --verbose > PLCNCLI.log 2>&1 
$PathToCLI get targets --path $build > PLCNCLI.log 2>&1 
