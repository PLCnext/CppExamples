#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
# $DIR/build-forOneTarget.sh  -p ${BUILD_PROJECTNAME} -a "${BUILD_ARPVERSION[$i]}" -h "${BUILD_HARDWARE[$i]}" -t "${BUILDTYPE}"
while getopts p:a:h:t option
do
case "${option}"
in
p) BUILD_PROJECTNAME=${OPTARG};;
a) BUILD_ARPVERSION=${OPTARG};;
h) BUILD_HARDWARE=${OPTARG};;
t) BUILD_BUILDTYPE=${OPTARG};;
esac
done

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
mkdir -p $DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION}/${BUILD_PROJECTNAME}
echo "###############"
echo "###############"
set -x
echo "Build"
plcncli build \
            --path $DIR/../build/${BUILD_PROJECTNAME} \
            --buildtype "RELEASE" \
            --configure \
            --target ${BUILD_HARDWARE},${BUILD_ARPVERSION} \
            --output $DIR/../build/${BUILD_PROJECTNAME}/bin/${BUILD_HARDWARE}_${BUILD_ARPVERSION}/ \
            --verbose |& tee $DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION}/BUILD_${BUILD_PROJECTNAME}.log
mkdir -p $DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION}

cp "$DIR/../build/${BUILD_PROJECTNAME}/bin/${BUILD_HARDWARE}_${BUILD_ARPVERSION}/RELEASE/lib/lib${BUILD_PROJECTNAME}.so" "$DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION}/lib${BUILD_PROJECTNAME}.so"
echo "###############"
echo "###############"
plcncli set target --help
echo "###############"
echo "###############"
echo " Add sucessfully build target to project."
if [[ -n $(find $DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION} -name "lib${BUILD_PROJECTNAME}.so") ]]
        then
            plcncli set target \
                --name ${BUILD_HARDWARE} \
                --version ${BUILD_ARPVERSION} \
                --add \
                --path  $DIR/../build/$BUILD_PROJECTNAME \
                --verbose |& tee $DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION}/SetTarget_${BUILD_PROJECTNAME}.log
            echo "Sucessfully build ${BUILD_HARDWARE}_${BUILD_ARPVERSION}"
        else
            rm -r $DIR/../deploy/${BUILD_HARDWARE}_${BUILD_ARPVERSION}
            echo "Failed to build ${BUILD_HARDWARE}_${BUILD_ARPVERSION}"
fi

set +x



