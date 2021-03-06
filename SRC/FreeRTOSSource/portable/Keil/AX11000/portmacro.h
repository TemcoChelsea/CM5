/* 
	FreeRTOS V2.6.0 - Copyright (C) 2003 - 2005 Richard Barry.

	This file is part of the FreeRTOS distribution.

	FreeRTOS is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS, without being obliged to provide
	the source code for any proprietary components.  See the licensing section 
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************
	See http://www.FreeRTOS.org for documentation, latest information, license 
	and contact details.  Please ensure to read the configuration and relevant 
	port sections of the online documentation.
	***************************************************************************
*/

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* Include the definitions file for the 8052.  This must be the file
supplied with the distribution. */
#include "reg80390.h"

#include "mstimer_cfg.h"

/*-----------------------------------------------------------
 * Port specific definitions for the 390 port.
 *----------------------------------------------------------*/
extern idata unsigned char STACK_START[1];
#define portSTACK_START			( STACK_START )

#define portUSE_PREEMPTION		1
#define portTICK_RATE_HZ		( ( portTickType ) 1000 )
#define portTICK_RATE_MS		( ( unsigned portLONG ) 1000 / portTICK_RATE_HZ )
#define portMAX_PRIORITIES		( ( unsigned portSHORT ) 15 )
#define portMINIMAL_STACK_SIZE	( ( unsigned portSHORT ) 512 - ( unsigned portSHORT ) portSTACK_START )
#define portTOTAL_HEAP_SIZE		( ( unsigned portSHORT ) ( 10 * 1024 ))

/* Set the following definitions to 1 to include the component, or zero
to exclude the component. */

/* Include/exclude the stated API function. */
#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_ucTaskPriorityGet		0
#define INCLUDE_vTaskDelete				0
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* Timer Tick Hook */
#define configUSE_TICK_HOOK				0

/* Use/don't use the trace visualisation. */
#define USE_TRACE_FACILITY				0

/* 
 * The tick count (and times defined in tick count units) can be either a 16bit
 * or a 32 bit value.  See documentation on http://www.FreeRTOS.org to decide
 * which to use.
 */
#define USE_16_BIT_TICKS	0

/*-----------------------------------------------------------
 * Do not modify anything below here. 
 *----------------------------------------------------------*/

#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		float
#define portLONG		long
#define portSHORT		short

#define INT8U           unsigned char
#define INT16U			unsigned short 
#define INT32U			unsigned long

#define portSTACK_TYPE	unsigned portCHAR
#define portBYTE_ALIGNMENT			1

#if( USE_16_BIT_TICKS == 1 )
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif


/* As an undocumented keyword of keil c. __asm is supported in Keil C v6.20.
. No other means to define assemble language code in a macro, I have to use it here. If your compiler does not support __asm, use method 1 or 3 then. */
/* A2 AF MOV C, EA*/
/* C2 AF CLR EA   */
/* C0 D0 PUSH PSW */
#define  portENTER_CRITICAL()    __asm DB 0A2H, 0AFH, 0C2H, 0AFH, 0C0H, 0D0H

/* D0 D0 POP PSW   */
/* 92 AF MOV EA, C */
#define  portEXIT_CRITICAL()     __asm DB 0D0H, 0D0H, 092H, 0AFH

/*-----------------------------------------------------------*/

#define portDISABLE_INTERRUPTS()	EA = 0;
#define portENABLE_INTERRUPTS()		EA = 1;

/*-----------------------------------------------------------*/

#define portSTACK_GROWTH			( -1 )


/*
 * Prototype for manual context switch function.
 */

extern void vPortYield( void ) reentrant;
#define portYIELD	vPortYield

#define inline
//#if 0
//void vSerialISR( void ) interrupt 4;

/* All ISR's must have a prototype in the file containing main. */
//#if (portUSE_PREEMPTION == 0)
//	void vTimer2ISR( void ) interrupt 5;
//#else
//	void vTimer2ISR( void ) interrupt 5;
//#endif
//#endif

#endif /* PORTMACRO_H */


