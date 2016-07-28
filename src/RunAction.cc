#include "RunAction.hh"
#include "G4Run.hh"

// Specify constructed detector in argument
RunAction::RunAction(DetectorConstruction *det) : Detector(det) {
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(G4Run *aRun) {
	// Display run number
	G4cout << "--> Run number: " << (aRun->GetRunID()) + 1 << " started. " << G4endl;
}

void RunAction::EndOfRunAction(G4Run*) {}
