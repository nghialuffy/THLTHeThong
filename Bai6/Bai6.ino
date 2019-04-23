#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
Servo s;
MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  s.attach(9);
  lcd.init();  
  lcd.backlight();
  
  lcd.print("AngleX : ");
  lcd.setCursor(0,1);
  lcd.print("AngleY : ");
  lcd.createChar(1, degree);

}

void loop() {
    mpu6050.update();
  Serial.print("angleX : ");
  Serial.println(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.println(mpu6050.getAngleY());
  
  s.write(mpu6050.getAngleY()+90);
  if (isnan(mpu6050.getAngleX()) || isnan(mpu6050.getAngleY())) {
      
    }else{
      lcd.setCursor(10,0);
    lcd.print(round(mpu6050.getAngleX()));
    lcd.print(" ");
    lcd.write(1);
    lcd.print("       ");

    lcd.setCursor(10,1);
    lcd.print(round(mpu6050.getAngleY()));
    lcd.print(" ");
    lcd.write(1);
    lcd.print("      ");   
    }
  delay(50);
  
}
