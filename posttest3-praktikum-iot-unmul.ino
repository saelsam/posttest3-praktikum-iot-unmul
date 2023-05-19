#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
// #include <BlynkSimpleEsp32.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BLYNK_TEMPLATE_ID "TMPL6W5QUhrBs"
#define BLYNK_TEMPLATE_NAME "intensitas cahaya"
#define BLYNK_AUTH_TOKEN "6eoKPmNvzRPaasnHESux8HK9pG4w-LNb"
#define BLYNK_PRINT Serial

BH1750 lightMeter;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

float lux;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Universitas Mulawarman";
char pass[] = "";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Wire.begin();
  lightMeter.begin();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  // Blynk.begin(auth, ssid, pass, "sgp1.blynk.cloud", 80);
}

void loop() {
  sensorcahaya();
  kirimdatablynk();
  // delay(1000);
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}

void sensorcahaya() {
  lux = lightMeter.readLightLevel();
}

void kirimdatablynk() {
  // Blynk.virtualWrite(V0, lux);
  Blynk.run();
}