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
#include <vxWorks.h>
#include <taskLib.h>
#include <stdio.h>
#include <stdlib.h>

/* defines */
#define ZERO           0

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

#endif /* __INCglobalData */