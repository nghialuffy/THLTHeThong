int pinled[]={2,3,4,5,6,7,8,9};

void setup() {
  Serial.begin(9600);  //Mở cổng Serial để giap tiếp | tham khảo Serial
}
 
void loop() {
  int value = analogRead(A0);    //đọc giá trị điện áp ở chân A0 
                                //(value luôn nằm trong khoảng 0-1023)
                               //xuất ra giá trị vừa đọc
  
  int voltage;
  voltage = map(value,0,1023,0,5000);   //chuyển thang đo của value 
                                        //từ 0-1023 sang 0-5000 (mV)
  Serial.println(voltage);              //xuất ra điện áp (đơn vị là mV)
//  
  Serial.println();     //xuống hàng
  //delay(200);           //đợi 0.2 giây
  for (int i =0; i<= int(voltage/625)-1; i++){
      digitalWrite(pinled[i],HIGH);
  }
  for (int i =int(voltage/625); i < 8; i++){
      digitalWrite(pinled[i],LOW);
  }
  
}
