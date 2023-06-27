#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <Wire.h>
#define INTERRUPT_PIN 2
#define LED_PIN 13

class MPU6050_New {
private:
  MPU6050 mpu;
  bool dmpReady = false;
  uint16_t packetSize;
  uint8_t fifoBuffer[64];
  Quaternion q;
  VectorFloat gravity;
  float ypr[3];

public:
  void MPU6050Setup() {
    Wire.begin();
    Wire.setClock(400000);  // 400kHz I2C clock. Comment this line if having compilation difficulties

    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);
    delay(1000);

    devStatus = mpu.dmpInitialize();

    mpu.setXGyroOffset(-8);
    mpu.setYGyroOffset(9);
    mpu.setZGyroOffset(-8);
    mpu.setZAccelOffset(2107);

    if (devStatus == 0) {
      mpu.setDMPEnabled(true);
      mpuIntStatus = mpu.getIntStatus();
      dmpReady = true;

      packetSize = mpu.dmpGetFIFOPacketSize();
      pinMode(LED_PIN, OUTPUT);
    }
  }

  float *MPU6050loop() {
    if (!dmpReady) return ypr;

    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    fifoCount = mpu.getFIFOCount();
    mpu.resetFIFO();
    fifoCount = mpu.getFIFOCount();

    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
      mpu.resetFIFO();
      Serial.println(F("FIFO overflow!"));
    }
    else if (mpuIntStatus & 0x02) {
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

      mpu.getFIFOBytes(fifoBuffer, packetSize);
      fifoCount -= packetSize;

      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    }

    mpu.resetFIFO();
    return ypr;
  }
} mylib;
