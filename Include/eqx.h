/*
 *  Copyright 2016 Wang Ge
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _EQX_H_
#define _EQX_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "eqx_port.h"
#include "event_queue.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef void (*EQX_Task)(event_t event);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void EQX_Init(void);
void EQX_Run(void);
bool EQX_CreateTask(EQX_Task task, uint8_t prio, event_t *buffer,
                    uint8_t size, uint8_t signal, uint8_t parameter);
bool EQX_DeleteTask(uint8_t prio);
bool EQX_PostEvent(uint8_t prio, uint8_t signal, uint8_t parameter);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _EQX_H_ */

/******************************************************************************
 * EOF
 *****************************************************************************/
