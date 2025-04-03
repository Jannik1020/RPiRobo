#include <chrono>
#include <thread>

#include <wiringPi.h>

#define IN1 16
#define IN2 18
#define IN3 11
#define IN4 13

#define PWMA 22
#define PWMB 15

/*
PWMA  IN1  IN2  OUT1  OUT2      PWMB  IN3  IN4  OUT1  OUT2
  0    x    x    0     0          0    x    x    0     0

  1    1    1    1     1          1    1    1    1     1
  1    0    0    0     0          1    0    0    0     0    Brake
  1    1    0    1     0          1    1    0    1     0    Forward
  1    0    1    0     1          1    0    1    0     1    Reverse

*/

class Motor{
    public:
        int in1;
        int in2;
        int pwm;

        Motor(int pin_in1, int pin_in2, int pin_pwm):in1(pin_in1), in2(pin_in2), pwm(pin_pwm){
            pinMode(in1, OUTPUT);
            pinMode(in2, OUTPUT);
            pinMode(pwm, OUTPUT);

            stop();
        }

        ~Motor(){
            stop();

            pinMode(in1, INPUT);
            pinMode(in2, INPUT);
            pinMode(pwm, INPUT);
        }

        void forward() {
            digitalWrite(pwm, HIGH);

            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
        }

        void backward() {
            digitalWrite(pwm, HIGH);

            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
        }

        void brake() {
            digitalWrite(pwm, HIGH);

            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
        }

        void stop() {

            digitalWrite(pwm, LOW);

            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
        }
};


int main(int argc, char * argv[]) {

    wiringPiSetupPinType(WPI_PIN_PHYS);

    Motor left(IN1, IN2, PWMA);
    Motor right(IN3, IN4, PWMB);

    left.forward();
    right.forward();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    left.brake();
    right.brake();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    left.backward();
    right.backward();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    left.stop();
    right.stop();
}