#include <gtest/gtest.h>

extern "C" {
#include "../../source/TemperatureSensor/temperatureSensor.h"
#include "../../source/TemperatureSensor/evaluateData.h"
#include "../../source/TemperatureSensor/logError.h"
#include "../../source/TemperatureSensor/globalData.h"
}

TEST(EvaluateTempTest_LLTC_1, NullPointer)
{
    STATE_STATUS status = evaluateTemperature(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(EvaluateTempTest_LLTC_2, BoundaryViolation)
{
    int8_t temperature = TEMP_UPPERBOUND;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    int8_t temperature = TEMP_UPPERBOUND + 10;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    int8_t temperature = TEMP_UPPERBOUND + 1; // Just above the upper boundary
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    int8_t temperature = TEMP_UPPERBOUND - 1; // Just below the upper boundary
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    int8_t temperature = TEMP_UPPERBOUND - 40;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    int8_t temperature = TEMP_UPPERBOUND + 28;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND; 
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND - 10;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND - 1; // Just below the lower boundary
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND + 1; // Just above the lower boundary
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = TEMP_LOWERBOUND + 40;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = TEMP_LOWERBOUND - 28;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);
}

TEST(EvaluateTempTest_LLTC_3, ThresholdViolation)
{
    int8_t temperature = MAX_THRESHOLD + 10;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    int8_t temperature = MAX_THRESHOLD - 10;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    int8_t temperature = MAX_THRESHOLD + 1; // Just above the maximum threshold
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    int8_t temperature = MAX_THRESHOLD + -1; // Just below the maximum threshold
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MIN_THRESHOLD;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = MIN_THRESHOLD + 1; // Adjusted to be just below the minimum threshold
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MIN_THRESHOLD - 1; // Adjusted to be just above the minimum threshold
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = MIN_THRESHOLD + 10; // Adjusted to be just below the minimum threshold
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(EvaluateTempTest_LLTC_4, Success)
{
    int8_t temperature = (MIN_THRESHOLD + MAX_THRESHOLD) / 2;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(LogErrorTest_LLTC_1, NullMessage)
{
    STATE_STATUS status = logError(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(LogErrorTest_LLTC_2, ValidMessage)
{
    const char* message = "Temperature threshold violation detected.";
    STATE_STATUS status = logError(message);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(GetTempTest_LLTC_1, NullPointer)
{
    STATE_STATUS status = getTemperature(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(GetTempTest_LLTC_2, Readtemperature)
{
    int8_t temperature;
    STATE_STATUS status = getTemperature(&temperature);
    EXPECT_TRUE(status == STATUS_SUCCESS_READ || status == STATUS_READ_ERROR);
}