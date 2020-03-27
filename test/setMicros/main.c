#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_setMicros_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setMicros(&motor, 0);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MIN, motor.ticks);
}

void test_setMicros_1() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setMicros(&motor, 5000);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MAX, motor.ticks);
}

void test_setMicros_2() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setMicros(&motor, 1234);

    TEST_ASSERT_EQUAL(1234, motor.ticks);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_setMicros_0);
    RUN_TEST(test_setMicros_1);
    RUN_TEST(test_setMicros_2);
    return UNITY_END();
}
