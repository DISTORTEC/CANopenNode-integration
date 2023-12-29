/**
 * \file
 * \brief CANopenNode locks
 *
 * \author Copyright (C) 2020-2023 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "CO_driver_target.h"

#include <cassert>

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void canOpenNodeLockEmergency(CO_CANmodule_t* const canModule)
{
	const auto ret = distortos_Mutex_lock(&canModule->emergencyLock);
	assert(ret == 0);
}

void canOpenNodeLockObjectDictionary(CO_CANmodule_t* const canModule)
{
	const auto ret = distortos_Mutex_lock(&canModule->objectDictionaryLock);
	assert(ret == 0);
}

void canOpenNodeLockSend(CO_CANmodule_t* const canModule)
{
	const auto ret = distortos_Mutex_lock(&canModule->sendLock);
	assert(ret == 0);
}

void canOpenNodeUnlockEmergency(CO_CANmodule_t* const canModule)
{
	const auto ret = distortos_Mutex_unlock(&canModule->emergencyLock);
	assert(ret == 0);
}

void canOpenNodeUnlockObjectDictionary(CO_CANmodule_t* const canModule)
{
	const auto ret = distortos_Mutex_unlock(&canModule->objectDictionaryLock);
	assert(ret == 0);
}

void canOpenNodeUnlockSend(CO_CANmodule_t* const canModule)
{
	const auto ret = distortos_Mutex_unlock(&canModule->sendLock);
	assert(ret == 0);
}
