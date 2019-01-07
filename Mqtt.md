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

above all, it's a lightweight message queeing and transport protocol
