#include <WiFi.h>
#include <HTTPClient.h>
#include "EmonLib.h"

EnergyMonitor STC0131;
EnergyMonitor STC0132;
EnergyMonitor STC0133;

int SCT1 = 36;
int SCT2 = 34;
int SCT3 = 32;
const int tension = 110; 
float potencia1, potencia2, potencia3;

const char* ssid = "Luisifer";            // Your network SSID (name)
const char* password = "cradleoffilth21";    // Your network password
const char* serverName = "http://192.168.100.25:5000/Potencia/readings"; // Server URL

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  // Readings 
  STC0131.current(SCT1, 0.425); //el 0.425 se calcula para cada caso
  STC0132.current(SCT2, 0.425); 
  STC0133.current(SCT3, 0.425); 
  
  double Irms1 = STC0131.calcIrms(4096);
  double Irms2 = STC0132.calcIrms(4096);
  double Irms3 = STC0133.calcIrms(4096);
  
  potencia1 = Irms1 * tension;
  potencia2 = Irms2 * tension;
  potencia3 = Irms3 * tension;

  Serial.print(Irms1);
  Serial.print("mA, ");
  Serial.print(potencia1);
  Serial.println("W");

  Serial.print(Irms2);
  Serial.print("mA, ");
  Serial.print(potencia2);
  Serial.println("W");
  
  Serial.print(Irms3);
  Serial.print("mA, ");
  Serial.print(potencia3);
  Serial.println("W");
  
  if (isnan(potencia1) || isnan(potencia2) || isnan(potencia3)) {
    Serial.println("Failed to read from SCT013 sensor!");
  } else {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      String httpRequestData = "{\"firstSensor\":" + String(potencia1, 1) + ",\"secondSensor\":" + String(potencia2, 1) + ", \"thirdSensor\":" + String(potencia3, 1) + "}";
      
      Serial.print("Sending data: ");
      Serial.println(httpRequestData);
      
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        Serial.println(response);
      }
      else {
        Serial.println("Error on sending POST: " + String(httpResponseCode));
      }
      http.end();
    }
  }

  // Go to deep sleep for 60 seconds
  esp_sleep_enable_timer_wakeup(60 * 1000000);
  esp_deep_sleep_start();
}

void loop() {
  // This is not used as the device is either sending data or in deep sleep.
}
