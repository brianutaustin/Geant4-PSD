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

private:
	DetectorConstruction *Detector;
};

#endif
