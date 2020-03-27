#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_detachMotor_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;
    PE_Servo180_Status_t status;

    PE_Servo180_createTimer(&timer);

    status = PE_Servo180_detachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_FAILURE, status);
}

void test_detachMotor_1() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;
    PE_Servo180_Status_t status;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    status = PE_Servo180_detachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_SUCCESS, status);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_detachMotor_0);
    RUN_TEST(test_detachMotor_1);
    return UNITY_END();
}
