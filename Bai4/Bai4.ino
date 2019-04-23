#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
//0x27 là d?a ch? màn hình trong bus I2C. Ph?n này chúng ta không c?n ph?i quá b?n tâm vì h?u h?t màn hình (20x4,...) d?u nhu th? này!
//16 là s? c?t c?a màn hình (n?u dùng lo?i màn hình 20x4) thì thay b?ng 20
//2 là s? dòng c?a
#define IN1  7
#define IN2 6
#define IN3 5
#define IN4 4
#define MAX_SPEED 255 //t? 0-255
#define MIN_SPEED 0
void setup()
{
lcd.init();
lcd.backlight();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
 
void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
 
void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 
void motor_1_Tien(int speed) { //speed: t? 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//d?m báo giá tr? n?m trong m?t kho?ng t? 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, HIGH);// chân này không có PWM
  analogWrite(IN2, 255 - speed);
}
 
void motor_1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//d?m báo giá tr? n?m trong m?t kho?ng t? 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, LOW);// chân này không có PWM
  analogWrite(IN2, speed);
}
 
void motor_2_Lui(int speed) { //speed: t? 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//d?m báo giá tr? n?m trong m?t kho?ng t? 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);// chân này không có PWM
}
 
void motor_2_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//d?m báo giá tr? n?m trong m?t kho?ng t? 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, 255 - speed);
  digitalWrite(IN4, HIGH);// chân này không có PWM
}
 
void loop()
{
  lcd.print("Speed1 = ");
  lcd.print(MAX_SPEED);
  lcd.setCursor(0,1);
  lcd.print("Speed2 = ");
  lcd.print(MAX_SPEED);
  motor_1_Tien(MAX_SPEED); // motor 1 ti?n
  motor_2_Tien(MAX_SPEED); //motor 2 lùi
  delay(2000);//ti?n 5 s
  lcd.clear();
  lcd.print("Speed1 = ");
  lcd.print(MAX_SPEED);
  lcd.setCursor(0,1);
  lcd.print("Speed2 = ");
  lcd.print(-MAX_SPEED);
  motor_1_Tien(MAX_SPEED); // motor 1 ti?n
  motor_2_Lui(MAX_SPEED); //motor 2 lùi
  delay(2000);//ti?n 5 s
  lcd.clear();
  lcd.print("Speed1 = ");
  lcd.print(-MAX_SPEED);
  lcd.setCursor(0,1);
  lcd.print("Speed2 = ");
  lcd.print(-MAX_SPEED);
  motor_1_Lui(MAX_SPEED); // motor 1 ti?n
  motor_2_Lui(MAX_SPEED); //motor 2 lùi
 
  delay(2000);//ti?n 5 s
  lcd.clear();
 
}
