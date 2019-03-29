using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SpreadsheetGUI
{
    static class SpreadsheetGUI
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            // Start an application context and run one form inside it
            SpreadsheetAplicationContext appContext = SpreadsheetAplicationContext.getAppContext();
            appContext.RunForm(new Form1());
            Application.Run(appContext);


            //****
            //Application.Run(new Form1());
        }
    }
}
