static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
#define gp Serial2

//GPS data
int denemem;
double gpslongitude=41.123456;
double gpslatitude=21.564356;
double mylongtitude=0;
double mylatitude=0;

union cvt {
double fval;
byte gpsbyte[4];
} gpsfloat;

union cvt2 {
byte gpsbyte2[4];
double fval2;
} gpsfloat2;

void initializegps(){
  gp.begin(GPSBaud);
}
void readgps(){
     while (gp.available())
      gps.encode(gp.read());

 if(gps.location.isValid())
{
    gpslongitude = gps.location.lng();
    Serial.println(gps.location.lng(),8);
    Serial.println(gpslongitude,8);
    gpslatitude = gps.location.lat();
}
    gpsfloat.fval = gpslongitude ;
    Packet[30]=gpsfloat.gpsbyte[0] ;
    Packet[31]=gpsfloat.gpsbyte[1] ;
    Packet[32]=gpsfloat.gpsbyte[2] ;
    Packet[33]=gpsfloat.gpsbyte[3] ;
    Packet[34]=gpsfloat.gpsbyte[4] ;
    Packet[35]=gpsfloat.gpsbyte[5] ;
    Packet[36]=gpsfloat.gpsbyte[6] ;
    Packet[37]=gpsfloat.gpsbyte[7] ;
    
    gpsfloat2.gpsbyte2[0] =  Packet[30];
    gpsfloat2.gpsbyte2[1] =  Packet[31];
    gpsfloat2.gpsbyte2[2] =  Packet[32];
    gpsfloat2.gpsbyte2[3] =  Packet[33];
    gpsfloat2.gpsbyte2[4] =  Packet[34];
    gpsfloat2.gpsbyte2[5] =  Packet[35];
    gpsfloat2.gpsbyte2[6] =  Packet[36];
    gpsfloat2.gpsbyte2[7] =  Packet[37];
    mylongtitude = gpsfloat2.fval2;
    Serial.println(mylongtitude,8);

    gpsfloat.fval = gpslatitude ;
    Packet[38]=gpsfloat.gpsbyte[0] ;
    Packet[39]=gpsfloat.gpsbyte[1] ;
    Packet[40]=gpsfloat.gpsbyte[2] ;
    Packet[41]=gpsfloat.gpsbyte[3] ;
    Packet[42]=gpsfloat.gpsbyte[4] ;
    Packet[43]=gpsfloat.gpsbyte[5] ;
    Packet[44]=gpsfloat.gpsbyte[6] ;
    Packet[45]=gpsfloat.gpsbyte[7] ;

    
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
