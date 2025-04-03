import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)

IN1 = 17
IN2 = 27
PWMA = 22

GPIO.setup((IN1, IN2, PWMA), GPIO.OUT )

GPIO.output(IN1, True)
GPIO.output(IN2, False)
GPIO.output(PWMA, True)

time.sleep(5)


GPIO.output(IN1, False)
GPIO.output(IN2, False)


time.sleep(1)

GPIO.output(IN1, False)
GPIO.output(IN2, True)

time.sleep(5)

GPIO.output(IN2, False)
GPIO.output(PWMA, False)

GPIO.cleanup()