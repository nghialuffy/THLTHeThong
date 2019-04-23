#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9


MFRC522 mfrc522(SS_PIN, RST_PIN);  


int ot = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Please Scan Your Card...");
  Serial.println();
}



void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "23 28 83 1B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Card Identified");
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    Serial.println();
   
    
  }
 
  else   {
   Serial.println("Card Not Identified");
   digitalWrite(7, LOW);
   Serial.println();
//   
  }
  delay(1000);

}
