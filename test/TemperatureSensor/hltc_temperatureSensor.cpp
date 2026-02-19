#include <gtest/gtest.h>

extern "C" {
#include "../../source/TemperatureSensor/temperatureSensor.h"
#include "../../source/TemperatureSensor/evaluateData.h"
#include "../../source/TemperatureSensor/logError.h"
#include "../../source/TemperatureSensor/globalData.h"
}

#define TEMP_FIVE                    5
#define TWO                          2

TEST(EvaluateTempTest_HLTC_1, NullPointer)
{
    STATE_STATUS status = evaluateTemperature(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(EvaluateTempTest_HLTC_3, BoundaryViolation)
{
    int8_t temperature = TEMP_UPPERBOUND + TEMP_FIVE;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND - TEMP_FIVE; 
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);
}

TEST(EvaluateTempTest_HLTC_2, ThresholdViolation)
{
    int8_t temperature = MAX_THRESHOLD + TEMP_FIVE;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = MIN_THRESHOLD - TEMP_FIVE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);
}

TEST(EvaluateTempTest_HLTC_4, Success)
{
    int8_t temperature = (MIN_THRESHOLD + MAX_THRESHOLD) / TWO;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(LogErrorTest_HLTC_1, NullMessage)
{
    STATE_STATUS status = logError(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(LogErrorTest_HLTC_2, ValidMessage)
{
    const char* message = "Temperature threshold violation detected.";
    STATE_STATUS status = logError(message);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(GetTempTest_HLTC_1, NullPointer)
{
    STATE_STATUS status = getTemperature(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(GetTempTest_HLTC_2, Readtemperature)
{
    int8_t temperature;
    STATE_STATUS status = getTemperature(&temperature);
    EXPECT_TRUE(status == STATUS_SUCCESS_READ || status == STATUS_READ_ERROR);
}