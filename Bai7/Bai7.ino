#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h> 
//**GND - GND
//**VCC - 5V 
//** MOSI - pin 11
// ** MISO - pin 12
// ** CLK - pin 13
// ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

const int DHTPIN = 2;             //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;        //Khai báo loại cảm biến

DHT dht(DHTPIN, DHTTYPE);

File myFile;

void setup() {
  Serial.begin(9600);
  
  dht.begin();                    // Khởi động cảm biến DHT11

  while (!Serial) {
    ; // wait for serial port to connect.
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
}

void loop() {
  float h = dht.readHumidity();               //Đọc độ ẩm 
  float t = dht.readTemperature();            //Đọc nhiệt độ
  // kiểm tra lại giá trị nhiệt độ và độ ẩm đọc được, nếu chúng là "NaN" ( not a number) thì có vấn đề
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  }
  else{
  //Mở File 
   myFile = SD.open("test.txt", FILE_WRITE);

    // Viết dữ liệu vào File
    if (myFile) {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" % ");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
    myFile.print("Nhiệt độ: ");
    myFile.print(t);
    myFile.print("*C ");
    myFile.print("Độ ẩm: ");
    myFile.print(h);
    myFile.println("%");
    myFile.close();
      //đóng file :
      myFile.close();
      } 
      else {
      // Nếu lỗi mở File, in thông báo ra Serial
      Serial.println("error opening data file");
       }
  }
  }
