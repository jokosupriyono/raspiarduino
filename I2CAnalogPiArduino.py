from gpiozero import LED, Button, Buzzer
import smbus
from time import sleep

LED1 = LED(17)
LED2 = LED(18)
LED3 = LED(27)
LED4 = LED(22)
LED5 = LED(5)
LED6 = LED(12)
LED7 = LED(13)
LED8 = LED(19)

SW1 = Button(21)
SW2 = Button(16)
SW3 = Button(20)

BUZZER = Buzzer(26)

i2c = smbus.SMBus(1)
I2C_ADD = 0x08 # Arduino I2C address

def beep(times, delay):
  for x in range(times):
    BUZZER.on()
    sleep(delay)
    BUZZER.off()
    sleep(delay)

def writeI2C(data):
  i2c.write_byte(I2C_ADD, data)

def readI2C():
  inData = i2c.read_byte(I2C_ADD)
  return inData

prevI2CData = 0
beep(2, 0.07)

try:
  while True:
    if SW1.is_pressed:
      writeI2C(1)
      SW1.wait_for_release()

    elif SW2.is_pressed:
      writeI2C(2)
      SW2.wait_for_release()
    
    elif SW3.is_pressed:
      writeI2C(3)
      SW3.wait_for_release()

    I2Cdata = readI2C()
    if I2Cdata != prevI2CData:
      prevI2CData = I2Cdata
      
      if I2Cdata > 28:
        LED1.on()
      else:
        LED1.off()
                
      if I2Cdata > 56:
        LED2.on()
      else:
        LED2.off()

      if I2Cdata > 84:
        LED3.on()
      else:
        LED3.off()

      if I2Cdata > 112:
        LED4.on()
      else:
        LED4.off()

      if I2Cdata > 140:
        LED5.on()
      else:
        LED5.off()

      if I2Cdata > 168:
        LED6.on()
      else:
        LED6.off()

      if I2Cdata > 196:
        LED7.on()
      else:
        LED7.off()

      if I2Cdata > 224:
        LED8.on()
      else:
        LED8.off()

      sleep(0.1)

except KeyboardInterrupt:
  GPIO.cleanup()
