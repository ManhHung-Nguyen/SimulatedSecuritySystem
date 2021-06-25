using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Demo.Controllers
{
    class IOController : Controller
    {
        int inputs = 0;
        Random rand = new Random();
        public void SetInput(int index, bool high)
        {
            int v = 1 << index;

            if (high)
            {
                inputs |= v;
            }
            else
            {
                inputs ^= v;
            }
            Response("INP(" + inputs + ")");
        }
        public void CreateBeam(int index)
        {
            int a = index << 6;
            int b = a + 64;
            int beam = rand.Next(a, b);
            if (beam == 0) { beam = 15; }

            Response("BEAM(" + beam + ")");
        }
        public void ClearBeam()
        {
            Response("BEAM(0)");
        }
    }
}
