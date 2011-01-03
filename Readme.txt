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
4.  Create an Oblivion\Data\OBSE\Plugins\COEF_Example folder, and copy the Settings.ini to it from your working directory
5.  In your working directory, open COEF_Example.sln in Visual Studio and begin development.  You may get an error the first time you
    compile the solution, compile it at least twice before troubleshooting.