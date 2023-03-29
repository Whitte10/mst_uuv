static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
#define gp Serial2

//GPS data
float longtitude=41.123456;
float lantitude=21.564356;
float mylongtitude=0;
float mylantitude=0;

union cvt {
float fval;
byte gpsbyte[4];
} gpsfloat;

//union cvt2 {
//byte gpsbyte2[4];
//float fval2;
//} gpsfloat2;

void initializegps(){
  gp.begin(GPSBaud);
}
void readgps(){
     while (gp.available())
      gps.encode(gp.read());

 if(gps.location.isValid())
{
    longtitude = gps.location.lng();
    lantitude = gps.location.lat();
}
    gpsfloat.fval = longtitude ;
    Packet[30]=gpsfloat.gpsbyte[0] ;
    Packet[31]=gpsfloat.gpsbyte[1] ;
    Packet[32]=gpsfloat.gpsbyte[2] ;
    Packet[33]=gpsfloat.gpsbyte[3] ;
    
//    gpsfloat2.gpsbyte2[0] =  Packet[30];
//    gpsfloat2.gpsbyte2[1] =  Packet[31];
//    gpsfloat2.gpsbyte2[2] =  Packet[32];
//    gpsfloat2.gpsbyte2[3] =  Packet[33];
//    gpsfloat2.gpsbyte2[4] =  Packet[34];
//    gpsfloat2.gpsbyte2[5] =  Packet[35];
//    gpsfloat2.gpsbyte2[6] =  Packet[36];
//    gpsfloat2.gpsbyte2[7] =  Packet[37];
//    mylongtitude = gpsfloat2.fval2;
//    Serial.println(mylongtitude,8);

    gpsfloat.fval = lantitude ;
    Packet[34]=gpsfloat.gpsbyte[0] ;
    Packet[35]=gpsfloat.gpsbyte[1] ;
    Packet[36]=gpsfloat.gpsbyte[2] ;
    Packet[37]=gpsfloat.gpsbyte[3] ;

    
//    gpsfloat2.gpsbyte2[0] =  Packet[38];
//    gpsfloat2.gpsbyte2[1] =  Packet[39];
//    gpsfloat2.gpsbyte2[2] =  Packet[40];
//    gpsfloat2.gpsbyte2[3] =  Packet[41];
//    gpsfloat2.gpsbyte2[4] =  Packet[42];
//    gpsfloat2.gpsbyte2[5] =  Packet[43];
//    gpsfloat2.gpsbyte2[6] =  Packet[44];
//    gpsfloat2.gpsbyte2[7] =  Packet[45];
//    mylongtitude = gpsfloat2.fval2;
//    Serial.println(mylongtitude,8);
}
