#include <vector>

#ifdef G4MULTITHREADED
    #include <G4MTRunManager.hh>
    using RunManager = G4MTRunManager;
#else
    #include <G4RunManager.hh>
    using RunManager = G4RunManager;
#endif

#ifdef G4VIS_USE
#include <G4VisExecutive.hh>
#endif

#ifdef G4UI_USE
#include <G4UIExecutive.hh>
#endif
#include <G4MTRunManager.hh>
#include <G4RunManager.hh>
#include <G4String.hh>

#include <G4UImanager.hh>

#include <G4ScoringManager.hh>

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

using namespace std;

/* Main function that enables to:
 * - run any number of macros (put them as command-line arguments)
 * - start interactive UI mode (no arguments or "-i")
 */
int main(int argc, char** argv)
{

    std::cout<<" Application starting ....."<<std::endl;


    vector<G4String> macros;
    bool interactive = false;

    // Parse command line arguments
    if  (argc == 1)
    {
        interactive = true;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            G4String arg = argv[i];
            if (arg == "-i" || arg == "--interactive")
            {
                interactive = true;
                continue;
            }
            else
            {
                macros.push_back(arg);
            }
        }
    }

 /*       //Use sequential mode only
        G4RunManager* runManager = new G4RunManager();
        runManager->SetVerboseLevel(1);
*/

    // Create the run manager ( MT ) and make it a bit SetVerboseLevel
    // To use multithread, instal again Geant4 with switch ON -DG4MULTITHREADED

        auto runManager = new RunManager();
        runManager->SetVerboseLevel(1);

#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive();
        visManager->SetVerboseLevel(1);    // Default, you can always override this using macro commands
    visManager->Initialize();
#endif

    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInitialization());

#ifdef G4UI_USE
    G4UIExecutive* ui = nullptr;
    if (interactive)
    {
        ui = new G4UIExecutive(argc, argv);
    }
#endif

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    // scoring manager will be needed later
    G4ScoringManager::GetScoringManager();               //sks

    for (auto macro : macros)
    {
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    }

#ifdef G4UI_USE
    if (interactive)
    {
        if(ui->IsGUI())
        {
            UImanager->ApplyCommand("/control/execute macros/ui.mac");
        }
        else
        {
            UImanager->ApplyCommand("/run/Initialize");
        }
        ui->SessionStart();
        delete ui;
    }
#endif

    delete runManager;

    // G4AnalysisManager* man = G4AnalysisManager::Instance();
    // man->CloseFile();

     std::cout<<" Application successfully ended.\nBye :-) :-)"<<std::endl;

    return 0;
}
