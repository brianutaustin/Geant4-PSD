#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "DetectorConstruction.hh"
#include "globals.hh"
#include <iostream>

class G4Run;

class RunAction : public G4UserRunAction {
public:
	RunAction(DetectorConstruction*);
	virtual ~RunAction();

public:
	virtual void BeginOfRunAction(G4Run*);
	virtual void EndOfRunAction(G4Run*);

	// Accessor methods for dose computation
	virtual void AddDoseTarget(G4double dose) { doseTarget += dose; }
	virtual void SetDoseTarget(G4double dose) { doseTarget = dose; }
	virtual G4double GetDoseTarget() { return doseTarget; }

	// Accessor methods for mass computation
	virtual void SetMassTarget(G4double mT) { massTarget = mT; }
	virtual G4double GetMassTarget() { return massTarget; }

private:
	DetectorConstruction *Detector;
	G4double doseTarget;
	G4double massTarget;
};

#endif
