#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_setDegree_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setDegree(&motor, 0);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MIN, motor.ticks);
}

void test_setDegree_1() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setDegree(&motor, 90);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MID, motor.ticks);
}

void test_setDegree_2() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setDegree(&motor, 180);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MAX, motor.ticks);
}

void test_setDegree_3() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor;

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_setDegree(&motor, 360);

    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MAX, motor.ticks);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_setDegree_0);
    RUN_TEST(test_setDegree_1);
    RUN_TEST(test_setDegree_2);
    RUN_TEST(test_setDegree_3);
    return UNITY_END();
}
