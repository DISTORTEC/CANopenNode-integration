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
if(NOT EXISTS "${CANOPENNODE_DIRECTORY}/CMakeLists.txt")
	message(SEND_ERROR "Path to CANopenNode directory - CANOPENNODE_DIRECTORY = ${CANOPENNODE_DIRECTORY} - does not "
			"contain CMakeLists.txt")
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

add_subdirectory("${CANOPENNODE_DIRECTORY}" CANopenNode)

add_library(CANopenNode-object-library OBJECT
		canOpenNodeLocks.cpp)
target_include_directories(CANopenNode-object-library PRIVATE
		$<TARGET_PROPERTY:CANopenNode,INTERFACE_INCLUDE_DIRECTORIES>)

target_include_directories(CANopenNode PUBLIC
		include
		${CANOPENNODE_CONFIGURATION_H_DIRECTORY}
		${CANOPENNODE_CO_OD_H_DIRECTORY})
target_sources(CANopenNode INTERFACE
		$<TARGET_OBJECTS:CANopenNode-object-library>)
