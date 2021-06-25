using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using uPLibrary.Networking.M2Mqtt;

namespace Demo.Controllers
{
    public class MqttController : Controller
    {
        static MqttClient _mqttClient;
        const string host = "localhost";

        public MqttClient Client => _mqttClient;
        public event Action OnClientConnectionChanged;
        protected virtual void OnConnectError(Exception e)
        {
            Console.WriteLine(e.Message);
        }
        public void ConnectToServer(string clientId, int checkConnectionSeconds = 0)
        {
            if (clientId == null)
            {
                if (_mqttClient != null && (_mqttClient.IsConnected || clientId == _mqttClient.ClientId))
                {
                    return;
                }
            }
            else
            {
                Disconnect();
            }

            BinaryWrite(null, 0);
            Console.Write("Connect to " + host + "...");
            try
            {
                _mqttClient = new MqttClient(
                    host,
                    1883,
                    false,
                    MqttSslProtocols.None,
                    null,
                    null
                );
                _mqttClient.MqttMsgPublishReceived += (s, e) => {
                    Response(Encoding.ASCII.GetString(e.Message));
                };
                _mqttClient.ConnectionClosed += (s, e) => {
                    //OnClientConnectionChanged?.Invoke();
                    //BinaryWrite(null, 0);
                    Response("NET(0)");
                };

                if (clientId == null)
                {
                    clientId = Guid.NewGuid().ToString();
                }
                _mqttClient.Connect(clientId);
                if (_mqttClient.IsConnected)
                {
                    //OnClientConnectionChanged?.Invoke();
                    //BinaryWrite(null, 1);

                    Response("NET(1)");
                    _mqttClient.Subscribe(
                        new string[] { "response/default/" + clientId }, 
                        new byte[] { 0 });
                }
            }
            catch (Exception e)
            {
                OnConnectError(e);
            }
        }
        public void Connect()
        {
            string clientId = FileContext.DeviceId;
            if (clientId == null) { clientId = Guid.NewGuid().ToString(); }

            ConnectToServer(clientId);
        }
        public void Disconnect()
        {
            if (IsConnected)
            {
                _mqttClient.Disconnect();
            }
        }
        public bool IsConnected => _mqttClient != null && _mqttClient.IsConnected;
        public void Subscribe()
        {
            _mqttClient?.Subscribe(new string[] { FileContext.Value.ToString() }, new byte[] { 0 });
        }
        public void Publish()
        {
            _mqttClient?.Publish("device", Encoding.ASCII.GetBytes(FileContext.Value.ToString()));
        }
    }
}
