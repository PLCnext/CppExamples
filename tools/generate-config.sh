#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
while getopts p: option
        do case "${option}" in
        p) PROJECTNAME=${OPTARG};;
        esac
done

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
echo "###############"
echo "###############"
plcncli generate config --help
echo "###############"
echo "###############"
echo "generate Config"
plcncli generate config \
        --path $DIR/../build/$PROJECTNAME \
        --output  $DIR/../build/$PROJECTNAME/intermediate \
        --verbose

