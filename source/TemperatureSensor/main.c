/* main.c - main function */
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
/*
DESCRIPTION
This module contains the main function that continuously reads temperature data,
 evaluates it, and logs any errors encountered during the process. The main 
 function uses the following functions defined in globalData.h:
- getTemperature: Reads the temperature data and returns a status indicating 
success or failure.
- evaluateTemperature: Evaluates the temperature data against predefined 
thresholds and returns a status indicating the result of the evaluation.
- logError: Logs any error messages encountered during the temperature 
reading and evaluation process
...
INCLUDE FILES: globalData.h
*/

/* includes */
#include "globalData.h"
#include "evaluateData.h"
#include "temperatureSensor.h"
#include "logError.h"

/* defines */
#define DELAY        100
#define ZERO         0
/*******************************************************************************
*
* main - This function reads temperature data, evaluates it, and logs 
any errors encountered.
*
* DESCRIPTION
* This function [main] reads temperature data, evaluates it against predefined 
thresholds, and logs any errors encountered during the process.
*
* PARAMETERS
* \is
* \i N/A
* \ie
*
* GLOBALS:
* \is
* \i
* [in] N/A
* \ie
*
* RETURNS:
* \is
* \i <SUCCESS>
* when the temperature data is read and evaluated successfully
* 
* \ie
* ERRNO:
* \is
* \i
* N/A
* \ie
*
* SEE ALSO:
* N/A
*
* \INTERNAL
* This function reads temperature data, evaluates it against predefined 
thresholds, and logs any errors encountered during the process.
*/

int main(void)
{
    int8_t temperature = ZERO;
    STATE_STATUS status;

    while(1)
    {
        status = getTemperature(&temperature);

        if (status == STATUS_SUCCESS_READ)
        {
            status = evaluateTemperature(&temperature);

            if (status == STATUS_SUCCESS)
            {
                printf("Evaluation successful\n");
            }
            else if (status == STATUS_THRESHOLD_VIOLATION)
            {
                logError("Temperature threshold violation");
            }
            else if (status == STATUS_BOUNDARY_VIOLATION)
            {
                logError("Temperature boundary violation");
            }
            else
            {
                logError("Temperature evaluation failed");
            }
        }
        else
        {
            logError("Failed to read temperature");
        }
        taskDelay(DELAY);
    }
    return STATUS_SUCCESS;
}

