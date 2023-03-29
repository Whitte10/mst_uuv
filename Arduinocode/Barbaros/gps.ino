union cvt {
float fval;
byte gpsbyte[4];
} gpsfloat;

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
    
    gpsfloat.fval = lantitude ;
    Packet[34]=gpsfloat.gpsbyte[0] ;
    Packet[35]=gpsfloat.gpsbyte[1] ;
    Packet[36]=gpsfloat.gpsbyte[2] ;
    Packet[37]=gpsfloat.gpsbyte[3] ;
}
