#define LED_PIN 13
 
#define CMD_SEND_BEGIN  "AT+CIPSEND=0"
#define CMD_SEND_END    "AT+CIPCLOSE=0"
 
#define STDIO_PROTOCOL_HTTP     80
#define STDIO_PROTOCOL_HTTPS    443
#define STDIO_PROTOCOL_FTP      21
#define STDIO_PROTOCOL_CURRENT  STDIO_PROTOCOL_HTTP
 
#define STDIO_CHAR_CR     0x0D
#define STDIO_CHAR_LF     0x0A
 
#define STDIO_STRING_EMPTY  ""
 
#define STDIO_DELAY_SEED  1000
#define STDIO_DELAY_1X    (1*STDIO_DELAY_SEED)
#define STDIO_DELAY_2X    (2*STDIO_DELAY_SEED)
#define STDIO_DELAY_3X    (3*STDIO_DELAY_SEED)
#define STDIO_DELAY_4X    (4*STDIO_DELAY_SEED)
#define STDIO_DELAY_5X    (5*STDIO_DELAY_SEED)
 
bool hasRequest = false;
 
void setup()
{
  delay(STDIO_DELAY_5X);
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN, LOW);
  
  initESP8266();
}
 
void loop()
{
  while(Serial.available())
  {   
    bufferingRequest(Serial.read());
  }
  
  if(hasRequest == true) 
  {
    String htmlResponse = "<!doctype html>"
    "<html>"
      "<head>"
        "<title>STDIO.VN ESP8266 DEMO</title>"
      "</head>"
      "<body>"
        "<h1>STDIO.VN ESP8266 DEMO</h1>"
        "<form action='' method='GET'>"
          "<input type='radio' name='LED' name='STDIO' value='STDIO_ON' /> LED ON<br/>"
          "<input type='radio' name='LED' name='STDIO' value='STDIO_OFF' /> LED OFF<br/>"
          "<input type='submit' value='Submit' />"
        "</form>"
      "</body>"
     "</html>";
    
    String beginSendCmd = String(CMD_SEND_BEGIN) + "," + htmlResponse.length();
    deliverMessage(beginSendCmd, STDIO_DELAY_1X);
    deliverMessage(htmlResponse, STDIO_DELAY_1X);
    deliverMessage(CMD_SEND_END, STDIO_DELAY_1X);
    hasRequest = false;
  }
}
 
void initESP8266()
{
  deliverMessage("AT+RST", STDIO_DELAY_2X);
  deliverMessage("AT+CWMODE=2", STDIO_DELAY_3X);
  deliverMessage("AT+CWSAP=\"STDIO_ESP8266\",\"STDIOElectronics\",1,4", STDIO_DELAY_3X);
  deliverMessage("AT+CIFSR", STDIO_DELAY_1X);
  deliverMessage("AT+CIPMUX=1", STDIO_DELAY_1X);
  deliverMessage(String("AT+CIPSERVER=1,") + STDIO_PROTOCOL_CURRENT, STDIO_DELAY_1X);  
}
 
void bufferingRequest(char c)
{
  static String bufferData = STDIO_STRING_EMPTY;
 
  switch (c)
  {
    case STDIO_CHAR_CR:
      break;
    case STDIO_CHAR_LF:
    {
      STDIOProcedure(bufferData);
      bufferData = STDIO_STRING_EMPTY;
    }
      break;
    default:
      bufferData += c;
  }
} 
 
void STDIOProcedure(const String& command)
{ 
  hasRequest = command.startsWith("+IPD,");
  
  if(command.indexOf("STDIO_OFF") != -1)
  { 
    digitalWrite(LED_PIN, LOW);
  }
  else if(command.indexOf("STDIO_ON") != -1)
  { 
    digitalWrite(LED_PIN, HIGH);
  }
}
 
void deliverMessage(const String& msg, int dt)
{
  Serial.println(msg);
  delay(dt);
}
