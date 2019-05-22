using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SpreadsheetGUI
{
    /// <summary>
    /// Keeps track of the number of forms that are running
    /// </summary>
    public class SpreadsheetAplicationContext : ApplicationContext
    {

        // Number of open forms
        private int formCount = 0;

        // Singleton ApplicationContext
        private static SpreadsheetAplicationContext appContext;

        /// <summary>
        /// Private constructor for singleton pattern
        /// </summary>
        private SpreadsheetAplicationContext()
        {
        }

        /// <summary>
        /// Returns the one DemoApplicationContext.
        /// </summary>
        public static SpreadsheetAplicationContext getAppContext()
        {
            // if no appContext has been given return the default
            if (appContext == null)
            {
                appContext = new SpreadsheetAplicationContext();
            }
            return appContext;
        }

        /// <summary>
        /// Runs the form
        /// </summary>
        public void RunForm(Form form)
        {
            // One more form is running
            formCount++;

            // When this form closes, we want to find out if there are no more forms open close 
            // the appliaction
            form.FormClosed += (o, e) => { if (--formCount <= 0) ExitThread(); };

            // Run the form
            form.Show();
        }
    }
}
