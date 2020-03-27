#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_setRadian_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setRadian(&motor, 0);

    TEST_ASSERT_FLOAT_WITHIN(0.1, PE_Servo180_MOTOR_MIN, motor.ticks);
}

void test_setRadian_1() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setRadian(&motor, M_PI_2);

    TEST_ASSERT_FLOAT_WITHIN(0.1, PE_Servo180_MOTOR_MID, motor.ticks);
}

void test_setRadian_2() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setRadian(&motor, M_PI);

    TEST_ASSERT_FLOAT_WITHIN(0.1, PE_Servo180_MOTOR_MAX, motor.ticks);
}

void test_setRadian_3() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setRadian(&motor, M_PI * 2);

    TEST_ASSERT_FLOAT_WITHIN(0.1, PE_Servo180_MOTOR_MAX, motor.ticks);
}

void test_setRadian_4() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setRadian(&motor, -M_PI);

    TEST_ASSERT_FLOAT_WITHIN(0.1, PE_Servo180_MOTOR_MIN, motor.ticks);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_setRadian_0);
    RUN_TEST(test_setRadian_1);
    RUN_TEST(test_setRadian_2);
    RUN_TEST(test_setRadian_3);
    RUN_TEST(test_setRadian_4);
    return UNITY_END();
}
