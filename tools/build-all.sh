#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//

# $DIR/build-all.sh -p  ${PROJECTNAME}  -h ${BUILD_HARDWARE} -t "RELEASE"
while getopts p:h:t: option
do
case "${option}"
in
p) INPUT_PROJECTNAME=${OPTARG};;
h) INPUT_HARDWARE=(${OPTARG});;
t) INPUT_BUILDTYPE=${OPTARG};;
esac
done

echo Start Build All
# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

source $DIR/before-script.sh

containsElement () {
    local e; match="$1"; 
    shift;
    for e; do [[ "$e" == "$match" ]] && return 0; done; 
    return 1;
    }
echo "###############"
echo "###############"
plcncli build --help 
echo "###############"
echo "###############"
echo "TRY Build All: ${INPUT_HARDWARE[@]} Toolchains: ${#CI_HARDWARE[@]}";
for ((i=0; i<${#CI_HARDWARE[@]}; i++ ));
do
    echo -e "T: ${CI_TOOLCHAINS[$i]} \n V:${CI_VERSION[$i]} \n HW:${CI_HARDWARE[$i]} \n ";
        if $(containsElement "${CI_HARDWARE[$i]}" ${INPUT_HARDWARE[@]})  
    then
    echo "Build ${CI_HARDWARE[$i]}"
    $DIR/build-forOneTarget.sh  -p "${INPUT_PROJECTNAME}" \
                                -a "${CI_VERSION[$i]}" \
                                -h "${CI_HARDWARE[$i]}" \
                                -t "${INPUT_BUILDTYPE}"    
    fi
done;


