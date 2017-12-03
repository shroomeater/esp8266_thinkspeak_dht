#include "DHT.h"
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

#define DHTPIN D1
#define DHTTYPE DHT11

const char* ssid = "HUAWEI-E5172-E9FC";
const char* password = "0M65JFMA5BA";
WiFiClient  client;
unsigned long myChannelNumber = 377981;
//unsigned long myChannelNumber = CHANNEL_ID;

const char* myWriteAPIKey = "NG511VC425ICKQQL";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  ThingSpeak.begin(client);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Error en la lectura del sensor!\n");
    return;
  }
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C \n");
  ThingSpeak.setField(1, (float)t);
  ThingSpeak.setField(2, (float)h);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(300000); 
}
