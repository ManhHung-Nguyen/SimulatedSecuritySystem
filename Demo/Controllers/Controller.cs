using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using uPLibrary.Networking.M2Mqtt;
using Vst;

namespace Demo
{
    public class FileContext 
    {
        public string Action { get; set; }
        public object Value { get; set; }
        public string DeviceId { get; set; }
    }
    public class Controller : System.Mvc.Controller
    {
        Dictionary<string, string> _file_content = new Dictionary<string, string>();
        public static System.Windows.Window Browser { get; set; }
        string BinPath(string name)
        {
            return "d:\\test\\" + name + ".bin";
        }
        public virtual void BinaryWrite(string name, int value)
        {
            using (var bw = new BinaryWriter(File.Open(BinPath(name), FileMode.OpenOrCreate)))
            {
                bw.Write(value);
            }
        }
        public void Response(string name, string content)
        {
            try
            {
                using (var sw = new StreamWriter(BinPath(name)))
                {
                    sw.Write(content);
                }
            }
            catch
            {

            }
        }
        public string ReadFile(string name, Action<string> callback)
        {
            try
            {
                string content = string.Empty;
                if (_file_content.ContainsKey(name) == false) 
                {
                    _file_content.Add(name, content);
                }

                var fi = new FileInfo(BinPath(name));
                if (fi.Exists)
                {

                    using (var sr = fi.OpenText())
                    {
                        StringBuilder sb = new StringBuilder();
                        while (true)
                        {
                            int c = sr.Read();
                            if (0 >= c) break;

                            if (c < 128)
                            {
                                sb.Append((char)c);
                            }
                        }
                        content = sb.ToString();
                        if (content != _file_content[name])
                        {
                            _file_content[name] = content;
                        }
                        else
                        {
                            content = null;
                        }
                        if (!string.IsNullOrEmpty(content) && callback != null)
                        {
                            Browser.Dispatcher.InvokeAsync(() => {
                                callback.Invoke(content);
                            });
                        }
                    }
                    //fi.Delete();
                }

            }
            catch
            {

            }
            return null;
        }

        protected FileContext FileContext;
        public void ReadAction(string name)
        {
            ReadFile(name, s => {
                try
                {
                    FileContext = Json.GetObject<FileContext>(s);
                    var method = base.GetMethod(FileContext.Action);
                    if (method != null)
                    {
                        method.Invoke(this, new object[] { });
                        Response(name, "");
                    }
                }
                catch
                {
                    Console.WriteLine("ERROR: " + s);
                }
            });
        }
        public void ReadAction()
        {
            ReadAction("device");
        }
        public void Response(string content)
        {
            Response("system", content);
        }

        protected int ToChar(int hex)
        {
            if (hex >= 65) return hex - 55;
            return hex & 15;
        }
    }
}
