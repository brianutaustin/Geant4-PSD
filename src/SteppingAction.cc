#include "SteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// RunAction, DetectorConstruction, PrimaryGeneratorAction objets in argument
SteppingAction::SteppingAction(RunAction* run, DetectorConstruction* det, PrimaryGeneratorAction* pri) : Run(run), Detector(det), Primary(pri) {
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* s) {}
