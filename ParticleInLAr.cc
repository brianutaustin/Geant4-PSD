#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv) {

	G4RunManager *runManager = new G4RunManager;
	DetectorConstruction* detector = new DetectorConstruction;
	runManager->SetUserInitialization(detector);
	runManager->SetUserInitialization(new PhysicsList);
	runManager->SetUserAction(new PrimaryGeneratorAction(detector));

	PrimaryGeneratorAction *primary = new PrimaryGeneratorAction(detector);

	RunAction *RunAct = new RunAction(detector);
	runManager->SetUserAction(RunAct);
	runManager->SetUserAction(new EventAction(RunAct));
	runManager->SetUserAction(new SteppingAction(RunAct, detector, primary));

	#ifdef G4VIS_USE
	G4VisManager *visManager = new G4VisExecutive;
	visManager->Initialize();
	#endif

	runManager->Initialize();
	G4UImanager *UI = G4UImanager::GetUIpointer();

	#ifdef G4VIS_USE
	delete visManager;
	#endif
	delete runManager;

	return 0;
}
