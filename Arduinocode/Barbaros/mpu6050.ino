void mpuInitialize()
{
   Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXAccelOffset(-1169);
    mpu.setYAccelOffset(744);
    mpu.setZAccelOffset(1620);
    mpu.setXGyroOffset(48);
    mpu.setYGyroOffset(47);
    mpu.setZGyroOffset(-8);

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

void mpuLoop()
{
      // get current FIFO count
    fifoCount = mpu.getFIFOCount();
    while (fifoCount < packetSize) {
      fifoCount = mpu.getFIFOCount();
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
    }
  mpuIntStatus = mpu.getIntStatus();
    
    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);

        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        // display quaternion values in InvenSense mpu demo format:
        Packet[2] = fifoBuffer[0];
        Packet[3] = fifoBuffer[1];
        Packet[4] = fifoBuffer[4];
        Packet[5] = fifoBuffer[5];
        Packet[6] = fifoBuffer[8];
        Packet[7] = fifoBuffer[9];
        Packet[8] = fifoBuffer[12];
        Packet[9] = fifoBuffer[13];
        // gyro values
        Packet[10] = fifoBuffer[16];
        Packet[11] = fifoBuffer[17];
        Packet[12] = fifoBuffer[20];
        Packet[13] = fifoBuffer[21];
        Packet[14] = fifoBuffer[24];
        Packet[15] = fifoBuffer[25];
       
        // accelerometer values
        Packet[16] = fifoBuffer[28];
        Packet[17] = fifoBuffer[29];
        Packet[18] = fifoBuffer[32];
        Packet[19] = fifoBuffer[33];
        Packet[20] = fifoBuffer[36];
        Packet[21] = fifoBuffer[37];
        //temperature
        int16_t temperature = mpu.getTemperature();
        Packet[22] = temperature >> 8;
        Packet[23] = temperature & 0xFF;
        Serial.write(Packet, 42);
        Packet[39]++; // packetCount, loops at 0xFF on purpose

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}
