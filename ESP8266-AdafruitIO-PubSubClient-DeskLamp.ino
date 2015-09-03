
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "WiFiPassword.h"
#include "AdafruitIOKey.h"




// EDIT THIS
#define FEED_PATH "tomn46037/feeds/cube-"





#define LIGHTS_ALL FEED_PATH"lights-all"
#define COLOR_ALL FEED_PATH"color-all"

#define LIGHTS_ONE FEED_PATH"lights-1"
#define COLOR_ONE FEED_PATH"color-1"

#define LIGHTS_TWO FEED_PATH"lights-2"
#define COLOR_TWO FEED_PATH"color-2"

#define LIGHTS_THREE FEED_PATH"lights-3"
#define COLOR_THREE FEED_PATH"color-3"


void callback(char* topic, byte* payload, unsigned int length) {
  
  // handle message arrived
  Serial.print("Recieved a message: ");
  Serial.print(topic);
  Serial.print(" => ");
  Serial.write(payload, length);
  Serial.println();

}

WiFiClient wifiClient;

PubSubClient mqttclient(AIO_SERVER, AIO_PORT, callback, wifiClient);

void setup() {

  Serial.begin(115200);
  Serial.println("Starting wifi.");

  WiFi.begin(ssid, pass);

  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 20)) {
    retries++;
    delay(500);
    Serial.println(retries);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
  }
  
  Serial.println(AIO_USERNAME);
  Serial.println(AIO_KEY);
  
  if (mqttclient.connect(AIO_CLIENT, AIO_USERNAME, AIO_KEY)) {
     Serial.println(F("MQTT Connected"));
     subscribe_all();
  }
  Serial.println("Done with attempt to connect to MQTT.");
 
}

int old_time = 0;

void loop() {

  // are we still connected?
  if (!mqttclient.connected()) {
    Serial.println("Re-connecting");
    subscribe_all();
  }
  
  if ( millis() > old_time + 10000 ) {
    old_time = millis();
    Serial.println("NOT Publishing..");
//    mqttclient.publish(FEED_PATH, "11");    
  }
 
  mqttclient.loop();
  delay(250);  

}

void subscribe_all(){
  
  Serial.println("Subscribing:");
  Serial.println(LIGHTS_ALL);
  Serial.println(COLOR_ALL);
  mqttclient.subscribe(LIGHTS_ALL);
  mqttclient.subscribe(COLOR_ALL);
//  mqttclient.subscribe(LIGHTS_ONE);
//  mqttclient.subscribe(COLOR_ONE);
//  mqttclient.subscribe(LIGHTS_TWO);
//  mqttclient.subscribe(COLOR_TWO);
//  mqttclient.subscribe(LIGHTS_THREE);
//  mqttclient.subscribe(COLOR_THREE);

}
