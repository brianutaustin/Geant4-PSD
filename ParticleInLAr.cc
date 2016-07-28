#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

int main(int argc,char** argv)
{
  // construct the default run manager
  G4RunManager * runManager = new G4RunManager;

  // set mandatory initialization classes
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new PhysicsList);

  // visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // set user action classes
	PrimaryGeneratorAction *primary = new PrimaryGeneratorAction(detector);
  runManager->SetUserAction(primary);

	RunAction* runaction = new RunAction(detector);
  runManager->SetUserAction(runaction);
  runManager->SetUserAction(new EventAction(runaction));
  runManager->SetUserAction(new SteppingAction(runaction, detector, primary));

  // get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();

  if(argc==1)
  // Define (G)UI terminal for interactive mode
  {
    G4UIsession * session = new G4UIterminal;
    UI->ApplyCommand("/control/execute init_vis.mac");
    session->SessionStart();
    delete session;
  }
  else
  // Batch mode
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);
  }

  // job termination
  delete visManager;
  delete runManager;

  return 0;
}
