#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

uint8_t setTimerOverflow = 0;
void PE_Servo180_setTimerOverflow(PE_Servo180_Timer_t *timer, uint16_t value) {
    setTimerOverflow++;
}

uint8_t setTimerRefresh = 0;
void PE_Servo180_setTimerRefresh(PE_Servo180_Timer_t *timer) {
    setTimerRefresh++;
}

uint8_t setMotorPin0;
void PE_Servo180_setMotorPin0(uint8_t id) {
    setMotorPin0 = id;
}

uint8_t setMotorPin1;
void PE_Servo180_setMotorPin1(uint8_t id) {
    setMotorPin1 = id;
}

void test_onOverflow_0() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor = {.ID = 1};

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    setMotorPin0 = 255;

    PE_Servo180_onOverflow(&timer);

    TEST_ASSERT_EQUAL(255, setMotorPin0);
}

void test_onOverflow_1() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor = {.ID = 1};

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    timer.motorIndex = 0;

    setMotorPin0 = 255;

    PE_Servo180_onOverflow(&timer);

    TEST_ASSERT_EQUAL(1, setMotorPin0);
}

void test_onOverflow_2() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor = {.ID = 1};

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    setMotorPin1 = 255;

    PE_Servo180_onOverflow(&timer);

    TEST_ASSERT_EQUAL(1, setMotorPin1);
}

void test_onOverflow_3() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor = {.ID = 1};

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    setTimerOverflow = 0;
    setMotorPin1     = 255;

    PE_Servo180_onOverflow(&timer);

    TEST_ASSERT_EQUAL(1, setTimerOverflow);
    TEST_ASSERT_EQUAL(1, setMotorPin1);
}

void test_onOverflow_4() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor = {.ID = 1};

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    timer.motorIndex = 2;

    setTimerOverflow = 0;
    setMotorPin1     = 255;

    PE_Servo180_onOverflow(&timer);

    TEST_ASSERT_EQUAL(1, setTimerOverflow);
    TEST_ASSERT_EQUAL(255, setMotorPin1);
}

void test_onOverflow_5() {
    PE_Servo180_Timer_t timer;
    PE_Servo180_Motor_t motor = {.ID = 1};

    PE_Servo180_createTimer(&timer);
    PE_Servo180_attachMotor(&timer, &motor);

    timer.motorIndex = PE_Servo180_MOTOR_PER_TIMER;

    setTimerOverflow = 0;
    setTimerRefresh  = 0;

    PE_Servo180_onOverflow(&timer);

    TEST_ASSERT_EQUAL(-1, timer.motorIndex);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_onOverflow_0);
    RUN_TEST(test_onOverflow_1);
    RUN_TEST(test_onOverflow_2);
    RUN_TEST(test_onOverflow_3);
    RUN_TEST(test_onOverflow_4);
    RUN_TEST(test_onOverflow_5);
    return UNITY_END();
}
