/* temperatureSensor.c - getTemperature function */
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
The function [getTemperature] will generate simulated temperature value 
within a required boundary.
...
INCLUDE FILES: globalData.h.h
*/

/* includes */
#include "globalData.h"
#include "temperatureSensor.h"

/* defines */
#define RAND_MINIMUM_RANGE      -40
#define RAND_MAXIMUM_RANGE      150
#define RAND_MAXIMUM_RANGE      150
#define INVALID_TEMPERATURE     1000

/*******************************************************************************
*
* getTemperature - This function reads temperature data.
*
* DESCRIPTION
* The function [getTemperature] will generate simulated temperature value within
* a required boundary.
* The function will return:
* [STATUS_INVALID_DATA] when the [pTemperature] is NULL.
* [STATUS_READ_ERROR] when the [pTemperature] has no valid data after 
* temperature simulation.
* [STATUSREAD_SUCCESS] when [pTemperature] contains updated temperature value.
*
* PARAMETERS
* \is
* \i <*pTemperature>
* [out] A pointer to an integer where the generated temperature value will be 
* stored.
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
* \i <STATUS_READ_SUCCESS>
* when [pTemperature] was successfully updated with temperature value
* 
* \i <STATUS_INVALID_DATA>
* when the pointer to temperature data is NULL 
* \i <STATUS_READ_ERROR>
* when the generated temperature value is invalid (exceeds defined limits)
* \ie
* ERRNO:
* \is
* \i
* N/A
* \ie
*
* SEE ALSO:
* main.c
*
* \INTERNAL
* This function reads temperature data by simulating a random temperature value 
* within a defined range. It checks for the validity of the generated 
* temperature and returns appropriate status codes based on the outcome of the 
* operation.
*/

STATE_STATUS getTemperature(int8_t *pTemperature)
{
    STATE_STATUS status = STATUS_SUCCESS;

    if (pTemperature == NULL)
    {
        status = STATUS_INVALID_DATA;            /* req: getTemperature_LLR_1 */
    }
    else
    {

        *pTemperature = (int8_t)(rand() % RAND_MAXIMUM_RANGE - RAND_MINIMUM_RANGE);

        if(*pTemperature > INVALID_TEMPERATURE)
        {
            status = STATUS_READ_ERROR;          /* req: getTemperature_LLR_2 */
        }
        else
        {
         status = STATUS_SUCCESS_READ;           /* req: getTemperature_LLR_3 */
        }
    }

    return status;
}