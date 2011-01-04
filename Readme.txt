Requirements for Developers:
============================
1.  Common Oblivion Engine Framework
2.  Oblivion Script Extender, v19 or later
3.  A TR1 compliant version of Visual Studio (2008 with TR1 extras installed, or 2010 or later)

Setup Instructions for Developers:
==================================
1.  Extract the archive to a working directory for development
2.  Open COEF_Example.sln in a text editor and find the line beginning with
        Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "COEF"
    Enter the path (relative or absolute) to COEF.vcproj, found in your COEF directory
3.  Open EnvPaths.vsprops in a text editor, and change the paths it contains:
        COEFPATH - the path (relative or absolute) of your COEF directory
        OBSEPATH - the path (relative or absolute) to the OBSE source code directory containing 'Common' and 'OBSE' subdirectories
        OBLIVIONPATH - the path to your Oblivion\ directory
4.  (Optional) Rename COEF_Example.sln to the project name of your choice.  All internal strings (log file names, plugin name
    provided to OBSE, etc). should automatically reflect whatever name you choose.
5.  Navigate to your Oblivion\Data\OBSE\Plugins\ directory and create a new folder called COEF_Example, or whatever name you chose
    in step 4.  Copy the Settings.ini to this new folder from your working directory.
6.  Open the solution in Visual Studio and begin development.  You may get an error the first time you compile the code;
    compile it at least twice before troubleshooting.