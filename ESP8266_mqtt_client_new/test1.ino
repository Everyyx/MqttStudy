#include <ESP8266WiFi.h>
    #include <PubSubClient.h>
    
    const char* ssid = "B98E";//连接的路由器的名字
    const char* password = "an@686996cao686996@";//连接的路由器的密码
    const char* mqtt_server = "192.168.1.106";//服务器的地址 
    const int port=1883;//服务器端口号
    
    const char* topic_name = "config_change/esp8266";//订阅的主题
    const char* client_id = "esp8266_0000002";//尽量保持唯一，相同的id连接会被替代
    const int Gpio2=2;//gpio_control
    WiFiClient espClient;
    PubSubClient client(espClient);
    
    //初始化WIFI
    void setup_wifi() {//自动连WIFI接入网络
      delay(10);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("...");
        
      }
    }
    
    
    void callback(char* topic, byte* payload, unsigned int length) {
      String callMsg = "";
      Serial.print("Message arrived [");
      Serial.print(topic);   // 打印主题信息
      Serial.print("] ");
    
      for (int i = 0; i < length; i++) {
        callMsg += char(payload[i]);
      }
      
      Serial.println(callMsg);
      
      //如果返回ON关闭LED
      if(callMsg.equals("ON")){
           //digitalWrite(Gpio2, LOW);   // Turn the LED on (Note that LOW is the voltage level
           digitalWrite(Gpio2,HIGH);
        }
    
       //如果返回OFF关闭LED
      if(callMsg.equals("OFF")){
           //digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED off by making the voltage HIGH
           digitalWrite(Gpio2,LOW);  
           
        }
    }
    
    
    
    
    void reconnect() {//等待，直到连接上服务器
      while (!client.connected()) {//如果没有连接上
        if (client.connect(client_id,"user","password")) {//接入时的用户名，尽量取一个很不常用的用户名
          client.subscribe(topic_name);//接收外来的数据时的intopic
          Serial.println("connect success");
        } else {
          Serial.print("failed, rc=");//连接失败
          Serial.print(client.state());//重新连接
          Serial.println(" try again in 5 seconds");//延时5秒后重新连接
          delay(5000);
        }
      }
    }
    
    
    void setup() {//初始化程序，只运行一遍
      Serial.begin(115200);//设置串口波特率（与烧写用波特率不是一个概念）
      
      //pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
      pinMode(2,OUTPUT);
      digitalWrite(2,LOW);
      //digitalWrite(LED_BUILTIN, HIGH);
      
      setup_wifi();//自动连WIFI接入网络
      client.setServer(mqtt_server, port);//端口号
      client.setCallback(callback); //用于接收服务器接收的数据
    }
    
    
    
    
    void loop() {//主循环
      String msg = "";//用于存放
       reconnect();//确保连上服务器，否则一直等待。
       client.loop();//MUC接收数据的主循环函数。
      
       
      while (Serial.available() > 0)  
        {
            msg += char(Serial.read());
            delay(2);
        }
        int msglen = msg.length();
        if (msglen > 0)
        {
            Serial.println(msg);
            char msgArr[msglen+1];
            msg.toCharArray(msgArr,msglen + 1);
            client.publish(topic_name,msgArr);
        }
       
    }
