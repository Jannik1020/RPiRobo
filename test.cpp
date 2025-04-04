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



void forward() {
    digitalWrite(38, HIGH);
    digitalWrite(36, HIGH);
}

void brake() {
    digitalWrite(38, LOW);
    digitalWrite(36, LOW);
}

int main() {
    char c;

    wiringPiSetupPinType(WPI_PIN_PHYS);

    pinMode(38, OUTPUT);
    pinMode(36, OUTPUT);

   // Set the terminal to raw mode
    while(1) {
        system("stty raw");
        c = getchar(); 
        // terminate when "." is pressed
        system("stty cooked");
        system("clear");
        std::cout << c << " was pressed."<< std::endl;
        if(c == 'w') {
          forward();
        }
        if(c == 'b') {
          brake();
        }
        if(c == '.') {
            system("stty cooked");
            exit(0);
        }  
    }
}
