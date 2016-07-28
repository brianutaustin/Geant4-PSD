#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

int main(int argc,char** argv)
{
  // Construct the default run manager
  G4RunManager *runManager = new G4RunManager;

  // Set mandatory initialization classes
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new PhysicsList);

	G4cout << "-----> " << argc << G4endl;
	for (G4int i = 0; i < argc; i++) G4cout << "-----> " << argv[i] << G4endl;

  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Set user action classes
	PrimaryGeneratorAction *primary = new PrimaryGeneratorAction(detector);
  runManager->SetUserAction(primary);

	RunAction* runaction = new RunAction(detector);
  runManager->SetUserAction(runaction);
  runManager->SetUserAction(new EventAction(runaction));
  runManager->SetUserAction(new SteppingAction(runaction, detector, primary));

  // Set the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
	G4UIExecutive* UI = new G4UIExecutive(argc, argv);
	G4UIsession *UIterminal = new G4UIterminal;

  if(argc == 1) {
    // Command lines
    UIterminal->SessionStart();
		UImanager->ApplyCommand("/control/execute vis.mac");
    delete UIterminal;
	} else {
    // Interactive (GUI)
    UI->SessionStart();
		UImanager->ApplyCommand("/control/execute vis.mac");
		delete UI;
  }

  // Job termination
  delete visManager;
  delete runManager;

  return 0;
}
