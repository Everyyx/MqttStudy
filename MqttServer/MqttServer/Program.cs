using MQTTnet;
using MQTTnet.Protocol;
using MQTTnet.Server;
using System;
using System.Net;
using System.Threading.Tasks;

namespace mqttServer
{
    class Program
    {
        static void Main(string[] args)
        {
            MyWriteLine("Start running mqtt server......");
            Task.Run(RunServerTaskAsync);
            MyWriteLine("Press anykey to exit.....");
            Console.ReadKey();
        }

        public static async Task RunServerTaskAsync()
        {
            var mqttServer = new MqttFactory().CreateMqttServer();

            IPAddress iPAddress = IPAddress.Parse("192.168.137.1");
            var optionBuilder = new MqttServerOptionsBuilder()
                .WithConnectionBacklog(100)
                .WithDefaultEndpointBoundIPAddress(iPAddress)
                .WithDefaultEndpointPort(1883);

            var options = optionBuilder.Build();
            (options as MqttServerOptions).ConnectionValidator = c =>
            {
                if (c.ClientId.Length < 10)
                {
                    c.ReturnCode = MqttConnectReturnCode.ConnectionRefusedIdentifierRejected;
                    return;
                }

                if (c.Username != "user")
                {
                    c.ReturnCode = MqttConnectReturnCode.ConnectionRefusedBadUsernameOrPassword;
                    return;
                }

                if (c.Password != "password")
                {
                    c.ReturnCode = MqttConnectReturnCode.ConnectionRefusedBadUsernameOrPassword;
                    return;
                }

                c.ReturnCode = MqttConnectReturnCode.ConnectionAccepted;
            };

            MyWriteLine("Mqttsever is Starting.....");
            await mqttServer.StartAsync(options);

            mqttServer.ClientConnected += (s, e) =>
            {
                 MyWriteLine($"{e.ClientId} has connected!");
            };

            mqttServer.ClientDisconnected += (s, e) =>
            {
                MyWriteLine($"{e.ClientId} has ClientDisconnected");
            };

            mqttServer.Started += (s, e) =>
            {
                MyWriteLine("The mqtt server has started!");

            };

            mqttServer.Stopped += (s, e) =>
            {
                MyWriteLine("The mqttserver has stopped!");
            };

            mqttServer.ApplicationMessageReceived += (s, e) =>
              {
                  MyWriteLine($"Receive message from  client-{e.ClientId}:");
                  MyWriteLine($"Topic:{e.ApplicationMessage.Topic}\n");
                  //MyWriteLine($"ContenType:{e.ApplicationMessage.ContentType}");
                  //MyWriteLine($"{e.ApplicationMessage.Payload.ToString()}");

              };
            
            Console.WriteLine("Press any key to stop the server.");
            Console.ReadLine();
            await mqttServer.StopAsync();

            
        }

        public static void MyWriteLine(string msg)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(msg);
        }
    }
}

