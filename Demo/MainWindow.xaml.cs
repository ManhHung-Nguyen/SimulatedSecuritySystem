using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Demo
{
    using Controllers;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {

            System.Mvc.Engine.Register(this, result => { });

            InitializeComponent();

            int i = 0;

            Controller.Browser = this;
            var device = new DeviceController();
            var mqtt = new MqttController();
            var sim = new SimController { 
                SmsNumber = smsNumber,
                SmsText = smsText,
                CallNumber = callNumber
            };
            var io = new IOController();

            foreach (Border border in inputGroup.Children)
            {
                var chk = (CheckBox)border.Child;
                chk.Tag = i++;

                chk.Click += (s, e) => {
                    io.SetInput((int)chk.Tag, chk.IsChecked.Value);
                };
            }

            List<Button> zones = new List<Button>();
            i = 0;
            foreach (Border border in beamGroup.Children)
            {
                var btn = (Button)border.Child;
                if (btn.Tag != null)
                {
                    btn.Click += (s, e) => {
                        io.ClearBeam();
                        foreach (var b in zones)
                        {
                            b.Background = Brushes.Black;
                        }
                    };
                    continue;
                }
                btn.Tag = i++;
                btn.Background = Brushes.Black;
                btn.Foreground = Brushes.White;

                zones.Add(btn);
                btn.Click += (s, e) => {
                    btn.Background = Brushes.Red;
                    io.CreateBeam((int)btn.Tag);
                };
            }

            btnPublish.Click += (s, e) => {
                var msg = mqttMsg.Text;
                if (!string.IsNullOrEmpty(msg))
                {
                   // mqtt.FromServer(msg);
                }
            };

            callAccept.Click += (s, e) => sim.AcceptCall();
            callDeny.Click += (s, e) => sim.DenyCall();

            var ts = new ThreadStart(() => { 
                while (true)
                {
                    Thread.Sleep(100);

                    mqtt.ReadAction();
                    sim.ReadAction();
                }
            });
            var th = new Thread(ts);
            th.Start();

            this.Closing += (s, e) =>
            {
                mqtt.Disconnect();
                th.Abort();
            };
        }
    }
}
