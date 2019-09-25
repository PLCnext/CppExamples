#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
OLD=$IFS
IFS=$'\n'
CI_HARDWARE=( $( plcncli get targets | grep -oPe [[:alpha:]]+[[:digit:]]+[[:alpha:]]?) )
CI_TARGETS=( $( plcncli get targets | grep -oPe '(?<=,)[^,]*\(*\)' ) )
CI_ARPVERSION=( $( plcncli get targets | grep -oPe '(?<=\().+?(?=\))' ) )
CI_VERSION=( $( plcncli get targets | grep -oPe  [0-9]+[.][0-9]+[.][0-9]+[.][0-9]+) )
CI_TOOLCHAINS=($(plcncli get sdks | grep -oPe [[:blank:]]?[/][[:alnum:][:blank:][:punct:]]*[[:blank:]]?))
IFS=$OLD
#
#
#