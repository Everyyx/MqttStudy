using System;
using System.Threading.Tasks;
using MqttClient;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Client.Connecting;
using MQTTnet.Client.Options;

namespace MqttClient
{
    class Program
    {


        static void Main(string[] args)
        {
            //Task.Run(RunClientTaskAsync);
            MqttclientConnect();
            MyTrueWriteLine("press anykey to stop client....");
            Console.ReadKey();
        }

        public static async Task RunClientTaskAsync()
        {
            MyTrueWriteLine("Creating a new client.....");
            var mqttclient = new MqttFactory().CreateMqttClient();
            MqttClientTcpOptions mqttClientTcpOptions = new MqttClientTcpOptions()
            {
                Server = "127.0.0.1",
                Port = 1883,
            };
            var optionbuilder = new MqttClientOptionsBuilder()
                .WithWillMessage(BuildMessage())
                .WithTcpServer("127.0.0.1", 1883)
                .WithClientId("Test1")
                .WithCredentials("user", "password")
                .WithTls()
                .WithCommunicationTimeout(new TimeSpan(0,0,20))
                .WithKeepAlivePeriod(new TimeSpan(0,0,20))
                .WithCleanSession(true);
                
            var options = optionbuilder.Build();
            
            
            MyTrueWriteLine("Client starting to connect the server......");
            try
            {

                MqttClientConnectResult clientConnectResult= await mqttclient.ConnectAsync(options);              
                MyTrueWriteLine("The result of action:"+clientConnectResult.ToString());
            }
            catch (Exception e)
            {
                MyTrueWriteLine("Failed:"+Environment.NewLine + e);
            }
 
            mqttclient.Connected += (s, e) =>
              {
                  MyTrueWriteLine("Client has connected to server successfully!");
                  MyTrueWriteLine($"Detail:{e.ConnectResult.ToString()}");
              };
            mqttclient.Disconnected += (s, e) =>
              {
                  MyTrueWriteLine("Client has disconnected from the server");
              };
        }

        public static void MyTrueWriteLine(string msg)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(msg);
        }

        public static MqttApplicationMessage BuildMessage()
        {
            var message = new MqttApplicationMessageBuilder()
                .WithAtMostOnceQoS()
                .WithPayload("123")
                .WithTopic("test.netcore");
            return message.Build();
        }

        public static async void MqttclientConnect()
        {
            try
            {

                var clientoptions = new MqttClientOptions();
                clientoptions.ChannelOptions = new MqttClientTcpOptions()
                {
                    Server = "192.168.137.1",
                    Port = 1883
                };
                clientoptions.Credentials = new MqttClientCredentials()
                {
                    Username = "user",
                    Password = "password"
                };
                clientoptions.CleanSession = true;
                clientoptions.KeepAlivePeriod = TimeSpan.FromSeconds(100.0);
                clientoptions.KeepAliveSendInterval = TimeSpan.FromSeconds(20000);

                var mqttclient = new MqttFactory().CreateMqttClient();

                await mqttclient.ConnectAsync(clientoptions);
            }
            catch (Exception)
            {

                throw;
            }
        }
    }
}
