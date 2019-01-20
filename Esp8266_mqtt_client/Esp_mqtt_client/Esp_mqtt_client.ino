/*
 Name:		Esp_mqtt_client.ino
 Created:	2019/1/20 11:12:07
 Author:	every
*/

// the setup function runs once when you press reset or power the board
#include <WiFiUdp.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <CertStoreBearSSL.h>
#include <BearSSLHelpers.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "LAPTOP"
#define STAPSK "awr126126"
#endif // !STASSID

const char* ssid = STASSID;
const char* password = STAPSK;
const char* mqtt_server = "192.168.137.1";
const int mqtt_serverport = 1883;
const char* clientID = "esp8266test";
const char* username = "user";
const char* mqttpassword = "password";
const int willQos = 0;
const int willRetain = 0;


WiFiClient espClient;
PubSubClient mqttClient(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi()
{
	//start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to :");
	Serial.println(ssid);
	/* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
	would try to act as both a client and an access-point and could cause
	network-issues with your other WiFi-devices on your WiFi-network. */
	WiFi.mode(WIFI_AP_STA);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print("wifi connected failed!");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	// Switch on the LED if an 1 was received as first character
	if ((char)payload[0] == '1') {
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
		// but actually the LED is on; this is because
		// it is active low on the ESP-01)
	}
	else {
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
	}

}
void reconnect()
{
	// Loop until we're reconnected
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Create a random client ID
		String clientId = "ESP8266Client-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
		if (mqttClient.connect(clientId.c_str(), username, mqttpassword)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			mqttClient.publish("outTopic", "hello world");
			// ... and resubscribe
			mqttClient.subscribe("inTopic");
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup() {
	Serial.begin(115200);
	setup_wifi();//setup_wifi
	Serial.println("start setting server....");
	mqttClient.setServer(mqtt_server, mqtt_serverport);
	Serial.println("setting callback....");
	mqttClient.setCallback(callback);

}

// the loop function runs over and over again until power down or reset
void loop() {
	if (!mqttClient.connect(clientID,username,mqttpassword))
	{
		reconnect();
	}
	mqttClient.loop();
	long now = millis();
	if (now - lastMsg > 2000) {
		lastMsg = now;
		++value;
		snprintf(msg, 50, "hello world #%ld", value);
		Serial.print("Publish message: ");
		Serial.println(msg);
		mqttClient.publish("outTopic", msg);
	}
}
