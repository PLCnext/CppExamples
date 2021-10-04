cmake_minimum_required(VERSION 3.13)

project(ComponentPorts)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

################# create target #######################################################

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS src/*.h src/*.hpp src/*.hxx intermediate/code/*.h intermediate/code/*.hpp intermediate/code/*.hxx)
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS src/*.cpp intermediate/code/*.cpp)
add_library(ComponentPorts SHARED ${Headers} ${Sources})

#######################################################################################

################# project include-paths ###############################################

target_include_directories(ComponentPorts
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intermediate/code>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

#######################################################################################

################# include arp cmake module path #######################################

list(INSERT CMAKE_MODULE_PATH 0 "${ARP_TOOLCHAIN_CMAKE_MODULE_PATH}")

#######################################################################################

################# set RPATH to ORIGIN for third party libraries #######################
# Only by setting this is it possible to use libraries which are not already          #
# installed in the default install locations on the target.                           #
#######################################################################################

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" AND NOT "$ENV{SHELL}" MATCHES ".*[\/\\]bash($|.exe$)")
    # With Windows there is a known issue with CMake: https://gitlab.kitware.com/cmake/cmake/-/issues/21291
    # This is currently the only way to set the RPATH to $ORIGIN in Windows
    target_link_libraries(ComponentPorts PRIVATE "-Wl,-rpath,\$$ORIGIN")
else()
    set_target_properties(ComponentPorts PROPERTIES INSTALL_RPATH $ORIGIN)
endif()

#######################################################################################

################# set link options ####################################################
# WARNING: Without --no-undefined the linker will not check, whether all necessary    #
#          libraries are linked. When a library which is necessary is not linked,     #
#          the firmware will crash and there will be NO indication why it crashed.    #
#######################################################################################

target_link_options(ComponentPorts PRIVATE LINKER:--no-undefined)

#######################################################################################

################# add link targets ####################################################

find_package(ArpDevice REQUIRED)
find_package(ArpProgramming REQUIRED)

target_link_libraries(ComponentPorts PRIVATE ArpDevice ArpProgramming)

#######################################################################################

################# install ############################################################

string(REGEX REPLACE "^.*\\(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+).*$" "\\1" _ARP_SHORT_DEVICE_VERSION ${ARP_DEVICE_VERSION})
install(TARGETS ComponentPorts
    LIBRARY DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/lib
    ARCHIVE DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/lib
    RUNTIME DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/bin)
unset(_ARP_SHORT_DEVICE_VERSION)

#######################################################################################