
#include<SPI.h> //Load SPI Library
#include<Wire.h>
#include<Math.h>
#include <SoftwareSerial.h>
#include <Adafruit_BMP280.h>
                                                                                 
unsigned long previousMillis = 0;                
const long interval = 30;                       
char uyari;
const int led=12;
float ang_x; 
float ang_y; 
float ang_z;  

#define BMP_SCK  (13)  // Kullanmadığı halde Bmp280 için gerekli olan tanımlamalar.
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // BMP 280 İçin nesne tanımlama

const int MPU_addr = 0x68; //MPU adresi


unsigned long yeni_zaman, eski_zaman = 0; //millis zaman fonksiyonu kullanımı için değişkenler.

double irtifa_deger, irtifa, eski_irtifa; //Bmp 280 basınç sensöründen irtifa değeri okumak için tanımlanan değişkenler.




//*************************************************************************************************************************************************************************************

void setup() {

  Serial.begin(9600);//Seri haberlşeme başlatılır

  Wire.begin();   // İvme sensörü İçin I2C Başlatılır
  bmp.begin();   // BMP 280 başlatma
  

  // Mpu 6050 İvme sensörü bağlangıç ayarları.
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  // Bmp 280 İçin  Başlangıç ayarları
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Çalışma modu. */
                  Adafruit_BMP280::SAMPLING_X16,    /* Basınç yüksek hızda örnekleme */
                  Adafruit_BMP280::FILTER_X16,      /* Filtreleme. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Bekleme süresi. */
 pinMode(led,OUTPUT);                 
  delay(10);
  }
void loop() {
 
  yeni_zaman = millis();

  if (yeni_zaman - eski_zaman >= 400) {
    eski_zaman = yeni_zaman;


    //  Serial.print(F("Sıcaklık = "));// Basınç sensöründen sıcaklık alınması
      Serial.print(bmp.readTemperature());
    //  Serial.print(" *C");
        Serial.print(" ");
      // İrtifa değerinin ekrana yazdırılması
 //     Serial.print(F("Rakım = "));
      Serial.print(bmp.readAltitude(1022));
  //    Serial.print(" m");
       Serial.print(" ");
    //      Serial.print(F("Pressure = "));
          Serial.print(bmp.readPressure());
    //      Serial.println(" Pa");
       Serial.print(" ");
//   class CommaForDot : public Print
//{
//public:
//    CommaForDot(Print &downstream) : downstream(downstream) {}
//    virtual size_t write(uint8_t c) {
 //       return downstream.write(c=='.' ? ',' : c);  // replacement
//    }
//private:
//    Print &downstream;
//};  
// CommaForDot filteredSerial(Serial);
//   filteredSerial.println(bmp.readTemperature());
//   Serial.print(" ");

    Wire.beginTransmission(MPU_addr);                                         //MPU6050 ile I2C haberleşme başlatılır
    Wire.write(0x3B);                                                         //İvme bilgisinin olduğu 0x3B-0x40 için request gönderilir
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 6, true);
  int16_t XAxisFull =  (Wire.read() << 8 | Wire.read());
  int16_t YAxisFull =  (Wire.read() << 8 | Wire.read());
  int16_t ZAxisFull =  (Wire.read() << 8 | Wire.read());
    float XAxisFinal = (float) XAxisFull / 16384.0;                  //Datasheet'te yazan değerlere göre "g" cinsinden ivme buldum. (X ekseni için)
    float YAxisFinal = (float) YAxisFull / 16384.0;                 
    float ZAxisFinal = (float) ZAxisFull / 16384.0;   


    if(XAxisFinal>0.99) XAxisFinal=1;   //0.99 olan değerler 1'e tamamladım
    if(YAxisFinal>0.99) YAxisFinal=1;
    if(ZAxisFinal>0.99) ZAxisFinal=1;

    if(XAxisFinal<-0.99) XAxisFinal=-1; //-0.99 olan değerler 1'e tamamladım.
    if(YAxisFinal<-0.99) YAxisFinal=-1;
    if(ZAxisFinal<-0.99) ZAxisFinal=-1;

    ang_x = (atan(YAxisFull/(sqrt(pow(XAxisFull,2)+pow(ZAxisFull,2)))) * 57296 / 1000)+1.35; //Euler Açı formülüne göre açı hesabı+sensör hatasu (X-Ekseni)
    ang_y = (atan(-1*XAxisFull/(sqrt(pow(YAxisFull,2)+pow(ZAxisFull,2)))) * 57296 / 1000)+1.64; //Euler Açı formülüne göre açı hesabı+sensör hatası (Y-Ekseni)
  //    Serial.print("X İVME = ");  //Her eksen için g değerleri seri porttan bastım
    if(XAxisFinal<0)
      Serial.print(-1*XAxisFinal);
 else{
    Serial.print(XAxisFinal);
   }
 
  Serial.print(" ");

 //   Serial.print("X AÇISI = "); //X ve Y eksenleri için açı değerleri seri porttan bastım
 if(ang_x<0)
      Serial.print(-1*ang_x);
 else{
    Serial.print(ang_x);
   }
 
  Serial.print(" ");
//    Serial.print("Y AÇISI = ");
   if(ang_y<0)
      Serial.println(-1*ang_y);
 else{
    Serial.println(ang_y);
   }
   
  }
  delay(500);
  uyari=Serial.read(); // Seri iletişim hattan gelen veri okunuyor
    if( uyari=='1')
    {
      digitalWrite(led,HIGH);
    }
    else
      digitalWrite(led,LOW);

}
