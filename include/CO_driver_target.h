/**
 * \file
 * \brief CANopenNode integration header
 *
 * \author Copyright (C) 2020 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CANOPENNODE_INTEGRATION_INCLUDE_CO_DRIVER_TARGET_H_
#define CANOPENNODE_INTEGRATION_INCLUDE_CO_DRIVER_TARGET_H_

#include "CANopenNode-configuration.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Locks critical section for CO_errorReport() and CO_errorReset().
 */

void canOpenNodeLockEmergency(void);

/**
 * \brief Locks critical section for accessing object dictionary.
 */

void canOpenNodeLockObjectDictionary(void);

/**
 * \brief Locks critical section for CO_CANsend() and CO_CANclearPendingSyncPDOs().
 */

void canOpenNodeLockSend(void);

/**
 * \brief Unlocks critical section for CO_errorReport() and CO_errorReset().
 */

void canOpenNodeUnlockEmergency(void);

/**
 * \brief Unlocks critical section for accessing object dictionary.
 */

void canOpenNodeUnlockObjectDictionary(void);

/**
 * \brief Unlocks critical section for CO_CANsend() and CO_CANclearPendingSyncPDOs().
 */

void canOpenNodeUnlockSend(void);

/*---------------------------------------------------------------------------------------------------------------------+
| global defines
+---------------------------------------------------------------------------------------------------------------------*/

/// configure endianness used by CANopenNode
#define CO_LITTLE_ENDIAN

/// swap bytes in a 16-bit variable on big-endian, dummy for little-endian
#define CO_SWAP_16(x)						(x)

/// swap bytes in a 32-bit variable on big-endian, dummy for little-endian
#define CO_SWAP_32(x)						(x)

/// swap bytes in a 64-bit variable on big-endian, dummy for little-endian
#define CO_SWAP_64(x)						(x)

/**
 * \brief Locks critical section for CO_CANsend() and CO_CANclearPendingSyncPDOs().
 */

#define CO_LOCK_CAN_SEND()					canOpenNodeLockSend()

/**
 * \brief Locks critical section for CO_errorReport() and CO_errorReset().
 */

#define CO_LOCK_EMCY()						canOpenNodeLockEmergency()

/**
 * \brief Locks critical section for accessing object dictionary.
 */

#define CO_LOCK_OD()						canOpenNodeLockObjectDictionary()

/**
 * \brief Unlocks critical section for CO_CANsend() and CO_CANclearPendingSyncPDOs().
 */

#define CO_UNLOCK_CAN_SEND()				canOpenNodeUnlockSend()

/**
 * \brief Unlocks critical section for CO_errorReport() and CO_errorReset().
 */

#define CO_UNLOCK_EMCY()					canOpenNodeUnlockEmergency()

/**
 * \brief Unlocks critical section for accessing object dictionary.
 */

#define CO_UNLOCK_OD()						canOpenNodeUnlockObjectDictionary()

/**
 * \brief Checks whether new message has arrived.
 *
 * \param [in] rxNew is the "new" flag of received message
 *
 * \return true if new message has arrived, false otherwise
 */

#define CO_FLAG_READ(rxNew)					((uintptr_t)rxNew != 0)

/**
 * \brief Marks message as "new".
 *
 * \param [in] rxNew is the "new" flag of received message
 */

#define CO_FLAG_SET(rxNew)					do { __sync_synchronize(); rxNew = (void*)1; } while (0)

/**
 * \brief Marks message as "processed"
 *
 * \param [in] rxNew is the "new" flag of received message
 */

#define CO_FLAG_CLEAR(rxNew)				do { __sync_synchronize(); rxNew = (void*)0; } while (0)

/*---------------------------------------------------------------------------------------------------------------------+
| global types
+---------------------------------------------------------------------------------------------------------------------*/

/** type alias for bool */
typedef bool bool_t;

/** type alias for element of CANopen "visible string" type */
typedef char char_t;

/** type alias for CANopen "domain" type */
typedef unsigned char domain_t;

/** type alias for 32-bit wide floating point value */
typedef float float32_t;

/** type alias for 64-bit wide floating point value */
typedef double float64_t;

/** type alias for element of CANopen "octet string" type */
typedef unsigned char oChar_t;

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* CANOPENNODE_INTEGRATION_INCLUDE_CO_DRIVER_TARGET_H_ */
