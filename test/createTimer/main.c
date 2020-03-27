#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_createTimer_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Status_t status;

    status = PE_Servo180_createTimer(&timer);

    TEST_ASSERT_EQUAL(-1, timer.motorIndex);
    TEST_ASSERT_EQUAL(0, timer.motorCount);
    TEST_ASSERT_EQUAL(PE_Servo180_SUCCESS, status);

    uint8_t index;
    for (index = 0; index < PE_Servo180_MOTOR_PER_TIMER; index++) {
        TEST_ASSERT_EQUAL_PTR(NULL, timer.motorItems[index]);
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_createTimer_0);
    return UNITY_END();
}
