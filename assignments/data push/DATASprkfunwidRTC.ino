#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>

#define myrtc 0x68

byte mac[] = { 0x90, 0xA2, 0xDA, 0xDE, 0x9E, 0x74 };
char server[] = "data.sparkfun.com";
IPAddress ip(10,0,1,116);


EthernetClient client;

char *dow[]={" ","MON","TUE","WED","THU","FRI","SAT","SUN"};
char *mode[]={"HR","AM","PM"};
int dd,mm,yy,day,hh,mins,ss,mde;


const String publicKey = "EJQAE2b9r3CAKAqgXvZr";
const String privateKey = "dqRmM7yzY1UBdBrEnqmN";

float temp = 0;
float light = 0;
float humid =0;
float pir = 0;
float rain = 0;

void setup() {
  Serial.begin(9600);
  setupEthernet();
  Wire.begin();
  Serial.println(F("=========== Ready to Stream ==========="));
}

void loop() {
  Serial.println("Posting");
  postData();
  delay(30000);
}  
  
void postData() {
  temp = analogRead(0);
  temp = temp*0.488;
  
  light = analogRead(1);

  humid = analogRead(2);
  humid = humid*5;
  humid = humid/1024;
  humid = humid*90;
  humid = humid/2.97;
  
  pir = analogRead(3);
  
  rain = analogRead(4);
   get_time();
  if (client.connect(server, 80))
  {
    client.print("GET /input/");
    client.print(publicKey);
    client.print("?private_key=");
    client.print(privateKey);
    client.print("&");
    client.print("_timestamp=");
    client.print(dd);
    client.print("/");
    client.print(mm);
    client.print("/");
    client.print(yy);
    client.print("%20"); 
    client.print(dow[day]);
    client.print("%20");
    client.print(hh);
    client.print(":"); 
    client.print(mins);
    client.print(":");
    client.print(ss);
    client.print("%20");
    client.print(mode[mde]); 
    client.print("&");
    client.print("humid=");
    client.print(humid);
    client.print("&");
    client.print("light=");
    client.print(light);
    client.print("&");
    client.print("pir=");
    client.print(pir);
    client.print("&");
    client.print("rain=");
    client.print(rain);
    client.print("&");
    client.print("temp=");
    client.print(temp);
    
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    Serial.println("Post Successful!!");
  }
  else
  {
    Serial.println(F("Connection failed"));
  } 
 while (client.connected())
 {
  if ( client.available() )
 {
 char c = client.read();
   Serial.print(c);
 }      
 }
 Serial.println();
  client.stop();  
}
  
void setupEthernet()
{
   if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
  delay(1000);
}

void get_time()
{
  Wire.beginTransmission(myrtc);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(myrtc, 7); 

  ss = bcd_to_dec(Wire.read());
  mins = bcd_to_dec(Wire.read());
  hh = Wire.read(); 
  if(hh > 35) 
  {
    hh = hh - 64;
    if(hh > 32)
    {
      mde = 2;
      hh = hh-32;
    }
    else
    {
      mde = 1;
    }   
  }
  else
  {
    mde = 0;
  }

  hh = bcd_to_dec(hh);
  day = bcd_to_dec(Wire.read());
  dd = bcd_to_dec(Wire.read());
  mm = bcd_to_dec(Wire.read());
  yy = bcd_to_dec(Wire.read());

}

int dec_to_bcd(int dec)
{
  return dec/10*16 + (dec%10);
}

int bcd_to_dec(int bcd)
{
  return bcd/16*10 + (bcd%16);
}
