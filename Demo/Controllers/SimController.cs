using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace Demo.Controllers
{
    class SimController : Controller
    {
        public TextBlock SmsNumber { get; set; }
        public TextBlock SmsText { get; set; }
        public TextBlock CallNumber { get; set; }
        string GetAT()
        {
            var v = FileContext.Value.ToString().ToCharArray();
            int i = 0, k = 0;
            while (i < v.Length)
            {
                int high = ToChar(v[i++]);
                int low = ToChar(v[i++]);
                v[k++] = (char)((high << 4) | low);
            }

            var s = new string(v, 0, k);
            return s;
        }
        public void ATCommand()
        {
            string s = GetAT();
            int i = s.IndexOf("+84");
            if (i > 0)
            {
                int k = s.IndexOf('\"', i + 3);
                if (k > 0)
                {
                    SmsNumber.Text = s.Substring(i, k - i);

                    i = k + 2;
                    k = s.IndexOf((char)26, k);
                    SmsText.Text = s.Substring(i, k - i);
                    return;
                }

                k = s.IndexOf(';', i + 3);
                if (k > 0)
                {
                    CallNumber.Text = s.Substring(i, k - i);
                }
            }
        }
        public void AcceptCall()
        {
            Response("sim", "PASS: 4");
        }
        public void DenyCall()
        {
            Response("sim", "NO CARRY");
        }
    }
}
