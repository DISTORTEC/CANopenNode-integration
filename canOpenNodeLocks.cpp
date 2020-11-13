/**
 * \file
 * \brief CANopenNode locks
 *
 * \author Copyright (C) 2020 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "CO_driver_target.h"

#include "distortos/assert.h"
#include "distortos/Mutex.hpp"

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// mutex for serializing access to CO_errorReport() and CO_errorReset()
distortos::Mutex emergencyMutex {distortos::Mutex::Protocol::priorityInheritance};

/// mutex for serializing access to object dictionary
distortos::Mutex objectDictionaryMutex {distortos::Mutex::Type::recursive,
		distortos::Mutex::Protocol::priorityInheritance};

/// mutex for serializing access to CO_CANsend() and CO_CANclearPendingSyncPDOs()
distortos::Mutex sendMutex {distortos::Mutex::Protocol::priorityInheritance};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void canOpenNodeLockEmergency()
{
	const auto ret = emergencyMutex.lock();
	assert(ret == 0);
}

void canOpenNodeLockObjectDictionary()
{
	const auto ret = objectDictionaryMutex.lock();
	assert(ret == 0);
}

void canOpenNodeLockSend()
{
	const auto ret = sendMutex.lock();
	assert(ret == 0);
}

void canOpenNodeUnlockEmergency()
{
	const auto ret = emergencyMutex.unlock();
	assert(ret == 0);
}

void canOpenNodeUnlockObjectDictionary()
{
	const auto ret = objectDictionaryMutex.unlock();
	assert(ret == 0);
}

void canOpenNodeUnlockSend()
{
	const auto ret = sendMutex.unlock();
	assert(ret == 0);
}
