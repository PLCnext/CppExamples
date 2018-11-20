cmake_minimum_required(VERSION 3.12)

project(ProgramComponentInteraction)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

################# create target #######################################################

set (WILDCARD_SOURCE *.cpp)
set (WILDCARD_HEADER *.h *.hpp *.hxx)

file(GLOB_RECURSE Headers src/${WILDCARD_HEADER} intermediate/Code/${WILDCARD_HEADER})
file(GLOB_RECURSE Sources src/${WILDCARD_SOURCE} intermediate/Code/${WILDCARD_SOURCE})
add_library(ProgramComponentInteraction SHARED ${Headers} ${Sources})

#######################################################################################

################# project include-paths ###############################################

target_include_directories(ProgramComponentInteraction
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intermediate/Code>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

#######################################################################################

list(INSERT CMAKE_MODULE_PATH 0 "${ARP_TOOLCHAIN_CMAKE_MODULE_PATH}")

################# add link targets ####################################################

find_package(ArpDevice REQUIRED)
find_package(ArpProgramming REQUIRED)

target_link_libraries(ProgramComponentInteraction PRIVATE ArpDevice ArpProgramming)

#######################################################################################

################# install ############################################################

install(TARGETS ProgramComponentInteraction
    LIBRARY DESTINATION ${ARP_DEVICE}_V${ARP_DEVICE_VERSION}/$<CONFIG>/lib
    ARCHIVE DESTINATION ${ARP_DEVICE}_V${ARP_DEVICE_VERSION}/$<CONFIG>/lib
    RUNTIME DESTINATION ${ARP_DEVICE}_V${ARP_DEVICE_VERSION}/$<CONFIG>/bin)

#######################################################################################
