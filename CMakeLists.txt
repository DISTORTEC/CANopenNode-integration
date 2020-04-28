#
# file: CMakeLists.txt
#
# This is the main CMakeLists.txt for CANopenNode integration with distortos
#
# author: Copyright (C) 2020 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.8)
project(CANopenNode-integration)

if(NOT DEFINED CANOPENNODE_DIRECTORY)
	message(SEND_ERROR "Variable with path to CANopenNode directory - CANOPENNODE_DIRECTORY - is not defined")
endif()
if(NOT IS_DIRECTORY "${CANOPENNODE_DIRECTORY}")
	message(SEND_ERROR "Path to CANopenNode directory - CANOPENNODE_DIRECTORY = ${CANOPENNODE_DIRECTORY} - is not "
			"valid")
endif()
if(NOT EXISTS "${CANOPENNODE_DIRECTORY}/CANopen.c")
	message(SEND_ERROR "Path to CANopenNode directory - CANOPENNODE_DIRECTORY = ${CANOPENNODE_DIRECTORY} - does not "
			"contain CANopenNode sources")
endif()

if(NOT DEFINED CANOPENNODE_CONFIGURATION_H_DIRECTORY)
	message(SEND_ERROR "Variable with path to CANopenNode-configuration.h - CANOPENNODE_CONFIGURATION_H_DIRECTORY - is "
			"not defined")
endif()
if(NOT IS_DIRECTORY "${CANOPENNODE_CONFIGURATION_H_DIRECTORY}")
	message(SEND_ERROR "Path to CANopenNode-configuration.h - "
			"CANOPENNODE_CONFIGURATION_H_DIRECTORY = ${CANOPENNODE_CONFIGURATION_H_DIRECTORY} - is not valid")
endif()
if(NOT EXISTS "${CANOPENNODE_CONFIGURATION_H_DIRECTORY}/CANopenNode-configuration.h")
	message(SEND_ERROR "Path to CANopenNode-configuration.h - "
			"CANOPENNODE_CONFIGURATION_H_DIRECTORY = ${CANOPENNODE_CONFIGURATION_H_DIRECTORY} - does not contain "
			"CANopenNode-configuration.h")
endif()

if(NOT DEFINED CANOPENNODE_CO_OD_H_DIRECTORY)
	message(SEND_ERROR "Variable with path to CO_OD.h - CANOPENNODE_CO_OD_H_DIRECTORY - is not defined")
endif()
if(NOT IS_DIRECTORY "${CANOPENNODE_CO_OD_H_DIRECTORY}")
	message(SEND_ERROR "Path to CO_OD.h - CANOPENNODE_CO_OD_H_DIRECTORY = ${CANOPENNODE_CO_OD_H_DIRECTORY} - is not "
			"valid")
endif()
if(NOT EXISTS "${CANOPENNODE_CO_OD_H_DIRECTORY}/CO_OD.h")
	message(SEND_ERROR "Path to CO_OD.h - CANOPENNODE_CO_OD_H_DIRECTORY = ${CANOPENNODE_CO_OD_H_DIRECTORY} - does not "
			"contain CO_OD.h")
endif()

add_library(CANopenNode STATIC
		${CANOPENNODE_DIRECTORY}/301/CO_Emergency.c
		${CANOPENNODE_DIRECTORY}/301/CO_HBconsumer.c
		${CANOPENNODE_DIRECTORY}/301/CO_NMT_Heartbeat.c
		${CANOPENNODE_DIRECTORY}/301/CO_PDO.c
		${CANOPENNODE_DIRECTORY}/301/CO_SDOclient.c
		${CANOPENNODE_DIRECTORY}/301/CO_SDOserver.c
		${CANOPENNODE_DIRECTORY}/301/CO_SYNC.c
		${CANOPENNODE_DIRECTORY}/301/CO_TIME.c
		${CANOPENNODE_DIRECTORY}/301/crc16-ccitt.c
		${CANOPENNODE_DIRECTORY}/305/CO_LSSmaster.c
		${CANOPENNODE_DIRECTORY}/305/CO_LSSslave.c
		${CANOPENNODE_DIRECTORY}/CANopen.c
		${CANOPENNODE_DIRECTORY}/extra/CO_trace.c)
target_compile_options(CANopenNode PRIVATE
		-Wno-type-limits
		-Wno-unused-parameter)
target_include_directories(CANopenNode PUBLIC
		${CANOPENNODE_DIRECTORY}
		include
		${CANOPENNODE_CONFIGURATION_H_DIRECTORY}
		${CANOPENNODE_CO_OD_H_DIRECTORY})

add_library(CANopenNode-object-library OBJECT
		canOpenNodeLocks.cpp)
target_include_directories(CANopenNode-object-library PRIVATE
		$<TARGET_PROPERTY:CANopenNode,INTERFACE_INCLUDE_DIRECTORIES>)

target_sources(CANopenNode INTERFACE
		$<TARGET_OBJECTS:CANopenNode-object-library>)
