/*
    Main unit for OBME submodules.  Handles:
    -   Initialization (writing hooks & patches)
    -   global debugging log
    -   global OBME interface

    This example plugin has two submodule DLLs - one for the CS, and one for the game.  
    This is necessary because the game and CS use slightly different definitions for many COEF classes.
    However, there is (usually) a lot of overlap between the code for the two.
    The best all-around solution, to minimize redefinition and the hassle similar but separate VS projects,
    is to use a single 'Submodule' project that compiles as the CS submodule under the 'Debug_CS' and 'Release_CS' 
    configurations, but compiles as the Game submodule under the 'Debug_Game' and 'Release_Game' configurations.
    IMPORTANT: this project must be compiled *twice*, once using a 'CS' configuration, and once using a 'Game'
    configuration.  One will generate a 'CS' dll, and the other a 'Game' dll. 
*/
#include "Submodule/Interface.h"

/*--------------------------------------------------------------------------------------------*/
// macro for strings that use "CS" or "Game" depending on compiler state
#ifdef OBLIVION
    #define DLLNAME(pre,post) (pre ## "Game" ## post)
#else
    #define DLLNAME(pre,post) (pre ## "CS" ## post)
#endif

/*--------------------------------------------------------------------------------------------*/
// global debugging log for the submodule
HTMLTarget _gLogFile(DLLNAME("Data\\obse\\plugins\\COEF_Example\\COEF_Example.",".log.html"),DLLNAME("COEF_Example.",".Log"));
OutputLog  _gLog;
OutputLog& gLog = _gLog;

/*--------------------------------------------------------------------------------------------*/
// global interfaces and handles
HMODULE hModule = 0;    // windows module handle ("instance") for this dll
char    sModuleName[0x100] = {{0}}; // name of this dll
SubmoduleInterface      g_submoduleIntfc;   // global submodule interface

/*--------------------------------------------------------------------------------------------*/
// submodule initialization
extern "C" _declspec(dllexport) void* Initialize()
{   
    // begin initialization  
    _MESSAGE("Initializing Submodule {%p} '%s' ...", hModule, sModuleName); 

    // ... Perform hooks & patches here
    
    // initialization complete
    _DMESSAGE("Submodule initialization completed sucessfully");
    return &g_submoduleIntfc;
}

/*--------------------------------------------------------------------------------------------*/
// submodule loading
#ifndef MFC
// Project uses standard windows libraries, define an entry point for the DLL to handle loading/unloading
BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:    // dll loaded
        // get submodule handle, name
        hModule = (HMODULE)hDllHandle;
        GetModuleFileName(hModule,sModuleName,sizeof(sModuleName));
        // attach log file to output handle & load rules from ini
        gLog.AttachTarget(_gLogFile);        
        _gLogFile.LoadRulesFromINI("Data\\obse\\Plugins\\COEF_Example\\Settings.ini",DLLNAME("",".Log"));
        // done loading
        _MESSAGE("Attaching Submodule {%p} '%s' ...", hModule, sModuleName); 
        break;
    case DLL_PROCESS_DETACH:    // dll unloaded
        _MESSAGE("Detaching Submodule {%p} '%s' ...", hModule, sModuleName);      
        gLog.DetachTarget(_gLogFile);
        break;
    }   
    return true;
}
#else
// Project uses MFC, we define here an instance of CWinApp to make this a 'well-formed' DLL
class CSubmoduleApp : public CWinApp
{
public:
    virtual BOOL InitInstance()
    {// dll loaded
        // get submodule handle, name
        hModule = m_hInstance;
        GetModuleFileName(hModule,sModuleName,sizeof(sModuleName));
        // attach log file to output handle & load rules from ini
        gLog.AttachTarget(_gLogFile);      
        _gLogFile.LoadRulesFromINI("Data\\obse\\Plugins\\COEF_Example\\Settings.ini",DLLNAME("",".Log"));
        // done loading
        _MESSAGE("Initializing Submodule {%p} '%s' ...", hModule, sModuleName); 
        return true;
    }
    virtual int ExitInstance() 
    {// dll unloaded
       _MESSAGE("Exiting Submodule {%p} '%s' ...", hModule, sModuleName);      
        gLog.DetachTarget(_gLogFile);
       return CWinApp::ExitInstance();
    }
} gApp;
#endif