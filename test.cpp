#include <chrono>
#include <thread>
#include <iostream>

#include <wiringPi.h>

#define IN_A 11
#define IN_B 13

#define PWM_A 38
#define PWM_B 36

/*
PWMA  IN1  IN2  OUT1  OUT2      PWMB  IN3  IN4  OUT1  OUT2
  0    x    x    0     0          0    x    x    0     0

  1    1    1    1     1          1    1    1    1     1
  1    0    0    0     0          1    0    0    0     0    Brake
  1    1    0    1     0          1    1    0    1     0    Forward
  1    0    1    0     1          1    0    1    0     1    Reverse

*/

using namespace std;


int main(int argc, char *argv[])
{

    wiringPiSetupPinType(WPI_PIN_PHYS);

    pinMode(38, OUTPUT);
    pinMode(36, OUTPUT);

    digitalWrite(38, HIGH);
    digitalWrite(36, HIGH);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    digitalWrite(38, LOW);
    digitalWrite(36, LOW);
}