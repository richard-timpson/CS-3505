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
        private static SpreadsheetView ssView;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            SpreadsheetAplicationContext appContext = SpreadsheetAplicationContext.getAppContext();
            ClientLogIn startup = new ClientLogIn();

            ssView = startup.SSView;

            appContext.RunForm(startup);


            Application.Run(appContext);

        }

        public static void runView(Dictionary<string, IEnumerable<string>> cellDependencies)
        {
            SpreadsheetAplicationContext.getAppContext().RunForm(ssView);
            ssView.PopulateSpreadsheet(cellDependencies);
        }
    }
}
