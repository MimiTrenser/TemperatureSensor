#include <gtest/gtest.h>

extern "C" {
#include "../../source/TemperatureSensor/temperatureSensor.h"
#include "../../source/TemperatureSensor/evaluateData.h"
#include "../../source/TemperatureSensor/logError.h"
#include "../../source/TemperatureSensor/globalData.h"
}

#define TEMP_TEN                     10
#define TEMP_ONE                     1
#define TEMP_FORTY                   40
#define TEMP_TWENTY_EIGHT            28


TEST(EvaluateTempTest_LLTC_1, NullPointer)
{
    STATE_STATUS status = evaluateTemperature(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(EvaluateTempTest_LLTC_2, BoundaryViolationCases)
{
    int8_t temperature = ZERO;
    STATE_STATUS status = STATUS_SUCCESS;

    temperature = TEMP_UPPERBOUND;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = TEMP_UPPERBOUND + TEMP_TEN;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_UPPERBOUND + TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_UPPERBOUND - TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = TEMP_UPPERBOUND - TEMP_FORTY;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = TEMP_UPPERBOUND + TEMP_TWENTY_EIGHT;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND; 
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = TEMP_LOWERBOUND - TEMP_TEN;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND - TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);

    temperature = TEMP_LOWERBOUND + TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = TEMP_LOWERBOUND + TEMP_FORTY;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = TEMP_LOWERBOUND - TEMP_TWENTY_EIGHT;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_BOUNDARY_VIOLATION);
}

TEST(EvaluateTempTest_LLTC_3, ThresholdViolationCases)
{
    int8_t temperature = ZERO;
    STATE_STATUS status = STATUS_SUCCESS;

    temperature = MAX_THRESHOLD;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MAX_THRESHOLD + TEMP_TEN;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = MAX_THRESHOLD - TEMP_TEN;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MAX_THRESHOLD + TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = MAX_THRESHOLD - TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MIN_THRESHOLD;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MIN_THRESHOLD + TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);

    temperature = MIN_THRESHOLD - TEMP_ONE;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_THRESHOLD_VIOLATION);

    temperature = MIN_THRESHOLD + TEMP_TEN;
    status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(EvaluateTempTest_LLTC_4, Success)
{
    int8_t temperature = (MIN_THRESHOLD + MAX_THRESHOLD) / 2;
    STATE_STATUS status = evaluateTemperature(&temperature);
    EXPECT_EQ(status, STATUS_SUCCESS);
}

TEST(LogAlarmStatusTest_LLTC_1, NullMessage)
{
    STATE_STATUS status = logAlarmStatus(NULL);
    EXPECT_EQ(status, STATUS_INVALID_DATA);
}

TEST(LogAlarmStatusTest_LLTC_2, ValidMessage)
{
    const char* message = "Temperature threshold violation detected.";
    STATE_STATUS status = logAlarmStatus(message);
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