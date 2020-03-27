#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_attachMotor_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;
    PE_Servo180_Status_t status;

    PE_Servo180_createTimer(&timer);

    timer.motorCount = PE_Servo180_MOTOR_PER_TIMER;

    status = PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_FAILURE, status);
}

void test_attachMotor_1() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;
    PE_Servo180_Status_t status;

    PE_Servo180_createTimer(&timer);

    status = PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_SUCCESS, status);
    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MID, motor.ticks);
    TEST_ASSERT_EQUAL(1, timer.motorCount);
    TEST_ASSERT_EQUAL_PTR(&motor, timer.motorItems[0]);

    status = PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_FAILURE, status);
}

void test_attachMotor_2() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);

    PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MIN, motor.min);
    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MAX, motor.max);
}

void test_attachMotor_3() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);

    motor.min = 600;
    motor.max = 2400;

    PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(600, motor.min);
    TEST_ASSERT_EQUAL(2400, motor.max);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_attachMotor_0);
    RUN_TEST(test_attachMotor_1);
    RUN_TEST(test_attachMotor_2);
    RUN_TEST(test_attachMotor_3);
    return UNITY_END();
}