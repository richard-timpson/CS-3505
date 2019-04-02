using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JSonTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var mess = new
            {
                type = "edit",
                cell = "A1",
                value = "=2*A1+1+B3",
                Dependencies = new[] { "A1", "B1" }
            };


            Console.WriteLine(JsonConvert.SerializeObject(mess));

            string json = JsonConvert.SerializeObject(mess);

            var receive = new
            {
                type = "",
                cell = "",
                value = "",
                dependencies = new[] { "" }

            };


            var deserial = JsonConvert.DeserializeAnonymousType(json, receive);

            Console.WriteLine(deserial.type);
            Console.WriteLine(deserial.cell);
            Console.WriteLine(deserial.value);
            Console.WriteLine(deserial.dependencies[0]);


            Console.Read();



        }
    }
}
