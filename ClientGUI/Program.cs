using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using SpreadsheetGUI;

namespace ClientGUI
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            SpreadsheetAplicationContext appContext = SpreadsheetAplicationContext.getAppContext();
            appContext.RunForm(new ClientLogIn());
            Application.Run(appContext);

            //SpreadsheetAplicationContext appContext = SpreadsheetAplicationContext.getAppContext();
            //appContext.RunForm(new ClientLogIn());
            //// Application.Run(new ClientLogIn());
            //Application.Run(appContext);
        }
    }
}
