# MQTT with .Net core

## What is MQTT

**A Message Protocol:**

+ a small code footprint and on-the-wire footprint
+ a published-subscribe-based messaging protocol
+ on top of Tcp/IP
+ websocket support with mosquitto
+ require a broker （e.g mosquitto,hivemq,Azure Iot Hub,....)
**A message bus for:**
+ unreliable,hight latency,low bandwidth
+ payload with a plain byte array
+ IANA Port:1883 and with TLS 8883

above all, it's a lightweight message queueing and transport protocol

## MQTT Learning Materials:

IBM develper:
<https://www.ibm.com/developerworks/cn/iot/iot-mqtt-why-good-for-iot/index.html>

MCXIAOKE:
<https://mcxiaoke.gitbooks.io/mqtt-cn/content/>

## MQTT Tool Box

Tool box:<https://www.hivemq.com/mqtt-toolbox/>

**MQTTLens**(*whitch i used*):MQTTLens is build on top of MQTT.js. All UI components are created with HTML and JavaScript, based on Polymer and Web Components.

## What will been included in this project?

* MqttServer.Console
* MqttClient.Console(unstable,easily disconnect by itself)
* MqttClient.Esp8266
* MqttServer.uwp
* MqttClient.uwp
* MqttBroker.web

## Illustration

![illustration png](https://github.com/Everyyx/MqttStudy/blob/master/illustration.PNG)
