/* evaluateData.c - main function */
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
The function is responsible for evaluating the temperature data against 
predefined thresholds and boundaries. It checks if the temperature is within 
the acceptable range and logs any violations accordingly. The function uses the 
following functions defined in globalData.h:
- logError: Logs any error messages encountered during the evaluation process.
INCLUDE FILES: globalData.h
*/

/* includes */
#include "globalData.h"
#include "evaluateData.h"

/* defines */
#define TEMP_LOWERBOUND        -20
#define TEMP_UPPERBOUND        100
#define MIN_THRESHOLD          -10
#define MAX_THRESHOLD           70

/*******************************************************************************
*
* evaluateTemperature - This function evaluates temperature data against 
* thresholds and boundaries
*
* DESCRIPTION
* The function [evaluatetemperature] will compare acquired [pTemperarture] 
* value with required limits.Limits are [TEMP_LOWERBOUND],[TEMP_UPPERBOUND],
* [MIN_THRESHOLD] and [MAX_THRESHOLD] values.If violation is found return the 
* error status
*
* PARAMETERS
* \is
* \i <*pTemperature>
* [in] A pointer to an integer representing the temperature value to be 
* evaluated.
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
* \i <STATUS_INVALID_DATA>
* when the pointer to temperature data is NULL
*
* \i <STATUS_BOUNDARY_VIOLATION>
* when the temperature is outside the acceptable range
*
* \i <STATUS_THRESHOLD_VIOLATION>
* when the temperature is outside the predefined thresholds
*
* \i <STATUS_SUCCESS>
* when the temperature is within acceptable range and thresholds
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
* main.c, logError.c, temperatureSensor.c
*
* \INTERNAL
* This function evaluates the temperature data against predefined thresholds and
* boundaries. It checks if the temperature is within the acceptable range and 
* ogs any violations accordingly. The function uses the logError function 
* defined in globalData.h to log any error messages encountered during the 
* evaluation process.
*/

STATE_STATUS evaluateTemperature(const int8_t *pTemperature)
{
    STATE_STATUS status = STATUS_SUCCESS;

    if (pTemperature == NULL)
    {
        status = STATUS_INVALID_DATA;       /* req: evaluateTemperature_LLR_1 */
    }
    else
    {
        printf("Measured Temperature = %d\n", *pTemperature);

        if ((*pTemperature < TEMP_LOWERBOUND) || (*pTemperature > TEMP_UPPERBOUND))
        {
            status = STATUS_BOUNDARY_VIOLATION;/* req: evaluateTemperature_LLR_2 */
        }
        else if ((*pTemperature < MIN_THRESHOLD) || (*pTemperature > MAX_THRESHOLD))
        {
            status = STATUS_THRESHOLD_VIOLATION;/* req: evaluateTemperature_LLR_3 */
        }
        else
        {
            printf("Temperature is within the required range\n");
            status = STATUS_SUCCESS;        /* req: evaluateTemperature_LLR_4 */
        }
    }

    return status;
}