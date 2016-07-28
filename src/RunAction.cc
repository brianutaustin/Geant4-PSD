#include "RunAction.hh"
#include "G4Run.hh"

// Specifi constructed detector in argument
RunAction::RunAction(DetectorConstruction *det) : Detector(det) {
	// Initialize total deposited dose
	doseTarget = 0;

	// Compute target mass
	G4double radius = 10*1e-6;
	G4double density = 1000;
	massTarget = (4/3)*M_PI*pow(radius, 3)*density;
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(G4Run *aRun) {
	// Display run number
	G4cout << "--> Run number: " << (aRun->GetRunID()) + 1 << " started. " << G4endl;
}

void RunAction::EndOfRunAction(G4Run*) {}
