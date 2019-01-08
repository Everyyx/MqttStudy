using System;
using System.Threading.Tasks;
using MqttClient;
using MQTTnet;
using MQTTnet.Client.Connecting;
using MQTTnet.Client.Options;

namespace MqttClient
{
    class Program
    {

        static void Main(string[] args)
        {
            Task.Run(RunClientTaskAsync);
            MyTrueWriteLine("press anykey to stop client....");
            Console.ReadKey();
        }

        public static async Task RunClientTaskAsync()
        {
            MyTrueWriteLine("Creating a new client.....");
            var mqttclient = new MqttFactory().CreateMqttClient();
            var optionbuilder = new MqttClientOptionsBuilder()
                //.WithWillMessage(null)
                .WithTcpServer("127.0.0.1", 1883)
                .WithClientId("Test1")
                .WithCredentials("user", "password")
                .WithTls()
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

    }
}
