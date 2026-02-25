/* globalData.h - global data definitions */
/*
* Copyright (c) 2026 Trenser Technology Solutions (P) Ltd
*
* The right to copy, distribute, modify, or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/
/*
modification history --------------------
07feb26, Updated coding standards
*/
#ifndef __INCglobalData
#define __INCglobalData

/* includes */
#ifndef UNIT_TEST
#include <vxWorks.h>
#include <taskLib.h>
#endif
#include <stdio.h>
#include <stdlib.h>

/* defines */
#define ZERO           0
#define TEMP_LOWERBOUND        -20
#define TEMP_UPPERBOUND        100
#define MIN_THRESHOLD          -10
#define MAX_THRESHOLD           70

/* typedefs */
typedef enum
{
    STATUS_SUCCESS = ZERO,
    STATUS_INVALID_DATA,
    STATUS_READ_ERROR,
    STATUS_SUCCESS_READ,
    STATUS_THRESHOLD_VIOLATION,
    STATUS_BOUNDARY_VIOLATION
} STATE_STATUS;

/* function declarations */
STATE_STATUS temperatureTask(void);

#endif /* __INCglobalData */