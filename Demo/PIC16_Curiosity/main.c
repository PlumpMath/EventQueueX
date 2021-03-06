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
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "eqx.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static event_t blink1EvtQueue[10];
static event_t blink2EvtQueue[10];

/*******************************************************************************
 * Code
 ******************************************************************************/
void TMR0_IrqHandler(void)
{
    EQX_PostEvent(0, 1U, 0);
}

void blinking1(event_t event)
{
    if (0U != event.signal)
    {
        IO_RA2_Toggle();
        EQX_PostEvent(1U, 1U, 0);
    }
}

void blinking2(event_t event)
{
    if (0U != event.signal)
    {
        IO_RA5_Toggle();
        if (ADC_IsConversionDone())
        {
            printf("ADC Result:%d\r\n", ADC_GetConversionResult());
        }
    }
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

void EQX_GoToSleep(void)
{
}

void main(void)
{
    SYSTEM_Initialize();

    ADC_Initialize();
    ADC_SelectChannel(channel_AN4);
    ADC_StartConversion();
    EUSART_Initialize();

    EQX_Init();
    EQX_CreateTask(blinking1, 0U, blink1EvtQueue,
                   sizeof(blink1EvtQueue)/sizeof(blink1EvtQueue[0]),
                   0U, 0U);
    EQX_CreateTask(blinking2, 1U, blink2EvtQueue,
                   sizeof(blink2EvtQueue)/sizeof(blink2EvtQueue[0]),
                   0U, 0U);

    /* Give flow control to scheduler. */
    EQX_Run();
}

/******************************************************************************
 * EOF
 *****************************************************************************/
