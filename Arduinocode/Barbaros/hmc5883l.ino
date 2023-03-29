int x,y,z; //triple axis data
#define Magnetometer 0x1E //I2C 7bit address of HMC5883

void initiliazehmc(){
  Wire.beginTransmission(Magnetometer); 
  Wire.write(0x02); // Select mode register
  Wire.write(0x00); // Continuous measurement mode
  Wire.endTransmission();
}
void hmcread(){
 
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(Magnetometer);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(Magnetometer, 6);
  if(6<=Wire.available()){
    Packet[24] = Wire.read();
    Packet[25] = Wire.read();
    Packet[26] = Wire.read();
    Packet[27] = Wire.read();
    Packet[28] = Wire.read();
    Packet[29] = Wire.read();
    x = Packet[24]<<8; //X msb
    x |= Packet[25]; //X lsb
    y = Packet[26]<<8; //Z msb
    y |= Packet[27]; //Z lsb
    z = Packet[28]<<8; //Y msb
    z |= Packet[29]; //Y lsb
  }
  
  //Print out values of each axis
//  Serial.print("x: ");
//  Serial.print(x);
//  Serial.print("  y: ");
//  Serial.print(y);
//  Serial.print("  z: ");
//  Serial.println(z);  
}
