#include <Arduino.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "max6675.h"

#define MOTOR 16
#define KDO 12
#define KCS 15
#define KCLK 14

MAX6675 thermocouple(KCLK, KCS, KDO);

MqttConnector *mqtt;

#define MQTT_HOST         "mqtt.espert.io"
#define MQTT_PORT         1883
#define MQTT_USERNAME     ""
#define MQTT_PASSWORD     ""
#define MQTT_CLIENT_ID    ""
#define MQTT_PREFIX       "/CMMC"
#define PUBLISH_EVERY     (1*1000)// every 10 seconds

/* DEVICE DATA & FREQUENCY */
#define DEVICE_NAME       "CMMC-CupCoff"

/* WIFI INFO */
#ifndef WIFI_SSID
  #define WIFI_SSID        "ESPERT-002"
  #define WIFI_PASSWORD    "espertap"
#endif

#include "_publish.h"
#include "_receive.h"
#include "init_mqtt.h"


void init_hardware()
{
  Serial.begin(115200);
  delay(10);
  pinMode(MOTOR, OUTPUT);
  Serial.println();
  Serial.println("Serial port initialized.");
}

void setup()
{
  init_hardware();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.printf ("Connecting to %s:%s\r\n", WIFI_SSID, WIFI_PASSWORD);
    delay(300);
  }

  Serial.println("WiFi Connected.");

  init_mqtt();
}

void loop()
{
  mqtt->loop();
}
