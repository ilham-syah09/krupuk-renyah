// Wifi
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
// Buat object Wifi
ESP8266WiFiMulti WiFiMulti;
// Buat object http
HTTPClient http;
WiFiClient client;
#define USE_SERIAL Serial

String host = "http://192.168.181.7/kerupuk/alat";
String urlSimpanData = host + "/simpanData?suhu=";
String urlGetSuhu = host + "/getSetting";

String respon;

// LCD
#include <LiquidCrystal_I2C.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27, 16, 2);

// SCL -> D1
// SDA -> D2

//library sensor suhu
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float suhu = 0;

char c;
String data, statusKipas, statusHeater;
int suhuSetting = 30;

#define pinKipas D5
#define pinHeater D6

#define relay_on LOW
#define relay_off HIGH

void setup()
{
  Serial.begin(115200);
  
  USE_SERIAL.begin(115200);
  USE_SERIAL.setDebugOutput(false);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("hp murah", "12345678"); // Sesuaikan SSID dan password ini
  
  Serial.println();

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
  lcd.setCursor(0, 1);
  lcd.print("PENGERING KRUPUK");
  
  delay(3000);
  
  for (int u = 1; u <= 5; u++)
  {  
    if ((WiFiMulti.run() == WL_CONNECTED))
    {
      USE_SERIAL.println("Internet Connected");
      USE_SERIAL.flush();
    }
    else
    {
      USE_SERIAL.println("No Internet Connected");
      USE_SERIAL.flush();
    }

    delay(1000);
  }
  
  Serial.println();

  delay(1000);
}

void loop()
{
  getSettingSuhu();
  
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
  
  Serial.println();

  kirimDatabase(suhu, statusKipas);

  Serial.println();
  delay(500);
}

void kirimDatabase(int suhu, String statusKipas) {
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    http.begin(client, urlSimpanData + (String) suhu + "&status=" + statusKipas);

    USE_SERIAL.print("[HTTP] Kirim ke database ...\n");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      USE_SERIAL.printf("[HTTP] kode response GET : %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) // code 200
      {
        respon = http.getString();
        
        USE_SERIAL.println("Respon kirim data : " + respon);

        Serial.println();
      }
    }
    else
    {
      USE_SERIAL.printf("[HTTP] GET data gagal, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void getSettingSuhu() {
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    USE_SERIAL.print("[HTTP] Memulai ambil suhu setting...\n");

    http.begin(client, urlGetSuhu);

    int httpCode = http.GET();

    if (httpCode > 0)
    {
      USE_SERIAL.printf("[HTTP] kode response GET : %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) // code 200
      {
        suhuSetting = http.getString().toInt();
        
        USE_SERIAL.println("Setting suhu : " + (String) suhuSetting);

        Serial.println();
      }
    }
    else
    {
      USE_SERIAL.printf("[HTTP] GET data gagal, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
