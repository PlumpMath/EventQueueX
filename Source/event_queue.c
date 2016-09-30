/*
 * Copyright (C) 2016 Wang Ge
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "event_queue.h"
#include "port.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void EvtQueue_Init(event_queue_t *evtQueueHandle, event_t *buffer, uint8_t size)
{
	evtQueueHandle->buffer = buffer;
	evtQueueHandle->head = buffer;
	evtQueueHandle->tail = buffer;
	evtQueueHandle->size = size;
	evtQueueHandle->full = false;
}

bool EvtQueue_Push(event_queue_t *evtQueueHandle, event_t *event)
{
    ENTER_CRITICAL_SECTION();
	if (EvtQueue_IsFull(evtQueueHandle))
	{
        EXIT_CRITICAL_SECTION();

		return false;
	}

	*evtQueueHandle->tail = *event;
	evtQueueHandle->tail++;

	if (evtQueueHandle->tail == (evtQueueHandle->buffer + evtQueueHandle->size))
	{
		evtQueueHandle->tail = evtQueueHandle->buffer;
	}
    EXIT_CRITICAL_SECTION();

	return true;
}

bool EvtQueue_Pull(event_queue_t *evtQueueHandle, event_t *event)
{
    ENTER_CRITICAL_SECTION();
	if (EvtQueue_IsEmpty(evtQueueHandle))
	{
        EXIT_CRITICAL_SECTION();

		return false;
	}

	*event = *evtQueueHandle->head;
	evtQueueHandle->head++;

	if (evtQueueHandle->head == (evtQueueHandle->buffer + evtQueueHandle->size))
	{
		evtQueueHandle->head = evtQueueHandle->buffer;
	}
    EXIT_CRITICAL_SECTION();

	return true;
}

bool EvtQueue_IsFull(event_queue_t *evtQueueHandle)
{
	return ((evtQueueHandle->head == evtQueueHandle->tail) && (evtQueueHandle->full));
}

bool EvtQueue_IsEmpty(event_queue_t *evtQueueHandle)
{
	return ((evtQueueHandle->head == evtQueueHandle->tail) && (!evtQueueHandle->full));
}

/******************************************************************************
 * EOF
 *****************************************************************************/