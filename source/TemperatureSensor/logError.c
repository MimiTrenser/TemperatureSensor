/* main.c - main function */
/*
* Copyright (c) 2026 Trenser Technology Solutions (P) Ltd
*
* The right to copy, distribute, modify, or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/
/*
modification history -------------------
07feb26, Updated coding standards
*/
/*
DESCRIPTION
This module contains the main function that continuously reads temperature data,
 evaluates it, and logs any errors encountered during the process.
- logError: Logs any error messages encountered during the temperature 
reading and evaluation process
...
INCLUDE FILES: globalData.h
*/

/* includes */
#include "globalData.h"
#include "logError.h"

/* defines */

/*******************************************************************************
*
* logAlarmStatus - This function logs error messages
*
* DESCRIPTION
* The function [logAlarmStatus] logs error if temperature value is out of 
* operating temperature range or exceeds upper/lower threshold.
*
* PARAMETERS
* \is
* \i <*message>
* [in] A pointer to a string representing the error message to be logged.
* \ie
*
* GLOBALS:
* \is
*
* \i N/A
* \ie
*
* RETURNS:
* \is
* \i <STATUS_SUCCESS>
* when the error message is successfully logged.
*
* \i <STATUS_INVALID_DATA>
* when the pointer to error message is NULL.
*
* \ie
*
* ERRNO:
* \is
* \i N/A
*
* \i N/A
* \ie
*
* SEE ALSO:
* main.c, temperatureSensor.c, evaluateTemperature.c
*
* \INTERNAL
* This function logs error if temperature value is out of operating temperature 
* range or exceeds upper/lower threshold values.If violation is found return the
* error status
*
*/
STATE_STATUS logAlarmStatus(const char *message)
{
    STATE_STATUS status = STATUS_SUCCESS;

    if (message == NULL)
    {
        status = STATUS_INVALID_DATA;            /* req: logAlarmStatus_LLR_1 */
    }
    else
    {
        printf("ERROR: %s\n", message);
        status = STATUS_SUCCESS;                 /* req: logAlarmStatus_LLR_2 */
    }

    return status;
}