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

class Motor{
    public:
        int pin_dir;
        int pin_speed;

        Motor(int pin_in, int pin_pwm):pin_dir(pin_in), pin_speed(pin_pwm){
            pinMode(pin_dir, OUTPUT);
            pinMode(pin_speed, OUTPUT);

            stop();
        }

        ~Motor(){
            stop();

            pinMode(pin_dir, INPUT);
            pinMode(pin_speed, INPUT);
        }

        void forward() {
            digitalWrite(pin_speed, HIGH);
            digitalWrite(pin_dir, HIGH);
        }

        void backward() {
            digitalWrite(pin_speed, HIGH);
            digitalWrite(pin_dir, LOW);
        }

        void brake() {
            digitalWrite(pin_speed, LOW);
        }

        void stop() {

            digitalWrite(pin_speed, LOW);
            digitalWrite(pin_dir, LOW);
        }
};


int main(int argc, char * argv[]) {

    wiringPiSetupPinType(WPI_PIN_PHYS);

    Motor left(IN_A, PWM_A);
    Motor right(IN_B, PWM_B);

    left.forward();
    right.forward();

    this_thread::sleep_for(chrono::milliseconds(300));

    left.brake();
    right.brake();

    this_thread::sleep_for(chrono::milliseconds(100));

    left.backward();
    right.backward();

    this_thread::sleep_for(chrono::milliseconds(300));

    left.stop();
    right.stop();

    /*string token = "";
    while(token != "x"){
        cin >> token;
        if(token == "f") {
            left.forward();
            right.forward();
        }
        else if(token == "b"){
            left.backward();
            right.backward();
        }
        else if(token == "s") {
            left.brake();
            right.brake();
        }
    }

    left.stop();
    right.stop();*/
}