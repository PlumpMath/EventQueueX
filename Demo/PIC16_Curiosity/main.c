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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "eqx.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static event_t blinkEvtQueue[10];

/*******************************************************************************
 * Code
 ******************************************************************************/
void blinking(event_t event)
{
    if (0U != event.signal)
    {
        IO_RA5_Toggle();
    }
}

void TMR0_IrqHandler(void)
{
    IO_RA2_Toggle();
    EQX_PostEvent(0, 1U, 0);
}

void EQX_Start(void)
{
    TMR0_Initialize();
    TMR0_SetInterruptHandler(TMR0_IrqHandler);

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
}

void main(void)
{
    SYSTEM_Initialize();

    IO_RA1_SetLow();
    IO_RA2_SetLow();
    IO_RA5_SetLow();
    IO_RC5_SetLow();

    EQX_Init();
    EQX_CreateTask(blinking, 0U, blinkEvtQueue,
                   sizeof(blinkEvtQueue)/sizeof(blinkEvtQueue[0]),
                   0U, 0U);

    /* Give flow control to scheduler. */
    EQX_Run();
}

/******************************************************************************
 * EOF
 *****************************************************************************/
