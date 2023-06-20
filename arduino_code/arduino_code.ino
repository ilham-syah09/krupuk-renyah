#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);

// LCD
#include <LiquidCrystal_I2C.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27, 16, 2);

// SCL -> A5
// SDA -> A4

//library sensor suhu
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float suhu = 0;

char c;
String data, statusKipas, statusHeater;
int suhuSetting = 30;

#define pinKipas 6
#define pinHeater 7

#define relay_on LOW
#define relay_off HIGH

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  mlx.begin();

  pinMode(pinKipas, OUTPUT);
  digitalWrite(pinKipas, relay_off);

  pinMode(pinHeater, OUTPUT);
  digitalWrite(pinHeater, relay_off);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(1, 1);
  lcd.print("PENGERING UDANG");
  
  delay(3000);
}

void loop() {
  getSuhuSetting();
  
  suhu = mlx.readObjectTempC();

  Serial.println("Suhu : " + (String) suhu);
  Serial.println("Suhu Setting : " + (String) suhuSetting);
  
  Serial.println();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SUHU  : ");
  lcd.setCursor(8, 0);
  lcd.print(suhu);

  if (suhu <= suhuSetting) {
    statusKipas = "ON";
    statusHeater = "ON";
    digitalWrite(pinKipas, relay_on);
    digitalWrite(pinHeater, relay_on);
  } else {
    statusKipas = "OFF";
    statusHeater = "OFF";
    digitalWrite(pinKipas, relay_off);
    digitalWrite(pinHeater, relay_off);
  }

  Serial.println("Status Kipas : " + statusKipas);
  Serial.println("Status Heater : " + statusHeater);

  lcd.setCursor(0, 1);
  lcd.print("KIPAS : ");
  lcd.setCursor(8, 1);
  lcd.print(statusKipas);

  mySerial.println((String) suhu + "#" + statusKipas + "#ok");

  Serial.println();

  delay(500);
}

void getSuhuSetting() {
  while(mySerial.available() > 0) {
    delay(10);
    c = mySerial.read();
    data += c;
  }
  
  if (data.length() > 0) {
    data.trim();
    
    Serial.println("Pembacaan Serial : " + data);

    Serial.println();

    String shSt = getValue(data, '#', 0);
    String statusOk = getValue(data, '#', 1);
    
    if (statusOk == "OK") {
      suhuSetting = shSt.toInt(); 
    }
    
    Serial.println("Suhu Setting : " + (String) suhuSetting);

    Serial.println();

    data = "";
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
 
  for(int i=0; i <= maxIndex && found <= index; i++){
    if(data.charAt(i) == separator || i == maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  } 
 
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
