#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
while getopts p:t: option
do
case "${option}"
in
p) PROJECTNAME=${OPTARG};;
t) TARGETS=${OPTARG};;
esac
done

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

#  -p, --path               Directory where the plcnext.proj file is located.
#  -m, --metapath           Directory where the library meta files are located.
#  -c, --compilationpath    Path to the compilation output file(s), if different from <projectname>/bin.
#  -o, --output             Output directory for the library. The directory can 
#                           be either absolute or relative to the project 
#                           directory.
#  -i, --id                 The GUID for the library.
#  -t, --target             List of targets to add to library: 
#                           <target>[,<version>[,<path to compilation file>]].
#  -s, --sources            The path of the source directories separated by ','.
#                           Default is the 'src' directory if such a directory 
#                           exists. If not, the directory defined with the 
#                           '--path' option is used. Relative paths are relative
#                           to the directory defined with the '--path' option. 
#                           If any path contains a ' ' quotation marks should be
#                           used around all paths, e.g. "path1,path With 
#                           Space,path2".

for i in $(ls -d ${DIR}/../deploy/*/); do SourceList+=${i}; SourceList+=","; done

source $DIR/before-script.sh

containsElement () {
    local e; match="$1"; 
    shift;
    for e; do [[ "$e" == "$match" ]] && return 0; done; 
    return 1;
    }
echo "###############"
echo "###############"

echo "###############"
echo "###############"
echo "TRY Build All: ${TARGETS[@]} Toolchains: ${#CI_HARDWARE[@]}";
for ((i=0; i<${#CI_HARDWARE[@]}; i++ ));
do
    echo -e "V:${CI_VERSION[$i]}  HW:${CI_HARDWARE[$i]} ";
        if $(containsElement "${CI_HARDWARE[$i]}" ${TARGETS[@]})  
    then
    TargetString+="${CI_HARDWARE[$i]},${CI_VERSION[$i]},deploy/${CI_HARDWARE[$i]}_${CI_VERSION[$i]}/lib${PROJECTNAME}.so "
    fi
done
TargetStringTrimmed="$(echo -e "${TargetString}" | xargs)"
echo "Target List: $TargetString"
echo "###############"
echo "###############"
plcncli generate library --help
echo "###############"
echo "###############"
set -x
plcncli generate library \
--path "$DIR/../build/${PROJECTNAME}" \
--output "$DIR/../deploy" \
--target "${TargetStringTrimmed}" \
--metapath "$DIR/../build/${PROJECTNAME}/intermediate" \
--verbose |& tee $DIR/../deploy/${PROJECTNAME}_GenerateLib.log
