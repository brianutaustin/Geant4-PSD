#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

class G4Step;
class RunAction;
class DetectorConstruction;
class PrimaryGeneratorAction;

class SteppingAction : public G4UserSteppingAction {
public: 
	SteppingAction(RunAction*, DetectorConstruction*, PrimaryGeneratorAction*);
	~SteppingAction();

public:
	void UserSteppingAction(const G4Step*);
	

private:
	RunAction *Run;
	DetectorConstruction *Detector;
	PrimaryGeneratorAction *Primary;
};

#endif
