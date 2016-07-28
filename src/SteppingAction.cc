#include "SteppingAction.hh"
//#include "RunAction.hh"
//#include "DetectorConstruction.hh"
//#include "PrimaryGeneratorAction.hh"

#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// RunAction, DetectorConstruction, PrimaryGeneratorAction objets in argument
SteppingAction::SteppingAction(RunAction* run, DetectorConstruction* det, PrimaryGeneratorAction* pri) : Run(run),
																																			Detector(det),
																																			Primary(pri) { 
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* s) {
	// Dose incrementation
	if (s->GetPreStepPoint()->GetPhysicalVolume()->GetName()  == "Target") { 
		G4double dose = (e_SI*(s->GetTotalEnergyDeposit()/eV))/(Run->GetMassTarget());
		Run->AddDoseTarget(dose);
	}
	
	// Beam spread after target
	if ((s->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "proton") && 
	    (s->GetPreStepPoint()->GetPhysicalVolume()->GetName()  == "Target") && 
		 (s->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "World")) {
		FILE* myFile;
		myFile = fopen("dose.txt", "a");
		fprintf(myFile, "%e %e %e ", (s->GetTrack()->GetPosition().x())/micrometer,
							 				  (s->GetTrack()->GetPosition().y())/micrometer,
											  (s->GetTrack()->GetPosition().z())/micrometer);
		fclose(myFile);
	}

	// Linear energy transfer computation

	if ((s->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Target") && 
		 (s->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "World") &&
		 (s->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "proton")) {
		FILE *myFile;
		myFile = fopen("dose.txt", "a");	
		fprintf(myFile, "%e ",(s->GetTotalEnergyDeposit()/keV)/(s->GetStepLength()/micrometer));	
		fclose(myFile);
	}
}
